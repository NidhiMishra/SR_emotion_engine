#include "Probability.h"
using namespace std;

int probability_func(int size,int _bit, float *p)
	// number, accuracy and the probability array itself
{
	float *_p=new float[size];
	int *p1=new int[size+1];
	int r;
	for(int i=0;i!=size;++i){
		_p[i]=p[i]*pow((float)10,_bit);
		//cout<<"_p "<<i<<" :"<<_p[i]<<endl;
	}
	
	p1[0]=0;
	for(int i=0;i!=size;++i){
	    p1[i+1]=(int)(p1[i]+_p[i]);
		//cout<<"p1 "<<i+1<<" :"<<p1[i+1]<<endl;
	}

  
	r=random(p1[size]);

	 
	 for(int i=0;i!=size;++i){
		  if(p1[i]<=r && p1[i+1]>=r)
		      return i;
	 }
	 delete [] p1;
	 delete [] _p;
}

int maximum_func(int size, float *p)
{
	float max=-2;
	int max_idx=-1;
	for(int i=0;i!=size;++i){
		if(p[i]>max){
			max=p[i];
			max_idx=i;
		}
	}
	return max_idx;
}
