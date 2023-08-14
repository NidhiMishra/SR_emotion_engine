#include "global_declaration.h"

int w_personality=1;
int w_fac_exp=1;
int w_emo_decay=1;
int w_stimuli=0;

/********************** Variable Declaration************/
// the Dominances of Joy and Distress have been changed.
float E_value[22][3]={0.5,0.3,-0.2,-0.51,-0.59,0.25,
-0.3,0.1,-0.4,-0.4,-0.2,-0.5,-0.64,0.60,-0.43,-0.5,-0.3,-0.7,0.3,
-0.3,-0.1,0.6,0.5,0.4,0.4,0.2,-0.3,0.4,0.2,0.2,-0.6,0.6,0.3,0.2,
0.2,-0.1,0.4,0.2,0.1,0.3,0.1,0.2,-0.4,-0.2,-0.5,
0.4,0.3,0.3,0.2,-0.3,0.4,-0.3,0.1,-0.6,-0.3,-0.1,0.4,-0.2,-0.3,
-0.2,0.3,-0.2,0.4,-0.3,0.1,-0.6};
/************************** Transfer functions*************************/
// Transfer the type of emotions into numbers.
int str_num(const string& s){
	if(s=="ADMIRATION")
		return 0;
	if(s=="ANGER")
		return 1;	
	if(s=="DISAPPOINTMENT")
		return 2;
	if(s=="DISTRESS")
		return 3;
	if(s=="FEAR")
		return 4;
	if(s=="FEARSCONFIRMED")
		return 5;
	if(s=="GLOATING")
		return 6;
	if(s=="GRATIFICATION")
		return 7;
	if(s=="GRATITUDE")
		return 8;
	if(s=="HAPPYFOR")
		return 9;
	if(s=="HATE")
		return 10;
	if(s=="HOPE")
		return 11;
	if(s=="JOY")
		return 12;
	if(s=="LOVE")
		return 13;
	if(s=="PITY")
		return 14;
	if(s=="PRIDE")
		return 15;
	if(s=="RELIEF")
		return 16;
	if(s=="REMORSE")
		return 17;
	if(s=="REPROACH")
		return 18;
	if(s=="RESENTMENT")
		return 19;
	if(s=="SATISFACTION")
		return 20;
	if(s=="SHAME")
		return 21;
}

int TransferSentence(const std::string& phrase){
	  if(phrase== "I like you so much" || phrase =="You look pretty today" || phrase =="You are so nice"||
	     phrase== "Your voice sounds charming" || phrase =="You are so interesting" || phrase =="You are my best friend" )
		  return 2;
	  else if(phrase == "I don't like you" || phrase =="You look ugly today" || 
	  phrase =="You are so mean" || phrase=="Your voice sounds sleepy"||phrase=="You are so boring"||phrase=="I don't like to talk with you")
		  return 1;
  }

std::string num_str(const int n){
	if(n==0)
		return "ADMIRATION";
	else if(n==1)
		return "ANGER";	
	else if(n==2)
		return "DISAPPOINTMENT";
	else if(n==3)
		return "DISTRESS";
	else if(n==4)
		return "FEAR";
	else if(n==5)
		return "FEARSCONFIRMED";
	else if(n==6)
		return "GLOATING";
	else if(n==7)
		return "GRATIFICATION";
	else if(n==8)
		return "GRATITUDE";
	else if(n==9)
		return "HAPPYFOR";
	else if(n==10)
		return "HATE";
	else if(n==11)
		return "HOPE";
	else if(n==12)
		return "JOY";
	else if(n==13)
		return "LOVE";
	else if(n==14)
		return "PITY";
	else if(n==15)
		return "PRIDE";
	else if(n==16)
		return "RELIEF";
	else if(n==17)
		return "REMORSE";
	else if(n==18)
		return "REPROACH";
	else if(n==19)
		return "RESENTMENT";
	else if(n==20)
		return "SATISFACTION";
	else if(n==21)
		return "SHAME";
	else
		return "";
}



int switch_func(int & idx){
	switch(idx){
	case 0: return 12;break;
	case 1: return 11;break;
	case 2: return 16;break;
	case 3: return 15;break;
	case 4: return 8;break;
	case 5: return 13;break;
	case 6: return 9;break;
	case 7: return 6;break;
	case 8: return 3;break;
	case 9: return 4;break;
	case 10: return 2;break;
	case 11: return 17;break;
	case 12: return 1;break;
	case 13: return 10;break;
	case 14: return 14;break;
	case 15: return 19;break;
	
		
	}
}

std::string num_to_name(const int& idx){
   	switch(idx){
	case -1: return "No_Active_Emotion";break;
	case 0: return "JOY";break;
	case 1: return "HOPE";break;
	case 2: return "RELIEF";break;
	case 3: return "PRIDE";break;
	case 4: return "GRATITUDE";break;
	case 5: return "LOVE";break;
	case 6: return "HAPPYFOR";break;
	case 7: return "GLOATING";break;
	case 8: return "DISTRESS";break;
	case 9: return "FEAR";break;
	case 10: return "DISAPPOINT";break;
	case 11: return "REMORSE";break;
	case 12: return "ANGER";break;
	case 13: return "HATE";break;
	case 14: return "SORRYFOR";break;
	case 15: return "RESENTMENT";break;
	}
}