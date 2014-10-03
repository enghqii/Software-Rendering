#pragma once
#include "matrix.h"

enum TRANSFORMSTATE{
	WORLD,
	VIEW,
	PROJECTION,
	VIEW_PORT,
};

#include <windows.h>
class CRender{
public:
	CRender();
	~CRender();

	void Init(HWND hWnd);
	void Release();

	void Clear();
	void Present();
	void DrawLine(/*HDC hdc,*/POINT p1,POINT p2);
	void DrawLine(Vector v1,Vector v2,Vector v3);
	void DrawLine(Vector* v,int number);
	void DrawLine(Vector* v,int* indices,int number);
	void DrawAxis(Vector x,Vector y,Vector z);

	void SetTransForm(TRANSFORMSTATE ts,Matrix& m);

private:
	HWND m_hWnd;

	RECT m_crt;
	
	HBITMAP m_hBit;
	HBITMAP m_OldBit;
	
	HDC m_hdc;
	HDC m_hMemDC;

	Matrix World;
	Matrix View;
	Matrix Proj;
	Matrix vPort;

	//산은 산이요, 물은 물이로다. 이 세상에 잘잘못만 따진다면, 잘된것은 무엇이고 못된것은 무엇인가. 난 모르겠네
};