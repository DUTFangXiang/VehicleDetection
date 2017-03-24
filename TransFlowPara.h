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
	//�������Ĳ���
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
//�����������Ľṹָ��
	TRANSPORTATIONFLOWPARAMETER *m_pFlowParaStruc;
//����1
	TRANSPORTATIONFLOWPARAMETER* FlowCounter1(CDC *pDC,float m_fSpace1,int m_nMaxErrorToler11,int m_nMiniReliability11,int m_nMaxErrorToler12,int m_nMiniReliability12,
		                                      int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShow,BOOL bIsShowSignal);
	void MinuteVehicleNum1(int nPos);
	void Speed1(int nStart1,int nStart2,float m_fSpace1);
	void TimeDensity1(int nPos);
//����2
	TRANSPORTATIONFLOWPARAMETER* FlowCounter2(CDC *pDC,float m_fSpace2,int m_nMaxErrorToler21,int m_nMiniReliability21,int m_nMaxErrorToler22,int m_nMiniReliability22,
		                                      int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShow,BOOL bIsShowSignal);
	void MinuteVehicleNum2(int nPos);
	void Speed2(int nStart1,int nStart2,float m_fSpace2);
	void TimeDensity2(int nPos);
//����3
	TRANSPORTATIONFLOWPARAMETER* FlowCounter3(CDC *pDC,float m_fSpace3,
		                                      int m_nMaxErrorToler31,int m_nMiniReliability31,int m_nMaxErrorToler32,int m_nMiniReliability32,
		                                      int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShow,BOOL bIsShowSignal);
	void MinuteVehicleNum3(int nPos);
	void Speed3(int nStart1,int nStart2,float m_fSpace3);
	void TimeDensity3(int nPos);
//����4
	TRANSPORTATIONFLOWPARAMETER* FlowCounter4(CDC *pDC,float m_fSpace4,
		                                      int m_nMaxErrorToler41,int m_nMiniReliability41,int m_nMaxErrorToler42,int m_nMiniReliability42,
		                                      int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShow,BOOL bIsShowSignal);
	void MinuteVehicleNum4(int nPos);
	void Speed4(int nStart1,int nStart2,float m_fSpace4);
	void TimeDensity4(int nPos);

private:
	int m_nThresshold1;//�ж��ź���Ч����С����ֵ,�б�ҪʱҲҪ��Ϊ4������
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
//����1
	int m_nMaxErrorToler11;//�����ݴ��
	int m_nMiniReliability11;//��С�Ŀ��Ŷ�
	int m_nMaxErrorToler12;
	int m_nMiniReliability12;
	
	int m_nCredible11;//���ŵ��ź�
	int m_nSufferance11;//�����̵��ź�(ָ������)
	int m_nCredible12;
	int m_nSufferance12;
	
	BOOL m_bIsProcess11;//�Ƿ��н�������
	BOOL m_bIsProcess12;

	int m_nOccupyFrame1;
	
	int nTempHas1;
	int nTempnPos1;	
//����2
	int m_nMaxErrorToler21;//�����ݴ��
	int m_nMiniReliability21;//��С�Ŀ��Ŷ�	
	int m_nMaxErrorToler22;
	int m_nMiniReliability22;
	
	int m_nCredible21;//���ŵ��ź�
	int m_nSufferance21;//�����̵��ź�(ָ������)
	int m_nCredible22;
	int m_nSufferance22;

	BOOL m_bIsProcess21;//�Ƿ��н�������
	BOOL m_bIsProcess22;
	
	int m_nOccupyFrame2;

	int nTempHas2;
	int nTempnPos2;
//����3
	int m_nMaxErrorToler31;//�����ݴ��
	int m_nMiniReliability31;//��С�Ŀ��Ŷ�	
	int m_nMaxErrorToler32;
	int m_nMiniReliability32;
	
	int m_nCredible31;//���ŵ��ź�
	int m_nSufferance31;//�����̵��ź�(ָ������)
	int m_nCredible32;
	int m_nSufferance32;

	BOOL m_bIsProcess31;//�Ƿ��н�������
	BOOL m_bIsProcess32;

	int m_nOccupyFrame3;

	int nTempHas3;
	int nTempnPos3;
//����4
	int m_nMaxErrorToler41;//�����ݴ��
	int m_nMiniReliability41;//��С�Ŀ��Ŷ�	
	int m_nMaxErrorToler42;
	int m_nMiniReliability42;

	int m_nCredible41;//���ŵ��ź�
	int m_nSufferance41;//�����̵��ź�(ָ������)
	int m_nCredible42;
	int m_nSufferance42;

	BOOL m_bIsProcess41;//�Ƿ��н�������
	BOOL m_bIsProcess42;

	int m_nOccupyFrame4;

	int nTempHas4;
	int nTempnPos4;
};

#endif // !defined(AFX_TRANSFLOWPARA_H__7B8C6AC6_5613_4D6D_B824_45DA57F5E725__INCLUDED_)
