#include "Camera.h"
#include <stdio.h>

Camera::Camera(){
	Type = AIRCRAFT;

	Right= Up.Cross(Look);
	Right.Normalize();
}
Camera::Camera(CameraType cameratype){
	Type = cameratype;

	/*Position[0] = -0.1038f;
	Position[1] = 0.3481f;
	Position[2] = -0.5094f;*/

	Position[0] = 0;
	Position[1] = 0;
	Position[2] = -1.0f;

	Look[0] = 0;
	Look[1] = 0;
	Look[2] = 1;

	Up[0] = 0;
	Up[1] = 1;
	Up[2] = 0;

	Right= Up.Cross(Look);
	Right.Normalize();
}

Camera::~Camera(){

}

void Camera::strafe(float units){
	if(Type == LANDOBJECT)
		Position += Vector(Right[0],0.0f,Right[2]) * units;
	if(Type == AIRCRAFT)
		Position += Right * units;
}

void Camera::fly(float units){
	if(units == 0)
		return;

	if(Type == AIRCRAFT){
		Position += Look * units;
	}
}

void Camera::walk(float units){
	if(units == 0)
		return ;

	if(Type == LANDOBJECT){
		Position += Vector(Look[0],0.0f,Look[2]) * units;
	}
	if(Type == AIRCRAFT){
		Position += Look * units;
	}
}

void Camera::pitch(float angle)
{
	Matrix T;
	T.RotationAxis(Right,angle);

	// rotate _up and _look around _right vector
	//D3DXVec3TransformCoord(&_up,&_up, &T);
	Up *= T;
	//D3DXVec3TransformCoord(&_look,&_look, &T);
	Look *= T;
}

void Camera::yaw(float angle)
{
	Matrix T;
	T.Identity();

	if( Type == LANDOBJECT )
		T.RotationY(angle);

	if( Type == AIRCRAFT )
		T.RotationAxis(Up,angle);

	// rotate _right and _look around _up or y-axis
	Right	*= T;
	Look	*= T;
}

void Camera::roll(float angle)
{
	// only roll for aircraft type
	if( Type == AIRCRAFT )
	{
		Matrix T;
		T.RotationAxis(Look,angle);

		Right *=T;
		Up *= T;
	}
}

Matrix Camera::GetViewMatrix()
{
	// Keep camera's axes orthogonal to eachother
	/*Look.Normalize();

	Up = Look.Cross(Right);
	Up.Normalize();

	Right = Up.Cross(Look);
	Right.Normalize();*/

	Vector R;
	R[0] = Right[0]; R[1] = Right[1]; R[2] =Right[2];
	Vector U;
	U[0] = Up[0]; U[1] = Up[1]; U[2] = Up[2];
	Vector L;
	L[0] = Look[0]; L[1] = Look[1]; L[2] = Look[2];
	Vector P;
	P[0] = Position[0]; P[1] = Position[1]; P[2] = Position[2];

	L.Normalize();

	U = L.Cross(R);
	U.Normalize();

	R = U.Cross(L);
	R.Normalize();

	float X = -R.Dot(P);
	float Y = -U.Dot(P);
	float Z = -L.Dot(P);

	Matrix T;

	T[0][0] = R[0]; T[0][1] = U[0]; T[0][2] = L[0]; T[0][3] = 0;
	T[1][0] = R[1]; T[1][1] = U[1]; T[1][2] = L[1]; T[1][3] = 0;
	T[2][0] = R[2]; T[2][1] = U[2]; T[2][2] = L[2]; T[2][3] = 0;
	T[3][0] =   X; T[3][1] =   Y; T[3][2] =   Z; T[3][3] = 1;

	return T;
}

Camera::CameraType Camera::GetCameraType(){
	return Type;
}

void Camera::SetCameraType(Camera::CameraType cameraType)
{
	Type = cameraType;
}


