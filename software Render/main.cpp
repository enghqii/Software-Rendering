#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "vector.h"
#include "Render.h"
#include "Camera.h"



LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

HINSTANCE g_hInst;
LPCWSTR lpszClass=L"Software Rendering";

CRender Renderer;
Vector v[12];
Vector v2[8];
int indices[36];
     //3°¢ÇüÀÌ 2°³

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
					 ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_POPUP,//WS_SYSMENU|WS_CAPTION|WS_OVERLAPPED ,
		CW_USEDEFAULT,CW_USEDEFAULT,800,600,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	
	
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage) {
	case WM_CREATE:
		srand(time(NULL));
		Renderer.Init(hWnd);
		return 0;
	case WM_DESTROY:
		Renderer.Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}


void Setup(){
	v[0].init(-0.1f,-0.1f,0.1f);
	v[1].init(-0.1f, 0.1f,0.1f);
	v[2].init( 0.1f,-0.1f,0.1f);

	v[3].init(-0.1f, 0.1f,0.1f);
	v[4].init( 0.1f, 0.1f,0.1f);
	v[5].init( 0.1f,-0.1f,0.1f);

	v[6].init(-0.1f,-0.1f,-0.1f);
	v[7].init(-0.1f, 0.1f,-0.1f);
	v[8].init( 0.1f,-0.1f,-0.1f);

	v[9].init(-0.1f, 0.1f,-0.1f);
	v[10].init( 0.1f, 0.1f,-0.1f);
	v[11].init( 0.1f,-0.1f,-0.1f);


	v2[0].init(-0.1f,-0.1f,-0.1f);
	v2[1].init(-0.1f, 0.1f,-0.1f);
	v2[2].init( 0.1f, 0.1f,-0.1f);
	v2[3].init( 0.1f,-0.1f,-0.1f);
	v2[4].init(-0.1f,-0.1f, 0.1f);
	v2[5].init(-0.1f, 0.1f, 0.1f);
	v2[6].init( 0.1f, 0.1f, 0.1f);
	v2[7].init( 0.1f,-0.1f, 0.1f);

	// ¾Õ¸é
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// µÞ¸é
	indices[6] = 5; indices[7]  = 7; indices[8]  = 4;
	indices[9] = 5; indices[10] = 6; indices[11] = 7;
	
	// ¿ÞÂÊ
	indices[12] = 4; indices[13] =  5; indices[14] = 1;
	indices[15] = 4; indices[16] =  1; indices[17] = 0;

	// ¿À¸¥ÂÊ
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;
	
	// À­¸é
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// ¾Æ·§¸é
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;


	/*Matrix View;
	View.Identity();
	View.LookAt(Vector(-0.5f,0.5,0),Vector(0,0,1),Vector(0,1,0));
	Renderer.SetTransForm(VIEW,View);*/
	Matrix Proj;
	Proj.Identity();
	Proj.PerspectiveFov(3.14f/2.0f, 800.0f/600.0f , 10.0f, 100.0f);
	Renderer.SetTransForm(PROJECTION,Proj);
	Matrix vPort;
	vPort.Identity();
	vPort.ViewPort(0 , 0 , 800 , 600 , 0.0f , 1.0f);
	Renderer.SetTransForm(VIEW_PORT,vPort);
}


void FrameMove(float timeDelta){
	Matrix dy;
	Matrix dx;
	Matrix dz;
	dy.Identity();
	dx.Identity();
	dz.Identity();
	static float Angle = 0.0f;
	dy.RotationY(Angle);
	//dx.RotationX(Angle);
	//dz.RotationZ(Angle);
	Angle+=0.05;

	Renderer.SetTransForm(WORLD,dz*dy*dx);

	static Camera TheCamera(Camera::AIRCRAFT);

	if( ::GetAsyncKeyState(VK_UP) & 0x8000f ){
		TheCamera.pitch(0.00625f * timeDelta);
	}

	if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f ){
		TheCamera.pitch(-0.00625f * timeDelta);
	}

	if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f ){
		TheCamera.roll(0.000625 * timeDelta);
	}

	if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f ){
		TheCamera.roll(-0.000625 * timeDelta);
	}

	if( ::GetAsyncKeyState('Q') & 0x8000f ){
		TheCamera.yaw(-0.000625 * timeDelta);
	}

	if( ::GetAsyncKeyState('E') & 0x8000f ){
		TheCamera.yaw(0.000625 * timeDelta);
	}

	if( ::GetAsyncKeyState('W') & 0x8000f ){
		TheCamera.walk(0.00625f * timeDelta);
	}

	if( ::GetAsyncKeyState('S') & 0x8000f ){
		TheCamera.walk(-0.00625f * timeDelta);
	}

	Renderer.SetTransForm(VIEW,TheCamera.GetViewMatrix());
}

void Render(){
	Renderer.Clear();

	Renderer.DrawLine(v2,indices,36);

	Renderer.Present();
}

void main(){

	WinMain(GetModuleHandle(NULL),NULL,"",SW_SHOW);

	Setup();

	float Start = GetTickCount();

	MSG msg = {0,};
	while( msg.message != WM_QUIT ){

		float End = GetTickCount();

		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ){
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else{
			FrameMove(End - Start);
			Render();
			Start = End;
		}
	}
}