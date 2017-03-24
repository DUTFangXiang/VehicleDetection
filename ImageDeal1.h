// ImageDeal1.h: interface for the CImageDeal1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEDEAL1_H__DD02825D_1EA3_49BB_B76E_9D9C42007DE3__INCLUDED_)
#define AFX_IMAGEDEAL1_H__DD02825D_1EA3_49BB_B76E_9D9C42007DE3__INCLUDED_

//#include "AVIProducer.h"
#include "Dib.h"
#include "LineSignal.h"
#include "KirschEdgeDetect.h"
//#include "MacDefine.h"


class CImageDeal1 
{
public:
	CImageDeal1();
	virtual ~CImageDeal1();
	TRANSPORTATIONFLOWPARAMETER* GetNextFrame(CDC *pDC,int nLeftPos3,int nRightPos3,int nHeightPos3,int m_nRoadWay11Width,
		                       int nLeftPos2,int nRightPos4,int nHeightPos4,int m_nRoadWay12Width,float m_fSignal1,float m_fSignal2,float m_fSpace2,
							   int m_nMaxErrorToler21,int m_nMiniReliability21,int m_nMaxErrorToler22,int m_nMiniReliability22,
							   int nLineHeight,BOOL bIsPause,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion,DWORD *m_pdwPos,BOOL bIsShowSignal2);
	void LineDeal(CDC *pDC,BOOL bIsPause);
	void SetDetectLine1(CDC *pDC,int nLineNum,
		                int nHeightPos3,int nLeftPos3,int nRightPos3,int nWidthLine1,BOOL bIsShow);
	void SetDetectLine2(CDC *pDC,int nLineNum,
		                int nHeightPos4,int nLeftPos2,int nRightPos4,int nWidthLine2,BOOL bIsShow);
    TRANSPORTATIONFLOWPARAMETER* DrawLineDealRes(CDC *pDC,int m_nLeftPos3,int m_nRightPos3,int m_nHeightPos3,int m_nRoadWay11Width,
															int m_nLeftPos2,int m_nRightPos4,int m_nHeightPos4,int m_nRoadWay12Width,
															float m_fSignal1,float m_fSignal2,float m_fSpace2,
															int m_nMaxErrorToler21,int m_nMiniReliability21,int m_nMaxErrorToler22,int m_nMiniReliability22,
															int m_nLineHeight,BOOL bIsShowStat,DWORD* m_pdwPos,BOOL bIsShowSignal2);	
	void Initial();
	
	
private:	
	void KillClass();
	void DisplayCurFrame(CDC *pDC,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion);
	void DisplayContinuousVideo(CDC *pDC,int m_nRoadWay11Width,int m_nRoadWay12Width,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion);
	void UpdateBackground(CDC *pDC,int m_nRoadWay11Width,int m_nRoadWay12Width,BOOL bIsPause,BOOL bIsShow);
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
	int		m_nHeightPos3;
	int		m_nLeftPos3;
	int		m_nRightPos3;
	int		m_nHeightPos4;
	int		m_nLeftPos4;
	int		m_nRightPos4;

	CRect    m_rect1;
	CRect    m_rect2;
};

#endif // !defined(AFX_IMAGEDEAL1_H__DD02825D_1EA3_49BB_B76E_9D9C42007DE3__INCLUDED_)
