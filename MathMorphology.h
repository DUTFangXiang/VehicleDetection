// MathMorphology.h: interface for the CMathMorphology class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHMORPHOLOGY_H__BB670270_0B6F_4A75_81BA_C6F211D35A9A__INCLUDED_)
#define AFX_MATHMORPHOLOGY_H__BB670270_0B6F_4A75_81BA_C6F211D35A9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MacDefine.h"

class CMathMorphology  
{
public:	
	MORPHOLOGYELEMENT* m_pME;
	int m_nElementUsed;

	CMathMorphology();
	virtual ~CMathMorphology();

	BOOL Erode(LPBYTE lpbyBits24,int nWidth,int nHeight);
	BOOL Dilate(LPBYTE lpbyBits24,int nWidth,int nHeight);
	BOOL Denoise(LPBYTE lpbyBits24,int nWidth,int nHeight);

	void Morph(CDC* pDC,LPBYTE lpbyBits24,int nWidth,int nHeight,int m_nRoadWayWidth,int nLineNum,int OpraType,BOOL bIsShow,int DrivewayNum);
private:	
	void Erode(short *pcxDataSrc,int nWidth,int nHeight,short  *pcxDataDst);
	void Dilate(short *pcxDataSrc,int nWidth,int nHeight,short* pcxDataDst);
};

#endif // !defined(AFX_MATHMORPHOLOGY_H__BB670270_0B6F_4A75_81BA_C6F211D35A9A__INCLUDED_)
