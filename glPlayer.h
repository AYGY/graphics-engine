// glPlayer.h: interface for the CglPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLPLAYER_H__DE98CFA9_9F9D_4A6F_BF79_800916A5CB68__INCLUDED_)
#define AFX_GLPLAYER_H__DE98CFA9_9F9D_4A6F_BF79_800916A5CB68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "glVector.h"
class CglMeshBranch;
class CglParticleCtrl;
class COpenGL;
class CglPlayer
{
public:
	void ParticleReInit();
	void Run(bool bUpdate = true, int iDrawBoundBox = -1);//-1����ֻ��Χ�У�0���ƿյİ�Χ��,1--n��Χ����������ֱ�ʾ����
	virtual ~CglPlayer();
	CglVector4 m_SpecialColor;
	CglVector3 m_curpos, m_curdir, m_curhpr;
	CglVector3 m_nextpos, m_nextdir, m_nexthpr;
};
#endif