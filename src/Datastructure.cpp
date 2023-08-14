#include "Datastructure.h"

zjz::Emotion & zjz::Emotion::operator =(const Emotion & rhs){
	Position=rhs.Position;
	Position_new=rhs.Position_new;
	Direction=rhs.Direction;
	Intensity=rhs.Intensity;
	Intensity_new=rhs.Intensity_new;
	vel_contribution=rhs.vel_contribution;
	return *this;
}

Mood & Mood::operator =(const Mood &rhs){
	Position=rhs.Position;
	Velocity=rhs.Velocity;
	Position_new=rhs.Position_new;
	Ini_D=rhs.Ini_D;
	return *this;
}

void Memory::UpdateStatus(){
	if(Intensity>threshold)
		MemoryStatus=true;
	else
		MemoryStatus=false;
};