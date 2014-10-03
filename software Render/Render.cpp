#include "Render.h"
#include <stdio.h>
#include <d3dx9.h>

CRender::CRender(){
}
CRender::~CRender(){
}

void CRender::Init(HWND hWnd){
	m_hWnd		= hWnd;
	GetClientRect(hWnd,&m_crt);
	m_hdc		= GetDC(hWnd);
	m_hBit		= CreateCompatibleBitmap(m_hdc,m_crt.right,m_crt.bottom);
	m_hMemDC	= CreateCompatibleDC(m_hdc);
	m_OldBit	= (HBITMAP)SelectObject(m_hMemDC,m_hBit);

	World.	Identity();
	View.	Identity();
	Proj.	Identity();
	vPort.	Identity();
}

void CRender::Clear(){
	FillRect(m_hMemDC,&m_crt,GetSysColorBrush(COLOR_WINDOW));
}

void CRender::DrawLine(/*HDC hdc,*/POINT p1,POINT p2){
	if(m_hdc==NULL)
		return;
	HPEN hPen,OldPen;

	int R,G,B;
	R = 0;//rand()%128 + 127;
	G = 0;//rand()%128 + 127;
	B = 0;//rand()%128 + 127;

	hPen = CreatePen(PS_INSIDEFRAME,2,RGB(R,G,B));
	OldPen = (HPEN)SelectObject(m_hdc,hPen);

	MoveToEx(m_hMemDC,p1.x,p1.y,NULL);
	LineTo(m_hMemDC,p2.x,p2.y);

	DeleteObject(SelectObject(m_hdc,OldPen));
}

void CRender::DrawLine(Vector v1,Vector v2,Vector v3){
	if(m_hdc==NULL)
		return;
	HPEN hPen,OldPen;

	int R,G,B;
	R = 0;//rand()%128 + 127;
	G = 0;//rand()%128 + 127;
	B = 0;//rand()%128 + 127;

	hPen = CreatePen(PS_INSIDEFRAME,2,RGB(R,G,B));
	OldPen = (HPEN)SelectObject(m_hdc,hPen);

	v1 *= World; 
	v1 *= View;
	v1 *= Proj;
	v1 *= 1/v1[3];
	v1 *= vPort;

	v2 *= World; 
	v2 *= View;
	v2 *= Proj;
	v2 *= 1/v2[3];
	v2 *= vPort;
	
	v3 *= World; 
	v3 *= View;
	v3 *= Proj;
	v3 *= 1/v3[3];
	v3 *= vPort;
	
	//printf("--------------------------\n");
	///*for(int i=0;i<4;i++){
	//	for(int j=0;j<4;j++){
	//		printf("%3.4f ",Proj[i][j]);
	//	}
	//	printf("\n\n");
	//}*/
	//printf("RHW: %f %f %f\n",v1[3],v2[3],v3[3]);
	//printf("--------------------------\n\n");


	MoveToEx(m_hMemDC,v1[0],v1[1],NULL);
	LineTo(m_hMemDC,v2[0],v2[1]);
	LineTo(m_hMemDC,v3[0],v3[1]);
	LineTo(m_hMemDC,v1[0],v1[1]);

	printf("-------------------\n");
	printf("%f %f %f\n",v1[0],v1[1],v1[2]);
	printf("%f %f %f\n",v2[0],v2[1],v2[2]);
	printf("%f %f %f\n",v3[0],v3[1],v3[2]);
	printf("-------------------\n");

	DeleteObject(SelectObject(m_hdc,OldPen));
}

void CRender::DrawLine(Vector* v,int number){
	for(int i=0;i<number;i+=3){
		DrawLine(v[i],v[i+1],v[i+2]);
	}
}
void CRender::DrawLine(Vector* v,int* indices,int number){
	for(int i=0;i<number;i+=3){
		DrawLine(v[ indices[i] ],v[ indices[i+1] ],v[ indices[i+2] ]);
	}
}
void CRender::DrawAxis(Vector x,Vector y,Vector z){

	Matrix t;
	t.Identity();
	t *= View;
	t *= Proj;
	t *= vPort;

	x *= t;
	y *= t;
	z *= t;

	Vector a;

	a*= t;

	MoveToEx(m_hMemDC,a[0],a[1],NULL);
	LineTo(m_hMemDC,x[0],x[1]);
	MoveToEx(m_hdc,a[0],a[1],NULL);
	LineTo(m_hMemDC,y[0],y[1]);
	MoveToEx(m_hdc,a[0],a[1],NULL);
	LineTo(m_hMemDC,z[0],z[1]);
}

void CRender::Present(){
	BitBlt(m_hdc,0,0,m_crt.right,m_crt.bottom,m_hMemDC,0,0,SRCCOPY);
}

void CRender::SetTransForm(TRANSFORMSTATE ts,Matrix& m){
	switch(ts){
		case WORLD:
			World = m;
			break;
		case VIEW:
			View = m;
			break;
		case PROJECTION:
			Proj = m;
			break;
		case VIEW_PORT:
			vPort = m;
			break;
	}
}

void CRender::Release(){
	SelectObject(m_hMemDC,m_OldBit);
	DeleteObject((HBITMAP)m_hBit);
	DeleteDC(m_hMemDC);
	ReleaseDC(m_hWnd,m_hdc);
}