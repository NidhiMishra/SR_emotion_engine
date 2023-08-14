#include "ThriftTools.hpp"
#include "ProtectedClient.h"
#include "EmotionEngineService.h"
#include "Inputs_constants.h"

#include "control_interface.h"



//Emotion Client

ProtectedClient<imi::EmotionEngineServiceClient> EmotionClient;

 GLvoid Timer( int value)
{
  
	if( value ) {
		// deal with user speech input
			if(user_speech_input==1){
				Stimuli S;
				S.Etype=1;//anger
				S.Intensity=0.5;
				S.Time=0;
				aff_sys.STIMULI.push_back(S);
				aff_sys.stimuli_input=true;
				out<<"User: I hate you!\n"<<endl;
				str_output.append("User: I hate you!\n");
			    //txt_output->set_text(str_output.c_str());
				aff_sys.user_dialogue_choice=1;
				user_speech_input=0;
			}
			else if(user_speech_input==2){
				Stimuli S;
				S.Etype=8;//gratitude
				S.Intensity=0.5;
				S.Time=0;
				aff_sys.STIMULI.push_back(S);
				aff_sys.stimuli_input=true;
				out<<"User: I like you!\n"<<endl;
				str_output.append("User: I like you!\n");
			    //txt_output->set_text(str_output.c_str());
				aff_sys.user_dialogue_choice=2;
				user_speech_input=0;
			}
			
			
			// mood dynamics iteration
			aff_sys.mood_dynamics_process();

			// send emotion focus and mood 	
			if(EmotionClient.ensureConnection())
			{
				try 
				{
					std::string EmotionType=num_str(aff_sys.emo_id);
					double Intensity=aff_sys.EmotionPool[aff_sys.emo_id].Intensity;
					imi::Vec3 SendEmotion;
					imi::Vec3 SendMood;
					if(aff_sys.emo_id>-1){
						SendEmotion.x = aff_sys.EmotionPool[aff_sys.emo_id].Position[0];
						SendEmotion.y = aff_sys.EmotionPool[aff_sys.emo_id].Position[1];
						SendEmotion.z = aff_sys.EmotionPool[aff_sys.emo_id].Position[2];
					}
					
					SendMood.x = aff_sys.mood.Position[0];
					SendMood.y = aff_sys.mood.Position[1];
					SendMood.z = aff_sys.mood.Position[2];

					std::string sentence;
					EmotionClient.getClient()->emotion(sentence,imi::getTimeStamp(),EmotionType,SendEmotion,Intensity,SendMood);
					if(sentence!=""){
						//cout<<sentence<<endl;
						getInputStimuli(sentence);
					}
				
				}   
				catch( apache::thrift::TException &tx ) 
				{
					std::cerr << "EXCEPTION opening the network conn: " << tx.what() << "\n";
					EmotionClient.receiveNetworkException();
				}
				catch (...){
					std::cerr << "Unexpected EXCEPTION!!!" << "\n";
					EmotionClient.receiveNetworkException();
				}
			}

			// For glui output
			if(aff_sys.active_emo_check()){
				emo_focus_txt= num_to_name(aff_sys.chosen_emo);
			    emo_focus_intensity=aff_sys.chosen_emo_intensity;
			}
			else{
				emo_focus_txt="No_Choosen_Emotion";
				emo_focus_intensity=0;
					
			}

			if(start){
				glutTimerFunc(aff_sys.parameter.timestep*1000,Timer,value);
			}

			if(aff_sys.stimuli_input)
				aff_sys.stimuli_input=false;

			initialization();
			glutPostRedisplay();
		}
} 

std::vector<std::string> split(const std::string txt)
{
	std::vector<std::string> strs;
    unsigned int pos = txt.find(" ");
    unsigned int initialPos = 0;

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos) );
        initialPos = pos + 1;

        pos = txt.find(" ", initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, min( pos, txt.size() ) - initialPos + 1 ) );

    return strs;
}
void getInputStimuli(std::string& _str){
	std::vector<std::string> inputs=split(_str);
	Stimuli S;
	S.Etype=str_num(inputs[0]);
	S.Intensity=stof(inputs[1]);
	S.Time=0;
	aff_sys.STIMULI.push_back(S);
	aff_sys.stimuli_input=true;

}

void mymouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) 
	{
		press_x = x; press_y = y; 
		if (button == GLUT_LEFT_BUTTON)
			xform_mode = TRANSFORM_ROTATE; 
		
		else if (button == GLUT_MIDDLE_BUTTON) 
			xform_mode = TRANSFORM_SCALE; 
	}
	else if (state == GLUT_UP) 
	{
		xform_mode = TRANSFORM_NONE; 
	}
}

void mymotion(int x, int y)
{
	if (xform_mode == TRANSFORM_ROTATE) 
	{
		x_angle += (x - press_x)/5.0; 

		if (x_angle > 180) 
			x_angle -= 360; 
		else if (x_angle <-180) 
			x_angle += 360; 
      
		press_x = x; 
	   
		y_angle += (y - press_y)/5.0; 

		if (y_angle > 180) 
			y_angle -= 360; 
		else if (y_angle <-180) 
			y_angle += 360; 
      
		press_y = y; 
    }
	else if (xform_mode == TRANSFORM_ROTATE_Z)
	{
		z_angle += -(y-press_y)/5.0; 

		if (z_angle > 180) 
			z_angle -= 360; 
		else if (z_angle <-180) 
			z_angle += 360; 
      
		press_y = y; 
	}

	else if (xform_mode == TRANSFORM_SCALE)
	{
		float old_size = scale_size;
		
		scale_size *= (1 + (y - press_y)/60.0); 

		if (scale_size <0) 
			scale_size = old_size; 
		press_y = y; 
    }
	else if (xform_mode == TRANSFORM_TRANSLATE)
	{
		x_trans +=-(x-press_x)/60.0;
		press_x=x;
		y_trans +=(y-press_y)/60.0;
		press_y=y;
	}
	else if (xform_mode == TRANSFORM_TRANSLATE_Z)
	{
		z_trans +=(press_y-y)/60.0;
		press_y=y;
	}

	// force the redraw function
	glutPostRedisplay(); 
}

void mykey(unsigned char key, int x, int y)
{
	switch(key) 
	{
	
	case 'x':
		
			xform_mode = TRANSFORM_TRANSLATE; 
			break;
	case 'z':
		
		xform_mode= TRANSFORM_TRANSLATE_Z;
		break;
	case 'r':
		xform_mode= TRANSFORM_ROTATE_Z;
		break;
	

	}

	// force the redraw function
	//glutPostRedisplay(); 
}
 
 void myGlutDisplay()
{

     glEnable(GL_DEPTH_TEST); 

	 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	 
	 glMatrixMode(GL_PROJECTION); 
	 glLoadIdentity(); 
	 gluPerspective(50, 1.6, 0.1, 200);

	
	 glMatrixMode(GL_MODELVIEW); 
	 glLoadIdentity(); 
	 gluLookAt(0.5,4.2,0.1,0,0.1,0,0,0,1);

    glRotatef(x_angle, 0, 0,1); 
	glRotatef(y_angle, 0,1,0); 
	glRotatef(z_angle, 1,0,0); 
	glScalef(scale_size, scale_size, scale_size); 
	glTranslatef(x_trans,y_trans,z_trans);

	 coordinate();
		 
	 
	if(w_personality)
		draw_vector(aff_sys.parameter.Mp,GREEN,3);
	mydraw(aff_sys.mood,aff_sys.EmotionPool);
		
	
	 glutSwapBuffers();
    
}

 void control_cb( int control )
{
	if(control==MODEL_ID){
		initialization();
	}
	if(control==DEPRESS_ID){
			Stimuli S;
			S.Etype=1;//distress
			S.Intensity=0.5;
			S.Time=0;
			aff_sys.STIMULI.push_back(S);
			aff_sys.stimuli_input=true;
			out<<"User: I don't like you!"<<endl;
			str_output.append("User: I hate you!\n");
			//txt_output->set_text(str_output.c_str());
			aff_sys.user_dialogue_choice=1;
	
	}
	    

	if(control==ENTERTAIN_ID){
			Stimuli S;
			S.Etype=8;//joy
			S.Intensity=0.5;
			S.Time=0;
			aff_sys.STIMULI.push_back(S);
			aff_sys.stimuli_input=true;
			out<<"User: I like you so much!"<<endl;
			str_output.append("User: I like you!\n");
			//txt_output->set_text(str_output.c_str());

			aff_sys.user_dialogue_choice=2;
		
	}

	if(control == DECISION_ID){
		user_speech_input=3;
	}

	if(control == DECAY_ID){
		start_mem_decay=true;
	}
	if(control == REPORT_MEMORY_ID){
		user_speech_input=7;
	}


	if(control==TXTBOX_ID){
		str_output.clear();
		//txt_output->set_text(str_output.c_str());
	}

	if(control==END_ID){
		start=false;
	}
	if(control==START_ID){
		start=true;
	
			glutTimerFunc(aff_sys.parameter.timestep*1000,Timer,1);
			// dialogue output to file
			out<<"*************************************\n"<<endl;
			out<<"Start BeingThere Dialogue Scenario.\n"<<endl;
			if(w_personality)
			    out<<"Personality = True\n"<<endl;
			else
				out<<"Personality = False\n"<<endl;
			if(w_fac_exp)
				out<<"Facial Expression = True\n"<<endl;
		    else
				out<<"Facial Expression = False\n"<<endl;
			out<<"*************************************\n"<<endl;
			
			// dialogue output to textbox in glui
			str_output.append("*************************************\n");
			str_output.append("Start BeingThere Dialogue Scenario.\n");
			if(w_personality)
			    str_output.append("Personality = True\n");
			else
				str_output.append("Personality = False\n");
			if(w_fac_exp)
				str_output.append("Facial Expression = True\n");
		    else
				str_output.append("Facial Expression = False\n");
			str_output.append("*************************************\n");
			//txt_output->set_text(str_output.c_str());
		 
	
	}

 
  if(control==RESET_ID)
  {   
		  aff_sys=Affsys();
		  aff_sys.Initialvalue("parameter.txt");
		  start_mem_decay=false;

		  emo_focus_txt="No_Choosen_Emotion";
		  emo_focus_intensity=0;
	     // emo_focus->set_text(emo_focus_txt.c_str());
	     // emo_focus_intens->set_float_val(emo_focus_intensity);

		  start=true;
		  scale_size = 1; 
		  x_trans=0,y_trans=0,z_trans=0;
		  xform_mode = 0; 
		  aff_sys.STIMULI.clear();

		  if(w_stimuli)
		      aff_sys.InputStimuli("stimuli.txt");

		  initialization();
 		  glutSwapBuffers();
  
  }

  if(control==POSITIVE_ID)
  {   
		  aff_sys=Affsys();
		  aff_sys.Initialvalue("parameter_w_positive_personality.txt");
		  start_mem_decay=false;

		  emo_focus_txt="No_Choosen_Emotion";
		  emo_focus_intensity=0;
	     // emo_focus->set_text(emo_focus_txt.c_str());
	     // emo_focus_intens->set_float_val(emo_focus_intensity);

		  start=true;
		  scale_size = 1; 
		  x_trans=0,y_trans=0,z_trans=0;
		  xform_mode = 0; 
		  aff_sys.STIMULI.clear();

		  if(w_stimuli)
		      aff_sys.InputStimuli("stimuli.txt");

		  initialization();
 		  glutSwapBuffers();
  
  }

  if(control==NEGATIVE_ID)
  {   
		  aff_sys=Affsys();
		  aff_sys.Initialvalue("parameter_w_negative_personality.txt");
		  start_mem_decay=false;

		  emo_focus_txt="No_Choosen_Emotion";
		  emo_focus_intensity=0;
	     // emo_focus->set_text(emo_focus_txt.c_str());
	     // emo_focus_intens->set_float_val(emo_focus_intensity);

		  start=true;
		  scale_size = 1; 
		  x_trans=0,y_trans=0,z_trans=0;
		  xform_mode = 0; 
		  aff_sys.STIMULI.clear();

		  if(w_stimuli)
		      aff_sys.InputStimuli("stimuli.txt");

		  initialization();
 		  glutSwapBuffers();
  
  }

  if(control==QUIT_ID)
  {
	   glutDestroyWindow(main_window);
	   GLUI_Master.close_all();
		exit(0);
  }
}



/***************************************** myGlutIdle() ***********/

void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  


  glutPostRedisplay();

  /****************************************************************/
  /*            This demonstrates GLUI::sync_live()               */
  /*   We change the value of a variable that is 'live' to some   */
  /*   control.  We then call sync_live, and the control          */
  /*   associated with that variable is automatically updated     */
  /*   with the new value.  This frees the programmer from having */
  /*   to always remember which variables are used by controls -  */
  /*   simply change whatever variables are necessary, then sync  */
  /*   the live ones all at once with a single call to sync_live  */
  /****************************************************************/

   
  glui->sync_live();

}

void initialization(){

		MOOD=aff_sys.mood;
		Joy =aff_sys.EmotionPool[12];
		Distress= aff_sys.EmotionPool[3];

}





int main(int argc, char* argv[])
{ 


  imi::initializeThrift();
  imi::InputsConstants input_constants;
  
  std::string localhost;
  if (argc>1)
	  localhost=argv[1];
  else
	  localhost="localhost";
  cout<<localhost;



  //EmotionClient= ProtectedClient<imi::EmotionEngineServiceClient>("localhost",imi::g_Inputs_constants.DEFAULT_EMOTIONENGINE_SERVICE_PORT);
  //boost::thread SpeechInputThread(serveSpeechInputServer,9099);
  EmotionClient= ProtectedClient<imi::EmotionEngineServiceClient>(localhost,imi::g_Inputs_constants.DEFAULT_EMOTIONENGINE_SERVICE_PORT);
   

  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition( 100, 100 );
  glutInitWindowSize(500, 300);
 
  main_window = glutCreateWindow( "Mood Dynamics" );
  glClearColor(0,0,0,0.0);

  aff_sys.Initialvalue("parameter.txt");


 /* aff_sys.InputStimuli("stimuli.txt");
  miralab_aff_sys.InputStimuli("stimuli.txt");
  alma_aff_sys.InputStimuli("stimuli.txt");*/

  initialization();
 // if(client_check)
	//setclient();
  //cout<<"Please Enter the Name of Output Dialogue Files :"<<endl ;
	//string sout;
	//cin>>sout;
  out.open("Dialogue.txt");
	//print_result();

  glutTimerFunc(aff_sys.parameter.timestep*1000,Timer,1);

  glutDisplayFunc( myGlutDisplay );
  glutMouseFunc(mymouse);
  glutMotionFunc(mymotion);
  glutKeyboardFunc(mykey);


  


    /****************************************/
  /*       Set up OpenGL lights           */
  /****************************************/

  /****************************************/
  /*          Enable z-buferring          */
  /****************************************/

  glEnable(GL_DEPTH_TEST);

  /****************************************/
  /*         Here's the GLUI code         */
  /****************************************/

  printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

  glui = GLUI_Master.create_glui( "GLUI", 0, 600, 50 ); 
  new GLUI_StaticText( glui, "mood_dynamics_w_dialogue" ); 



   GLUI_Rollout* state_panel=new GLUI_Rollout(glui,"CurrentState",true);

	 GLUI_Panel *obj_panel3 = new GLUI_Panel(state_panel, "Mood Position");
  GLUI_Spinner * spinner12 = 
    new GLUI_Spinner( obj_panel3, "Pleasure", &MOOD.Position[0]);
   spinner12->set_float_limits(-1, 1);
 GLUI_Spinner * spinner13 = 
    new GLUI_Spinner( obj_panel3, "Arousal", &MOOD.Position[1]);
    spinner13->set_int_limits(-1, 1);
 GLUI_Spinner * spinner14 = 
    new GLUI_Spinner( obj_panel3, "Dominance", &MOOD.Position[2]);
    spinner14->set_float_limits(-1, 1);

	 GLUI_Panel *obj_panel7 = new GLUI_Panel(state_panel, "Mood Velocity");
  GLUI_Spinner * spinner3 = 
	  new GLUI_Spinner( obj_panel7, "P", &MOOD.Velocity[0]);
 GLUI_Spinner * spinner4 = 
	 new GLUI_Spinner( obj_panel7, "A", &MOOD.Velocity[1]);
 GLUI_Spinner * spinner5 = 
	 new GLUI_Spinner( obj_panel7, "D", &MOOD.Velocity[2]);
	
	GLUI_Panel *obj_panel4 = new GLUI_Panel(state_panel, "Active Emotion");
    GLUI_Spinner * spinner1 = 
	  new GLUI_Spinner( obj_panel4, "Joy_intensity", &Joy.Intensity);
    spinner1->set_float_limits(-1, 1);
    GLUI_Spinner * spinner2 = 
    new GLUI_Spinner( obj_panel4, "Distress_intensity", &Distress.Intensity);
    spinner2->set_int_limits(-1, 1);

	/*GLUI_Panel *obj_panel5 = new GLUI_Panel(state_panel, "Active Emotion");
	emo_focus= glui->add_edittext_to_panel(obj_panel5,"Emo_Focus: ");
	emo_focus->set_text(emo_focus_txt.c_str());
	emo_focus->set_w(200);
	emo_focus_intens= glui->add_edittext_to_panel(obj_panel5,"Emo_Focus Intensity: ");
	emo_focus_intens->set_float_val(emo_focus_intensity);*/

  GLUI_Panel *obj_pane25 = new GLUI_Panel( glui, "", GLUI_PANEL_NONE );
	GLUI_Checkbox* method_check=new GLUI_Checkbox(obj_pane25,"w/o personality",&w_personality);
	GLUI_Checkbox* face_check=new GLUI_Checkbox(obj_pane25,"w/o facial expression",&w_fac_exp);
	GLUI_Checkbox* decay_check=new GLUI_Checkbox(obj_pane25,"w/o emotion decay",&w_emo_decay);
	GLUI_Checkbox* stimuli_check=new GLUI_Checkbox(obj_pane25,"load stimuli",&w_stimuli);
  
   //GLUI_EditText *edittext =glui->add_edittext( "Emotion Focus:", GLUI_EDITTEXT_TEXT, emo_focus_txt );
   //GLUI_EditText *edittext =glui->add_edittext( "Emo_Intensity:", GLUI_EDITTEXT_FLOAT, emo_focus_intensity );
	//client_check_=new GLUI_Checkbox(obj_panel25,"Client",&client_check);

	 /**************** control panel ******************/
    GLUI_Panel *obj_panel25 = new GLUI_Panel( glui, "Control Panel", GLUI_PANEL_NONE );
  GLUI_Button* start_but=new GLUI_Button(obj_panel25,"Start",START_ID,control_cb);
   new GLUI_Column( obj_panel25 , false );
  GLUI_Button* reset_but=new GLUI_Button(obj_panel25,"Pause",END_ID,control_cb);
    GLUI_Panel *obj_panel26 = new GLUI_Panel( glui, "", GLUI_PANEL_NONE );
    GLUI_Button* def_but=new GLUI_Button(obj_panel26,"Reset",RESET_ID,control_cb);
	new GLUI_Column( obj_panel26 , false );
  new GLUI_Button(obj_panel26, "Quit", QUIT_ID,control_cb);

  new GLUI_Column( glui , false );
  GLUI_Panel *obj_panel27 = new GLUI_Panel(glui, "Game Control");
  new GLUI_Spinner( obj_panel27, "Friendliness", &game_exp.relationship[0]);
  new GLUI_Spinner( obj_panel27, "Dominance", &game_exp.relationship[2]);
  new GLUI_Spinner( obj_panel27, "K", &game_exp.k);
  new GLUI_Spinner( obj_panel27, "agent_shopping", &game_exp.Go_Shopping.agent_utility);
  new GLUI_Spinner( obj_panel27, "user_shopping", &game_exp.Go_Shopping.user_utility);
  new GLUI_Spinner( obj_panel27, "agent_swimming", &game_exp.Go_Swimming.agent_utility);
  new GLUI_Spinner( obj_panel27, "user_swimming", &game_exp.Go_Swimming.user_utility);
  new GLUI_Spinner( obj_panel27, "utility_threshold", &game_exp.utility_threshold);
  new GLUI_Spinner( obj_panel27, "delta_threshold", &game_exp.delta_utility_threshold);
  new GLUI_Spinner( obj_panel27, "theata", &game_exp.theata);
   GLUI_Rollout* user_panel=new GLUI_Rollout(glui,"UserChoice",true);
  GLUI_Panel *obj_panel20 = new GLUI_Panel( user_panel, "User Dialogue Stagtegy", GLUI_PANEL_NONE );
   GLUI_Button* depress_but=new GLUI_Button(obj_panel20,"Hate you",DEPRESS_ID,control_cb);
   //new GLUI_Column( obj_panel20 , false );
   GLUI_Button* entertain_but=new GLUI_Button(obj_panel20,"Like you", ENTERTAIN_ID,control_cb);
   new GLUI_Button(obj_panel20, "Make Decision", DECISION_ID,control_cb);
   new GLUI_Button(obj_panel20, "Memory Decay", DECAY_ID,control_cb);
   new GLUI_Button(obj_panel20, "Report Memory", REPORT_MEMORY_ID,control_cb);
   new GLUI_Button(obj_panel20, "Positive Personality", POSITIVE_ID,control_cb);
   new GLUI_Button(obj_panel20, "Negative Personality", NEGATIVE_ID,control_cb);
  //new GLUI_Column(glui,false);
  //new GLUI_StaticText( glui, "Dialogue Window" ); 
  //txt_output=new GLUI_TextBox(glui,true);
  //txt_output->set_h(500);
  //txt_output->set_w(350);
  ////txt_output->disable();
  //GLUI_Button* txt_but=new GLUI_Button(glui,"Clear TextBox",TXTBOX_ID,control_cb);
  //txt_but->set_w(350);
  //txt_output->set_text(str_output.c_str());
  /**** Link windows to GLUI, and register idle callback ******/
  
  glui->set_main_gfx_window( main_window );

  /* We register the idle callback with GLUI, not with GLUT */
  GLUI_Master.set_glutIdleFunc( myGlutIdle );


  glutMainLoop();

  return EXIT_SUCCESS;
}