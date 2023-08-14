#include "collision_detection.h"



float sign_change_moment(const float &emotion,const float &mood,const float & mood_v, const float &timestep,const float emo_decay_factor){
	float A,B,C,D,x1,x2,x3,y1,y2;
	A=0.5*emotion*pow(emo_decay_factor,2);
	B=-(mood_v+emotion*emo_decay_factor);
	C=emotion-mood;
	D=sqrt(B*B-4*A*C);
	x1=(-B+D)/(2*A);
	x2=(-B-D)/(2*A);
	x3=-C/B;
	y1=emotion*exp(-emo_decay_factor*x2)-(mood+mood_v*x2);
	y2=emotion*exp(-emo_decay_factor*x3)-(mood+mood_v*x3);
	if(x1>0&&x1<timestep)
		return x1;
	if(x2>0&&x2<timestep)
		return x2;
	
}

int sign(const float &emotion,const float &mood) 
{
	if(emotion*mood>0 && abs(mood)>abs(emotion))
		return -1;
	else
		return 1;
}

bool check_collision(const float &emotion,const float &mood,const float & emotion_new, const float & mood_new){
	
	if(sign(emotion,mood)!=sign(emotion_new, mood_new))
		return true;
	else
	    return false;
}

void collision_detection(const float &timestep,const float& emo_decay_factor,const Mood & mood, zjz::Emotion* EmotionPool,Collision & cls)  
{
	cls.t_min=timestep+0.01;
	float emotion_p,mood_p, emotion_new_p, mood_new_p,mood_v, change_moment;

	for(int i=0;i!=22;++i){
       for( int j=0;j!=3;++j){
		   emotion_p=EmotionPool[i].Position[j];
		   mood_p=mood.Position[j];
		   emotion_new_p= EmotionPool[i].Position_new[j];
		   mood_new_p=mood.Position_new[j];
		   mood_v=mood.Velocity[j];
		   if(check_collision(emotion_p,mood_p,emotion_new_p,mood_new_p)){
			     change_moment=sign_change_moment(emotion_p, mood_p, mood_v, timestep, emo_decay_factor);
		                if(change_moment>1e-4&&cls.t_min>change_moment){
				             cls.t_min=change_moment;
				             cls.emotion_id=i;
							 cls.coordinate_id=j;
						}
		   }
	   }		
	}
}


