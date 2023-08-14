

#include "alma_AffectiveSystem.h"

using namespace std;


/******************** Initial Value Part *************************/
// Normalize E_value and set E_V
void alma_Affsys::set_emo_direction(void){ 
	for(int i=0;i!=22;++i){
		for(int j=0;j!=3;++j){
			EmotionPool[i].Direction[j]=E_value[i][j];
			EmotionPool[i].Position[j]=E_value[i][j];
		}
		EmotionPool[i].Direction.normalize();	
	}
}
	



bool alma_Affsys::input_parameter(const char * Filename)
{
    FILE   *pFile;

    pFile = fopen(Filename, "r");

    if(pFile != NULL)
    {
		
		fscanf(pFile,"temperament_p: %f\n", &parameter.Mp[0]);        
		fscanf(pFile,"temperament_a: %f\n", &parameter.Mp[1]);  
        fscanf(pFile,"temperament_d: %f\n", &parameter.Mp[2]);             
		fscanf(pFile,"attractive_factor: %f\n", &parameter.alma_attractive_factor);  	                  
		fscanf(pFile,"repulsive_factor: %f\n", &parameter.alma_repulsive_factor);  	                  
		fscanf(pFile,"emo_decay_factor: %f\n", &parameter.emo_decay_factor);
		fscanf(pFile,"mood_decay_factor: %f\n", &parameter.mood_decay_factor);
		fscanf(pFile,"intensity_lower_bound:%f\n", &parameter.intensity_lower_bound);
		fscanf(pFile,"timestep: %f\n", &parameter.timestep);

		return true;
	}

               
    else
    {
        cout<< "could not read file %s\n"<<endl;
        return false;
    }
}

bool alma_Affsys::InputStimuli(const char * Filename)
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
void alma_Affsys::Initialvalue(const char * Filename){
	input_parameter(Filename);
	set_emo_direction();
	if(w_personality)
		BaseMood=parameter.Mp;
	mood.Position=BaseMood;

	//point p(0.5,0.5,0.5);
	//mood.Position=p;

}


/************functions for judging conditions **************/


// check if emotion's intensity is out of bound
void alma_Affsys::ebound(void)  
{
	for(int i=0;i!=22;++i){
		if(EmotionPool[i].Intensity<parameter.intensity_lower_bound)
			EmotionPool[i].Intensity=0;
		else if(EmotionPool[i].Intensity>1)
			EmotionPool[i].Intensity=1;
	}
}




// check if mood's position is out of bound
void alma_Affsys::mbound(void)
{
	for(int i=0;i!=3;++i){
		if(mood.Position[i]>1)
			mood.Position[i]=1;
		else if(mood.Position[i]<-1)
			mood.Position[i]=-1;
	}
}

void alma_Affsys::vec_bound(){
	if(Virtual_Emo_Center.Intensity<parameter.intensity_lower_bound)
			Virtual_Emo_Center.Intensity=0;
	else if(Virtual_Emo_Center.Intensity>1)
			Virtual_Emo_Center.Intensity=1;
}

bool alma_Affsys::active_emo_check(){
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

void alma_Affsys::update_vec(){
	if(active_emo_check()){
		int num_active_emo=0;
		point vec_pos;
		float vec_i=0;
		for(int i=0;i!=22;++i){
			if(EmotionPool[i].Intensity>parameter.intensity_lower_bound){
				vec_pos += EmotionPool[i].Position;
				vec_i += EmotionPool[i].Intensity;
				++num_active_emo;
			}
		}
	
		Virtual_Emo_Center.Position=(1.f/num_active_emo)*vec_pos;
		Virtual_Emo_Center.Intensity=vec_i/num_active_emo;

		//vec_bound();
	}
	else{
		point p(0,0,0);
		Virtual_Emo_Center.Position=p;
		Virtual_Emo_Center.Intensity=0;

	}
	
	//cout<<"vec_i: "<<Virtual_Emo_Center.Intensity<<endl;
}



int  alma_Affsys::sign(const Emotion &E,const Mood &M)  
{
	point e,m;
	// deal with the current mood and emotion   
    e=E.Position;
	m=M.Position;
	
	// Judge by whether the mood and the emotion are in the same octant
		
	if(e[0]*m[0]>=0 && e[1]*m[1]>=0 && e[2]*m[2]>=0 && (m.norm()>=dot(m,e)))
		return -1;
	else 
		return 1;
}

void alma_Affsys::update_mood_vel(float &timestep){
	point vel_sum(0,0,0);
	if(Virtual_Emo_Center.Intensity>parameter.intensity_lower_bound){
		point pos_diff=Virtual_Emo_Center.Position-mood.Position;
		if(pos_diff.norm()>1e-4){
			pos_diff.normalize();
			if(sign(Virtual_Emo_Center,mood)==1)
				Virtual_Emo_Center.vel_contribution=(parameter.alma_attractive_factor*Virtual_Emo_Center.Intensity)*pos_diff;
			else
				Virtual_Emo_Center.vel_contribution=(-1*parameter.alma_repulsive_factor*Virtual_Emo_Center.Intensity)*pos_diff;
	
	    }
		else
			Virtual_Emo_Center.vel_contribution = Virtual_Emo_Center.vel_contribution * exp(-parameter.emo_decay_factor*timestep);
		vel_sum=Virtual_Emo_Center.vel_contribution;
    }
				
	mood.Velocity=vel_sum;
	//cout<<"vec_i: "<<Virtual_Emo_Center.Intensity<<endl;
	//cout<<"alma_mood_vel: "<<mood.Velocity[0]<<" "<<mood.Velocity[1]<<" "<<mood.Velocity[2]<<endl;
}

void alma_Affsys::update_mood_pos(float &timestep){
 
	    mood.Position+=mood.Velocity*timestep;
	    mbound();
}



// the intensity of the emotion decay
void alma_Affsys::decay_emotion(float &timestep){
	for(int i=0; i!=22;++i){
		EmotionPool[i].Intensity =exp(-parameter.emo_decay_factor*timestep)*EmotionPool[i].Intensity;   //decay of emotion
		
		ebound();// check
	}	
}



// update the intensity of emotion under stimuli.
bool alma_Affsys::update_emotion(void)  // when new stimulus comes in
{
	// diff is the accumulated time since the last stimuli comes in
    if(abs(diff-STIMULI[0].Time)<1e-4 || STIMULI[0].Time<1e-4)                                                         
	{	
		int type=STIMULI[0].Etype;

		EmotionPool[type].Intensity +=STIMULI[0].Intensity;
	
		STIMULI.erase(STIMULI.begin());
         // Add Emotions happen in the same time
		while(STIMULI.size()>0&& (abs(diff-STIMULI[0].Time)<1e-4 || STIMULI[0].Time<1e-4)){                              
			int type=STIMULI[0].Etype;
			EmotionPool[type].Intensity +=STIMULI[0].Intensity;

			STIMULI.erase(STIMULI.begin());
		}
	
		ebound();	

		diff=0;
		m_d=false; // to make the mood not decay anymore
		return true;	    
	}
	else{
		diff+=parameter.timestep;
		return false;
	}
}



// The main process
void alma_Affsys::mood_dynamics_process(void){
	if((STIMULI.size()>0 || stimuli_input) && update_emotion()){
	   update_vec();
	}
	
	/*****for Glui use****/
	//alma_draw(mood,Virtual_Emo_Center);
	/******End for Glui***/   

	if(active_emo_check()){
		update_mood_vel(parameter.timestep);
		update_mood_pos(parameter.timestep);
		if(w_emo_decay)
			decay_emotion(parameter.timestep);
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
		}
	}
	
	update_vec();

	comput_emo_state();
	comput_mood_state();
	comput_choosen_emo();

	if(stimuli_input){
		vh_dialogue.process(mood,user_dialogue_choice);
		out<<vh_dialogue.auto_reply<<endl;
	}   
}


/********************************Functions for output******************************************************/

int alma_Affsys::SelectEmotion(){
	float data[22];
	for(int i=0;i!=22;++i){
		if(EmotionPool[i].Intensity>parameter.intensity_lower_bound)
		    data[i]=EmotionPool[i].Intensity;
		else
			data[i]=-4;
	}
	
	return maximum_func(22,data);
}

void alma_Affsys::input_emo(Stimuli & s)
{
	std::cout << "Inputting stimulus s: " << s.Etype << ", " << s.Intensity << ", at time " << s.Time << std::endl;
	STIMULI.push_back(s);
}

void alma_Affsys::comput_emo_state(){
	for(int i=0;i!=16;++i)
		emo_state[i]=EmotionPool[switch_func(i)].Intensity;
}
void alma_Affsys::comput_mood_state(){
	for(int i=0;i!=3;++i)
		mood_state[i]=mood.Position[i];
}
void alma_Affsys::comput_choosen_emo(){
	int j=SelectEmotion();

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

		
}


bool alma_Affsys::output_control(){
	if((last_chosen_emo==chosen_emo && last_chosen_emo_intensity>chosen_emo_intensity)||chosen_emo==-1)
		return false;
	else
		return true;
}












