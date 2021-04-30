#if !defined(AFX_CglVector3_H)
#define AFX_CglVector3_H
#pragma once

#include "math.h"

#define PAI (3.14159)
//弧度转角度
#define RadToAng(x) ((x)/PAI*180)
//角度转弧度
#define AngToRad(x) ((x)/180.0*PAI)


class  CglVector3
{
public:
	CglVector3(void) { x = 0; y = 0; z = 0; };
	CglVector3(double fx, double fy, double fz)
	{
		x = fx; y = fy; z = fz;
	}

	CglVector3(float* pos)
	{
		x = pos[0];
		y = pos[1];
		z = pos[2];
	}
	CglVector3(double* pos)
	{
		x = pos[0];
		y = pos[1];
		z = pos[2];
	}
	void Set(double fx, double fy, double fz)
	{
		x = fx; y = fy; z = fz;
	}
	void Set(float* pos)
	{
		x = pos[0];
		y = pos[1];
		z = pos[2];
	}
	void Set(double* pos)
	{
		x = pos[0];
		y = pos[1];
		z = pos[2];
	}
	void Get(double* pos)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}
	void Get(float* pos)
	{
		pos[0] = float(x);
		pos[1] = float(y);
		pos[2] = float(z);
	}
public:
	~CglVector3(void) {};
public:
	double x, y, z;
	operator double* ()
	{
		return &x;
	}
	operator const double* () const
	{
		return &x;
	}
	CglVector3& operator=(const CglVector3& p)
	{
		x = p.x; y = p.y; z = p.z;
		return *this;
	}
	CglVector3 operator+(const CglVector3& p) const
	{
		CglVector3 vec;
		vec.x = x + p.x;
		vec.y = y + p.y;
		vec.z = z + p.z;
		return vec;
	}
	CglVector3& operator+=(const CglVector3& p)
	{
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}
	CglVector3& operator-=(const CglVector3& p)
	{
		x -= p.x;
		y -= p.y;
		z -= p.z;
		return *this;
	}
	CglVector3 operator-(const CglVector3& p) const
	{
		CglVector3 vec;
		vec.x = x - p.x;
		vec.y = y - p.y;
		vec.z = z - p.z;
		return vec;
	}
	CglVector3 operator-() const
	{
		CglVector3 vec;
		vec.x = -x;
		vec.y = -y;
		vec.z = -z;
		return vec;
	}
	CglVector3 operator*(double data) const
	{
		CglVector3 vec;
		vec.x = x * data;
		vec.y = y * data;
		vec.z = z * data;
		return vec;
	}
	friend CglVector3 operator*(double data, const CglVector3& p)
	{
		CglVector3 vec;
		vec.x = p.x * data;
		vec.y = p.y * data;
		vec.z = p.z * data;
		return vec;
	}
	CglVector3 operator*(float* mat) const
	{
		int i;
		double v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i * 4] * x + mat[1 + i * 4] * y + mat[2 + i * 4] * z + mat[3 + i * 4];
		}
		CglVector3 vec;
		for (i = 0; i < 3; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	friend CglVector3 operator*(float* mat, const CglVector3& p)
	{
		int i;
		double v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i] * p.x + mat[4 + i] * p.y + mat[8 + i] * p.z + mat[12 + i];
		}
		CglVector3 vec;
		vec.x = v[0] / v[3];
		vec.y = v[1] / v[3];
		vec.z = v[2] / v[3];
		return vec;
	}
	CglVector3 operator*(double* mat) const
	{
		int i;
		double v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i * 4] * x + mat[1 + i * 4] * y + mat[2 + i * 4] * z + mat[3 + i * 4];
		}
		CglVector3 vec;
		for (i = 0; i < 3; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	friend CglVector3 operator*(double* mat, const CglVector3& p)
	{
		int i;
		double v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i] * p.x + mat[4 + i] * p.y + mat[8 + i] * p.z + mat[12 + i];
		}
		CglVector3 vec;
		vec.x = float(v[0] / v[3]);
		vec.y = float(v[1] / v[3]);
		vec.z = float(v[2] / v[3]);
		return vec;
	}
	CglVector3 operator/(double data) const
	{
		CglVector3 vec;
		vec.x = x / data;
		vec.y = y / data;
		vec.z = z / data;
		return vec;
	}
	double dotMul(const CglVector3& p)
	{
		return x * p.x + y * p.y + z * p.z;
	}
	CglVector3 crossMul(const CglVector3& p) const
	{
		CglVector3 vec;
		vec.x = y * p.z - z * p.y;
		vec.y = z * p.x - x * p.z;
		vec.z = x * p.y - y * p.x;
		return vec;
	}
	double len()
	{
		return sqrt(x * x + y * y + z * z);
	}
	void EulerToAng()
	{
		x = RadToAng(x);	//h
		y = RadToAng(y);	//p
		z = RadToAng(z);	//r
	}
	void EulerToRad()
	{
		x = AngToRad(x);	//h
		y = AngToRad(y);	//p
		z = AngToRad(z);	//r
	}
	void Normalize()
	{
		double l = len();
		x /= l;
		y /= l;
		z /= l;
	}
	void Add(int addr, double val)
	{
		if (addr == 0)
			x += val;
		else if (addr == 1)
			y += val;
		else if (addr == 2)
			z += val;
	}
	void Rotate(double seta, int axis)//绕某个轴旋转seta角度,弧度角
	{
		switch (axis)
		{
		case 0://X 轴
		{
			double y1 = y * cos(seta) - z * sin(seta);
			z = y * sin(seta) + z * cos(seta);
			y = y1;
		}
		break;
		case 1://Y 轴
		{
			double x1 = x * cos(seta) + z * sin(seta);
			z = -x * sin(seta) + z * cos(seta);
			x = x1;
		}
		break;
		case 2://Y 轴
		{
			double x1 = x * cos(seta) - y * sin(seta);
			y = x * sin(seta) + y * cos(seta);
			x = x1;
		}
		break;
		}
	}
	void Rotate(double seta, double x, double y, double z)//绕某个方向转seta角度,弧度角
	{
		double dis1 = x * x + z * z;
		double dis2 = dis1 + y * y;
		dis1 = sqrt(dis1);
		dis2 = sqrt(dis2);
		//先绕x轴转，使轴转动到XOZ平面上,角度为xyz与XOZ夹角
		double setax = acos(dis1 / dis2);
		if (y < 0) setax = -setax;
		Rotate(setax, 0);
		//再绕y轴转，使轴转动到Z轴重合位置,角度为xyz投影与z轴夹角
		double setay = acos(z / dis1);
		if (x > 0) setay = -setay;
		Rotate(setay, 1);
		//开始绕z轴转
		Rotate(seta, 2);
		//////////////////////////////////////////////////////////////////////////恢复
		//绕y转回来。
		Rotate(-setay, 1);
		//绕x转回来。
		Rotate(-setax, 0);
	}
};


class CglVectorFloat3
{
public:
	CglVectorFloat3(void) { x = 0; y = 0; z = 0; };
	CglVectorFloat3(float fx, float fy, float fz)
	{
		x = fx; y = fy; z = fz;
	}

	CglVectorFloat3(float* pos)
	{
		x = pos[0];
		y = pos[1];
		z = pos[2];
	}
	CglVectorFloat3(double* pos)
	{
		x = (float)pos[0];
		y = (float)pos[1];
		z = (float)pos[2];
	}
	void Set(float fx, float fy, float fz)
	{
		x = fx; y = fy; z = fz;
	}
	void Set(float* pos)
	{
		x = pos[0];
		y = pos[1];
		z = pos[2];
	}
	void Set(double* pos)
	{
		x = (float)pos[0];
		y = (float)pos[1];
		z = (float)pos[2];
	}
	void Get(double* pos)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}
	void Get(float* pos)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}
public:
	~CglVectorFloat3(void) {};
public:
	float x, y, z;
	operator float* ()
	{
		return &x;
	}
	operator const float* () const
	{
		return &x;
	}
	CglVectorFloat3& operator=(const CglVectorFloat3& p)
	{
		x = p.x; y = p.y; z = p.z;
		return *this;
	}
	CglVectorFloat3 operator+(const CglVectorFloat3& p) const
	{
		CglVectorFloat3 vec;
		vec.x = x + p.x;
		vec.y = y + p.y;
		vec.z = z + p.z;
		return vec;
	}
	CglVectorFloat3& operator+=(const CglVectorFloat3& p)
	{
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}
	CglVectorFloat3& operator-=(const CglVectorFloat3& p)
	{
		x -= p.x;
		y -= p.y;
		z -= p.z;
		return *this;
	}
	CglVectorFloat3 operator-(const CglVectorFloat3& p) const
	{
		CglVectorFloat3 vec;
		vec.x = x - p.x;
		vec.y = y - p.y;
		vec.z = z - p.z;
		return vec;
	}
	CglVectorFloat3 operator-() const
	{
		CglVectorFloat3 vec;
		vec.x = -x;
		vec.y = -y;
		vec.z = -z;
		return vec;
	}
	CglVectorFloat3 operator*(float data) const
	{
		CglVectorFloat3 vec;
		vec.x = x * data;
		vec.y = y * data;
		vec.z = z * data;
		return vec;
	}
	friend CglVectorFloat3 operator*(float data, const CglVectorFloat3& p)
	{
		CglVectorFloat3 vec;
		vec.x = p.x * data;
		vec.y = p.y * data;
		vec.z = p.z * data;
		return vec;
	}
	CglVectorFloat3 operator*(float* mat) const
	{
		int i;
		float v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i * 4] * x + mat[1 + i * 4] * y + mat[2 + i * 4] * z + mat[3 + i * 4];
		}
		CglVectorFloat3 vec;
		for (i = 0; i < 3; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	friend CglVectorFloat3 operator*(float* mat, const CglVectorFloat3& p)
	{
		int i;
		float v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i] * p.x + mat[4 + i] * p.y + mat[8 + i] * p.z + mat[12 + i];
		}
		CglVectorFloat3 vec;
		vec.x = v[0] / v[3];
		vec.y = v[1] / v[3];
		vec.z = v[2] / v[3];
		return vec;
	}
	CglVectorFloat3 operator*(double* mat) const
	{
		int i;
		float v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = float(mat[i * 4] * x + mat[1 + i * 4] * y + mat[2 + i * 4] * z + mat[3 + i * 4]);
		}
		CglVectorFloat3 vec;
		for (i = 0; i < 3; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	friend CglVectorFloat3 operator*(double* mat, const CglVectorFloat3& p)
	{
		int i;
		float v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = float(mat[i] * p.x + mat[4 + i] * p.y + mat[8 + i] * p.z + mat[12 + i]);
		}
		CglVectorFloat3 vec;
		vec.x = float(v[0] / v[3]);
		vec.y = float(v[1] / v[3]);
		vec.z = float(v[2] / v[3]);
		return vec;
	}
	CglVectorFloat3 operator/(float data) const
	{
		CglVectorFloat3 vec;
		vec.x = x / data;
		vec.y = y / data;
		vec.z = z / data;
		return vec;
	}
	double dotMul(const CglVectorFloat3& p)
	{
		return x * p.x + y * p.y + z * p.z;
	}
	CglVectorFloat3 crossMul(const CglVectorFloat3& p) const
	{
		CglVectorFloat3 vec;
		vec.x = y * p.z - z * p.y;
		vec.y = z * p.x - x * p.z;
		vec.z = x * p.y - y * p.x;
		return vec;
	}
	double len()
	{
		return sqrt(x * x + y * y + z * z);
	}
	void Normalize()
	{
		double l = len();
		x = float(x / l);
		y = float(y / l);
		z = float(z / l);
	}
	void Add(int addr, float val)
	{
		if (addr == 0)
			x += val;
		else if (addr == 1)
			y += val;
		else if (addr == 2)
			z += val;
	}
	void Rotate(double seta, int axis)//绕某个轴旋转seta角度,弧度角
	{
		switch (axis)
		{
		case 0://X 轴
		{
			double y1 = y * cos(seta) - z * sin(seta);
			z = float(y * sin(seta) + z * cos(seta));
			y = float(y1);
		}
		break;
		case 1://Y 轴
		{
			double x1 = x * cos(seta) + z * sin(seta);
			z = float(-x * sin(seta) + z * cos(seta));
			x = float(x1);
		}
		break;
		case 2://Y 轴
		{
			double x1 = x * cos(seta) - y * sin(seta);
			y = float(x * sin(seta) + y * cos(seta));
			x = float(x1);
		}
		break;
		}
	}
	void Rotate(double seta, double x, double y, double z)//绕某个方向转seta角度,弧度角
	{
		double dis1 = x * x + z * z;
		double dis2 = dis1 + y * y;
		dis1 = sqrt(dis1);
		dis2 = sqrt(dis2);
		//先绕x轴转，使轴转动到XOZ平面上,角度为xyz与XOZ夹角
		double setax = acos(dis1 / dis2);
		if (y < 0) setax = -setax;
		Rotate(setax, 0);
		//再绕y轴转，使轴转动到Z轴重合位置,角度为xyz投影与z轴夹角
		double setay = acos(z / dis1);
		if (x > 0) setay = -setay;
		Rotate(setay, 1);
		//开始绕z轴转
		Rotate(seta, 2);
		//////////////////////////////////////////////////////////////////////////恢复
		//绕y转回来。
		Rotate(-setay, 1);
		//绕x转回来。
		Rotate(-setax, 0);
	}
};


class CglVector4
{
public:
	CglVector4(void) { x = 0; y = 0; z = 0; w = 1; };
	CglVector4(double fx, double fy, double fz, double fw)
	{
		x = fx; y = fy; z = fz; w = fw;
	}
	void Set(double fx, double fy, double fz, double fw)
	{
		x = fx; y = fy; z = fz; w = fw;
	}
	void Set(const CglVector3& p, double fw)
	{
		x = p.x; y = p.y; z = p.z; w = fw;
	}

public:
	~CglVector4(void) {};
public:
	double x, y, z, w;
	operator double* ()
	{
		return &x;
	}
	operator const double* () const
	{
		return &x;
	}
	CglVector4& operator=(const CglVector4& p)
	{
		x = p.x; y = p.y; z = p.z; w = p.w;
		return *this;
	}
	CglVector4& operator=(const CglVector3& p)
	{
		x = p.x; y = p.y; z = p.z; w = 1;
		return *this;
	}
	CglVector4 operator+(const CglVector4& p) const
	{
		CglVector4 vec;
		vec.x = x + p.x;
		vec.y = y + p.y;
		vec.z = z + p.z;
		vec.w = w + p.w;
		return vec;
	}
	CglVector4& operator+=(const CglVector4& p)
	{
		x += p.x;
		y += p.y;
		z += p.z;
		w += p.w;
		return *this;
	}
	CglVector4& operator-=(const CglVector4& p)
	{
		x -= p.x;
		y -= p.y;
		z -= p.z;
		w -= p.w;
		return *this;
	}
	CglVector4 operator-(const CglVector4& p) const
	{
		CglVector4 vec;
		vec.x = x - p.x;
		vec.y = y - p.y;
		vec.z = z - p.z;
		vec.w = w - p.w;
		return vec;
	}
	CglVector4 operator-() const
	{
		CglVector4 vec;
		vec.x = -x;
		vec.y = -y;
		vec.z = -z;
		vec.w = -w;
		return vec;
	}
	CglVector4 operator*(double data) const
	{
		CglVector4 vec;
		vec.x = x * data;
		vec.y = y * data;
		vec.z = z * data;
		vec.w = w * data;
		return vec;
	}
	friend CglVector4 operator*(double data, const CglVector4& p)
	{
		CglVector4 vec;
		vec.x = p.x * data;
		vec.y = p.y * data;
		vec.z = p.z * data;
		vec.w = p.w * data;
		return vec;
	}
	CglVector4 operator*(float* mat) const
	{
		int i;
		double v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i * 4] * x + mat[1 + i * 4] * y + mat[2 + i * 4] * z + mat[3 + i * 4] * w;
		}
		CglVector4 vec;
		for (i = 0; i < 4; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	friend CglVector4 operator*(float* mat, const CglVector4& p)
	{
		int i;
		double v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i] * p.x + mat[4 + i] * p.y + mat[8 + i] * p.z + mat[12 + i] * p.w;
		}
		CglVector4 vec;
		for (i = 0; i < 4; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	CglVector4 operator*(double* mat) const
	{
		int i;
		double v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i * 4] * x + mat[1 + i * 4] * y + mat[2 + i * 4] * z + mat[3 + i * 4] * w;
		}
		CglVector4 vec;
		for (i = 0; i < 4; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	friend CglVector4 operator*(double* mat, const CglVector4& p)
	{
		int i;
		double v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i] * p.x + mat[4 + i] * p.y + mat[8 + i] * p.z + mat[12 + i] * p.w;
		}
		CglVector4 vec;
		for (i = 0; i < 4; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	void Normalize()
	{
		x /= w;
		y /= w;
		z /= w;
		w = 1;
	}
};


class CglVectorFloat4
{
public:
	CglVectorFloat4(void) { x = 0; y = 0; z = 0; w = 1; };
	CglVectorFloat4(float fx, float fy, float fz, float fw)
	{
		x = fx; y = fy; z = fz; w = fw;
	}
	void Set(float fx, float fy, float fz, float fw)
	{
		x = fx; y = fy; z = fz; w = fw;
	}
	void Set(const CglVectorFloat3& p, float fw)
	{
		x = p.x; y = p.y; z = p.z; w = fw;
	}

public:
	~CglVectorFloat4(void) {};
public:
	float x, y, z, w;
	operator float* ()
	{
		return &x;
	}
	operator const float* () const
	{
		return &x;
	}
	CglVectorFloat4& operator=(const CglVectorFloat4& p)
	{
		x = p.x; y = p.y; z = p.z; w = p.w;
		return *this;
	}
	CglVectorFloat4& operator=(const CglVectorFloat3& p)
	{
		x = p.x; y = p.y; z = p.z; w = 1;
		return *this;
	}
	CglVectorFloat4 operator*(float* mat) const
	{
		int i;
		float v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i * 4] * x + mat[1 + i * 4] * y + mat[2 + i * 4] * z + mat[3 + i * 4] * w;
		}
		CglVectorFloat4 vec;
		for (i = 0; i < 4; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	friend CglVectorFloat4 operator*(float* mat, const CglVectorFloat4& p)
	{
		int i;
		float v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = mat[i] * p.x + mat[4 + i] * p.y + mat[8 + i] * p.z + mat[12 + i] * p.w;
		}
		CglVectorFloat4 vec;
		for (i = 0; i < 4; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	CglVectorFloat4 operator*(double* mat) const
	{
		int i;
		float v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = float(mat[i * 4] * x + mat[1 + i * 4] * y + mat[2 + i * 4] * z + mat[3 + i * 4] * w);
		}
		CglVectorFloat4 vec;
		for (i = 0; i < 4; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	friend CglVectorFloat4 operator*(double* mat, const CglVectorFloat4& p)
	{
		int i;
		float v[4];
		for (i = 0; i < 4; i++)
		{
			v[i] = float(mat[i] * p.x + mat[4 + i] * p.y + mat[8 + i] * p.z + mat[12 + i] * p.w);
		}
		CglVectorFloat4 vec;
		for (i = 0; i < 4; i++)
			vec[i] = v[i] / v[3];
		return vec;
	}
	void Normalize()
	{
		x /= w;
		y /= w;
		z /= w;
		w = 1;
	}
};


class CglMatrixFloat
{
public:
	CglMatrixFloat(void)
	{
		m00 = 1; m01 = 0; m02 = 0; m03 = 0;
		m10 = 0; m11 = 1; m12 = 0; m13 = 0;
		m20 = 0; m21 = 0; m22 = 1; m23 = 0;
		m30 = 0; m31 = 0; m32 = 0; m33 = 1;
	}
	void Identity()
	{
		m00 = 1; m01 = 0; m02 = 0; m03 = 0;
		m10 = 0; m11 = 1; m12 = 0; m13 = 0;
		m20 = 0; m21 = 0; m22 = 1; m23 = 0;
		m30 = 0; m31 = 0; m32 = 0; m33 = 1;
	}
	void Set(float* p)
	{
		for (int i = 0; i < 16; i++)
			(*this)[i] = p[i];
	}
	void SetRow(int i, CglVectorFloat4& p)
	{
		if (i == 0)
		{
			m00 = p.x; m01 = p.y; m02 = p.z; m03 = p.w;
		}
		if (i == 1)
		{
			m10 = p.x; m11 = p.y; m12 = p.z; m13 = p.w;
		}
		if (i == 2)
		{
			m20 = p.x; m21 = p.y; m22 = p.z; m23 = p.w;
		}
		if (i == 3)
		{
			m30 = p.x; m31 = p.y; m32 = p.z; m33 = p.w;
		}
	}
	void SetCol(int i, CglVectorFloat4& p)
	{
		if (i == 0)
		{
			m00 = p.x; m10 = p.y; m20 = p.z; m30 = p.w;
		}
		if (i == 1)
		{
			m01 = p.x; m11 = p.y; m21 = p.z; m31 = p.w;
		}
		if (i == 2)
		{
			m02 = p.x; m12 = p.y; m22 = p.z; m32 = p.w;
		}
		if (i == 3)
		{
			m03 = p.x; m13 = p.y; m23 = p.z; m33 = p.w;
		}
	}
	void SetRow(int i, CglVectorFloat3& p)
	{
		if (i == 0)
		{
			m00 = p.x; m01 = p.y; m02 = p.z; m03 = 1;
		}
		if (i == 1)
		{
			m10 = p.x; m11 = p.y; m12 = p.z; m13 = 1;
		}
		if (i == 2)
		{
			m20 = p.x; m21 = p.y; m22 = p.z; m23 = 1;
		}
		if (i == 3)
		{
			m30 = p.x; m31 = p.y; m32 = p.z; m33 = 1;
		}
	}
	void SetCol(int i, CglVectorFloat3& p)
	{
		if (i == 0)
		{
			m00 = p.x; m10 = p.y; m20 = p.z; m30 = 1;
		}
		if (i == 1)
		{
			m01 = p.x; m11 = p.y; m21 = p.z; m31 = 1;
		}
		if (i == 2)
		{
			m02 = p.x; m12 = p.y; m22 = p.z; m32 = 1;
		}
		if (i == 3)
		{
			m03 = p.x; m13 = p.y; m23 = p.z; m33 = 1;
		}
	}

public:
	~CglMatrixFloat(void) {};
public:
	//	m00	m01	m02	m03
	//	m10	m11	m12	m13
	//	m20	m21	m22	m23
	//	m30	m31	m32	m33
	float m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33;
	operator float* ()
	{
		return &m00;
	}
	operator const float* () const
	{
		return &m00;
	}
	CglMatrixFloat& operator=(const CglMatrixFloat& p)
	{
		for (int i = 0; i < 16; i++)
			(*this)[i] = p[i];
		return *this;
	}
};


class CglMatrix
{
public:
	CglMatrix(void)
	{
		m00 = 1; m01 = 0; m02 = 0; m03 = 0;
		m10 = 0; m11 = 1; m12 = 0; m13 = 0;
		m20 = 0; m21 = 0; m22 = 1; m23 = 0;
		m30 = 0; m31 = 0; m32 = 0; m33 = 1;
	}
	void Identity()
	{
		m00 = 1; m01 = 0; m02 = 0; m03 = 0;
		m10 = 0; m11 = 1; m12 = 0; m13 = 0;
		m20 = 0; m21 = 0; m22 = 1; m23 = 0;
		m30 = 0; m31 = 0; m32 = 0; m33 = 1;
	}
	void Set(double* p)
	{
		for (int i = 0; i < 16; i++)
			(*this)[i] = p[i];
	}
	CglMatrix MakeRotate(double seta, int axis)
	{
		CglMatrix mat;
		mat.SetRotate(seta, axis);
		return mat;
	}//直接获得一个旋转矩阵	弧度制
	CglMatrix& SetRotate(double seta, int axis)	//设置为旋转矩阵	//绕nx,ny,nz方向seta弧度的矩阵
	{
		double c = cos(seta);
		double s = sin(seta);
		if (axis == 0)
		{
			m00 = 1; m01 = 0; m02 = 0; m03 = 0;
			m10 = 0; m11 = c; m12 = -s; m13 = 0;
			m20 = 0; m21 = s; m22 = c; m23 = 0;
			m30 = 0; m31 = 0; m32 = 0; m33 = 1;
		}
		else if (axis == 1)
		{
			m00 = c; m01 = 0; m02 = s; m03 = 0;
			m10 = 0; m11 = 1; m12 = 0; m13 = 0;
			m20 = -s; m21 = 0; m22 = c; m23 = 0;
			m30 = 0; m31 = 0; m32 = 0; m33 = 1;
		}
		else
		{
			m00 = c; m01 = -s; m02 = 0; m03 = 0;
			m10 = s; m11 = c; m12 = 0; m13 = 0;
			m20 = 0; m21 = 0; m22 = 1; m23 = 0;
			m30 = 0; m31 = 0; m32 = 0; m33 = 1;
		}
		return *this;
	}
	void SetRow(int i, CglVector4& p)
	{
		if (i == 0)
		{
			m00 = p.x; m01 = p.y; m02 = p.z; m03 = p.w;
		}
		if (i == 1)
		{
			m10 = p.x; m11 = p.y; m12 = p.z; m13 = p.w;
		}
		if (i == 2)
		{
			m20 = p.x; m21 = p.y; m22 = p.z; m23 = p.w;
		}
		if (i == 3)
		{
			m30 = p.x; m31 = p.y; m32 = p.z; m33 = p.w;
		}
	}
	void SetCol(int i, CglVector4& p)
	{
		if (i == 0)
		{
			m00 = p.x; m10 = p.y; m20 = p.z; m30 = p.w;
		}
		if (i == 1)
		{
			m01 = p.x; m11 = p.y; m21 = p.z; m31 = p.w;
		}
		if (i == 2)
		{
			m02 = p.x; m12 = p.y; m22 = p.z; m32 = p.w;
		}
		if (i == 3)
		{
			m03 = p.x; m13 = p.y; m23 = p.z; m33 = p.w;
		}
	}
	void SetRow(int i, CglVector3& p)
	{
		if (i == 0)
		{
			m00 = p.x; m01 = p.y; m02 = p.z; m03 = 1;
		}
		if (i == 1)
		{
			m10 = p.x; m11 = p.y; m12 = p.z; m13 = 1;
		}
		if (i == 2)
		{
			m20 = p.x; m21 = p.y; m22 = p.z; m23 = 1;
		}
		if (i == 3)
		{
			m30 = p.x; m31 = p.y; m32 = p.z; m33 = 1;
		}
	}
	void SetCol(int i, CglVector3& p)
	{
		if (i == 0)
		{
			m00 = p.x; m10 = p.y; m20 = p.z; m30 = 1;
		}
		if (i == 1)
		{
			m01 = p.x; m11 = p.y; m21 = p.z; m31 = 1;
		}
		if (i == 2)
		{
			m02 = p.x; m12 = p.y; m22 = p.z; m32 = 1;
		}
		if (i == 3)
		{
			m03 = p.x; m13 = p.y; m23 = p.z; m33 = 1;
		}
	}

public:
	~CglMatrix(void) {};
public:
	//	m00	m01	m02	m03
	//	m10	m11	m12	m13
	//	m20	m21	m22	m23
	//	m30	m31	m32	m33
	double m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33;
	operator double* ()
	{
		return &m00;
	}
	operator const double* () const
	{
		return &m00;
	}
	CglMatrix& operator=(const CglMatrix& p)
	{
		for (int i = 0; i < 16; i++)
			(*this)[i] = p[i];
		return *this;
	}

};

#endif