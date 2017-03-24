//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*                    FX调试记录
                  设置车道参数处理
	        (并且规定了每个参数的处理范围)
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "VehicleFlowCounter.h"
#include "SetRoadWayParaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetRoadWayParaDlg dialog


CSetRoadWayParaDlg::CSetRoadWayParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetRoadWayParaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetRoadWayParaDlg)
	m_nHowManyRoadway = 0;
	m_nMaxErrorToler12 = 0;
	m_nMaxErrorToler21 = 0;
	m_nMaxErrorToler22 = 0;
	m_nMaxErrorToler31 = 0;
	m_nMaxErrorToler11 = 0;
	m_nMaxErrorToler32 = 0;
	m_nMaxErrorToler41 = 0;
	m_nMaxErrorToler42 = 0;
	m_nMinReliability11 = 0;
	m_nMinReliability12 = 0;
	m_nMinReliability21 = 0;
	m_nMinReliability22 = 0;
	m_nMinReliability31 = 0;
	m_nMinReliability32 = 0;
	m_nMinReliability41 = 0;
	m_nMinReliability42 = 0;
	m_nShowWhichSignal = 0;
	m_fSignal1 = 0.0f;
	m_fSignal2 = 0.0f;
	m_fSpace1 = 0.0f;
	m_fSpace2 = 0.0f;
	m_fSpace3 = 0.0f;
	m_fSpace4 = 0.0f;
	//}}AFX_DATA_INIT
}

/************************************
       FX    设置车道参数处理
	(并且规定了每个参数的处理范围)
************************************/
void CSetRoadWayParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetRoadWayParaDlg)
	DDX_Text(pDX, IDC_HOWMANYROADWAY, m_nHowManyRoadway);
	DDV_MinMaxInt(pDX, m_nHowManyRoadway, 1, 4);
	DDX_Text(pDX, IDC_MAXERRORTOLER12, m_nMaxErrorToler12);
	DDV_MinMaxInt(pDX, m_nMaxErrorToler12, 4, 15);
	DDX_Text(pDX, IDC_MAXERRORTOLER21, m_nMaxErrorToler21);
	DDV_MinMaxInt(pDX, m_nMaxErrorToler21, 4, 15);
	DDX_Text(pDX, IDC_MAXERRORTOLER22, m_nMaxErrorToler22);
	DDV_MinMaxInt(pDX, m_nMaxErrorToler22, 4, 15);
	DDX_Text(pDX, IDC_MAXERRORTOLER31, m_nMaxErrorToler31);
	DDV_MinMaxInt(pDX, m_nMaxErrorToler31, 4, 15);
	DDX_Text(pDX, IDC_MAXERRORTOLER11, m_nMaxErrorToler11);
	DDV_MinMaxInt(pDX, m_nMaxErrorToler11, 4, 15);
	DDX_Text(pDX, IDC_MAXERRORTOLER32, m_nMaxErrorToler32);
	DDV_MinMaxInt(pDX, m_nMaxErrorToler32, 4, 15);
	DDX_Text(pDX, IDC_MAXERRORTOLER41, m_nMaxErrorToler41);
	DDV_MinMaxInt(pDX, m_nMaxErrorToler41, 4, 15);
	DDX_Text(pDX, IDC_MAXERRORTOLER42, m_nMaxErrorToler42);
	DDV_MinMaxInt(pDX, m_nMaxErrorToler42, 4, 15);
	DDX_Text(pDX, IDC_MINRELIABILITY11, m_nMinReliability11);
	DDV_MinMaxInt(pDX, m_nMinReliability11, 5, 30);
	DDX_Text(pDX, IDC_MINRELIABILITY12, m_nMinReliability12);
	DDV_MinMaxInt(pDX, m_nMinReliability12, 5, 30);
	DDX_Text(pDX, IDC_MINRELIABILITY21, m_nMinReliability21);
	DDV_MinMaxInt(pDX, m_nMinReliability21, 5, 30);
	DDX_Text(pDX, IDC_MINRELIABILITY22, m_nMinReliability22);
	DDV_MinMaxInt(pDX, m_nMinReliability22, 5, 30);
	DDX_Text(pDX, IDC_MINRELIABILITY31, m_nMinReliability31);
	DDV_MinMaxInt(pDX, m_nMinReliability31, 5, 30);
	DDX_Text(pDX, IDC_MINRELIABILITY32, m_nMinReliability32);
	DDV_MinMaxInt(pDX, m_nMinReliability32, 5, 30);
	DDX_Text(pDX, IDC_MINRELIABILITY41, m_nMinReliability41);
	DDV_MinMaxInt(pDX, m_nMinReliability41, 5, 30);
	DDX_Text(pDX, IDC_MINRELIABILITY42, m_nMinReliability42);
	DDV_MinMaxInt(pDX, m_nMinReliability42, 5, 30);
	DDX_Text(pDX, IDC_SHOWWHICHSIGNAL, m_nShowWhichSignal);
	DDV_MinMaxInt(pDX, m_nShowWhichSignal, 1, 4);
	DDX_Text(pDX, IDC_SINGNAL1, m_fSignal1);
	DDV_MinMaxFloat(pDX, m_fSignal1, 1.f, 10.f);
	DDX_Text(pDX, IDC_SINGNAL2, m_fSignal2);
	DDV_MinMaxFloat(pDX, m_fSignal2, 1.f, 10.f);
	DDX_Text(pDX, IDC_SPACE1, m_fSpace1);
	DDV_MinMaxFloat(pDX, m_fSpace1, 5.f, 8.f);
	DDX_Text(pDX, IDC_SPACE2, m_fSpace2);
	DDV_MinMaxFloat(pDX, m_fSpace2, 5.f, 8.f);
	DDX_Text(pDX, IDC_SPACE3, m_fSpace3);
	DDV_MinMaxFloat(pDX, m_fSpace3, 5.f, 8.f);
	DDX_Text(pDX, IDC_SPACE4, m_fSpace4);
	DDV_MinMaxFloat(pDX, m_fSpace4, 5.f, 8.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetRoadWayParaDlg, CDialog)
	//{{AFX_MSG_MAP(CSetRoadWayParaDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetRoadWayParaDlg message handlers
