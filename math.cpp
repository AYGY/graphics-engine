#include "StdAfx.h"
#include <math.h>
#include "glVector.h"
#include "glew.h"
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
double InverseMatrix(float imat1[], float mat1[])
{
	double dimat[16], dmat[16];
	int i;
	for (i = 0; i < 16; i++)
		dmat[i] = mat1[i];
	double ret = InverseMatrix(dimat, dmat);
	for (i = 0; i < 16; i++)
		imat1[i] = float(dimat[i]);
	return ret;
}
void Dir2HPR(CglVector3 dir, CglVector3& hpr)
{
	CglVector3 direction(dir);
	direction.Normalize();
	CglVector3 dirXZ = direction;//在XOZ平面投影
	dirXZ.y = 0;
	dirXZ.Normalize();
	double temp = direction.dotMul(dirXZ);
	if (temp > 1) temp = 1;
	hpr.y = RadToAng(acos(temp));
	if (direction.y < 0)
		hpr.y = -hpr.y;
	CglVector3 dirZ(0, 0, -1);
	temp = dirXZ.dotMul(dirZ);
	if (temp > 1)temp = 1;
	hpr.x = RadToAng(acos(temp));
	if (direction.x > 0) hpr.x = -hpr.x;
	hpr.z = 0;
}
CglMatrix MakeRotate(double seta, int axis)
{
	CglMatrix mat;
	mat.SetRotate(seta, axis);
	return mat;
}
void CalculateNormal(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat normal[])
{
	GLfloat dirv2_v1[3], dirv2_v3[3];
	for (int i = 0; i < 3; i++)
	{
		dirv2_v1[i] = v1[i] - v2[i];
		dirv2_v3[i] = v3[i] - v2[i];
	}
	//叉乘计算法线方向
	normal[0] = dirv2_v1[1] * dirv2_v3[2] - dirv2_v1[2] * dirv2_v3[1];
	normal[1] = dirv2_v1[2] * dirv2_v3[0] - dirv2_v1[0] * dirv2_v3[2];
	normal[2] = dirv2_v1[0] * dirv2_v3[1] - dirv2_v1[1] * dirv2_v3[0];
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