// FrameRateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VehicleFlowCounter.h"
#include "FrameRateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrameRateDlg dialog


CFrameRateDlg::CFrameRateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFrameRateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrameRateDlg)
	m_nMillisecondNum = 0;
	//}}AFX_DATA_INIT
}


void CFrameRateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrameRateDlg)
	DDX_Text(pDX, IDC_MILLISECONDNUM, m_nMillisecondNum);
	DDV_MinMaxInt(pDX, m_nMillisecondNum, 0, 2000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrameRateDlg, CDialog)
	//{{AFX_MSG_MAP(CFrameRateDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameRateDlg message handlers
