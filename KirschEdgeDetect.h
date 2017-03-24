// KirschEdgeDetect.h: interface for the CKirschEdgeDetect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KIRSCHEDGEDETECT_H__10F01B44_B2A4_4318_ABB9_79D70F2C19CE__INCLUDED_)
#define AFX_KIRSCHEDGEDETECT_H__10F01B44_B2A4_4318_ABB9_79D70F2C19CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "MacDefine.h"
//#include "ImageDeal.h"
#include "MathMorphology.h"

class CKirschEdgeDetect  
{
public:
	CKirschEdgeDetect();
	virtual ~CKirschEdgeDetect();
	BYTE* KirschEdgeDet(CDC *pDC,int m_nLeftPos1,int m_nRightPos1,int m_nLineHeight,int m_nRoadWayWidth,LPBYTE lpbyBits24,int nLineNum,BOOL bIsShow,int DrivewayNum);
	BYTE* KirschEdgeDet(LPBYTE lpbyBits24,int nLineNum);

private:	
	PIXELCOLORRGB FilterPixelOnBorder(LPBYTE lpbyBitsSrc24,int x,int y,int nWidth,int nHeight);
	PIXELCOLORRGB FilterPixelInner(LPBYTE lpbyBitsSrc24,int x,int y,int nWidth,int nHeight);
	PIXELCOLORRGB Kirsch(BYTE *pbyRed,BYTE *pbyGreen,BYTE *pbyBlue);
	BYTE* DrawEdgeDetectRes(CDC *pDC,BYTE *pbyResult,int nWidth,int nHeight,int nLineNum,BOOL bIsShow,int DrivewayNum);
public:
	BYTE* pbyResult1;
	BYTE* pbyResult2;

private:
	CMathMorphology* m_pMathMorph;
	int m_nHeightPos1;
	int m_nLeftPos1;
	int m_nRightPos1;
	int m_nHeightPos2;
	int m_nLeftPos2;
	int m_nRightPos2;
	int m_nLineHeight;
	int nWidth;
	int nWidthBytes;
	int m_nRoadWayWidth;
};

#endif // !defined(AFX_KIRSCHEDGEDETECT_H__10F01B44_B2A4_4318_ABB9_79D70F2C19CE__INCLUDED_)
