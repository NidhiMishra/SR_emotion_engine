

#include "AffectiveSystem.h"

using namespace std;


/******************** Initial Value Part *************************/
// Normalize E_value and set E_V
void Affsys::set_emo_direction(void){ 
	for(int i=0;i!=22;++i){
		for(int j=0;j!=3;++j){
			EmotionPool[i].Dir[j]=E_value[i][j];
			EmotionPool[i].Direction[j]=E_value[i][j];
		}
		EmotionPool[i].Direction.normalize();	
	}
}
	



void Affsys::comput_mu(void)
{
	

	if(w_personality){
		point mp(parameter.Mp);

		//mp_max=abs(mp.max_component());

		mp.normalize();
		for(int i=0;i!=22;++i){
			parameter.mu[i]=((parameter.personality_upper_bound-parameter.personality_lower_bound)*(1+dot(EmotionPool[i].Direction,mp))/2+parameter.personality_lower_bound);
			parameter.decay[i]=(parameter.decay_lower_bound-parameter.decay_upper_bound)*(1+dot(EmotionPool[i].Direction,mp))/2+parameter.decay_upper_bound;
		}
	}
	else{
		for(int i=0;i!=22;++i){
			parameter.mu[i]=0.5;
		}
	}
	/*cout<<"Distress: "<<parameter.mu[3]<<endl;
	cout<<"Joy: "<<parameter.mu[12]<<endl;*/
	/*cout<<"Distress+mp: "<<parameter.mu[3]*parameter.Mp.length()<<endl;
	cout<<"Joy+mp: "<<parameter.mu[12]*parameter.Mp.length()<<endl;
	cout<<endl;*/
}

bool Affsys::input_parameter(const char * Filename)
{
    FILE   *pFile;

    pFile = fopen(Filename, "r");

    if(pFile != NULL)
    {
		
		fscanf(pFile,"temperament_p: %f\n", &parameter.Mp[0]);        
		fscanf(pFile,"temperament_a: %f\n", &parameter.Mp[1]);  
        fscanf(pFile,"temperament_d: %f\n", &parameter.Mp[2]);             
		fscanf(pFile,"attractive_factor_x: %f\n", &parameter.attractive_factor[0]);  	                  
        fscanf(pFile,"attractive_factor_y: %f\n", &parameter.attractive_factor[1]);
		fscanf(pFile,"attractive_factor_z: %f\n", &parameter.attractive_factor[2]);
		fscanf(pFile,"repulsive_factor_x: %f\n", &parameter.repulsive_factor[0]);  	                  
        fscanf(pFile,"repulsive_factor_y: %f\n", &parameter.repulsive_factor[1]);
		fscanf(pFile,"repulsive_factor_z: %f\n", &parameter.repulsive_factor[2]);
		fscanf(pFile,"emo_decay_factor: %f\n", &parameter.emo_decay_factor);
		fscanf(pFile,"mood_decay_factor: %f\n", &parameter.mood_decay_factor);
		fscanf(pFile,"mood_to_emo_factor: %f\n", &parameter.mood_to_emo_factor);
		fscanf(pFile,"intensity_lower_bound:%f\n", &parameter.intensity_lower_bound);
		fscanf(pFile,"personality_lower_bound: %f\n", &parameter.personality_lower_bound);
		fscanf(pFile,"personality_upper_bound: %f\n", &parameter.personality_upper_bound);
		fscanf(pFile,"decay_lower_bound: %f\n", &parameter.decay_lower_bound);
		fscanf(pFile,"decay_upper_bound: %f\n", &parameter.decay_upper_bound);
		fscanf(pFile,"decay_rate: %f\n", &parameter.decay_rate);
		fscanf(pFile,"timestep: %f\n", &parameter.timestep);
		fscanf(pFile,"p_c_factor: %f\n", &parameter.p_c_factor);
		fscanf(pFile,"m_c_factor: %f\n", &parameter.m_c_factor);
		fscanf(pFile,"r_c_factor: %f\n", &parameter.r_c_factor);


		return true;
	}

               
    else
    {
        cout<< "could not read file %s\n"<<endl;
        return false;
    }
}

bool Affsys::InputStimuli(const char * Filename)
{
    FILE   *pFile;
    int     rc;
	Stimuli S;

    

    pFile = fopen(Filename, "r");

    if(pFile != NULL)
    {
		while(!feof(pFile)){
      
			char str[20];
			string s;
            rc = fscanf(pFile, 
                                "%s %f %f\n", 
                                &str, 
								&S.Intensity, 
								&S.Time );        

                    if(rc == 3)
                    {
						s=str;
						S.Etype=str_num(s);
                        STIMULI.push_back(S);
                    }
			                  
        }
		
		return true;
	}

               
    else
    {
        cout<< "could not read file %s\n"<<endl;
        return false;
    }
}
// Initialize parameters and variables
void Affsys::Initialvalue(const char * Filename){
	input_parameter(Filename);
	set_emo_direction();
	comput_mu();

	/*point p(0.5,0.5,0.5);
	mood.Position=p;
	mood.Position_new=p;*/

}


/************functions for judging conditions **************/


// check if emotion's intensity is out of bound
void Affsys::ebound(void)  
{
	for(int i=0;i!=22;++i){
		if(EmotionPool[i].Intensity<parameter.intensity_lower_bound)
			EmotionPool[i].Intensity=0;
		else if(EmotionPool[i].Intensity>1)
			EmotionPool[i].Intensity=1;

		for(int j=0;j!=3;++j){
			if(EmotionPool[i].Position[j]*EmotionPool[i].Direction[j]<0)
				EmotionPool[i].Position[j]=0;
			if(EmotionPool[i].Position[j]>1)
				EmotionPool[i].Position[j]=1;
			else if(EmotionPool[i].Position[j]<-1)
				EmotionPool[i].Position[j]=-1;
	    }
	}
}

void Affsys::ebound_new(void){
		for(int i=0;i!=22;++i){
			if(EmotionPool[i].Intensity_new<parameter.intensity_lower_bound)
				EmotionPool[i].Intensity_new=0;

			else if(EmotionPool[i].Intensity_new>1)
				EmotionPool[i].Intensity_new=1;

			for(int j=0;j!=3;++j){
				if(EmotionPool[i].Position_new[j]*EmotionPool[i].Direction[j]<0)
				EmotionPool[i].Position_new[j]=0;
				if(EmotionPool[i].Position_new[j]>1)
					EmotionPool[i].Position_new[j]=1;
				else if(EmotionPool[i].Position_new[j]<-1)
					EmotionPool[i].Position_new[j]=-1;
	        }
	    }
}


// check if mood's position is out of bound
void Affsys::mbound(void)
{
	for(int i=0;i!=3;++i){
		if(mood.Position[i]>1)
			mood.Position[i]=1;
		else if(mood.Position[i]<-1)
			mood.Position[i]=-1;
	}
}

void Affsys::mbound_new(void){
	for(int i=0;i!=3;++i){
		if(mood.Position_new[i]>1)
			mood.Position_new[i]=1;
		else if(mood.Position_new[i]<-1)
			mood.Position_new[i]=-1;	
	}
}

bool Affsys::active_emo_check(){
	int n=0;
	for(int i=0;i!=22;++i){
		if(EmotionPool[i].Intensity>parameter.intensity_lower_bound)
			++n;
	}
	bool emo_check;
	if(n>0)
		emo_check=true;
	else
		emo_check=false;
		return emo_check;
}

/**************** Main Functions for Mood and Emotion Updating *************/

void Affsys::update_aff_context(void){
	if(w_personality)
		aff_context=(parameter.p_c_factor*parameter.Mp+parameter.m_c_factor*mood.Position)*(1.f/(parameter.p_c_factor+parameter.m_c_factor));
	else 
		aff_context=mood.Position;
//		        *(1/(1+parameter.m_c_factor+parameter.r_c_factor));
}

float Affsys::m_p_exertion(){
	point m(mood.Position);
	point mp(parameter.Mp);
	m.normalize();
	mp.normalize();
	return mp_max*((parameter.personality_upper_bound-parameter.personality_lower_bound)*(1+dot(m,mp))/2+parameter.personality_lower_bound);
}

float Affsys::adjust_m_factor(const point& m, const point& vel){
	float result=1000;
	for(int i=0;i!=3;++i){
		if(m[i]*vel[i]>0){
			if(m[i]>0){
			    if(result>1-m[i])
					result=1-m[i];
			}
			else{
				if(result>1+m[i])
					result=1+m[i];
			}
		}
	}
	return result;// if result=1000, then no adjusting needed
}

void Affsys::update_mood_vel(float &timestep){
	point vel_sum(0,0,0);
	//float mp_len=parameter.Mp.length();
	float mp_len=1;

	for(int j=0;j!=3;++j){
		for(int i=0;i!=22;++i){
			if(EmotionPool[i].Intensity>parameter.intensity_lower_bound){
				float pos_diff=EmotionPool[i].Position[j]-mood.Position[j];
				if(abs(pos_diff)>1e-4){
					if(pos_diff>0)
						pos_diff=1;
					else 
						pos_diff=-1;
					    // collision
					if(i==cls.emotion_id && j==cls.coordinate_id){
						//attraction
						if(sign(EmotionPool[i].Position_new[j],mood.Position_new[j])==1){
							EmotionPool[i].vel_contribution[j]=pos_diff*parameter.attractive_factor[j]*parameter.mu[i]*mp_len*abs(EmotionPool[i].Position[j]);
						}
						else{
							EmotionPool[i].vel_contribution[j]=-1*pos_diff*parameter.repulsive_factor[j]*parameter.mu[i]*mp_len*abs(EmotionPool[i].Position[j]);
						}
					}
					else{
						if(sign(EmotionPool[i].Position[j],mood.Position[j])==1){
							 EmotionPool[i].vel_contribution[j]=pos_diff*parameter.attractive_factor[j]*parameter.mu[i]*mp_len*abs(EmotionPool[i].Position[j]);
						}
						else{
							EmotionPool[i].vel_contribution[j]=-1*pos_diff*parameter.repulsive_factor[j]*parameter.mu[i]*mp_len*abs(EmotionPool[i].Position[j]);
						}
					}
				}
				else{
					EmotionPool[i].vel_contribution[j]*=exp(-parameter.emo_decay_factor*timestep);
				}
				vel_sum[j] += EmotionPool[i].vel_contribution[j];
			}
		}
	}
	mood.Velocity=vel_sum;
}

float Affsys::personality_to_mood(const point& personality, const point& mood){
	point p(personality);
	point m(mood);
	p.normalize();
	m.normalize();

	return (parameter.personality_upper_bound-parameter.personality_lower_bound)*(1+dot(m,p))/2+parameter.personality_lower_bound;
	
};



void Affsys::update_mood_pos(float &timestep){
	/*if(w_personality){
		mood.Position+=mood.Velocity*timestep*personality_to_mood(parameter.Mp,mood.Position);
		mbound();
	}
	else{
		mood.Position+=mood.Velocity*timestep;
		mbound();
	}*/
	mood.Position+=mood.Velocity*timestep;
	mbound();

	/*for(int i=0;i!=3;++i){ 
		if(mood.Velocity>0)
			mood.Position[i]+=(1-mood.Position[i])*mood.Velocity[i]*timestep;
		else
			mood.Position[i]+=(mood.Position[i]+1)*mood.Velocity[i]*timestep;
	}
	
	    mbound();*/
	//float a_m_f=adjust_m_factor(mood.Position,mood.Velocity);
	//if(a_m_f==1000)
	//	a_m_f=1;
 //
	//mood.Position+=a_m_f*mood.Velocity*timestep;
	//mbound();
}

void Affsys::update_mood_pos_new(float &timestep){
	point mood_pos;
	/*if(w_personality){
		mood_pos=mood.Position_new+mood.Velocity*timestep*personality_to_mood(parameter.Mp,mood.Position_new);
	}
	else{
		mood_pos=mood.Position_new+mood.Velocity*timestep;
	}*/
	mood_pos=mood.Position_new+mood.Velocity*timestep;
	// boundary check
	//if(!(abs(mood.Position.max_component())>=1&&abs(mood_pos.max_component())>=1))
		mood.Position_new=mood_pos;

	mbound_new();

	/*point mood_pos(0,0,0);
	for(int i=0;i!=3;++i){ 
		if(mood.Velocity>0)
			mood_pos[i]=mood.Position_new[i]+(1-mood.Position_new[i])*mood.Velocity[i]*timestep;
		else
			mood_pos[i]=mood.Position_new[i]+(mood.Position_new[i]+1)*mood.Velocity[i]*timestep;
	}*/
	
	// boundary check
	//if(!(abs(mood.Position.max_component())>=1&&abs(mood_pos.max_component())>=1))
		//mood.Position_new=mood_pos;

	//mbound_new();	
	
}




//void Affsys::update_emo_intensity(Emotion & emotion){
//	emotion.Intensity=abs(emotion.Position.max_component());
//}
//
//void Affsys::update_emo_new_intensity(Emotion & emotion){
//	emotion.Intensity_new=abs(emotion.Position_new.max_component());
//}
//
//void Affsys::update_emo_pos(Emotion& emotion){
//	emotion.Position=emotion.Direction*(emotion.Intensity/abs(emotion.Direction.max_component()));
//}
//void Affsys::update_emo_new_pos(Emotion& emotion){
//	emotion.Position_new=emotion.Direction*(emotion.Intensity_new/abs(emotion.Direction.max_component()));
//}
void Affsys::update_emo_pos(zjz::Emotion& emotion){
	emotion.Position =emotion.Intensity*emotion.Dir;
}
void Affsys::update_emo_new_pos(zjz::Emotion& emotion){
	emotion.Position_new =emotion.Intensity_new*emotion.Dir;
}




// the intensity of the emotion decay
void Affsys::decay_emotion(float &timestep){
	for(int i=0; i!=22;++i){
		EmotionPool[i].Intensity =exp(-parameter.emo_decay_factor*timestep)*EmotionPool[i].Intensity;   //decay of emotion
		update_emo_pos(EmotionPool[i]);
		ebound();// check
	}	
}

void Affsys::decay_emotion_new(float &timestep){
	for(int i=0; i!=22;++i){
		EmotionPool[i].Intensity_new =exp(-parameter.emo_decay_factor*timestep)*EmotionPool[i].Intensity_new;    //decay of emotion
		update_emo_new_pos(EmotionPool[i]);
		ebound_new();// check
	}	
}

void Affsys::memorydecay(){
	for(int i=0;i!=EmoMemory.size();++i){
		if(EmoMemory[i].MemoryStatus){
			EmoMemory[i].Intensity*=exp(-1*parameter.decay_rate*parameter.decay[EmoMemory[i].Etype]*parameter.timestep);
			EmoMemory[i].UpdateStatus();
		}
	}
};




void Affsys::stimuli_processing(void){
	    int type=STIMULI[0].Etype;
		float s_intensity=STIMULI[0].Intensity;
		
		
		//point dir=EmotionPool[type].Dir;
		//// adding the emotional context effect
		//if(dir[0]>0)
		//	s_intensity*=pow(float(2),aff_context[0]);
		//else
		//	s_intensity*=pow(float(2),-1*aff_context[0]);
		//EmotionPool[type].Intensity +=(1-EmotionPool[type].Intensity)*s_intensity;
		//EmotionPool[type].Intensity_new=EmotionPool[type].Intensity;

		EmotionPool[type].Intensity +=STIMULI[0].Intensity;
		EmotionPool[type].Intensity +=parameter.mood_to_emo_factor*dot(mood.Position,EmotionPool[type].Direction);
		EmotionPool[type].Intensity_new=EmotionPool[type].Intensity;

		

		// calculate the user_relationship
		/*for(int i=0;i!=3;++i){
			if(EmotionPool[type].Dir[i]>0)
				user_rel[i]+=(1-user_rel[i])*EmotionPool[type].Dir[i]*EmotionPool[type].Intensity;
			else
				user_rel[i]+=(user_rel[i]+1)*EmotionPool[type].Dir[i]*EmotionPool[type].Intensity;
		}*/
		

		update_emo_pos(EmotionPool[type]);
		update_emo_new_pos(EmotionPool[type]);

		//emo_list.push_back(EmotionPool[type].Position);
		//if(emo_list.size()<=max_event_num)
		//	total_emo+= emo_list.back();
		//else if(emo_list.size()>max_event_num){
		//	total_emo-= emo_list.front();
		//	total_emo+= emo_list.back();
		//	emo_list.pop_front();
		//}
		//user_rel=total_emo*(1.f/emo_list.size());

		//encoding emotional memory
		Memory mem;
		mem.Etype=type;
		if(EmotionPool[type].Position[0]>0)
			mem.type=1; //positive comment
		else
			mem.type=-1; //negative comment
		mem.InitIntensity=EmotionPool[type].Intensity;
		mem.Intensity=mem.InitIntensity;
		mem.UpdateStatus();

		EmoMemory.push_back(mem);

		STIMULI.erase(STIMULI.begin());
};
// update the intensity of emotion under stimuli.
void Affsys::update_emotion(void)  // when new stimulus comes in
{
	// diff is the accumulated time since the last stimuli comes in
    if(abs(STIMULI[0].Time-diff)<1e-4 || STIMULI[0].Time<1e-4)                                                         
	{	
		stimuli_processing();
         // Add Emotions happen in the same time
		while(STIMULI.size()>0&&(abs(STIMULI[0].Time-diff)<1e-4 || STIMULI[0].Time<1e-4)){                              
			stimuli_processing();
		}
	
		ebound();	
		ebound_new();

		diff=0;
		m_d=false; // to make the mood not decay anymore
		    // update location		    
	}
	else
		diff+=parameter.timestep;

}


// The main process
void Affsys::mood_dynamics_process(void){
	update_aff_context();
	if(STIMULI.size()>0||stimuli_input)
	   update_emotion();
	/*****for Glui use****/
	//mydraw(mood,EmotionPool);
	/******End for Glui***/

	update_mood_vel(parameter.timestep);
	if(active_emo_check()){
		// no collision detection
		/*if(w_emo_decay)
			decay_emotion(parameter.timestep);
		update_mood_pos_new(parameter.timestep);*/
		

		/******collision detection*/
		float nts=parameter.timestep;
		update_mood_pos_new(nts);
		if(w_emo_decay)
			decay_emotion_new(nts);
		collision_detection(nts,parameter.emo_decay_factor,mood,EmotionPool,cls);
	
		// do collision detection until there is no critical mement anymore.
			while(cls.t_min<=nts){
				nts-=cls.t_min;
				update_mood_pos(cls.t_min);
				if(w_emo_decay)
					decay_emotion(cls.t_min);
				update_mood_vel(cls.t_min);

				update_mood_pos_new(nts);
				if(w_emo_decay)
					decay_emotion_new(nts);
				collision_detection(nts,parameter.emo_decay_factor,mood,EmotionPool,cls);
			}

		mood.Position=mood.Position_new;
		for(int i=0;i!=22;++i){
			EmotionPool[i].Position=EmotionPool[i].Position_new;
			EmotionPool[i].Intensity=EmotionPool[i].Intensity_new;
		}
	}
	// mood decay
	else{
		point v_b=mood.Position-BaseMood;    //decay to the base mood
	// find the moment mood will decay
	if(!m_d&&v_b.norm()>1e-8){
		mood.Ini_D=v_b;
		m_d=true;
	}
	// mood decay
	
	if(m_d){
		mood.Ini_D=mood.Ini_D*exp(-parameter.mood_decay_factor*parameter.timestep);
		mood.Position=mood.Ini_D+BaseMood;
		mood.Position_new=mood.Position;
	}
	}

	comput_emo_state();
	comput_mood_state();
	comput_choosen_emo();
	if(chosen_emo==3)
		std::cin.get();

}


/********************************Functions for output******************************************************/

int Affsys::SelectEmotion(){
	float data[22];
	bool flag=false;
	for(int i=0;i!=22;++i){
		if(EmotionPool[i].Intensity>parameter.intensity_lower_bound){
			data[i]=dot(EmotionPool[i].Position,mood.Position);
			flag=true;
		}
		else
			data[i]=-4;
	}
	if(flag){
	    return maximum_func(22,data);	
	}
	else{
		return -1;
	}
}

void Affsys::input_emo(Stimuli & s)
{
	std::cout << "Inputting stimulus s: " << s.Etype << ", " << s.Intensity << ", at time " << s.Time << std::endl;
	STIMULI.push_back(s);
}

void Affsys::comput_emo_state(){
	for(int i=0;i!=16;++i)
		emo_state[i]=EmotionPool[switch_func(i)].Intensity;
}
void Affsys::comput_mood_state(){
	for(int i=0;i!=3;++i)
		mood_state[i]=mood.Position[i];
}
void Affsys::comput_choosen_emo(){
	int j=SelectEmotion();
	emo_id=j;

	if(j>-1)// there exists active emotions
	{
		for(int i=0;i!=16;++i){
			if(switch_func(i)==j){
				chosen_emo_state[i]=EmotionPool[j].Intensity;

				last_chosen_emo=chosen_emo;
				last_chosen_emo_intensity=chosen_emo_intensity;
				chosen_emo=i;
				chosen_emo_intensity=chosen_emo_state[i];
			}
			else
				chosen_emo_state[i]=0;
		
		}
	}
	else // no active emotion
	{
		    last_chosen_emo=chosen_emo;
			last_chosen_emo_intensity=chosen_emo_intensity;
			chosen_emo=-1;
			chosen_emo_intensity=0;
			for(int i=0;i!=16;++i)
			    chosen_emo_state[i]=0;
	}

	//int j=SelectEmotion();

	////if(j>-1)// there exists active emotions
	////{
	//for(int i=0;i!=16;++i){
	//	if(switch_func(i)==j){
	//		if(EmotionPool[i].Intensity>parameter.intensity_lower_bound){
	//			chosen_emo_state[i]=EmotionPool[j].Intensity;
	//			last_chosen_flag=chosen_flag;
	//			chosen_flag=0;
	//		}
	//		else{
	//			chosen_emo_state[i]=dot(EmotionPool[j].Direction,mood.Position);
	//			last_chosen_flag=chosen_flag;
	//			chosen_flag=1;
	//		}
	//	
	//		last_chosen_emo=chosen_emo;
	//		last_chosen_emo_intensity=chosen_emo_intensity;
	//		chosen_emo=i;
	//		chosen_emo_intensity=chosen_emo_state[i];
	//	}	
	//	else
	//		chosen_emo_state[i]=0;
	//	
	//}
	////}
	////else // no active emotion
	////{
	////	    last_chosen_emo=chosen_emo;
	////		last_chosen_emo_intensity=chosen_emo_intensity;
	////		chosen_emo=-1;
	////		chosen_emo_intensity=0;
	////		for(int i=0;i!=16;++i)
	////		    chosen_emo_state[i]=0;
	////}
}


bool Affsys::output_control(){
	if((last_chosen_emo==chosen_emo && last_chosen_emo_intensity>chosen_emo_intensity)||chosen_emo==-1)
		return false;
	else
		return true;
}












