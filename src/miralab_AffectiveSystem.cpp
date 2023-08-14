#include "miralab_AffectiveSystem.h"

using namespace std;



/******************** Initial Value Part *************************/
// Normalize E_value and set E_V

// Normalize E_value and set E_V
void miralab_Affsys::set_emo_direction(void){ 
	for(int i=0;i!=22;++i){
		for(int j=0;j!=3;++j){
			EmotionPool[i].Direction[j]=E_value[i][j];
			EmotionPool[i].Position[j]=E_value[i][j];
		}
		EmotionPool[i].Direction.normalize();	
	}
}	


bool miralab_Affsys::input_parameter(const char * Filename)
{
    FILE   *pFile;

    pFile = fopen(Filename, "r");

    if(pFile != NULL)
    {
		
		fscanf(pFile,"temperament_p: %f\n", &parameter.Mp[0]);        
		fscanf(pFile,"temperament_a: %f\n", &parameter.Mp[1]);  
        fscanf(pFile,"temperament_d: %f\n", &parameter.Mp[2]);             
		fscanf(pFile,"emo_decay_factor: %f\n", &parameter.emo_decay_factor);
		fscanf(pFile,"mood_decay_factor: %f\n", &parameter.mood_decay_factor);
		fscanf(pFile,"mood_to_emo_factor: %f\n", &parameter.mood_to_emo_factor);
		fscanf(pFile,"intensity_lower_bound:%f\n", &parameter.intensity_lower_bound);
		fscanf(pFile,"timestep: %f\n", &parameter.timestep);

		return true;
	}

               
    else
    {
        cout<< "The miralab_parameter file can not be read!\n"<<endl;
        return false;
    }
}

bool miralab_Affsys::InputStimuli(const char * Filename)
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
void miralab_Affsys::Initialvalue(const char * Filename){
	input_parameter(Filename);
	set_emo_direction();
	if(w_personality)
		BaseMood=parameter.Mp;
	mood.Position=BaseMood;
}


/************functions for judging conditions **************/


// check if emotion's intensity is out of bound
void miralab_Affsys::ebound(void)  
{
	for(int i=0;i!=22;++i){
		if(EmotionPool[i].Intensity<parameter.intensity_lower_bound)
			EmotionPool[i].Intensity=0;
		else if(EmotionPool[i].Intensity>1)
			EmotionPool[i].Intensity=1;
	}
}




// check if mood's position is out of bound
void miralab_Affsys::mbound(void)
{
	for(int i=0;i!=3;++i){
		if(mood.Position[i]>1)
			mood.Position[i]=1;
		else if(mood.Position[i]<-1)
			mood.Position[i]=-1;
	}
}

bool miralab_Affsys::active_emo_check(){
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


void miralab_Affsys::update_mood_pos(float &timestep){
	    
	    for(int j=0;j!=3;++j)
			for(int i=0;i!=22;++i)
				mood.Position[j]+=EmotionPool[i].Intensity*E_value[i][j];
		// boundary check
	    mbound();
}




// the intensity of the emotion decay
void miralab_Affsys::decay_emotion(float &timestep){
	for(int i=0; i!=22;++i){
		EmotionPool[i].Intensity = exp(-1*parameter.emo_decay_factor*timestep)*EmotionPool[i].Intensity;   //decay of emotion
		ebound();// check
	}	
}



// update the intensity of emotion under stimuli.
bool miralab_Affsys::update_emotion(void)  // when new stimulus comes in
{
	// diff is the accumulated time since the last stimuli comes in
    if(abs(diff-STIMULI[0].Time)<1e-4 || STIMULI[0].Time<1e-4)                                                         
	{	
		int type=STIMULI[0].Etype;
		point element_v(1,1,1);
		point e_v;
		for(int j=0;j!=3;++j)
			e_v[j]=E_value[type][j];

		// mood_to_emo_factor=1

		EmotionPool[type].Intensity +=STIMULI[0].Intensity;
		EmotionPool[type].Intensity +=parameter.mood_to_emo_factor*dot(mood.Position,e_v)/dot(element_v,e_v);
		

		STIMULI.erase(STIMULI.begin());
         // Add Emotions happen in the same time
		while(STIMULI.size()>0&&(abs(diff-STIMULI[0].Time)<1e-4 || STIMULI[0].Time<1e-4)){                              
			int type=STIMULI[0].Etype;
			for(int j=0;j!=3;++j)
				e_v[j]=E_value[type][j];

		// mood_to_emo_factor=1

		    EmotionPool[type].Intensity +=STIMULI[0].Intensity;
			EmotionPool[type].Intensity +=parameter.mood_to_emo_factor*dot(mood.Position,e_v)/dot(element_v,e_v);

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
void miralab_Affsys::mood_dynamics_process(void){
	if((STIMULI.size()>0 ||stimuli_input) && update_emotion()){
		 update_mood_pos(parameter.timestep);

     //decay to the base mood
		 point v_b=mood.Position-BaseMood;  
	    if(v_b.norm()>1e-4)
		   mood.Ini_D=v_b;
	}
	    

	else{
		if(active_emo_check()&& w_emo_decay)
			decay_emotion(parameter.timestep);
		mood.Ini_D=mood.Ini_D*exp(-parameter.mood_decay_factor*parameter.timestep);
		mood.Position=mood.Ini_D+BaseMood;
		mood.Position_new=mood.Position;
	}
	/*****for Glui use****/
	//mydraw(mood,EmotionPool);
	/******End for Glui***/

	comput_emo_state();
	comput_mood_state();
	comput_choosen_emo();

	if(stimuli_input){
		vh_dialogue.process(mood,user_dialogue_choice);
	    out<<vh_dialogue.auto_reply<<endl;
	}
}


/********************************Functions for output******************************************************/

int miralab_Affsys::SelectEmotion(){
	float data[22];
	for(int i=0;i!=22;++i){
		if(EmotionPool[i].Intensity>parameter.intensity_lower_bound)
		    data[i]=EmotionPool[i].Intensity;
		else
			data[i]=-4;
	}
	
	return maximum_func(22,data);	
}

void miralab_Affsys::comput_emo_state(){
	for(int i=0;i!=16;++i)
		emo_state[i]=EmotionPool[switch_func(i)].Intensity;
}
void miralab_Affsys::comput_mood_state(){
	for(int i=0;i!=3;++i)
		mood_state[i]=mood.Position[i];
}
void miralab_Affsys::comput_choosen_emo(){
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


bool miralab_Affsys::output_control(){
	if((last_chosen_emo==chosen_emo && last_chosen_emo_intensity>chosen_emo_intensity)||chosen_emo==-1)
		return false;
	else
		return true;
}




