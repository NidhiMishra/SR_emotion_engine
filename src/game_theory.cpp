#include "game_theory.h"

float GameTheory::agent_valence_func(const float& r_v,const float& m_v,const float& p_v,const float& utility){
	float result=para_a_v[0]*r_v+para_a_v[1]*m_v+para_a_v[2]*p_v;
	if(utility>0){
		result=(1+result)/2.f;
	}
	else if(utility<0){
		result=(1-result)/2.f;
	}
	return result;
}

float GameTheory::user_valence_func(const float& r_v,const float& m_v,const float& p_v){
	float result=para_u_v[0]*r_v+para_u_v[1]*m_v+para_u_v[2]*p_v;
	result=(1+result)/2.f;
	return result;
}

float GameTheory::dominance_func(const float& r_d,const float& m_d,const float& p_d){
	float result=para_d[0]*r_d+para_d[1]*m_d+para_d[2]*p_d;
	return result;
}

void GameTheory::update_utility(Choice& choice){
	float a_val=agent_valence_func(relationship[0],mood[0],personality[0],choice.agent_utility);
	float u_val=user_valence_func(relationship[0],mood[0],personality[0]);
		choice.utility=a_val*choice.agent_utility+u_val*choice.user_utility+theata;
}

void GameTheory::set_personality(point& p){
	personality=p;
};


int GameTheory::make_choice(const point& Mood){
	mood=Mood;
	update_utility(Go_Shopping);
	update_utility(Go_Swimming);
	float dom=dominance_func(relationship[2],mood[2],personality[2]);
	float delta=pow(k,1.5*dom)*Go_Shopping.utility-pow(k,-1.5*dom)*Go_Swimming.utility;

	if(delta>delta_utility_threshold && Go_Shopping.utility>utility_threshold)
		return 1;   //Go_Shopping.name;
	else if(delta<-1*delta_utility_threshold && Go_Swimming.utility>utility_threshold)
		return 2;     //Go_Swimming.name;
	else if(abs(delta)<delta_utility_threshold){
		if(Go_Shopping.utility>utility_threshold && Go_Swimming.utility>utility_threshold)
			return 3;   //"either";
		else if(Go_Shopping.utility>utility_threshold && Go_Swimming.utility<utility_threshold)
			return 1;  //Go_Shopping.name;
		else if(Go_Shopping.utility<utility_threshold && Go_Swimming.utility>utility_threshold)
			return 2;  //Go_Swimming.name;
	}
	else
		return 4;    //"stay at home";
}