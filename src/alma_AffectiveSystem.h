#ifndef ALMA_H
#define ALMA_H

#include "global_declaration.h"
#include "Datastructure.h"
#include "Probability.h"
#include<GL\freeglut.h>
#include "axis.h"
#include "collision_detection.h"
#include "dialogue.h"

using namespace std;

class alma_Affsys{
public:

    alma_Affsys(){
	   chosen_emo=-1;
	   chosen_emo_intensity=0;
	   last_chosen_emo=-1;
	   last_chosen_emo_intensity=0;
		for(int i=0;i!=16;++i){
			emo_state[i]=0;
			chosen_emo_state[i]=0;}
		for(int i=0;i!=3;++i)
	        mood_state[i]=0;
		m_d=false;// decide whether mood decays at the very moment
        diff=0;// Calculate the time since the last stimulus comes in.
		stimuli_input=false;
		user_dialogue_choice=0;
		aff_access=false;
	};
	
	void Initialvalue(const char * Filename);
    void mood_dynamics_process(void);
	bool output_control();
	bool stimuli_input;

   // basic varibles
	Emotion EmotionPool[22];
	Emotion Virtual_Emo_Center;
	Mood mood;
	vector<Stimuli> STIMULI;
	Parameter parameter;
	point BaseMood;
	Collision cls;
	Dialogue vh_dialogue;


    // variables sent to other modules
	float emo_state[16];
	float mood_state[3];
	float chosen_emo_state[16];
	int chosen_emo;
	float chosen_emo_intensity;
    int user_dialogue_choice;
	bool InputStimuli(const char * );

	void input_emo(Stimuli & e);
	bool active_emo_check();
	bool aff_access;
private:
	
	// variables sent to other module

	int last_chosen_emo;
	float last_chosen_emo_intensity;
	

	// conditional varibles
    bool m_d;// decide whether mood decays at the very moment
    float diff;// Calculate the time since the last stimulus comes in.

	// input processing and initialization
	bool input_parameter(const char * Filename);
	void set_emo_direction(void);

	// conditional check
	
	void ebound(void);
	void mbound(void);
	void vec_bound(void);
	int sign(const Emotion &E,const Mood &M);

	// main process of affective update
	void update_mood_vel(float &timestep);
	void update_mood_pos(float &timestep);
	void decay_emotion(float &timestep);
	bool update_emotion(void);
	void update_vec(void);


	// choose and send selected emotion and mood
	void comput_emo_state();
	void comput_mood_state();
	void comput_choosen_emo();  
	int SelectEmotion(void);
	
};


#endif