#ifndef GAME_THEORY_H
#define GAME_THEORY_H

#include "global_declaration.h"
#include "Datastructure.h"
#include <math.h>

class Choice{
public:
	Choice(){};
	char* name;
	float agent_utility;
	float user_utility;
	float utility;

};

class GameTheory{
public:
	GameTheory(){
		relationship[0]=-0.2;
		relationship[2]=0;    

		Go_Shopping.name="shopping";
		Go_Shopping.agent_utility=1.1;
		Go_Shopping.user_utility=-1;

		Go_Swimming.name="swimming";
		Go_Swimming.agent_utility=-1.1;
		Go_Swimming.user_utility=1;
		

		para_a_v[0]=0.3;
		para_a_v[1]=0.5;
		para_a_v[2]=0.2;

		para_u_v[0]=0.5;
		para_u_v[1]=0.3;
		para_u_v[2]=0.2;
		
		para_d[0]=0.3;
		para_d[1]=0.5;
		para_d[2]=0.2;

		k=10;
		utility_threshold=0.05 ;
	    delta_utility_threshold=0.1;
		theata=0.05;
	};
	
	point mood;
	point personality;
	point relationship;

	Choice Go_Shopping;
	Choice Go_Swimming;

	point para_a_v;
	point para_u_v;
	point para_d;

    int make_choice(const point& Mood); // return the name of the choice
	
	int k;
	float utility_threshold;
	float delta_utility_threshold;
	void set_personality(point& p);
	float theata;

private:
	float agent_valence_func(const float& r_v,const float& m_v,const float& p_v,const float& utility);
	float user_valence_func(const float& r_v,const float& m_v,const float& p_v);
	float dominance_func(const float& r_d,const float& m_d,const float& p_d);
	void  update_utility(Choice& choice);
};

#endif