#ifndef COLLISION_H
#define COLLISION_H

#include "Datastructure.h"
#include  <stdlib.h>
#include <iostream>

class Collision{
public:
	int emotion_id; // The ball happen to "collision" 
    int coordinate_id;
    float t_min;// The minimal time the "collision" happens in a timestep

	Collision():emotion_id(-1),coordinate_id(-1),t_min(0){};
	~Collision(){};
};

float sign_change_moment(const float &emotion,const float &mood,const float & mood_v, const float &timestep,const float emo_decay_factor);
int sign(const float &emotion,const float &mood);
bool check_collision(const float &emotion,const float &mood,const float & emotion_new, const float & mood_new);
void collision_detection(const float &timestep,const float& emo_decay_factor,const Mood & mood, zjz::Emotion* EmotionPool,Collision & cls);


#endif