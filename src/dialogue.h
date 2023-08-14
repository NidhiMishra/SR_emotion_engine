#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "global_declaration.h"
#include "Datastructure.h"
#include <string.h>

class Dialogue{
public:
	Dialogue(){
		r_num=0;
		response_animation=3;
	};
	void process(const Mood&,int&);
	char auto_reply [100]; 
	int response_animation;
private:
	int r_num;
};

#endif DIALOGUE_H