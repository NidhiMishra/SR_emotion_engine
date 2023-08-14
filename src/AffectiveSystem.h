#ifndef AFFECTIVESYSTEM_H
#define AFFECTIVESYSTEM_H

#include "global_declaration.h"
#include "Datastructure.h"
#include "Probability.h"
#include "axis.h"
#include "collision_detection.h"
#include <list>
using namespace std;

class Affsys{
public:

    Affsys(){
	   chosen_emo=-1;
	   chosen_emo_intensity=0;
	   last_chosen_emo=-1;
	   last_chosen_emo_intensity=0;
		for(int i=0;i!=16;++i){
			emo_state[i]=0;
			chosen_emo_state[i]=0;}
		for(int i=0;i!=3;++i){
	        mood_state[i]=0;
			user_rel[i]=0;
			total_emo[i]=0;
		}
		m_d=false;// decide whether mood decays at the very moment
        diff=0;// Calculate the time since the last stimulus comes in.
		stimuli_input=false;
		user_dialogue_choice=0;
		aff_access=false;

		chosen_flag=-1;
		last_chosen_flag=-1;
		max_event_num=10;
	};
	
	void Initialvalue(const char * Filename);
    void mood_dynamics_process(void);
	bool output_control();
	bool stimuli_input;

   // basic varibles
	zjz::Emotion EmotionPool[22];
	Mood mood;
	vector<Stimuli> STIMULI;
	vector<Memory> EmoMemory;
	Parameter parameter;
	point BaseMood;
	Collision cls;
	point user_rel;
	point aff_context;

	int emo_id;

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

	void memorydecay();
private:
	float m_p_exertion();
	int max_event_num;
	point total_emo;
	list <point> emo_list;
	// variables sent to other modules
	int last_chosen_emo;
	float last_chosen_emo_intensity;
	int chosen_flag; // validate choose mood or emotion
	int last_chosen_flag; // validate choose mood or emotion
	float mp_max;// the maximum component of personality

	// conditional varibles
    bool m_d;// decide whether mood decays at the very moment
    float diff;// Calculate the time since the last stimulus comes in.

	// input processing and initialization
	bool input_parameter(const char * Filename);
	void set_emo_direction(void);
	void comput_mu();

	// conditional check
	
	void ebound(void);
	void ebound_new(void);
	void mbound(void);
	void mbound_new(void);
	void update_aff_context(void);
	void stimuli_processing(void);
	// main process of affective update
	void update_mood_vel(float &timestep);
	void update_mood_pos(float &timestep);
	void update_mood_pos_new(float &timestep);
	void decay_emotion(float &timestep);
	void decay_emotion_new(float &timestep);
	void update_emotion(void);

	void update_emo_intensity(zjz::Emotion &);
	void update_emo_new_intensity(zjz::Emotion &);
    void update_emo_pos(zjz::Emotion&);
	void update_emo_new_pos(zjz::Emotion&);
	
	// choose and send selected emotion and mood
	void comput_emo_state();
	void comput_mood_state();
	void comput_choosen_emo();  
	int SelectEmotion(void);
	float adjust_m_factor(const point& m, const point& vel);
	
	float personality_to_mood(const point& personality, const point& mood);
	
};


#endif