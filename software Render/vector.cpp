#include "Vector.h"
#include <math.h>

Vector::Vector(){
	x = y = z = 0;

	w = 1;
}

Vector::Vector(float _x, float _y, float _z){
	x= _x;
	y= _y;
	z= _z;

	w = 1;
}

Vector::Vector(const Vector &p){
	x= p.x;
	y= p.y;
	z= p.z;

	w = p.w;
	//w = 1;
}

float Vector::size(){
	return sqrt( x*x + y*y + z*z );
}

Vector Vector::Normalize(){
	float s = size();
	
	if(s != 0){
		x = x / s;
		y = y / s;
		z = z / s;
	}
	return *this;
}

float Vector::Dot(const Vector &p){
	return ( x*p.x + y*p.y + z*p.z );
}

Vector Vector::Cross(const Vector &p){
	return Vector(y * p.z - z * p.y 
				 ,z * p.x - x * p.z 
				 ,x * p.y - y * p.x);
}

Vector Vector::operator+ (const Vector &p){
	return Vector( x+p.x , y+p.y , z+p.z);
}
Vector Vector::operator- (const Vector &p){
	return Vector( x-p.x , y-p.y , z-p.z);
}
Vector Vector::operator* (const Vector &p){
	return Vector( x*p.x , y*p.y , z*p.z);
}
Vector Vector::operator /(const Vector &p){
	return Vector( x/p.x , y/p.y , z/p.z);
}

Vector Vector::operator+=(const Vector &p){
	(*this) = Vector( x+p.x , y+p.y , z+p.z);
	return *this;
}
Vector Vector::operator-=(const Vector &p){
	(*this) = Vector( x-p.x , y-p.y , z-p.z);
	return *this;
}
Vector Vector::operator*=(const Vector &p){
	(*this) = Vector( x*p.x , y*p.y , z*p.z);
	return *this;
}
Vector Vector::operator/=(const Vector &p){
	(*this) = Vector( x/p.x , y/p.y , z/p.z);
	return *this;
}

bool Vector::operator== (const Vector&p){
	if( x == p.x && y==p.y && z==p.z )
		return true;
	return false;
}

bool Vector::operator !=(const Vector &p){
	if( x == p.x && y==p.y && z==p.z )
		return false;
	return true;
}

Vector Vector::operator *(const float f){
	return Vector( x * f , y * f , z * f);
}

Vector Vector::operator /(const float f){
	return Vector( x / f , y / f , z / f);
}
Vector Vector::operator*= (const float f){
	(*this) = (*this) * f;
	return (*this);
}

Vector operator* (const float f,const Vector &p){
	return Vector(p.x * f ,p.y * f ,p.z * f);
}
Vector operator/ (const float f,const Vector &p){
	return Vector(p.x / f ,p.y / f ,p.z / f);
}

Vector operator*= (const float f, Vector &p){
	p.x *= f;
	p.y *= f;
	p.z *= f;

	return p;
}
Vector operator/= (const float f, Vector &p){
	p.x /= f;
	p.y /= f;
	p.z /= f;

	return p;
}

float& Vector::operator [](int n) {
	if(n==0)
		return x;
	else if(n==1)
		return y;
	else if(n==2)
		return z;
	else
		return w;
}