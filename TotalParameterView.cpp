//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*                    FX调试记录
1、      界面上各个计算得到的参数用于显示的
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "VehicleFlowCounter.h"
#include "TotalParameterView.h"
#include "VehicleFlowCounterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTotalParameterView

IMPLEMENT_DYNCREATE(CTotalParameterView, CFormView)

CTotalParameterView::CTotalParameterView()
	: CFormView(CTotalParameterView::IDD)
{	
	//{{AFX_DATA_INIT(CTotalParameterView)
	m_fSpeed1 = 0.0f;
	m_fSpeed2 = 0.0f;
	m_fSpeed3 = 0.0f;
	m_fSpeed4 = 0.0f;
	m_fSpeedSum = 0.0f;
	m_sMinuteVehicleNum1 = 0;
	m_sMinuteVehicleNum2 = 0;
	m_sMinuteVehicleNum3 = 0;
	m_sMinuteVehicleNum4 = 0;
	m_sMinuteVehicleNumSum = 0;
	m_fTimeDensity1 = 0.0f;
	m_fTimeDensity2 = 0.0f;
	m_fTimeDensity3 = 0.0f;
	m_fTimeDensity4 = 0.0f;
	m_fTimeDensitySum = 0.0f;	
	m_nVehicleNumSum = 0;
	m_nVehicleNum4 = 0;
	m_nVehicleNum2 = 0;
	m_nVehicleNum3 = 0;
	m_nVehicleNum1 = 0;
	//}}AFX_DATA_INIT
}

CTotalParameterView::~CTotalParameterView()
{
}
/************************************
   FX  随时更新界面新计算得到的参数
************************************/
void CTotalParameterView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTotalParameterView)
	DDX_Text(pDX, IDC_SPEED1, m_fSpeed1);
	DDV_MinMaxFloat(pDX, m_fSpeed1, 0.f, 150.f);
	DDX_Text(pDX, IDC_SPEED2, m_fSpeed2);
	DDV_MinMaxFloat(pDX, m_fSpeed2, 0.f, 150.f);
	DDX_Text(pDX, IDC_SPEED3, m_fSpeed3);
	DDX_Text(pDX, IDC_SPEED4, m_fSpeed4);
	DDV_MinMaxFloat(pDX, m_fSpeed4, 0.f, 150.f);
	DDX_Text(pDX, IDC_SPEEDSUM, m_fSpeedSum);
	DDV_MinMaxFloat(pDX, m_fSpeedSum, 0.f, 150.f);
	DDX_Text(pDX, IDC_MINUTEVEHICLENUM1, m_sMinuteVehicleNum1);
	DDV_MinMaxInt(pDX, m_sMinuteVehicleNum1, 0, 0);
	DDX_Text(pDX, IDC_MINUTEVEHICLENUM2, m_sMinuteVehicleNum2);
	DDV_MinMaxInt(pDX, m_sMinuteVehicleNum2, 0, 0);
	DDX_Text(pDX, IDC_MINUTEVEHICLENUM3, m_sMinuteVehicleNum3);
	DDV_MinMaxInt(pDX, m_sMinuteVehicleNum3, 0, 0);
	DDX_Text(pDX, IDC_MINUTEVEHICLENUM4, m_sMinuteVehicleNum4);
	DDX_Text(pDX, IDC_MINUTEVEHICLENUMSUM, m_sMinuteVehicleNumSum);
	DDV_MinMaxInt(pDX, m_sMinuteVehicleNumSum, 0, 0);
	DDX_Text(pDX, IDC_TIMEDENSITY1, m_fTimeDensity1);
	DDV_MinMaxFloat(pDX, m_fTimeDensity1, 0.f, 100.f);
	DDX_Text(pDX, IDC_TIMEDENSITY2, m_fTimeDensity2);
	DDV_MinMaxFloat(pDX, m_fTimeDensity2, 0.f, 100.f);
	DDX_Text(pDX, IDC_TIMEDENSITY3, m_fTimeDensity3);
	DDV_MinMaxFloat(pDX, m_fTimeDensity3, 0.f, 100.f);
	DDX_Text(pDX, IDC_TIMEDENSITY4, m_fTimeDensity4);
	DDV_MinMaxFloat(pDX, m_fTimeDensity4, 0.f, 100.f);
	DDX_Text(pDX, IDC_TIMEDENSITYSUM, m_fTimeDensitySum);
	DDV_MinMaxFloat(pDX, m_fTimeDensitySum, 0.f, 100.f);
	DDX_Text(pDX, IDC_VEHECLENUMSUM, m_nVehicleNumSum);
	DDV_MinMaxInt(pDX, m_nVehicleNumSum, 0, 2147483647);
	DDX_Text(pDX, IDC_VEHICELNUM4, m_nVehicleNum4);
	DDV_MinMaxInt(pDX, m_nVehicleNum4, 0, 2147483647);
	DDX_Text(pDX, IDC_VEHICLENUM2, m_nVehicleNum2);
	DDV_MinMaxInt(pDX, m_nVehicleNum2, 0, 2147483647);
	DDX_Text(pDX, IDC_VEHICLENUM3, m_nVehicleNum3);
	DDV_MinMaxInt(pDX, m_nVehicleNum3, 0, 2147483647);
	DDX_Text(pDX, IDC_VEHICLENUM1, m_nVehicleNum1);
	DDV_MinMaxInt(pDX, m_nVehicleNum1, 0, 2147483647);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTotalParameterView, CFormView)
	//{{AFX_MSG_MAP(CTotalParameterView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTotalParameterView diagnostics

#ifdef _DEBUG
void CTotalParameterView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTotalParameterView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif 

/************************************
   FX  从Doc中得到计算的数据，然后
     发送更新信号
************************************/
void CTotalParameterView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CVehicleFlowCounterDoc *pDoc=(CVehicleFlowCounterDoc*)GetDocument();
//1车道
	m_nVehicleNum1=pDoc->m_pFlowParaStruc->VehicleNumber1;
	if(m_nVehicleNum1==-858993460)
		m_nVehicleNum1=0;
	m_sMinuteVehicleNum1=pDoc->m_pFlowParaStruc->MinuteVehicleNum1;	
	m_fTimeDensity1=pDoc->m_pFlowParaStruc->TimeDensity1;
	m_fSpeed1=pDoc->m_pFlowParaStruc->Speed1;	
//屏蔽的部分只等计算完放开即可
//2车道
	m_nVehicleNum2=pDoc->m_pFlowParaStruc->VehicleNumber2;
	if(m_nVehicleNum2==-858993460)
		m_nVehicleNum2=0;
	m_sMinuteVehicleNum2=pDoc->m_pFlowParaStruc->MinuteVehicleNum2;
	m_fTimeDensity2=pDoc->m_pFlowParaStruc->TimeDensity2;
	m_fSpeed2=pDoc->m_pFlowParaStruc->Speed2;
//3车道
	m_nVehicleNum3=pDoc->m_pFlowParaStruc->VehicleNumber3;
	if(m_nVehicleNum3==-858993460)
		m_nVehicleNum3=0;
	m_sMinuteVehicleNum3=pDoc->m_pFlowParaStruc->MinuteVehicleNum3;
	m_fTimeDensity3=pDoc->m_pFlowParaStruc->TimeDensity3;
	m_fSpeed3=pDoc->m_pFlowParaStruc->Speed3;

//4车道
	m_nVehicleNum4=pDoc->m_pFlowParaStruc->VehicleNumber4;
	if(m_nVehicleNum4==-858993460)
		m_nVehicleNum4=0;
	m_sMinuteVehicleNum4=pDoc->m_pFlowParaStruc->MinuteVehicleNum4;
	m_fTimeDensity4=pDoc->m_pFlowParaStruc->TimeDensity4;
	m_fSpeed4=pDoc->m_pFlowParaStruc->Speed4;
	
//总的参量
	m_nVehicleNumSum=m_nVehicleNum1+m_nVehicleNum2+m_nVehicleNum3+m_nVehicleNum4;
	m_sMinuteVehicleNumSum=m_sMinuteVehicleNum1+m_sMinuteVehicleNum2+m_sMinuteVehicleNum3+m_sMinuteVehicleNum4;
	if(pDoc->m_nHowManyRoadWay==1)
	{
		m_fTimeDensitySum=m_fTimeDensity1;
		m_fSpeedSum=m_fSpeed1;
	}
	if(pDoc->m_nHowManyRoadWay==2)
	{
		m_fTimeDensitySum=(m_fTimeDensity1+m_fTimeDensity2)/2.0;
		m_fSpeedSum=(m_fSpeed1+m_fSpeed2)/2.0;
	}
	if(pDoc->m_nHowManyRoadWay==3)
	{
		m_fTimeDensitySum=(m_fTimeDensity1+m_fTimeDensity2+m_fTimeDensity3)/3.0;
		m_fSpeedSum=(m_fSpeed1+m_fSpeed2+m_fSpeed3)/3.0;
	}
	if(pDoc->m_nHowManyRoadWay==4)
	{
		m_fTimeDensitySum=(m_fTimeDensity1+m_fTimeDensity2+m_fTimeDensity3+m_fTimeDensity4)/4.0;
		m_fSpeedSum=(m_fSpeed1+m_fSpeed2+m_fSpeed3+m_fSpeed4)/4.0;
	}

	this->UpdateData(false);
	pDoc=NULL;
}
