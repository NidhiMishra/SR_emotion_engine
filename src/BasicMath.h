#ifndef BASICMATH_H
#define BASICMATH_H

#include <stdio.h>
#include <math.h>


class point
{
  private:

    float data[3];

  public:
  /***********  constructor*********/
    point(float x=0.f,float y=0.f,float z=0.f){
        data[0] =x; 
        data[1] =y;
        data[2] =z;    
    }
	 point(float& x,float& y,float& z){
        data[0] =x; 
        data[1] =y;
        data[2] =z;    
    }

	point(const point& p){
		for (int i=0;i!=3;++i)
			data[i]=p.data[i];
	}

    float &operator [](unsigned int idx)
    {
        return data[idx];
    } 
	const float &operator [](unsigned int idx) const
    {
        return data[idx];
    } 

	point& operator =(const point &);
	point & operator+=(const point &);
	point & operator-=(const point &);

	/**************operation*************/
	
	// The square of the length of a vector
	float norm() const;
	float length() const;
    float max_component() const;
  

    point& normalize();
 

	
};

point operator+(const point & , const point &);
point operator-(const point &);
point operator-(const point & , const point &);


point operator*(const float&, const point &);
point operator*(const point & , const float&);

point operator^(const point &, const int &);

bool operator==(const point & , const point &);
bool operator!=(const point & , const point &);
bool operator>(const point & , const point &);
bool operator>=(const point & , const point &);
bool operator<(const point & , const point &);
bool operator<=(const point & , const point &);
// dot product with point y
float dot(const point &, const point &);


#endif