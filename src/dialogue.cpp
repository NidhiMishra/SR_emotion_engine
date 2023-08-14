#include "dialogue.h"

void Dialogue::process(const Mood& mood,int& user_dialogue_choice){
	
		//float mood_max=mood.Position.max_component();
		
		int rm=(r_num++)%3;
		float mood_max=mood.Position[0];
		if(-0.2<=mood_max &&mood_max<0){
			if(user_dialogue_choice==1){
				// float rm=random(3);
				 if(rm==0)
					strcpy_s(auto_reply,"I am sorry for that, I hope you can change your mind.");
				 else if(rm==1)
					strcpy_s(auto_reply,"To be frankly, I can not agree with you.");
				 else
					strcpy_s(auto_reply,"Ok, let us talk something else.");
				// response_animation=10; // PAPER
				  int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=10; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=13;
					 else
						 response_animation=18;
				 }
			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
			else{
			//	float rm=random(3);
				if(rm==0)
					strcpy_s(auto_reply,"It sounds good.");
				else if(rm==1)
					strcpy_s(auto_reply,"I feel much better.");
				else
					strcpy_s(auto_reply,"You are right.");
				 
				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=9; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=16;
					 else
						 response_animation=18;
				 }
				//response_animation=9; // ROCK
			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
		}
		else if(-0.4<=mood_max && mood_max<-0.2){
			if(user_dialogue_choice==1){
				// float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"I am unhappy, why you say such bad words to me!");
				 else if(rm==1)
					strcpy_s(auto_reply,"What is wrong with you today.");
				 else
					strcpy_s(auto_reply,"I am a little angry.");
			     
				 //response_animation=13; // POINTING_YOU
				  int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=13; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=12;
					 else
						 response_animation=18;
				 }
			   //  out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
			else{
			//	float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"Really? You think so?");
				 else if(rm==1)
					strcpy_s(auto_reply,"It sounds better.");
				 else
					strcpy_s(auto_reply,"Ok.");
				
				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=9; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=16;
					 else
						 response_animation=18;
				 }
				//response_animation=16; // OFFER
			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
		}

		else if(-0.7<=mood_max && mood_max<-0.4){
			if(user_dialogue_choice==1){
				//float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"I am sad, I hope we can stop this conversation!");
				 else if(rm==1)
					strcpy_s(auto_reply,"Stop here.");
				 else
					strcpy_s(auto_reply,"Let us stop.");
			     
				 response_animation=12; // RIGHT_SWEEP
			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
			else{
				//float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"stop kidding me");
				 else if(rm==1)
					strcpy_s(auto_reply,"Are you satirizing me?");
				 else
					strcpy_s(auto_reply,"bla bla, you talk too much");
				

				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=9; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=16;
					 else
						 response_animation=18;
				 }
				 //response_animation=16; // OFFER
			     //out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
		}
		else if(-1<=mood_max && mood_max<-0.7){
			if(user_dialogue_choice==1){
				//float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"How you dare to say so, get out of here!");
				 else if(rm==1)
					strcpy_s(auto_reply,"go to hell!");
				 else
					strcpy_s(auto_reply,"Sorry, I have someting else to do.");
			     
				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=12; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=17;
					 else
						 response_animation=13;
				 }
				 //response_animation=17; // RIGHT_STRONG_SWEEP
			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
			else{
				//float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"Let us have no more of this, I do not believe you!");
				 else if(rm==1)
					strcpy_s(auto_reply,"I cannot say the same for you.");
				 else
					strcpy_s(auto_reply,"you are not.");

				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=9; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=16;
					 else
						 response_animation=18;
				 }
			
				 //response_animation=12; // RIGHT_SWEEP

			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
		}
		else if(0<=mood_max && mood_max<0.2){
			if(user_dialogue_choice==1){
				//float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"It sounds bad!");
				 else if(rm==1)
					strcpy_s(auto_reply,"Stop to say that");
				 else
					strcpy_s(auto_reply,"Sorry?");
			     
				 //response_animation=10; // PAPER
				  int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=10; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=16;
					 else
						 response_animation=18;
				 }
			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
			else{
				//float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"Oh, thank you.");
				 else if(rm==1)
					strcpy_s(auto_reply,"Really? Thank you");
				 else
					strcpy_s(auto_reply,"The same to you!");
				
				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=9; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=13;
					 else
						 response_animation=18;
				 }
				 //response_animation=9; // ROCK
			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
		}
		else if(0.2<=mood_max && mood_max<0.4){
			if(user_dialogue_choice==1){
				// float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"Really? You think so? ");
				 else if(rm==1)
					strcpy_s(auto_reply,"Do not fool me");
				 else
					strcpy_s(auto_reply,"Excuse me?");
			     
				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=16; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=14;
					 else
						 response_animation=18;
				 }
				// response_animation=16; // OFFER
			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
			else{
				//float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"You are so nice, my friend!");
				 else if(rm==1)
					strcpy_s(auto_reply," So nice you are!");
				 else
					strcpy_s(auto_reply,"You are so kind.");
				
				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=9; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=13;
					 else
						 response_animation=18;
				 }
				//response_animation=13; // POINTING_YOU
			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
		}
		else if(0.4<=mood_max && mood_max<0.7){
			if(user_dialogue_choice==1){
				//float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"Do not say so, we are good friends!");
				 else if(rm==1)
					strcpy_s(auto_reply,"Good friend does not say such word");
				 else
					strcpy_s(auto_reply,"Come on.");
			     
				// response_animation=14; // WHY
				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=14; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=13;
					 else
						 response_animation=18;
				 }
			    // out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
			else{
				//float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"I am happy, I enjoy our conversation very much!");
				 else if(rm==1)
					strcpy_s(auto_reply,"It is my great pleasure to hear that. It makes me feel good.");
				 else
					strcpy_s(auto_reply,"You are really kind. I really like you.");
				
				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=9; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=12;
					 else
						 response_animation=18;
				 }
				//response_animation=12; // RIGHT_SWEEP
			   //  out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
		}

		else {
			if(user_dialogue_choice==1){
				//float rm=random(3);
				 if(rm==0)
					 strcpy_s(auto_reply,"But I like you, my friend!");
				 else if(rm==1)
					strcpy_s(auto_reply,"Whatever you say, we are good friend!");
				 else
					strcpy_s(auto_reply,"Come on please");
			     
				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=16; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=13;
					 else
						 response_animation=18;
				 }
				// response_animation=16; // OFFER
			   //  out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
			else{
				//float rm=random(2);
				 if(rm==0)
					strcpy_s(auto_reply,"I am so so happy. You are such a kind person");
				 else
					strcpy_s(auto_reply,"I have never felt so happy before");
			
				 int randVar=rand() % 100;
				 if(randVar<33)
					 response_animation=12; // RIGHT_SWEEP
				 else
				 {
					 if(randVar<66)
						 response_animation=17;
					 else
						 response_animation=16;
				 }
				//response_animation=17; // RIGHT__STRONG_SWEEP
			 //   out<<"Current vh mood is: "<< mood.Position[0]<<" "<<mood.Position[1]<<" "<<mood.Position[2]<<endl;
			}
		}


		//stimuli_input=false;
		user_dialogue_choice=0;
	
}
