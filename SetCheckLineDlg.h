#if !defined(AFX_SETCHECKLINEDLG_H__1B7F9731_DC42_4662_8DD7_93B868EF0645__INCLUDED_)
#define AFX_SETCHECKLINEDLG_H__1B7F9731_DC42_4662_8DD7_93B868EF0645__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetCheckLineDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetCheckLineDlg dialog

class CSetCheckLineDlg : public CDialog
{
// Construction
public:
	CSetCheckLineDlg(CWnd* pParent = NULL);   // standard constructor
	void OpenDetectLineFile();
	void SaveLinePos();
public:
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
	CFile file;
// Dialog Data
	//{{AFX_DATA(CSetCheckLineDlg)
	enum { IDD = IDD_CHECKLINE_DIALOG };
	CSliderCtrl	m_sliderLineHeight;
	CSliderCtrl	m_sliderRightPos;
	CSliderCtrl	m_sliderLeftPos;
	CSliderCtrl	m_sliderHeightPos;
	CComboBox	m_comLineNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetCheckLineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetCheckLineDlg)
	virtual void OnOK();
	afx_msg void OnSelchangeComboLinenum();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETCHECKLINEDLG_H__1B7F9731_DC42_4662_8DD7_93B868EF0645__INCLUDED_)
