#pragma once
#include "matrix.h"

class Camera{
public:
	enum CameraType{LANDOBJECT,AIRCRAFT};

	Camera();
	Camera(CameraType cameratype);
	~Camera();
	
	void strafe(float units);
	void fly(float units);
	void walk(float units);

	void pitch(float angle);
	void yaw(float angle);
	void roll(float angle);

	Matrix GetViewMatrix();
	CameraType GetCameraType();
	void SetCameraType(CameraType cameraType);
	Vector GetPosition(){ return Position; }
	Vector GetRight(){ return Right; }
	Vector GetUp(){ return Up; }
	Vector GetLook(){ return Look; }

private:

	CameraType Type;

	Vector Right;
	Vector Up;
	Vector Look;

	Vector Position;
};