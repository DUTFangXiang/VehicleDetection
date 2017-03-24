#if !defined(AFX_TOTALPARAMETERVIEW_H__753F60CF_5156_4732_BF58_523EA6E4A9EA__INCLUDED_)
#define AFX_TOTALPARAMETERVIEW_H__753F60CF_5156_4732_BF58_523EA6E4A9EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TotalParameterView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTotalParameterView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "VehicleFlowCounterView.h"

class CTotalParameterView : public CFormView
{	
public:
protected:
    CTotalParameterView(); // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTotalParameterView)

// Form Data
public:
	//{{AFX_DATA(CTotalParameterView)
	enum { IDD = IDD_VIEW_TOTALPARA };
	float	m_fSpeed1;
	float	m_fSpeed2;
	float	m_fSpeed3;
	float	m_fSpeed4;
	float	m_fSpeedSum;
	short	m_sMinuteVehicleNum1;
	short	m_sMinuteVehicleNum2;
	short	m_sMinuteVehicleNum3;
	short	m_sMinuteVehicleNum4;
	short	m_sMinuteVehicleNumSum;
	float	m_fTimeDensity1;
	float	m_fTimeDensity2;
	float	m_fTimeDensity3;
	float	m_fTimeDensity4;
	float	m_fTimeDensitySum;
	int		m_nVehicleNumSum;
	int		m_nVehicleNum4;
	int		m_nVehicleNum2;
	int		m_nVehicleNum3;
	int		m_nVehicleNum1;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTotalParameterView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTotalParameterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTotalParameterView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOTALPARAMETERVIEW_H__753F60CF_5156_4732_BF58_523EA6E4A9EA__INCLUDED_)
