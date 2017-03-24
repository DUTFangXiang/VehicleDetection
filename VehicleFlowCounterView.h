// VehicleFlowCounterView.h : interface of the CVehicleFlowCounterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VEHICLEFLOWCOUNTERVIEW_H__3ADDA346_6D0B_4FA4_884F_A492FC3AD8AB__INCLUDED_)
#define AFX_VEHICLEFLOWCOUNTERVIEW_H__3ADDA346_6D0B_4FA4_884F_A492FC3AD8AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDeal.h"
#include "ImageDeal1.h"
#include "ImageDeal2.h"
#include "ImageDeal3.h"

#include "VehicleFlowCounterDoc.h"
//#include "AVIProducer.h"
#include "SetCheckLineDlg.h"
#include "SetRoadWayParaDlg.h"
#include "KirschEdgeDetect.h"
#include "TotalParameterView.h"
#include "Dib.h"
//#include "LineSignal.h"
//#include "MacDefine.h"

class CVehicleFlowCounterView : public CView
{
protected: // create from serialization only
	CVehicleFlowCounterView();
	DECLARE_DYNCREATE(CVehicleFlowCounterView)

// Attributes
public:
	CVehicleFlowCounterDoc* GetDocument();
	
// Operations
public:
	CImageDeal  *m_pImageDeal;
	CImageDeal1 *m_pImageDeal1;
	CImageDeal2 *m_pImageDeal2;
	CImageDeal3 *m_pImageDeal3;

	LPBYTE m_pSaveImageRegion;
	DWORD *m_pdwPos;

	CDib        *m_pDib;
	CKirschEdgeDetect *m_pKirsch;
	CLineSignal *m_pLineSignal;
    
	int m_nFlag;
//检测线的参数	
	int		m_nHeightPos1;
	int		m_nLeftPos1;
	int		m_nRightPos1;
	int		m_nHeightPos2;
	int		m_nLeftPos2;
	int		m_nRightPos2;

	int		m_nHeightPos3;
	int		m_nLeftPos3;
	int		m_nRightPos3;
	int		m_nHeightPos4;
	int		m_nLeftPos4;
	int		m_nRightPos4;

	int		m_nHeightPos5;
	int		m_nLeftPos5;
	int		m_nRightPos5;
	int		m_nHeightPos6;
	int		m_nLeftPos6;
	int		m_nRightPos6;

	int		m_nHeightPos7;
	int		m_nLeftPos7;
	int		m_nRightPos7;
	int		m_nHeightPos8;
	int		m_nLeftPos8;
	int		m_nRightPos8;

	int		m_nLineHeight;

    TRANSPORTATIONFLOWPARAMETER* m_pFlowParaStruc;
	TRANSPORTATIONFLOWPARAMETER* m_pFlowParaStruc1;
	
private:
	void OpenDetectLineFile();
	void DeliverCheckLinePara();
	void ShowWhichSignal();
	TRANSPORTATIONFLOWPARAMETER* OneRoadway();
	TRANSPORTATIONFLOWPARAMETER* TwoRoadway();
	TRANSPORTATIONFLOWPARAMETER* ThreeRoadway();
	TRANSPORTATIONFLOWPARAMETER* FourRoadway();
//各车道的检测车辆信号设置参数
 //车道1   
	int m_nMaxErrorToler11;//最大的容错度
	int m_nMinReliability11;//最小的可信度
	int m_nMaxErrorToler12;
	int m_nMinReliability12;
//车道2
	int m_nMaxErrorToler21;//最大的容错度
	int m_nMinReliability21;//最小的可信度	
	int m_nMaxErrorToler22;
	int m_nMinReliability22;	
//车道3
	int m_nMaxErrorToler31;//最大的容错度
	int m_nMinReliability31;//最小的可信度	
	int m_nMaxErrorToler32;
	int m_nMinReliability32;	
//车道4
	int m_nMaxErrorToler41;//最大的容错度
	int m_nMinReliability41;//最小的可信度	
	int m_nMaxErrorToler42;
	int m_nMinReliability42;
//信号增强系数
	float m_fSignal1;
	float m_fSignal2;
//两检测线的距离
	float m_fSpace1;
	float m_fSpace2;
	float m_fSpace3;
	float m_fSpace4;

	int m_nMillisecondPerFrame;
	BOOL bIsShow;	
	BOOL bIsDisplay;
	BOOL bIsPause;
	BOOL bIsFileOpen;
	BOOL bIsInitializtion;
	BOOL bIsSetRoadwayPara;

	int m_nHowManyRoadWay;
	int m_nShowWhichSignal;
	int m_nRoadWay11Width;
	int m_nRoadWay12Width;
	int m_nRoadWay21Width;
	int m_nRoadWay22Width;
	int m_nRoadWay31Width;
	int m_nRoadWay32Width;
	BOOL bIsShowSignal1;
	BOOL bIsShowSignal2;
	BOOL bIsShowSignal3;
	BOOL bIsShowSignal4;
	
	CSetCheckLineDlg*   m_pSetCheckLineDlg;
	CSetRoadWayParaDlg* m_pSetRoadWayParaDlg;

	BOOL bIsStop;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVehicleFlowCounterView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVehicleFlowCounterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVehicleFlowCounterView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDisplay();
	afx_msg void OnPause();
	afx_msg void OnUpdateDisplay(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	afx_msg void OnSetline();
	afx_msg void OnFileOpen();
	afx_msg void OnNextframe();
	afx_msg void OnPreviousframe();
	afx_msg void OnNexttenframe();
	afx_msg void OnPreviousframeten();
	afx_msg void OnShowlinesignal();
	afx_msg void OnHidelinesignal();
	afx_msg void OnUpdateShowlinesignal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHidelinesignal(CCmdUI* pCmdUI);
	afx_msg void OnSetframerate();
	afx_msg void OnSetroadwayparameter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VehicleFlowCounterView.cpp
inline CVehicleFlowCounterDoc* CVehicleFlowCounterView::GetDocument()
   { return (CVehicleFlowCounterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEHICLEFLOWCOUNTERVIEW_H__3ADDA346_6D0B_4FA4_884F_A492FC3AD8AB__INCLUDED_)
