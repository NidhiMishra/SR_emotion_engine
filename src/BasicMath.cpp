
#include "BasicMath.h"

point& point::operator =(const point & rhs){
	for(int i=0;i!=3;++i)
		data[i]=rhs[i];
	return *this;
}

point& point::operator+=(const point & rhs){
	for(int i=0;i!=3;++i)
		data[i]+=rhs[i];
	return *this;
}
point & point::operator-=(const point & rhs){
	for(int i=0;i!=3;++i)
		data[i]-=rhs[i];
	return *this;
}


point operator+(const point & lhs, const point & rhs){
	point ret(lhs);
	ret+=rhs;
	return ret;
}
point operator-(const point & rhs){
	point ret;
	for(int i=0;i!=3;++i)   
		ret[i]=-rhs[i];
	return ret;
}
point operator-(const point & lhs, const point & rhs){
	point ret(lhs);
	ret+=-rhs;
	return ret;
}



point operator*(const float& a, const point & rhs){
	point ret;
    for(int i=0;i!=3;++i)
		ret[i] = a*rhs[i];
	return ret;
}

point operator*(const point &rhs, const float &a){
	point ret;
    for(int i=0;i!=3;++i)
		ret[i] = a*rhs[i];
	return ret;
}

point operator^(const point & rhs, const int &a){
	point ret;
	for(int i=0;i!=3;++i){
		ret[i]=pow(rhs[i],a);
	}
	return ret;
}

bool operator==(const point & lhs , const point & rhs){
	return lhs[0]==rhs[0] && lhs[1]==rhs[1] && lhs[2]==rhs[2];
}
bool operator!=(const point & lhs, const point & rhs){
	return !(lhs==rhs);
}
bool operator>(const point & lhs, const point & rhs){
	return lhs[0]>rhs[0] && lhs[1]>rhs[1] && lhs[2]>rhs[2];
}
bool operator>=(const point & lhs , const point & rhs){
	return lhs[0]>=rhs[0] && lhs[1]>=rhs[1] && lhs[2]>=rhs[2];
}
bool operator<(const point & lhs, const point & rhs){
	return lhs[0]<rhs[0] && lhs[1]<rhs[1] && lhs[2]<rhs[2];
}
bool operator<=(const point& lhs  , const point & rhs){
	return lhs[0]<=rhs[0] && lhs[1]<=rhs[1] && lhs[2]<=rhs[2];
}








 float dot(const point &lhs, const point& rhs){
		float result=0;
	for(int i=0;i!=3;++i)
		result += lhs[i]*rhs[i];
	return result;
}
// The square of the length of a vector
 float point::norm() const{
	return dot(*this,*this);
	 /*	float result=0;
	for(int i=0;i!=3;++i)
		result += pow(data[i],2);
	return result;*/
}
// The length of a vector
 float point::length() const{	
	return sqrtf(this->norm());
}
 float point::max_component() const{	
	float max=abs(this->data[0]);
	float max_return=this->data[0];
	if(max<abs(this->data[1])){
		max=abs(this->data[1]);
		max_return=this->data[1];}
	if(max<abs(this->data[2])){
		max=abs(this->data[2]);
		max_return=this->data[2];}
	return max_return;
}
// vector normalization
 point& point::normalize(){
	 float a=this->length();
	 const point rhs(*this);
	 if(a!=0)
	    *this=(1/a)*rhs;
	 return *this;
}

