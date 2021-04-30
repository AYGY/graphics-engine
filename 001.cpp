// 001.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <atlimage.h>
#include "glew.h"
#include "glut.h"
#include "math.h"
#include <stdio.h>
#include "glVector.h"
#define M_PI 3.14159265358979323846
#pragma comment(lib,"glut32.lib")


float mov[3] = { 0,-5,-20 };
float rot[3] = { 0,0,0 };
float pseta = 0, tseta = 0, seta = 0;
int obj = 0;//操控对象
int m_target = -1;//视角对象
float R = 10;//旋转半径
bool tr = false;
float mx[3] = {0,0,0}, my[3] = { 0,0,0 }, mz[3] = { 0,0,0 }, rx[3] = { 0,0,0 }, ry[3] = { 0,0,0 }, rz[3] = { 0,0,0 };//飞机平移和旋转
float sx=1,sy=1,sz=1;//缩放
float mspeed=0.1,rspeed=5;//平移旋转速度
float speed = 0.01; //自动前进速度
void myDisplay(void);
bool pmove=0, tmove=0;//对象旋转控制
int m_iCameraType = 0;
bool m_bDrawFloor = false;
float delay = 1;
int lastbutton;
float lasttime;

bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraDistanceX=0;
float cameraDistanceY = 0;
float cameraDistanceZ = 0;
float cameraAngleX=0;
float cameraAngleY=0;
float cameraAngleZ = 0;
float times = 1;
bool cameratype = 0;
double m_viewMatrix[16];//视点的变换矩阵
double m_viewMatrixInverse[16];
float p_curmatrix[16];//飞机旋转矩阵
float t_curmatrix[16];//坦克旋转矩阵
float curmatrix[2][16];

CglVector3 m_pos = CglVector3(0, 5, 20);	//视点当前位置
CglVector3 m_hpr;	//视点旋转角度 hrp

unsigned int texture;
GLfloat tx = 0, ty = 1, tz = 1;		//本例子中 sx,sy作为调节贴图位置的变量

double modelviewmatrix[16];
double projectmatrix[16], pos[3];
int viewport[4];

CglVector3 pl_pos;	//视点旋转角度 hrp
CglVector3 tk_pos;	//视点旋转角度 hrp

double InverseMatrix(double imat1[], double mat1[])
{
	double imat[16];
	int i, j, k;
	for (i = 0; i < 16; i++)imat[i] = mat1[i];
	int is[4];
	int js[4];
	double fDet = 1.0f, temp;
	int f = 1;

	for (k = 0; k < 4; k++)
	{
		// 第一步，全选主元
		double fMax = 0.0f;
		for (i = k; i < 4; i++)
		{
			for (j = k; j < 4; j++)
			{
				const double f = fabs(imat[j * 4 + i]);
				if (f > fMax)
				{
					fMax = f;
					is[k] = i;
					js[k] = j;
				}
			}
		}
		if (fabs(fMax) < 1e-15)
			return 0;

		if (is[k] != k)
		{
			f = -f;
			temp = imat[k]; imat[k] = imat[is[k]]; imat[is[k]] = temp;
			temp = imat[4 + k]; imat[4 + k] = imat[4 + is[k]]; imat[4 + is[k]] = temp;
			temp = imat[8 + k]; imat[8 + k] = imat[8 + is[k]]; imat[8 + is[k]] = temp;
			temp = imat[12 + k]; imat[12 + k] = imat[12 + is[k]]; imat[12 + is[k]] = temp;
		}
		if (js[k] != k)
		{
			f = -f;
			temp = imat[k * 4]; imat[k * 4] = imat[js[k] * 4]; imat[js[k] * 4] = temp;
			temp = imat[k * 4 + 1]; imat[k * 4 + 1] = imat[js[k] * 4 + 1]; imat[js[k] * 4 + 1] = temp;
			temp = imat[k * 4 + 2]; imat[k * 4 + 2] = imat[js[k] * 4 + 2]; imat[js[k] * 4 + 2] = temp;
			temp = imat[k * 4 + 3]; imat[k * 4 + 3] = imat[js[k] * 4 + 3]; imat[js[k] * 4 + 3] = temp;
		}

		// 计算行列值
		fDet *= imat[k * 4 + k];

		// 计算逆矩阵

		// 第二步
		imat[k * 4 + k] = 1.0 / imat[k * 4 + k];
		// 第三步
		for (j = 0; j < 4; j++)
		{
			if (j != k)
				imat[j * 4 + k] *= imat[k * 4 + k];
			//m(k, j) *= m(k, k);
		}
		// 第四步
		for (i = 0; i < 4; i++)
		{
			if (i != k)
			{
				for (j = 0; j < 4; j++)
				{
					if (j != k)
						imat[j * 4 + i] -= imat[k * 4 + i] * imat[j * 4 + k];
					//m(i, j) = m(i, j) - m(i, k) * m(k, j);
				}
			}
		}
		// 第五步
		for (i = 0; i < 4; i++)
		{
			if (i != k)
				imat[k * 4 + i] *= -imat[k * 4 + k];
			//m(i, k) *= -m(k, k);
		}
	}

	for (k = 3; k >= 0; k--)
	{
		if (js[k] != k)
		{
			temp = imat[k]; imat[k] = imat[js[k]]; imat[js[k]] = temp;
			temp = imat[4 + k]; imat[4 + k] = imat[4 + js[k]]; imat[4 + js[k]] = temp;
			temp = imat[8 + k]; imat[8 + k] = imat[8 + js[k]]; imat[8 + js[k]] = temp;
			temp = imat[12 + k]; imat[12 + k] = imat[12 + js[k]]; imat[12 + js[k]] = temp;
		}
		if (is[k] != k)
		{
			temp = imat[k * 4]; imat[k * 4] = imat[is[k] * 4]; imat[is[k] * 4] = temp;
			temp = imat[1 + k * 4]; imat[1 + k * 4] = imat[1 + is[k] * 4]; imat[1 + is[k] * 4] = temp;
			temp = imat[2 + k * 4]; imat[2 + k * 4] = imat[2 + is[k] * 4]; imat[2 + is[k] * 4] = temp;
			temp = imat[3 + k * 4]; imat[3 + k * 4] = imat[3 + is[k] * 4]; imat[3 + is[k] * 4] = temp;
		}
	}
	for (i = 0; i < 16; i++)
		imat1[i] = imat[i];
	return fDet * f;
}
void Rotate(int dir, double len)
{
	if (cameratype == 0)
	{
		m_hpr.Add(dir, len);
		glPushMatrix();
		glLoadIdentity();
		glRotated(-m_hpr[2], 0, 0, 1);
		glRotated(-m_hpr[1], 1, 0, 0);
		glRotated(-m_hpr[0], 0, 1, 0);
		glTranslated(-m_pos.x, -m_pos.y, -m_pos.z);
		glGetDoublev(GL_MODELVIEW_MATRIX, m_viewMatrix);
		InverseMatrix(m_viewMatrixInverse, m_viewMatrix);
		glPopMatrix();
	}
	else if (cameratype == 1)
	{

		CglVector3 Rotdir;
		if (cameratype == 0)
		{
			if (dir == 0)	Rotdir.Set(0, 1, 0);
			else if (dir == 1) Rotdir.Set(1, 0, 0);
			else Rotdir.Set(0, 0, 1);
		}
		else
		{
			if (dir == 0)	//绕地球垂线运动
			{
				Rotdir = m_pos;
				Rotdir.Normalize();
			}
			else if (dir == 1) Rotdir.Set(1, 0, 0);
			else
			{
				Rotdir.Set(0, 0, 1);
			}
		}
		Rotdir = -Rotdir;
		glPushMatrix();
		glLoadIdentity();
		glRotated(len, Rotdir.x, Rotdir.y, Rotdir.z);
		glMultMatrixd(m_viewMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX, m_viewMatrix);
		InverseMatrix(m_viewMatrixInverse, m_viewMatrix);
		glPopMatrix();
	}
}
void Move(int dir, double len)
{
	CglVector3 vec(&m_viewMatrixInverse[4 * dir]);
	vec = vec * len;
	if (cameratype == 0)
	{
		m_pos += vec;
		glPushMatrix();
		glLoadIdentity();
		glRotated(-m_hpr.y, 1, 0, 0);
		glRotated(-m_hpr.x, 0, 1, 0);
		glRotated(-m_hpr.z, 0, 0, 1);
		glTranslated(-m_pos.x, -m_pos.y, -m_pos.z);
		glGetDoublev(GL_MODELVIEW_MATRIX, m_viewMatrix);
		InverseMatrix(m_viewMatrixInverse, m_viewMatrix);
		glPopMatrix();
	}
	else if (cameratype == 1)
	{
		m_pos += vec;
		glPushMatrix();
		glLoadIdentity();
		glMultMatrixd(m_viewMatrix);
		glTranslated(-vec.x, -vec.y, -vec.z);
		glGetDoublev(GL_MODELVIEW_MATRIX, m_viewMatrix);
		InverseMatrix(m_viewMatrixInverse, m_viewMatrix);
		glPopMatrix();
	}
}
int LoadGLTextures()								// Load Bitmaps And Convert To Textures
{
	CImage img;
	HRESULT hResult = img.Load("2.bmp");
	if (FAILED(hResult))
	{
		return 0;
	}
	glGenTextures(1, &texture);					// Create The Texture
	glBindTexture(GL_TEXTURE_2D, texture);
	// Generate The Texture
	int pitch = img.GetPitch();
	if (pitch < 0)
		gluBuild2DMipmaps(GL_TEXTURE_2D, img.GetBPP() / 8, img.GetWidth(), img.GetHeight(), GL_BGR, GL_UNSIGNED_BYTE, img.GetPixelAddress(0, img.GetHeight() - 1));
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, img.GetBPP() / 8, img.GetWidth(), img.GetHeight(), GL_BGR, GL_UNSIGNED_BYTE, img.GetBits());
	//filter 参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// Linear Filteringd
																					//glDisable(GL_CULL_FACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);	//颜色直接相乘
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//
																//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_BLEND);
	float col[4] = { 1,1,1 };
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, col);	//颜色直接相乘
	return TRUE;
}
void myTimerFunc(int val)
{
	seta += 0.5;
	myDisplay();
	glutTimerFunc(1,myTimerFunc,1);
}
void p_currentmatrix() {
	glPushMatrix();
	glLoadIdentity();
	glRotated(ry[1], 0, 1, 0);
	glRotatef(pseta, 0, 1, 0);
	glRotated(rz[1], 0, 0, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, curmatrix[0]);
	glPopMatrix();
}
void t_currentmatrix() {
	glPushMatrix();
	glLoadIdentity();
	glRotated(ry[2], 0, 1, 0);
	glRotatef(tseta, 0, 1, 0);
	glRotated(rz[2], 0, 0, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, curmatrix[1]);
	glPopMatrix();
}
void currentmatrix() {
	if (obj == 1)
	{
		p_currentmatrix();
	}
	if (obj == 2)
	{
		t_currentmatrix();
	}
	
}
void myKeyboardFunc(unsigned char key,int x, int y)
{
	if (key == 'a')
	{
		mx[obj] -= mspeed * curmatrix[obj-1][8];
		my[obj] -= mspeed * curmatrix[obj - 1][9];
		mz[obj] -= mspeed * curmatrix[obj - 1][10];
		
	}
	else if (key == 'd')
	{
		mx[obj] += mspeed * curmatrix[obj - 1][8];
		my[obj] += mspeed * curmatrix[obj - 1][9];
		mz[obj] += mspeed * curmatrix[obj - 1][10];
	}
	else if (key == 'w')
	{
		mx[obj] += mspeed * curmatrix[obj - 1][4];
		my[obj] += mspeed * curmatrix[obj - 1][5];
		mz[obj] += mspeed * curmatrix[obj - 1][6];
	}
	else if (key == 's')
	{
		mx[obj] -= mspeed * curmatrix[obj - 1][4];
		my[obj] -= mspeed * curmatrix[obj - 1][5];
		mz[obj] -= mspeed * curmatrix[obj - 1][6];
	}
	else if (key == 'q')
	{
		mx[obj] += mspeed * curmatrix[obj - 1][0];
		my[obj] += mspeed * curmatrix[obj - 1][1];
		mz[obj] += mspeed * curmatrix[obj - 1][2];
	}
	else if (key == 'e')
	{
		mx[obj] -= mspeed * curmatrix[obj - 1][0];
		my[obj] -= mspeed * curmatrix[obj - 1][1];
		mz[obj] -= mspeed * curmatrix[obj - 1][2];
	}
	else if (key == 'j')
	{
		ry[obj] += mspeed;
		currentmatrix();
		if (m_target == obj-1)
		{
			m_hpr.x += mspeed;
		}
	}
	else if (key == 'l')
	{
		ry[obj] -= mspeed;
		currentmatrix();
		if (m_target == obj - 1)
		{
			m_hpr.x -= mspeed;
		}
	}
	else if (key == 'i')
	{
		rz[obj] += mspeed;
		currentmatrix();
		if (m_target == obj - 1)
		{
			m_hpr.y += mspeed;
		}
	}
	else if (key == 'k')
	{
		rz[obj] -= mspeed;
		currentmatrix();
		if (m_target == obj - 1)
		{
			m_hpr.y -= mspeed;
		}
	}
	else if (key == '1')
	{
		obj = 1;
		currentmatrix();

	}
	else if (key == '2')
	{
		obj = 2;
		currentmatrix();
	}
	else if (key == 13)
	{
		tr = !tr;
	}
}
void SpecialKey(GLint key, GLint x, GLint y)
{
	if (key == GLUT_KEY_F1)
	{
		pmove = !pmove;
	}
	else if (key == GLUT_KEY_F2)
	{
		tmove = !tmove;
	}
}
CglMatrix MakeRotate(double seta, int axis)
{
	CglMatrix mat;
	mat.SetRotate(seta, axis);
	return mat;
}
void SetCamera(double* pdpos, double* pddir)//直接设置相机位置
{
	CglVector3 pos(pdpos), dir(pddir);
	CglMatrix mat;
	m_pos = pos;
	m_hpr = dir;
	m_hpr.EulerToRad();
	//得到当前矩阵
	Rotate(1,0);
}
void SetView()
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(mov[0], mov[1], mov[2]);
	glGetDoublev(GL_MODELVIEW_MATRIX, m_viewMatrix);
	glPopMatrix();
}
void SetRC()
{
	
	SetView();
	glLineWidth(3);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_BACK, GL_LINE);
	LoadGLTextures();

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}
void SetLight()
{
	//	GLfloat amb[4]={0.4,0.4,0.4,1};
	GLfloat amb[4] = { 1,1,1,1 };
	GLfloat dif[4] = { 1,1,1,1 };
	GLfloat spe[4] = { 0.2f,0.2f,0.2f,1 };
	GLfloat pos[4] = { 30,0,0,1 };
	glPushMatrix();
	glRotatef(seta, 1, 1, 1);
	glTranslatef(pos[0], pos[1], pos[2]);
	glColor3f(1, 0, 0);
	glutSolidSphere(0.1f, 10, 10);

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spe);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void normalize(GLfloat* v)
{
	GLfloat dis = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (dis > 0)
	{
		v[0] /= dis;
		v[1] /= dis;
		v[2] /= dis;
	}
}
void RenderAxis()//绘制坐标轴
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100);
	glEnd();
}
void RenderLightBall()	//绘制光源
{
	glPushMatrix();
	glRotatef(seta, 1, 1, 1);
	glTranslatef(50, 0, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.5, 20, 20);
	float pos[4] = { 0,0,0,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glPopMatrix();
}
void DrawPlane() {
	glFrontFace(GL_CW);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glPushMatrix();
	glTranslatef(0, 10, 0);
	if (pmove)
	{
		pseta += 0.1;
		if (m_target == 0)
		{
			m_hpr.x += 0.1;
		}
		p_currentmatrix();
	}
	glTranslatef(R * sin(pseta * M_PI / 180), 0, -(R - R * cos(pseta * M_PI / 180)));
	glTranslatef(mx[1], my[1], mz[1]);
	glRotated(ry[1], -sin(rz[1] * M_PI / 180), cos(rz[1] * M_PI / 180), 0);
	glRotatef(pseta, -sin(rz[1] * M_PI / 180), cos(rz[1] * M_PI / 180), 0);
	glRotated(rz[1], 0, 0, 1);
	glTranslated(-1, 0, 0);
	//绘制飞机
	glPushMatrix();
	glScalef(4, 1, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2, 0, 0);
	glRotatef(45, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(1, 2, 4, 4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1, 0, 0);
	//glRotatef(45, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScaled(8, 1, 1);
	glutSolidCone(0.5, 2, 4, 4);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
}
void Drawtank() {
	glFrontFace(GL_CW);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glPushMatrix();
	if (tmove)
	{
		tseta += 0.1;
		if (m_target == 1)
		{
			m_hpr.x += 0.1;
		}
		t_currentmatrix();
		
	}
	glTranslatef(R * sin(tseta * M_PI / 180), 0, -(R - R * cos(tseta * M_PI / 180)));
	glTranslatef(mx[2], my[2], mz[2]);
	glRotated(ry[2], -sin(rz[2] * M_PI / 180), cos(rz[2] * M_PI / 180), 0);
	glRotatef(tseta, -sin(rz[2] * M_PI / 180), cos(rz[2] * M_PI / 180), 0);
	glRotated(rz[2], 0, 0, 1);
	//绘制坦克
	glPushMatrix();
	glScaled(1, 0.5, 1);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2, 2, 0);
	glScaled(2, 1, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
}
void RenderWorld()
{
	RenderAxis();
	//设置光源属性
	SetLight();
	//设置材质属性
	GLfloat amb[4] = { 0.4f,0.4f,0.4f,1 };
	GLfloat dif[4] = { 1,1,1,1 };
	GLfloat spe[4] = { 0.1f,0.1f,0.1f,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_LIGHTING);
	if (tr == true)
	{
		mx[obj] += mspeed*0.1* curmatrix[obj - 1][0];
		my[obj] += mspeed * 0.1 * curmatrix[obj - 1][1];
		mz[obj] += mspeed * 0.1 * curmatrix[obj - 1][2];
	}
	DrawPlane();
	Drawtank();
	pl_pos = CglVector3(mx[1] + R * sin(pseta * M_PI / 180), my[1] + 10, mz[1] - (R - R * cos(pseta * M_PI / 180)));
	tk_pos = CglVector3(mx[2] + R * sin(tseta * M_PI / 180), my[2] + 1, mz[2] - (R - R * cos(tseta * M_PI / 180)));
	
	if (m_target == 0)
	{
		CglVector3 pos = pl_pos + CglVector3(0, 2, 0);
		CglVector3 dir = m_hpr;
		dir.EulerToAng();
		SetCamera(pos, dir, FALSE);
	}
	else if (m_target == 1)
	{
		CglVector3 pos = tk_pos + CglVector3(0, 3, 0);
		CglVector3 dir = m_hpr;
		dir.EulerToAng();
		SetCamera(pos, dir, FALSE);
	}
}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	glLoadMatrixd(m_viewMatrix);
	RenderWorld();
	
	glPopMatrix();
	glutSwapBuffers();
}
void myReshape(int w,int h)
{	
	GLfloat nRange = 100.0f;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,GLfloat(w)/h,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void mouseCB(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	times = 1;
	
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;
		}
		else if (state == GLUT_UP)
		{
			mouseLeftDown = false;
			time_t tv;
			tv = GetTickCount();
			if (tv - lasttime < 200 && lastbutton == GLUT_LEFT_BUTTON)
			{
				glGetDoublev(GL_PROJECTION_MATRIX, projectmatrix);
				glGetIntegerv(GL_VIEWPORT, viewport);
				float val;
				y = viewport[3] - y;
				glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &val);
				gluUnProject(x, y, val, m_viewMatrix, projectmatrix, viewport, &pos[0], &pos[1], &pos[2]);
				if (pow(pos[0] - pl_pos.x,2) + pow(pos[1] - pl_pos.y,2) + pow(pos[2] - pl_pos.z,2) < 9)
				{
					m_target = 0;
					CglVector3 pos = pl_pos + CglVector3(0, 2, 0);
					CglVector3 dir = m_hpr;
					dir.EulerToAng();
					dir.x = ry[1];
					SetCamera(pos, dir, FALSE);
					Rotate(0, -90);
				}
				else if (pow(pos[0] - tk_pos.x, 2) + pow(pos[1] - tk_pos.y, 2) + pow(pos[2] - tk_pos.z, 2) < 9)
				{
					m_target = 1;
					CglVector3 pos = tk_pos + CglVector3(0, 2, 0);
					CglVector3 dir = m_hpr;
					dir.EulerToAng();
					dir.x = ry[2];
					SetCamera(pos, dir, FALSE);
					Rotate(0, -90);
				}
				else
				{
					m_target = -1;
				}
				lasttime = 0;
				lastbutton = 0;
			}
			else
			{
				lasttime = tv;
				lastbutton = button;
			}
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseRightDown = true;
		}
		else if (state == GLUT_UP)
		{
			mouseRightDown = false;
			time_t tv;
			tv = GetTickCount();
			if (tv - lasttime < 200 && lastbutton == GLUT_RIGHT_BUTTON)
			{
				cameratype = !cameratype;
				lasttime = 0;
				lastbutton = 0;
			}
			else
			{
				lasttime = tv;
				lastbutton = button;
			}
		}
	}
}
void mouseMotionCB(int x, int y)
{
	cameraAngleX = cameraAngleY = 0;
	cameraDistanceX = cameraDistanceY = 0;
	cameraDistanceZ = 0;
	if (mouseLeftDown&&!mouseRightDown)
	{
		cameraAngleX += (x - mouseX) * 0.1f;
		cameraAngleY += (y - mouseY) * 0.1f;
		mouseX = x;
		mouseY = y;
		Rotate(0, -cameraAngleX);
		Rotate(1, -cameraAngleY);
	}
	if (mouseRightDown && !mouseLeftDown)
	{
		cameraDistanceX += (x - mouseX) * 0.1f;
		cameraDistanceY += -(y - mouseY) * 0.1f;
		mouseY = y;
		mouseX = x;
		Move(0, cameraDistanceX);
		Move(1, cameraDistanceY);
	}
	if (mouseRightDown&&mouseLeftDown)
	{
		cameraDistanceZ += -(y - mouseY) * 0.1f;
		mouseY = y;
		Move(2, -cameraDistanceZ);
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("第一个OpenGL程序");
	
    glutDisplayFunc(&myDisplay);
	glutTimerFunc(1,myTimerFunc,0);
	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(&myKeyboardFunc);
	glutSpecialFunc(&SpecialKey);
	glutMouseFunc(mouseCB);
	glutMotionFunc(mouseMotionCB);
	SetRC();
    glutMainLoop();
    return 0;
}