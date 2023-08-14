#ifndef MIRALAB_H
#define MIRALAB_H

#include "global_declaration.h"
#include "Datastructure.h"
#include "Probability.h"
#include<GL\glut.h>
#include "axis.h"
#include "dialogue.h"

using namespace std;


class miralab_Affsys{
public:

    miralab_Affsys(){
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
	bool active_emo_check();

   // basic varibles
	Emotion EmotionPool[22];
	Mood mood;
	vector<Stimuli> STIMULI;
	Parameter parameter;
	point BaseMood;
	Dialogue vh_dialogue;
	bool InputStimuli(const char * );
    // variables sent to other modules
	float emo_state[16];
	float mood_state[3];
	float chosen_emo_state[16];
	int chosen_emo;
	float chosen_emo_intensity;
    int user_dialogue_choice;
	bool aff_access;
private:

	// variables sent to other modules
	int last_chosen_emo;
	float last_chosen_emo_intensity;
	

	// conditional varibles
	
    bool m_d;// decide whether mood decays at the very moment
    float diff;// Calculate the time since the last stimulus comes in.

	// input processing and initialization
	bool input_parameter(const char * Filename);

	// conditional check
	void ebound(void);
	void mbound(void);


	// main process of affective update
	void update_mood_pos(float &timestep);
	void decay_emotion(float &timestep);
	bool update_emotion(void);

	// choose and send selected emotion and mood
	void comput_emo_state();
	void comput_mood_state();
	void comput_choosen_emo();  
	int SelectEmotion(void);
	void set_emo_direction(void);

	
};



//// transfer string to emotions
//int str_num(const string& s);
//int switch_func(int& idx);
//std::string num_to_name(const int& idx);
//
//// output stream
//extern ofstream out;

#endif