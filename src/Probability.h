#ifndef PROBABILITY_H
#define PROBABILITY_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<iostream>

#define random(x) (rand()%x)

extern int probability_func(int size,int _bit, float *p);
// number, accuracy and the probability array itself
extern int maximum_func(int size, float *p);
#endif