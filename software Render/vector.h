#pragma once

class Matrix;

class Vector{
public:
	Vector();
	Vector(float _x,float _y,float _z);
	Vector(const Vector &p);

	Vector operator+ (const Vector &p);
	Vector operator- (const Vector &p);
	Vector operator* (const Vector &p);
	Vector operator/ (const Vector &p);
	
	Vector operator+=(const Vector &p);
	Vector operator-=(const Vector &p);
	Vector operator*=(const Vector &p);
	Vector operator/=(const Vector &p);

	bool operator== (const Vector &p);
	bool operator!= (const Vector &p);

	Vector operator* (const float f);
	Vector operator/ (const float f);

	friend Vector operator* (const float t,const Vector &p);
	friend Vector operator/ (const float t,const Vector &p);
	
	friend Vector operator*= (const float f, Vector &p);
	Vector operator*= (const float f);
	friend Vector operator/= (const float f, Vector &p);

	friend Vector operator* (Vector &p,const Matrix &m);

	float& operator[](int n);

	void init(float _x,float _y,float _z){x=_x; y=_y; z=_z;}

	float size();
	Vector Normalize();

	float Dot(const Vector &p);
	Vector Cross(const Vector &p);

private:
	float x;
	float y;
	float z;

	float w;
};

