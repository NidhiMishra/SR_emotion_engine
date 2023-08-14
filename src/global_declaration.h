#ifndef GLOABLE_DECLARARION_H
#define GLOABLE_DECLARARION_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include  <stdlib.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159;

using namespace std;
// transfer string to emotions
int str_num(const string& s);
std::string num_str(const int n);
int TransferSentence(const std::string& phrase);
int switch_func(int& idx);
std::string num_to_name(const int& idx);

extern float E_value[22][3];
extern int w_personality;
extern int w_fac_exp;
extern int w_emo_decay;
extern int w_stimuli;
// output stream
extern ofstream out;
extern int user_speech_input;
extern string str_output;

#endif