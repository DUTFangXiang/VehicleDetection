// ImageDeal.h: interface for the CImageDeal class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_IMAGEDEAL_H_INCLUDED_)
#define AFX_IMAGEDEAL_H_INCLUDED_

//#include "AVIProducer.h"
#include "Dib.h"
#include "LineSignal.h"
//#include "KirschEdgeDetect.h"
//#include "MacDefine.h"

class CImageDeal 
{
public:
	CImageDeal();
	virtual ~CImageDeal();
	TRANSPORTATIONFLOWPARAMETER* GetNextFrame(CDC *pDC,int nLeftPos1,int nRightPos1,int nHeightPos1,
		                       int nLeftPos2,int nRightPos2,int nHeightPos2,float m_fSignal1,float m_fSignal2,float m_fSpace1,
							   int m_nMaxErrorToler11,int m_nMiniReliability11,int m_nMaxErrorToler12,int m_nMiniReliability12,
							   int nLineHeight,BOOL bIsPause,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion,DWORD* m_pdwPos,BOOL bIsShowSignal1);
	void LineDeal(CDC *pDC,BOOL bIsPause);
	void SetDetectLine1(CDC *pDC,int nLineNum,
		                int nHeightPos1,int nLeftPos1,int nRightPos1,int nWidthLine1,BOOL bIsShow);
	void SetDetectLine2(CDC *pDC,int nLineNum,
		                int nHeightPos2,int nLeftPos2,int nRightPos2,int nWidthLine2,BOOL bIsShow);
    TRANSPORTATIONFLOWPARAMETER* DrawLineDealRes(CDC *pDC,int m_nLeftPos1,int m_nRightPos1,int m_nHeightPos1,
															int m_nLeftPos2,int m_nRightPos2,int m_nHeightPos2,float m_fSignal1,float m_fSignal2,float m_fSpace1,
															int m_nMaxErrorToler11,int m_nMiniReliability11,int m_nMaxErrorToler12,int m_nMiniReliability12,
															int m_nLineHeight,BOOL bIsShowStat,BOOL bIsShowSignal1);	
	void Initial(CString strAVIFilePath);
	
private:	
	void KillClass();
	void DisplayCurFrame(CDC *pDC,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion);
	void DisplayContinuousVideo(CDC *pDC,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion);
	void UpdateBackground(CDC *pDC,BOOL bIsPause,BOOL bIsShow);
public:	
	int           m_nWidth;
	int           m_nHeight;
	DWORD         m_dwPos;
	DWORD         m_dwLength;
	
	
	LPBYTE m_pSubResult1;//��ż���ߵĲ�ֽ��
	LPBYTE m_pSubResult2;
	LPBYTE m_pFalseBackground1;//����ȡ�ʹ��˶���Ӱ�ĳ�����ͬ����;�������˶���Ӱ
	LPBYTE m_pFalseBackground2;
	
	LPBYTE        m_lpStoreBac1;//�ô�����ڱ������µ�����11
	LPBYTE        m_lpStoreBac2;//֡����������ʱ�õ�6֡����
	LPBYTE TemStoreBac1;
	LPBYTE TemStoreBac2;
	//����edge1,edge2��������ȥ����Ӱ��Ե��ͼ��
	LPBYTE edge1;
	LPBYTE edge2;
	
	BOOL bIsStoreBac;//������������洢�����Ľ���
	BOOL bIsNewCurFrame;

	TRANSPORTATIONFLOWPARAMETER* m_pFlowParaStruc;
private:
	int m_nLine1Width;//�ߵ����ҿ��
	int m_nLine2Width;

    AVIProducer   *m_pAvi;
	CDib          *m_pDib1;
	CDib          *m_pDib2;
	CLineSignal   *m_pLineSignal;

	LPBYTE        m_lpCurFrame1;
	LPBYTE        m_lpCurFrame2;
    LPBYTE        m_lpBacFrame1;
	LPBYTE        m_lpBacFrame2;

	int           NoVehicle1;//���ڸ��±�����
	int           NoVehicle2;
	int           NoVehicleFramePos1;
	int           NoVehicleFramePos2;
	int           TempMemory1;//������¼��������ʱ��ָ��λ��
	int           TempMemory2;
	int           UpdateNum1;
	int           UpdateNum2;
	
	BOOL    m_bHide;

	int		m_nLineHeight;//�ߵĸ߶�
	int		m_nHeightPos1;
	int		m_nLeftPos1;
	int		m_nRightPos1;
	int		m_nHeightPos2;
	int		m_nLeftPos2;
	int		m_nRightPos2;

	CRect    m_rect1;
	CRect    m_rect2;
};
#endif
