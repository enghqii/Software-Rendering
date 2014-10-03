#pragma once
#include "vector.h"

class Matrix{
public:
	Matrix();
	Matrix(const Matrix &p);

	Matrix operator+ (const Matrix &p);
	Matrix operator+=(const Matrix &p);
	Matrix operator- (const Matrix &p);
	Matrix operator-=(const Matrix &p);

	Matrix operator* (const Matrix &p);
	Matrix operator*=(const Matrix &p);
	Matrix operator* (const float f);
	Matrix operator*=(const float f);

	friend Matrix operator* (const float f, const Matrix &m);
	friend Vector operator* (Vector &p,const Matrix &m);
	friend Vector operator*=(Vector &p,const Matrix &m);

	float* operator[](int x);

	void Inverse();

	Matrix Identity();

	
	Matrix Scaling(float x,float y,float z);
	Matrix RotationX(float Angle); // in Radian
	Matrix RotationY(float Angle); // in Radian
	Matrix RotationZ(float Angle); // in Radian
	Matrix RotationAxis(Vector p,float Angle);
	Matrix Translation(float x,float y,float z);

	Matrix LookAt(Vector Position,Vector Look,Vector Up);

	Matrix PerspectiveFov(float fov,float Aspect,float zMin,float zMax); // fov - in Radian

	Matrix ViewPort(int x,int y,int width,int height,float zMin,float zMax);

	float Index(int x,int y){ return mat[y+1][x+1]; }

private:
	float mat[4][4];
};

void MatrixTranslation(Matrix& pOut,float x,float y,float z);