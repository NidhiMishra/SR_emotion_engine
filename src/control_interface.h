#ifndef CONTROLINTERFACE_H
#define CONTROLINTERFACE_H

#include "AffectiveSystem.h"
#include "axis.h"
#include <iostream>
#include <string>
#include <fstream>
#include "game_theory.h"


ofstream out;
string emo_focus_txt="No_Active_Emotion";
float emo_focus_intensity=0;
Affsys aff_sys;
GameTheory game_exp;
//creation of client
//OrcaConnect client = OrcaConnect();
//std::string fsmState=" ";
int user_speech_input=0;
string str_output;
int r_num=0;
/************************************/
#define TRANSFORM_NONE    0 
#define TRANSFORM_ROTATE  1
#define TRANSFORM_SCALE 2 
#define TRANSFORM_TRANSLATE  3
#define TRANSFORM_TRANSLATE_Z  4
#define TRANSFORM_ROTATE_Z  5

static int press_x, press_y; 
static float x_angle = 0.0; 
static float y_angle = 0.0; 
static float z_angle = 0.0; 
static float scale_size = 1; 
static float x_trans=0,y_trans=0,z_trans=0;


static int xform_mode = 0; 

bool start=true;
bool start_mem_decay=false;

int   main_window=0;
int client_check=1;
int restore=0;
/***************************************************/


//** Pointers to the windows and some of the controls we'll create **/
GLUI *cmd_line_glui=0, *glui;
//GLUI_TextBox* txt_output;
//GLUI_EditText * emo_focus;
//GLUI_EditText *emo_focus_intens;



#define SET_ID   251
#define START_ID          252
#define RESET_ID         253
#define QUIT_ID         254
#define END_ID      255
#define DECISION_ID  256
#define DECAY_ID 257
#define REPORT_MEMORY_ID 258
#define POSITIVE_ID 259
#define NEGATIVE_ID 260


#define RESET_CENTER 1;
#define RESET_NONE 0;
#define DEPRESS_ID 351
#define CONSOLE_ID 352
#define ENTERTAIN_ID 353
#define MODEL_ID 151
#define TXTBOX_ID 152

#define OBJ_POINTS	2
#define OBJ_WIREFRAME	3

#define OBJ_SHADE_SMOOTH   1
#define OBJ_SHADE_FLAT		0


#define PROJ_PERSPECTIVE	1
#define PROJ_ORTHO	0


std::vector<std::string> split(const std::string txt);
void getInputStimuli(std::string& _str);
void mymouse(int button, int state, int x, int y);
void mymotion(int x, int y);
void mykey(unsigned char key, int x, int y);
void myGlutIdle( void);
void setclient();
void myGlutDisplay();
void control_cb( int control );
GLvoid Timer( int value);
int main(int argc, char* argv[]);
void initialization();
void ReportMemory();

Mood MOOD;
zjz::Emotion Joy;
zjz::Emotion Distress;

#endif