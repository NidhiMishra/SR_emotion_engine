#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <vector>
#include <string>
#include "BasicMath.h"

namespace zjz{
class Emotion{
public:	
	// initializing
	Emotion(){
		Intensity=0;
		Intensity_new=0;
	}

	point Position; 
	point Position_new;
	point Direction;
	point Dir;
	float Intensity;
	float Intensity_new;
	point vel_contribution;

	Emotion& operator =(const Emotion &);
};
}

class Mood{
public:
	Mood(){}

    point Position;
	point Velocity;
	point Position_new;// the estimated position used in the collision detection
	point Ini_D; // the direction to decay

	Mood & operator =(const Mood &);

};



class Stimuli{
public:
	Stimuli(){
	Etype=-1;
	Intensity=0.f;
	Time=0.f;
	}

	int Etype;  // Emotion Type
	float Intensity;
	float Time;
};


class Memory{
public:
	Memory(){
	type=0;
	Etype=-1;
	InitIntensity=0.f;
	Intensity=0.f;
	MemoryStatus=false;
	threshold=0.1;
	}

	int type;  // Emotion Type
	int Etype;
	float InitIntensity;
	float Intensity;
	bool MemoryStatus;
	float threshold;

	void UpdateStatus();
};

//class EmoMemory{
//public:
//	EmoMemory(){}
//	std::vector<Memory> MemRec;
//	float DefultDecayRate;
//};

class Parameter{
public:
	Parameter(){
		emo_decay_factor=0;
		mood_decay_factor=0;
		mood_to_emo_factor=0;
		intensity_lower_bound=0;
		timestep=0;
		m_c_factor=0;
		r_c_factor=0;
		for(int i=0;i!=22;++i){
			mu[i]=0;
			decay[i]=0;
		}
	}
	point Mp;
	point attractive_factor;
	point repulsive_factor;
	float alma_attractive_factor;
	float alma_repulsive_factor;
	float emo_decay_factor;
	float mood_decay_factor;
	float mood_to_emo_factor;
    float intensity_lower_bound;
    float timestep;
	float mu[22];
	float decay[22];
	float personality_upper_bound;
	float personality_lower_bound;
	float decay_upper_bound;
	float decay_lower_bound;
	float decay_rate;
	float p_c_factor;
	float m_c_factor;
	float r_c_factor;
};


#endif