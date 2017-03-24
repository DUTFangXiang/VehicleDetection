// LineSignal.h: interface for the CLineSignal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINESIGNAL_H__E17E62B2_5E57_42F7_8C0A_281F179F4C63__INCLUDED_)
#define AFX_LINESIGNAL_H__E17E62B2_5E57_42F7_8C0A_281F179F4C63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AVIProducer.h"
#include "TransFlowPara.h"
#include "MacDefine.h"

class CLineSignal  
{
public:
	int m_nFramePosition;
	int m_nUnitaryValue1;
	int m_nUnitaryValue2;
	DWORD m_dwTotalSignal;
	int   m_nUnitary;
	float m_fSignal1;
	float m_fSignal2;
	
	CTransFlowPara *m_pTransFlowParaClass;	
	AVIProducer *m_pAVIProducer;
	
	TRANSPORTATIONFLOWPARAMETER* m_pFlowParaStruc;
	int m_nLineHeight;
	int m_nRightPos2;
	int m_nLeftPos2;
	int m_nHeightPos2;
	int m_nRightPos1;
	int m_nLeftPos1;
	int m_nHeightPos1;

	int m_nMaxErrorToler11;
	int m_nMiniReliability11;
	int m_nMaxErrorToler12;
	int m_nMiniReliability12;
private:
			
public:
	CLineSignal();
	virtual ~CLineSignal();

	TRANSPORTATIONFLOWPARAMETER* StatLineSignal(CDC *pDC,int m_nLeftPos1,int m_nRightPos1,int m_nLeftPos2,int m_nRightPos2,
		                                                 float m_fSignal1,float m_fSignal2,float m_fSpace,
														 int m_nMaxErrorToler11,int	m_nMiniReliability11,int m_nMaxErrorToler12,int m_nMiniReliability12,
														 int m_nLineHeight,LPBYTE pDetectLine1,LPBYTE pDetectLine2,DWORD nPos,BOOL bIsShow,int DrivewayNum,BOOL bIsShowSignal);
	TRANSPORTATIONFLOWPARAMETER* ShowCoordinate(CDC *pDC,DWORD nPos,float m_fSpace,int m_nUnitaryValue1,int m_nUnitaryValue2,BOOL bIsShow,int DrivewayNum,BOOL bIsShowSignal);
	void ShowSignal(CDC *pDC,DWORD nPos,int m_nUnitaryValue1,int m_nUnitaryValue2,BOOL bIsShowSignal);
};

#endif // !defined(AFX_LINESIGNAL_H__E17E62B2_5E57_42F7_8C0A_281F179F4C63__INCLUDED_)
