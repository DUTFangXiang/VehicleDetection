#if !defined(AFX_FRAMERATEDLG_H__CB7E0B85_A79A_4DB2_866A_0641B1488B74__INCLUDED_)
#define AFX_FRAMERATEDLG_H__CB7E0B85_A79A_4DB2_866A_0641B1488B74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrameRateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrameRateDlg dialog

class CFrameRateDlg : public CDialog
{
// Construction
public:
	CFrameRateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFrameRateDlg)
	enum { IDD = IDD_FRAMERATE };
	int		m_nMillisecondNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameRateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrameRateDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMERATEDLG_H__CB7E0B85_A79A_4DB2_866A_0641B1488B74__INCLUDED_)
