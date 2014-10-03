#include "matrix.h"
#include <math.h>

Matrix::Matrix(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			mat[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix &p){
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++){
			mat[i][j] = p.mat[i][j];
		}
	}
}

void Matrix::Inverse(){

}
Matrix Matrix::Identity(){

	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(i==j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}

	return (*this);
}

Matrix Matrix::Scaling(float x,float y,float z){
	Matrix T;

	T[0][0] = x; T[0][1] =0; T[0][2] =0; T[0][3] =0;
	T[1][0] = 0; T[1][1] =y; T[1][2] =0; T[1][3] =0;
	T[2][0] = 0; T[2][1] =0; T[2][2] =z; T[2][3] =0;
	T[3][0] = 0; T[3][1] =0; T[3][2] =0; T[3][3] =1;

	(*this) = T;

	return (*this);
}

Matrix Matrix::RotationX(float Angle){
	Matrix T;

	T[0][0] = 1; T[0][1] =           0; T[0][2] =          0; T[0][3] =0;
	T[1][0] = 0; T[1][1] = cosf(Angle); T[1][2] =sinf(Angle); T[1][3] =0;
	T[2][0] = 0; T[2][1] =-sinf(Angle); T[2][2] =cosf(Angle); T[2][3] =0;
	T[3][0] = 0; T[3][1] =           0; T[3][2] =          0; T[3][3] =1;

	(*this) = T;

	return (*this);
}

Matrix Matrix::RotationY(float Angle){
	Matrix T;

	T[0][0] = cosf(Angle); T[0][1] =0; T[0][2] =-sinf(Angle); T[0][3] =0;
	T[1][0] =           0; T[1][1] =1; T[1][2] =           0; T[1][3] =0;
	T[2][0] = sinf(Angle); T[2][1] =0; T[2][2] = cosf(Angle); T[2][3] =0;
	T[3][0] =           0; T[3][1] =0; T[3][2] =           0; T[3][3] =1;

	(*this) = T;

	return (*this);
}

Matrix Matrix::RotationZ(float Angle){
	Matrix T;

	T[0][0] = cosf(Angle); T[0][1] = sinf(Angle); T[0][2] =0; T[0][3] =0;
	T[1][0] =-sinf(Angle); T[1][1] = cosf(Angle); T[1][2] =0; T[1][3] =0;
	T[2][0] =           0; T[2][1] =           0; T[2][2] =1; T[2][3] =0;
	T[3][0] =           0; T[3][1] =           0; T[3][2] =0; T[3][3] =1;

	(*this) = T;

	return (*this);
}

Matrix Matrix::RotationAxis(Vector p,float Angle){

	Matrix T;

	float fCos = (float)cosf( Angle );
	float fSin = (float)sinf( Angle );

	p.Normalize();

	T.mat[0][0] = ( p[0] * p[0] ) * ( 1.0f - fCos ) + fCos;
	T.mat[0][1] = ( p[1] * p[0] ) * ( 1.0f - fCos ) + ( p[2] * fSin );
	T.mat[0][2] = ( p[2] * p[0] ) * ( 1.0f - fCos ) - ( p[1] * fSin );
	T.mat[0][3] = 0.0f;

	T.mat[1][0] = ( p[0] * p[1] ) * ( 1.0f - fCos ) - ( p[2] * fSin );
	T.mat[1][1] = ( p[1] * p[1] ) * ( 1.0f - fCos ) + fCos;
	T.mat[1][2] = ( p[2] * p[1] ) * ( 1.0f - fCos ) + ( p[0] * fSin );
	T.mat[1][3] = 0.0f;

	T.mat[2][0] = ( p[0] * p[2] ) * ( 1.0f - fCos ) + ( p[1] * fSin );
	T.mat[2][1] = ( p[1] * p[2] ) * ( 1.0f - fCos ) - ( p[0] * fSin );
	T.mat[2][2] = ( p[2] * p[2] ) * ( 1.0f - fCos ) + fCos;
	T.mat[2][3] = 0.0f;

	T.mat[3][0] = 0.0f;
	T.mat[3][1] = 0.0f;
	T.mat[3][2] = 0.0f;
	T.mat[3][3] = 1.0f;

	(*this) = T;

	return (*this);
}

Matrix Matrix::Translation(float x,float y,float z){
	Matrix T;

	T[0][0] = 1; T[0][1] =0; T[0][2] =0; T[0][3] =0;
	T[1][0] = 0; T[1][1] =1; T[1][2] =0; T[1][3] =0;
	T[2][0] = 0; T[2][1] =0; T[2][2] =1; T[2][3] =0;
	T[3][0] = x; T[3][1] =y; T[3][2] =z; T[3][3] =1;

	(*this) = T;

	return (*this);
}

Matrix Matrix::LookAt(Vector Position,Vector Look,Vector Up){

	Vector Right;
	Right = Up.Cross(Look);
	Right.Normalize();

	Matrix T;

	T[0][0] =            Right[0]; T[0][1] =            Up[0]; T[0][2] =            Look[0]; T[0][3] =0;
	T[1][0] =            Right[1]; T[1][1] =            Up[1]; T[1][2] =            Look[1]; T[1][3] =0;
	T[2][0] =            Right[2]; T[2][1] =            Up[2]; T[2][2] =            Look[2]; T[2][3] =0;
	T[3][0] =-Right.Dot(Position); T[3][1] =-Up.Dot(Position); T[3][2] =-Look.Dot(Position); T[3][3] =1;

	(*this) = T;

	return (*this);
}
Matrix Matrix::PerspectiveFov(float fov, float Aspect, float zMin, float zMax){
	Matrix T;

	float h = 1 / tanf(fov*0.5f);
	float w = h / Aspect;
	float Q = zMax / (zMax - zMin);

	T[0][0] = w; T[0][1] =0; T[0][2] =         0; T[0][3] =0;
	T[1][0] = 0; T[1][1] =h; T[1][2] =         0; T[1][3] =0;
	T[2][0] = 0; T[2][1] =0; T[2][2] =         Q; T[2][3] =1;
	T[3][0] = 0; T[3][1] =0; T[3][2] = -Q * zMin; T[3][3] =0;

	(*this) = T;

	return (*this);
}
Matrix Matrix::ViewPort(int x, int y, int width, int height, float zMin, float zMax){
	Matrix T;

	T[0][0] =     width * 0.5f; T[0][1] =              0; T[0][2] =          0; T[0][3] =0;
	T[1][0] =                0; T[1][1] = height * 0.5f; T[1][2] =          0; T[1][3] =0;
	T[2][0] =                0; T[2][1] =              0; T[2][2] =zMax - zMin; T[2][3] =0;
	T[3][0] = x + (width * 0.5f); T[3][1] =y+(height * 0.5f); T[3][2] =       zMin; T[3][3] =1;

	(*this) = T;

	return (*this);
}
/*행렬합*/
Matrix Matrix::operator+ (const Matrix &p){
	Matrix t;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			t.mat[i][j] = mat[i][j] + p.mat[i][j];
		}
	}
	return t;
}

Matrix Matrix::operator+=(const Matrix &p){
	(*this) = (*this) + p;
	return *this;
}

/*행렬차*/
Matrix Matrix::operator -(const Matrix &p){
	Matrix t;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			t.mat[i][j] = mat[i][j] - p.mat[i][j];
		}
	}
	return t;
}

Matrix Matrix::operator-=(const Matrix &p){
	(*this) = (*this) - p;
	return *this;
}


/*행렬곱*/
Matrix Matrix::operator *(const Matrix &p){
	Matrix t;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++)
				t.mat[i][j] += mat[i][k] * p.mat[k][j];
		}
	}
	return t;
}

Matrix Matrix::operator *=(const Matrix &p){
	(*this) = (*this) * p;
	return *this;
}

/*상수곱*/
Matrix Matrix::operator *(const float f){
	Matrix t;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			t.mat[i][j] = mat[i][j] * f;
		}
	}
	return t;
}

Matrix Matrix::operator *=(const float f){
	(*this) = (*this) * f;
	return *this;
}


float* Matrix::operator[](int x){
	x %= 4;
	return mat[x];
}
/* 상수 * 행렬 */
Matrix operator* (const float f,const Matrix &m){
	Matrix t;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			t.mat[i][j] = m.mat[i][j] * f;
		}
	}
	return t;
}

/* 벡터 * 행렬*/
Vector operator* (Vector &p,const Matrix &m){
	Vector t;
	/*for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			t[i] += p[j] * m.mat[j][i];
	}*/
	t[0] = p[0] * m.mat[0][0] + p[1] * m.mat[1][0] + p[2] * m.mat[2][0] + p[3] * m.mat[3][0];
	t[1] = p[0] * m.mat[0][1] + p[1] * m.mat[1][1] + p[2] * m.mat[2][1] + p[3] * m.mat[3][1];
	t[2] = p[0] * m.mat[0][2] + p[1] * m.mat[1][2] + p[2] * m.mat[2][2] + p[3] * m.mat[3][2];
	t[3] = p[0] * m.mat[0][3] + p[1] * m.mat[1][3] + p[2] * m.mat[2][3] + p[3] * m.mat[3][3];
	return t;
}
Vector operator*=(Vector &p,const Matrix &m){
	p = p * m;
	return p;
}


void MatrixTranslation(Matrix& pOut,float x,float y,float z){
	pOut[3][0] = x;
	pOut[3][1] = y;
	pOut[3][2] = z;
}