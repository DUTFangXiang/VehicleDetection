// ImageDeal2.h: interface for the CImageDeal2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEDEAL2_H__6E50CD01_955C_4431_90AA_C176A481470B__INCLUDED_)
#define AFX_IMAGEDEAL2_H__6E50CD01_955C_4431_90AA_C176A481470B__INCLUDED_

//#include "AVIProducer.h"
#include "Dib.h"
#include "LineSignal.h"
//#include "KirschEdgeDetect.h"
//#include "MacDefine.h"


class CImageDeal2 
{
public:
	CImageDeal2();
	virtual ~CImageDeal2();
	TRANSPORTATIONFLOWPARAMETER* GetNextFrame(CDC *pDC,int nLeftPos5,int nRightPos5,int nHeightPos5,int m_nRoadWay21Width,
		                       int nLeftPos6,int nRightPos6,int nHeightPos6,int m_nRoadWay22Width,
							   float m_fSignal1,float m_fSignal2,float m_fSpace3,
							   int m_nMaxErrorToler31,int m_nMiniReliability31,int m_nMaxErrorToler32,int m_nMiniReliability32,
							   int nLineHeight,BOOL bIsPause,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion,DWORD *m_pdwPos,BOOL bIsShowSignal3);
	void LineDeal(CDC *pDC,BOOL bIsPause);
	void SetDetectLine1(CDC *pDC,int nLineNum,
		                int nHeightPos5,int nLeftPos5,int nRightPos5,int nWidthLine1,BOOL bIsShow);
	void SetDetectLine2(CDC *pDC,int nLineNum,
		                int nHeightPos6,int nLeftPos6,int nRightPos6,int nWidthLine2,BOOL bIsShow);
    TRANSPORTATIONFLOWPARAMETER* DrawLineDealRes(CDC *pDC,int m_nLeftPos5,int m_nRightPos5,int m_nHeightPos5,int m_nRoadWay21Width,
															int m_nLeftPos6,int m_nRightPos6,int m_nHeightPos6,int m_nRoadWay22Width,
															float m_fSignal1,float m_fSignal2,float m_fSpace3,
															int m_nMaxErrorToler31,int m_nMiniReliability31,int m_nMaxErrorToler32,int m_nMiniReliability32,
															int m_nLineHeight,BOOL bIsShowStat,DWORD* m_pdwPos,BOOL bIsShowSignal3);	
	void Initial();
	
	
private:	
	void KillClass();
	void DisplayCurFrame(CDC *pDC,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion);
	void DisplayContinuousVideo(CDC *pDC,int m_nRoadWay21Width,int m_nRoadWay22Width,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion);
	void UpdateBackground(CDC *pDC,int m_nRoadWay21Width,int m_nRoadWay221Width,BOOL bIsPause,BOOL bIsShow);
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
	int		m_nHeightPos5;
	int		m_nLeftPos5;
	int		m_nRightPos5;
	int		m_nHeightPos6;
	int		m_nLeftPos6;
	int		m_nRightPos6;

	CRect    m_rect1;
	CRect    m_rect2;
};


#endif // !defined(AFX_IMAGEDEAL2_H__6E50CD01_955C_4431_90AA_C176A481470B__INCLUDED_)
