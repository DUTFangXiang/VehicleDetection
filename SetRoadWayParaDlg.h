#if !defined(AFX_SETROADWAYPARADLG_H__8AED2CBA_09A3_4F5A_970D_1EEF461AC4B6__INCLUDED_)
#define AFX_SETROADWAYPARADLG_H__8AED2CBA_09A3_4F5A_970D_1EEF461AC4B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetRoadWayParaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetRoadWayParaDlg dialog

class CSetRoadWayParaDlg : public CDialog
{
// Construction
public:
	CSetRoadWayParaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetRoadWayParaDlg)
	enum { IDD = IDD_SETROADPARAMETER };
	int		m_nHowManyRoadway;
	int		m_nMaxErrorToler12;
	int		m_nMaxErrorToler21;
	int		m_nMaxErrorToler22;
	int		m_nMaxErrorToler31;
	int		m_nMaxErrorToler11;
	int		m_nMaxErrorToler32;
	int		m_nMaxErrorToler41;
	int		m_nMaxErrorToler42;
	int		m_nMinReliability11;
	int		m_nMinReliability12;
	int		m_nMinReliability21;
	int		m_nMinReliability22;
	int		m_nMinReliability31;
	int		m_nMinReliability32;
	int		m_nMinReliability41;
	int		m_nMinReliability42;
	int		m_nShowWhichSignal;
	float	m_fSignal1;
	float	m_fSignal2;
	float	m_fSpace1;
	float	m_fSpace2;
	float	m_fSpace3;
	float	m_fSpace4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetRoadWayParaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetRoadWayParaDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETROADWAYPARADLG_H__8AED2CBA_09A3_4F5A_970D_1EEF461AC4B6__INCLUDED_)
