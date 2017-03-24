// TransFlowPara.h: interface for the CTransFlowPara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFLOWPARA_H__7B8C6AC6_5613_4D6D_B824_45DA57F5E725__INCLUDED_)
#define AFX_TRANSFLOWPARA_H__7B8C6AC6_5613_4D6D_B824_45DA57F5E725__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "LineSignal.h"
#include "MacDefine.h"
//#include "AVIProducer.h"

class CTransFlowPara  
{
public:
	CTransFlowPara();
	virtual ~CTransFlowPara();
	//各车道的参数
	int m_nVehicleNum11;
	int m_nVehicleNum12;
	int m_nVehicleNum21;
	int m_nVehicleNum22;
	int m_nVehicleNum31;
	int m_nVehicleNum32;
	int m_nVehicleNum41;
	int m_nVehicleNum42;

	int m_nVehicleTemp11;
	int m_nVehicleTemp12;
	int m_nVehicleTemp21;
	int m_nVehicleTemp22;
	int m_nVehicleTemp31;
	int m_nVehicleTemp32;
	int m_nVehicleTemp41;
	int m_nVehicleTemp42;	
//交道流参数的结构指针
	TRANSPORTATIONFLOWPARAMETER *m_pFlowParaStruc;
//车道1
	TRANSPORTATIONFLOWPARAMETER* FlowCounter1(CDC *pDC,float m_fSpace1,int m_nMaxErrorToler11,int m_nMiniReliability11,int m_nMaxErrorToler12,int m_nMiniReliability12,
		                                      int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShow,BOOL bIsShowSignal);
	void MinuteVehicleNum1(int nPos);
	void Speed1(int nStart1,int nStart2,float m_fSpace1);
	void TimeDensity1(int nPos);
//车道2
	TRANSPORTATIONFLOWPARAMETER* FlowCounter2(CDC *pDC,float m_fSpace2,int m_nMaxErrorToler21,int m_nMiniReliability21,int m_nMaxErrorToler22,int m_nMiniReliability22,
		                                      int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShow,BOOL bIsShowSignal);
	void MinuteVehicleNum2(int nPos);
	void Speed2(int nStart1,int nStart2,float m_fSpace2);
	void TimeDensity2(int nPos);
//车道3
	TRANSPORTATIONFLOWPARAMETER* FlowCounter3(CDC *pDC,float m_fSpace3,
		                                      int m_nMaxErrorToler31,int m_nMiniReliability31,int m_nMaxErrorToler32,int m_nMiniReliability32,
		                                      int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShow,BOOL bIsShowSignal);
	void MinuteVehicleNum3(int nPos);
	void Speed3(int nStart1,int nStart2,float m_fSpace3);
	void TimeDensity3(int nPos);
//车道4
	TRANSPORTATIONFLOWPARAMETER* FlowCounter4(CDC *pDC,float m_fSpace4,
		                                      int m_nMaxErrorToler41,int m_nMiniReliability41,int m_nMaxErrorToler42,int m_nMiniReliability42,
		                                      int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShow,BOOL bIsShowSignal);
	void MinuteVehicleNum4(int nPos);
	void Speed4(int nStart1,int nStart2,float m_fSpace4);
	void TimeDensity4(int nPos);

private:
	int m_nThresshold1;//判断信号有效的最小的阈值,有必要时也要设为4个变量
	int m_nThresshold2;

	int m_nSpeedNum1;
	int m_nSpeedNum2;
	int m_nSpeedNum3;
	int m_nSpeedNum4;

	int m_nTempSufferancePos11;
	int m_nSumSufferance11;
	int m_nTempSufferancePos12;
	int m_nSumSufferance12;

	int m_nTempSufferancePos21;
	int m_nSumSufferance21;
	int m_nTempSufferancePos22;
	int m_nSumSufferance22;

	int m_nTempSufferancePos31;
	int m_nSumSufferance31;
	int m_nTempSufferancePos32;
	int m_nSumSufferance32;

	int m_nTempSufferancePos41;
	int m_nSumSufferance41;
	int m_nTempSufferancePos42;
	int m_nSumSufferance42;
//车道1
	int m_nMaxErrorToler11;//最大的容错度
	int m_nMiniReliability11;//最小的可信度
	int m_nMaxErrorToler12;
	int m_nMiniReliability12;
	
	int m_nCredible11;//可信的信号
	int m_nSufferance11;//可容忍的信号(指车窗等)
	int m_nCredible12;
	int m_nSufferance12;
	
	BOOL m_bIsProcess11;//是否有进程启动
	BOOL m_bIsProcess12;

	int m_nOccupyFrame1;
	
	int nTempHas1;
	int nTempnPos1;	
//车道2
	int m_nMaxErrorToler21;//最大的容错度
	int m_nMiniReliability21;//最小的可信度	
	int m_nMaxErrorToler22;
	int m_nMiniReliability22;
	
	int m_nCredible21;//可信的信号
	int m_nSufferance21;//可容忍的信号(指车窗等)
	int m_nCredible22;
	int m_nSufferance22;

	BOOL m_bIsProcess21;//是否有进程启动
	BOOL m_bIsProcess22;
	
	int m_nOccupyFrame2;

	int nTempHas2;
	int nTempnPos2;
//车道3
	int m_nMaxErrorToler31;//最大的容错度
	int m_nMiniReliability31;//最小的可信度	
	int m_nMaxErrorToler32;
	int m_nMiniReliability32;
	
	int m_nCredible31;//可信的信号
	int m_nSufferance31;//可容忍的信号(指车窗等)
	int m_nCredible32;
	int m_nSufferance32;

	BOOL m_bIsProcess31;//是否有进程启动
	BOOL m_bIsProcess32;

	int m_nOccupyFrame3;

	int nTempHas3;
	int nTempnPos3;
//车道4
	int m_nMaxErrorToler41;//最大的容错度
	int m_nMiniReliability41;//最小的可信度	
	int m_nMaxErrorToler42;
	int m_nMiniReliability42;

	int m_nCredible41;//可信的信号
	int m_nSufferance41;//可容忍的信号(指车窗等)
	int m_nCredible42;
	int m_nSufferance42;

	BOOL m_bIsProcess41;//是否有进程启动
	BOOL m_bIsProcess42;

	int m_nOccupyFrame4;

	int nTempHas4;
	int nTempnPos4;
};

#endif // !defined(AFX_TRANSFLOWPARA_H__7B8C6AC6_5613_4D6D_B824_45DA57F5E725__INCLUDED_)
