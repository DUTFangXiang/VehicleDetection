// ImageDeal3.h: interface for the CImageDeal3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEDEAL3_H__D2B96854_3150_4412_9999_D13E9F22E2F3__INCLUDED_)
#define AFX_IMAGEDEAL3_H__D2B96854_3150_4412_9999_D13E9F22E2F3__INCLUDED_

//#include "AVIProducer.h"
#include "Dib.h"
#include "LineSignal.h"
//#include "KirschEdgeDetect.h"
//#include "MacDefine.h"


class CImageDeal3 
{
public:
	CImageDeal3();
	virtual ~CImageDeal3();
	TRANSPORTATIONFLOWPARAMETER* GetNextFrame(CDC *pDC,int nLeftPos7,int nRightPos7,int nHeightPos7,int m_nRoadWay31Width,
		                       int nLeftPos8,int nRightPos8,int nHeightPos8,int m_nRoadWay32Width,float m_fSignal1,float m_fSignal2,float m_fSpace4,
							   int m_nMaxErrorToler41,int m_nMiniReliability41,int m_nMaxErrorToler42,int m_nMiniReliability42,
							   int nLineHeight,BOOL bIsPause,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion,DWORD *m_pdwPos,BOOL bIsShowSignal4);
	void LineDeal(CDC *pDC,BOOL bIsPause);
	void SetDetectLine1(CDC *pDC,int nLineNum,
		                int nHeightPos7,int nLeftPos7,int nRightPos7,int nWidthLine1,BOOL bIsShow);
	void SetDetectLine2(CDC *pDC,int nLineNum,
		                int nHeightPos8,int nLeftPos8,int nRightPos8,int nWidthLine2,BOOL bIsShow);
    TRANSPORTATIONFLOWPARAMETER* DrawLineDealRes(CDC *pDC,int m_nLeftPos7,int m_nRightPos7,int m_nHeightPos7,int m_nRoadWay31Width,
															int m_nLeftPos8,int m_nRightPos8,int m_nHeightPos8,int m_nRoadWay32Width,
															float m_fSignal1,float m_fSignal2,float m_fSpace4,
															int m_nMaxErrorToler41,int m_nMiniReliability41,int m_nMaxErrorToler42,int m_nMiniReliability42,
															int m_nLineHeight,BOOL bIsShowStat,DWORD* m_pdwPos,BOOL bIsShowSignal4);	
	void Initial();
	
	
private:	
	void KillClass();
	void DisplayCurFrame(CDC *pDC,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion);
	void DisplayContinuousVideo(CDC *pDC,int m_nRoadWay31Width,int m_nRoadWay32Width,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion);
	void UpdateBackground(CDC *pDC,int m_nRoadWay31Width,int m_nRoadWay32Width,BOOL bIsPause,BOOL bIsShow);
public:	
	int           m_nWidth;
	int           m_nHeight;
	DWORD         m_dwPos;

	LPBYTE m_pSubResult1;//存放检测线的差分结果
	LPBYTE m_pSubResult2;
	LPBYTE m_pFalseBackground1;//用来取和带运动阴影的车辆相同区域;以消除运动阴影
	LPBYTE m_pFalseBackground2;
	
	LPBYTE TemStoreBac1;
	LPBYTE TemStoreBac2;
	LPBYTE        m_lpStoreBac1;//用存放用于背景更新的连续11
	LPBYTE        m_lpStoreBac2;//帧背景，更新时用第6帧背景
	//申请edge1,edge2用来保存去除阴影边缘的图像
	LPBYTE edge1;
	LPBYTE edge2;
	
	BOOL bIsStoreBac;//用来控制申请存储背景的进程
	BOOL bIsNewCurFrame;

	TRANSPORTATIONFLOWPARAMETER* m_pFlowParaStruc;
private:
	int m_nLine1Width;//线的左右宽度
	int m_nLine2Width;

 	CDib          *m_pDib1;
	CDib          *m_pDib2;
	CLineSignal   *m_pLineSignal;

	LPBYTE        m_lpCurFrame1;
	LPBYTE        m_lpCurFrame2;
    LPBYTE        m_lpBacFrame1;
	LPBYTE        m_lpBacFrame2;

	int           NoVehicle1;//用于更新背景用
	int           NoVehicle2;
	int           NoVehicleFramePos1;
	int           NoVehicleFramePos2;
	int           TempMemory1;//用来记录背景更新时的指针位置
	int           TempMemory2;
	int           UpdateNum1;
	int           UpdateNum2;
	
	BOOL    m_bHide;

	int		m_nLineHeight;//线的高度
	int		m_nHeightPos7;
	int		m_nLeftPos7;
	int		m_nRightPos7;
	int		m_nHeightPos8;
	int		m_nLeftPos8;
	int		m_nRightPos8;

	CRect    m_rect1;
	CRect    m_rect2;
};
#endif // !defined(AFX_IMAGEDEAL3_H__D2B96854_3150_4412_9999_D13E9F22E2F3__INCLUDED_)
