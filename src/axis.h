#ifndef AXIS_H
#define AXIS_H

#include <GL\freeglut.h>
#include <GL\glui.h>
#include <GL\GLU.h>
#include "Datastructure.h"
#include <vector>
#include "BasicMath.h"

using namespace std;

void coordinate();
void mydraw(const Mood &mood,const zjz::Emotion *EmotionPool);
void draw_aff_context(const point& emo_context);
void draw_relationship(const point& relationship);
void alma_draw(const Mood &mood,const zjz::Emotion &emotion,const zjz::Emotion *EmotionPool);
void draw_vector(const point& temp, const float* color, const float& width);
extern float GREEN[3];
extern float RED[3];

#endif