//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*                    FX调试记录
1、m_pFlowParaStruc1记录的是各个车道的车速，每分钟车流量
   车子通过时间，汽车数量
2、CVehicleFlowCounterView::OnTimer(UINT nIDEvent)
   定时器中对应视频车流量检测的主要部分。
   其中pDoc->UpdateAllViews(this);表示定时器计时到达即
   刷新view所有变量数。
3、SetRoadWayParaDlg是设置车道参数的界面
   SetCheckLineDlg  是设置检测线参数的界面
   FrameRateDlg     是设置频率的界面
   TransFlowPara.cpp是通多阈值计算诸如车速，车流量等参数的地方
   TotalParameterView是显示计算得到的车速和车流量的地方
4、OneRoadway();TwoRoadway();。。。
   几通道对应的处理函数GetNextFrame对应是不同的
5、m_fSpace1是1通道两条检测线的大致距离，用来检测车速的
   (默认值是6m)
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "VehicleFlowCounter.h"

#include "VehicleFlowCounterDoc.h"
#include "VehicleFlowCounterView.h"
//#include "AVIProducer.h"
#include "Dib.h"
#include "FrameRateDlg.h"
#include "TotalParameterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVehicleFlowCounterView

IMPLEMENT_DYNCREATE(CVehicleFlowCounterView, CView)

BEGIN_MESSAGE_MAP(CVehicleFlowCounterView, CView)
	//{{AFX_MSG_MAP(CVehicleFlowCounterView)
	ON_WM_TIMER()
	ON_COMMAND(ID_DISPLAY, OnDisplay)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY, OnUpdateDisplay)
	ON_UPDATE_COMMAND_UI(ID_PAUSE, OnUpdatePause)	
	ON_COMMAND(ID_SETLINE, OnSetline)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_NEXTFRAME, OnNextframe)
	ON_COMMAND(ID_PREVIOUSFRAME, OnPreviousframe)
	ON_COMMAND(ID_NEXTTENFRAME, OnNexttenframe)
	ON_COMMAND(ID_PREVIOUSFRAMETEN, OnPreviousframeten)
	ON_COMMAND(ID_SHOWLINESIGNAL, OnShowlinesignal)
	ON_COMMAND(ID_HIDELINESIGNAL, OnHidelinesignal)
	ON_UPDATE_COMMAND_UI(ID_SHOWLINESIGNAL, OnUpdateShowlinesignal)
	ON_UPDATE_COMMAND_UI(ID_HIDELINESIGNAL, OnUpdateHidelinesignal)
	ON_COMMAND(ID_SETFRAMERATE, OnSetframerate)
	ON_COMMAND(ID_SETROADWAYPARAMETER, OnSetroadwayparameter)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/************************************
   FX    构造函数中初始化各个参数
************************************/
CVehicleFlowCounterView::CVehicleFlowCounterView()
{
	m_pSetCheckLineDlg=new CSetCheckLineDlg();
	m_pSetCheckLineDlg->OpenDetectLineFile();
	m_pSetRoadWayParaDlg=new CSetRoadWayParaDlg();

	m_pImageDeal=new CImageDeal();
	m_pImageDeal1=new CImageDeal1();
	m_pImageDeal2=new CImageDeal2();
	m_pImageDeal3=new CImageDeal3();

	m_pLineSignal=new CLineSignal();
	m_pFlowParaStruc=new TRANSPORTATIONFLOWPARAMETER[1];
	m_pSaveImageRegion=new BYTE[240*320*3];
	m_pdwPos=new DWORD[1];

	m_pFlowParaStruc1=m_pFlowParaStruc;
	m_pFlowParaStruc->VehicleNumber1=0;
	m_pFlowParaStruc->Speed1=0;
	m_pFlowParaStruc->TimeDensity1=0.0;
	m_pFlowParaStruc->MinuteVehicleNum1=0;

	m_pFlowParaStruc->VehicleNumber2=0;
	m_pFlowParaStruc->Speed2=0;
	m_pFlowParaStruc->TimeDensity2=0;
	m_pFlowParaStruc->MinuteVehicleNum2=0;

	m_pFlowParaStruc->VehicleNumber3=0;
	m_pFlowParaStruc->Speed3=0;
	m_pFlowParaStruc->TimeDensity3=0;
	m_pFlowParaStruc->MinuteVehicleNum3=0;
	
	m_pFlowParaStruc->VehicleNumber4=0;
	m_pFlowParaStruc->Speed4=0;
	m_pFlowParaStruc->TimeDensity4=0;
	m_pFlowParaStruc->MinuteVehicleNum4=0;
	
	m_pFlowParaStruc->VehicleNumberSum=0;
	m_pFlowParaStruc->SpeedSum=0;
	m_pFlowParaStruc->TimeDensitySum=0;
	m_pFlowParaStruc->MinuteVehicleNumSum=0;
		
	//bIsShow=FALSE;
	//FX注释：开始就显示检测线等信息
	bIsShow=TRUE;	
	bIsDisplay=FALSE;
	bIsPause=TRUE;
	bIsFileOpen=FALSE;
	bIsInitializtion=FALSE;
	bIsSetRoadwayPara=FALSE;
		
	m_nRoadWay11Width=0;
	m_nRoadWay12Width=0;
	m_nRoadWay21Width=0;
	m_nRoadWay22Width=0;
	m_nRoadWay31Width=0;
	m_nRoadWay32Width=0;
	bIsShowSignal1=FALSE;
	bIsShowSignal2=FALSE;
	bIsShowSignal3=FALSE;
	bIsShowSignal4=FALSE;
//车道参数
	m_nHowManyRoadWay=3;   //default value equal 3
	m_nShowWhichSignal=2;  //default value equal 2
//1车道
	m_nMaxErrorToler11=10; //最大的容错度
	m_nMinReliability11=12;//最小的可信度
	m_nMaxErrorToler12=7;
	m_nMinReliability12=15;
//车道2
	m_nMaxErrorToler21=5;//最大的容错度
	m_nMinReliability21=8;//最小的可信度	
	m_nMaxErrorToler22=4;
	m_nMinReliability22=10;	
//车道3
	m_nMaxErrorToler31=6;//最大的容错度
	m_nMinReliability31=9;//最小的可信度	
	m_nMaxErrorToler32=5;
	m_nMinReliability32=12;	
//车道4
	m_nMaxErrorToler41=6;//最大的容错度
	m_nMinReliability41=9;//最小的可信度	
	m_nMaxErrorToler42=5;
	m_nMinReliability42=12;
//信号增强系数
	m_fSignal1=5.0;
	m_fSignal2=4.0;
//两线间的距离
	m_fSpace1=6;
	m_fSpace2=6;
	m_fSpace3=6;
	m_fSpace4=6;
//default value equal 40			
	m_nMillisecondPerFrame=40;
	m_nFlag=0;
	bIsStop=FALSE;
}

CVehicleFlowCounterView::~CVehicleFlowCounterView()
{
	m_pImageDeal=NULL;
	m_pImageDeal1=NULL;
	m_pImageDeal2=NULL;
	m_pImageDeal3=NULL;

	m_pDib=NULL;
	m_pDib=NULL;
	m_pSetCheckLineDlg=NULL;

	m_pLineSignal;
	delete[] m_pFlowParaStruc1;
	m_pFlowParaStruc1=NULL;	
	delete[] m_pSaveImageRegion;
	m_pSaveImageRegion=NULL;
	delete[] m_pdwPos;
	m_pdwPos=NULL;
}

BOOL CVehicleFlowCounterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVehicleFlowCounterView drawing

void CVehicleFlowCounterView::OnDraw(CDC *pDC)
{
	CVehicleFlowCounterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CVehicleFlowCounterView printing

BOOL CVehicleFlowCounterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVehicleFlowCounterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVehicleFlowCounterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CVehicleFlowCounterView diagnostics

#ifdef _DEBUG
void CVehicleFlowCounterView::AssertValid() const
{
	CView::AssertValid();
}

void CVehicleFlowCounterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVehicleFlowCounterDoc* CVehicleFlowCounterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVehicleFlowCounterDoc)));
	return (CVehicleFlowCounterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
/************************************
       FX    定时器处理部分
	      每隔多少时间处理一次
************************************/
void CVehicleFlowCounterView::OnTimer(UINT nIDEvent) 
{
	//设置检测线的位置参数
	DeliverCheckLinePara();
	//确定显示几路通道的数据
	ShowWhichSignal();
	//FX注释：几个通道数对应处理函数
	if(m_nHowManyRoadWay==1)
		OneRoadway();
	if(m_nHowManyRoadWay==2)
		TwoRoadway();
	if(m_nHowManyRoadWay==3)
		ThreeRoadway();
	if(m_nHowManyRoadWay==4)
		FourRoadway();	
//	if(m_pImageDeal->m_dwPos==(m_pImageDeal->m_dwLength-1))
//		Invalidate();
	if((bIsStop==TRUE)&&(m_pImageDeal->m_dwPos==(m_pImageDeal->m_dwLength-2)/*1*/))
	{
		bIsDisplay=FALSE;
		bIsPause=TRUE;	
		MessageBox("视频结束!如果需要重新测试请按播放按钮。","系统信息",MB_ICONINFORMATION|MB_OK);
	}
	if(m_pImageDeal->m_dwPos==1)
		bIsStop=TRUE;
	//每到定时器的时间，我就相应的刷新视角上的所有数据
	CVehicleFlowCounterDoc *pDoc=(CVehicleFlowCounterDoc*)GetDocument();
	pDoc->m_pFlowParaStruc=m_pFlowParaStruc1;
	pDoc->m_nHowManyRoadWay=m_nHowManyRoadWay;
	pDoc->UpdateAllViews(this);	

//每240帧更新	
	if((m_pImageDeal->m_dwPos%240==0)&&m_pImageDeal->m_dwPos!=0)
		Invalidate();

	CView::OnTimer(nIDEvent);
}
/************************************
       FX     设置车道宽度
	   (就是载入之前手动输入参数)
************************************/
void CVehicleFlowCounterView::DeliverCheckLinePara()
{
//1车道
	m_nHeightPos1=m_pSetCheckLineDlg->m_nHeightPos1;  //m_pSetCheckLineDlg对应检测线对话框
	m_nLeftPos1  =m_pSetCheckLineDlg->m_nLeftPos1;
	m_nRightPos1 =m_pSetCheckLineDlg->m_nRightPos1;
	m_nRoadWay11Width=abs(m_nRightPos1-m_nLeftPos1);

	m_nHeightPos2=m_pSetCheckLineDlg->m_nHeightPos2;
	m_nLeftPos2  =m_pSetCheckLineDlg->m_nLeftPos2;
	m_nRightPos2 =m_pSetCheckLineDlg->m_nRightPos2;
	m_nRoadWay12Width=abs(m_nRightPos2-m_nLeftPos2);
//2车道
	m_nHeightPos3=m_pSetCheckLineDlg->m_nHeightPos3;
	m_nLeftPos3  =m_pSetCheckLineDlg->m_nLeftPos3;
	m_nRightPos3 =m_pSetCheckLineDlg->m_nRightPos3;
	m_nRoadWay21Width=abs(m_nRightPos3-m_nLeftPos3)+m_nRoadWay11Width;

	m_nHeightPos4=m_pSetCheckLineDlg->m_nHeightPos4;
	m_nLeftPos4  =m_pSetCheckLineDlg->m_nLeftPos4;
	m_nRightPos4 =m_pSetCheckLineDlg->m_nRightPos4;
	m_nRoadWay22Width=abs(m_nRightPos4-m_nLeftPos4)+m_nRoadWay12Width;
//3车道
	m_nHeightPos5=m_pSetCheckLineDlg->m_nHeightPos5;
	m_nLeftPos5  =m_pSetCheckLineDlg->m_nLeftPos5;
	m_nRightPos5 =m_pSetCheckLineDlg->m_nRightPos5;
	m_nRoadWay31Width=abs(m_nRightPos5-m_nLeftPos5)+m_nRoadWay21Width;

	m_nHeightPos6=m_pSetCheckLineDlg->m_nHeightPos6;
	m_nLeftPos6  =m_pSetCheckLineDlg->m_nLeftPos6;
	m_nRightPos6 =m_pSetCheckLineDlg->m_nRightPos6;
	m_nRoadWay32Width=abs(m_nRightPos6-m_nLeftPos6)+m_nRoadWay22Width;
//4车道
	m_nHeightPos7=m_pSetCheckLineDlg->m_nHeightPos7;
	m_nLeftPos7  =m_pSetCheckLineDlg->m_nLeftPos7;
	m_nRightPos7 =m_pSetCheckLineDlg->m_nRightPos7;

	m_nHeightPos8=m_pSetCheckLineDlg->m_nHeightPos8;
	m_nLeftPos8  =m_pSetCheckLineDlg->m_nLeftPos8;
	m_nRightPos8 =m_pSetCheckLineDlg->m_nRightPos8;

	m_nLineHeight=m_pSetCheckLineDlg->m_nLineHeight;
}
/************************************
       FX     显示几个通道的数据
************************************/
void CVehicleFlowCounterView::ShowWhichSignal()
{
	if(m_nShowWhichSignal==1)
	{
		bIsShowSignal1=TRUE;
		bIsShowSignal2=FALSE;
		bIsShowSignal3=FALSE;
		bIsShowSignal4=FALSE;
	}
	if(m_nShowWhichSignal==2)
	{
		bIsShowSignal1=FALSE;
		bIsShowSignal2=TRUE;
		bIsShowSignal3=FALSE;
		bIsShowSignal4=FALSE;
	}
	if(m_nShowWhichSignal==3)
	{
		bIsShowSignal1=FALSE;
		bIsShowSignal2=FALSE;
		bIsShowSignal3=TRUE;
		bIsShowSignal4=FALSE;
	}
	if(m_nShowWhichSignal==4)
	{
		bIsShowSignal1=FALSE;
		bIsShowSignal2=FALSE;
		bIsShowSignal3=FALSE;
		bIsShowSignal4=TRUE;
	}
}
/************************************
   FX     仅一个通道的统计函数
************************************/
TRANSPORTATIONFLOWPARAMETER* CVehicleFlowCounterView::OneRoadway()
{
	CClientDC dc(this);	
	m_pFlowParaStruc=m_pImageDeal->GetNextFrame(&dc,m_nLeftPos1,m_nRightPos1,m_nHeightPos1,
		                           m_nLeftPos2,m_nRightPos2,m_nHeightPos2,m_fSignal1,m_fSignal2,m_fSpace1,
								   m_nMaxErrorToler11,m_nMinReliability11,m_nMaxErrorToler12,m_nMinReliability12,
								   m_nLineHeight,bIsPause,m_nFlag, bIsShow,bIsDisplay,m_pSaveImageRegion,m_pdwPos,bIsShowSignal1);	
	m_pFlowParaStruc1->MinuteVehicleNum1=m_pFlowParaStruc->MinuteVehicleNum1;
	m_pFlowParaStruc1->Speed1=m_pFlowParaStruc->Speed1;
	m_pFlowParaStruc1->TimeDensity1=m_pFlowParaStruc->TimeDensity1;
	m_pFlowParaStruc1->VehicleNumber1=m_pFlowParaStruc->VehicleNumber1;
	return m_pFlowParaStruc1;
}
/************************************
    FX     两个通道的统计函数
************************************/
TRANSPORTATIONFLOWPARAMETER* CVehicleFlowCounterView::TwoRoadway()
{
	CClientDC dc(this);
	m_pFlowParaStruc=m_pImageDeal->GetNextFrame(&dc,m_nLeftPos1,m_nRightPos1,m_nHeightPos1,
		                           m_nLeftPos2,m_nRightPos2,m_nHeightPos2,m_fSignal1,m_fSignal2,m_fSpace1,
								   m_nMaxErrorToler11,m_nMinReliability11,m_nMaxErrorToler12,m_nMinReliability12,
								   m_nLineHeight,bIsPause,m_nFlag, bIsShow,bIsDisplay,m_pSaveImageRegion,m_pdwPos,bIsShowSignal1);	
	m_pFlowParaStruc1->MinuteVehicleNum1=m_pFlowParaStruc->MinuteVehicleNum1;
	m_pFlowParaStruc1->Speed1=m_pFlowParaStruc->Speed1;
	m_pFlowParaStruc1->TimeDensity1=m_pFlowParaStruc->TimeDensity1;
	m_pFlowParaStruc1->VehicleNumber1=m_pFlowParaStruc->VehicleNumber1;
		
	m_pFlowParaStruc=m_pImageDeal1->GetNextFrame(&dc,m_nLeftPos3,m_nRightPos3,m_nHeightPos3,m_nRoadWay11Width,
		                           m_nLeftPos4,m_nRightPos4,m_nHeightPos4,m_nRoadWay12Width,m_fSignal1,m_fSignal2,m_fSpace2,
								   m_nMaxErrorToler21,m_nMinReliability21,m_nMaxErrorToler22,m_nMinReliability22,
								   m_nLineHeight,bIsPause,m_nFlag,bIsShow,bIsDisplay,m_pSaveImageRegion,m_pdwPos,bIsShowSignal2);				
	m_pFlowParaStruc1->MinuteVehicleNum2=m_pFlowParaStruc->MinuteVehicleNum2;
	m_pFlowParaStruc1->Speed2=m_pFlowParaStruc->Speed2;
	m_pFlowParaStruc1->TimeDensity2=m_pFlowParaStruc->TimeDensity2;
	m_pFlowParaStruc1->VehicleNumber2=m_pFlowParaStruc->VehicleNumber2;
	
	return m_pFlowParaStruc1;
}
/************************************
    FX     三个通道的统计函数
************************************/
TRANSPORTATIONFLOWPARAMETER* CVehicleFlowCounterView::ThreeRoadway()
{
	CClientDC dc(this);
	//一通道的车辆统计
	m_pFlowParaStruc=m_pImageDeal->GetNextFrame(&dc,m_nLeftPos1,m_nRightPos1,m_nHeightPos1,
		                           m_nLeftPos2,m_nRightPos2,m_nHeightPos2,m_fSignal1,m_fSignal2,m_fSpace1,
								   m_nMaxErrorToler11,m_nMinReliability11,m_nMaxErrorToler12,m_nMinReliability12,
								   m_nLineHeight,bIsPause,m_nFlag, bIsShow,bIsDisplay,m_pSaveImageRegion,m_pdwPos,bIsShowSignal1);	
	m_pFlowParaStruc1->MinuteVehicleNum1=m_pFlowParaStruc->MinuteVehicleNum1;
	m_pFlowParaStruc1->Speed1           =m_pFlowParaStruc->Speed1;
	m_pFlowParaStruc1->TimeDensity1     =m_pFlowParaStruc->TimeDensity1;
	m_pFlowParaStruc1->VehicleNumber1   =m_pFlowParaStruc->VehicleNumber1;
	//二通道的车辆统计
	m_pFlowParaStruc=m_pImageDeal1->GetNextFrame(&dc,m_nLeftPos3,m_nRightPos3,m_nHeightPos3,m_nRoadWay11Width,
		                           m_nLeftPos4,m_nRightPos4,m_nHeightPos4,m_nRoadWay12Width,m_fSignal1,m_fSignal2,m_fSpace2,
								   m_nMaxErrorToler21,m_nMinReliability21,m_nMaxErrorToler22,m_nMinReliability22,
								   m_nLineHeight,bIsPause,m_nFlag,bIsShow,bIsDisplay,m_pSaveImageRegion,m_pdwPos,bIsShowSignal2);					
	m_pFlowParaStruc1->MinuteVehicleNum2=m_pFlowParaStruc->MinuteVehicleNum2;
	m_pFlowParaStruc1->Speed2           =m_pFlowParaStruc->Speed2;
	m_pFlowParaStruc1->TimeDensity2     =m_pFlowParaStruc->TimeDensity2;
	m_pFlowParaStruc1->VehicleNumber2   =m_pFlowParaStruc->VehicleNumber2;
	//三通道的车辆统计
	m_pFlowParaStruc=m_pImageDeal2->GetNextFrame(&dc,m_nLeftPos5,m_nRightPos5,m_nHeightPos5,m_nRoadWay21Width,
		                           m_nLeftPos6,m_nRightPos6,m_nHeightPos6,m_nRoadWay22Width,m_fSignal1,m_fSignal2,m_fSpace3,
								   m_nMaxErrorToler31,m_nMinReliability31,m_nMaxErrorToler32,m_nMinReliability32,
								   m_nLineHeight,bIsPause,m_nFlag,bIsShow,bIsDisplay,m_pSaveImageRegion,m_pdwPos,bIsShowSignal3);					
	m_pFlowParaStruc1->MinuteVehicleNum3=m_pFlowParaStruc->MinuteVehicleNum3;
	m_pFlowParaStruc1->Speed3           =m_pFlowParaStruc->Speed3;
	m_pFlowParaStruc1->TimeDensity3     =m_pFlowParaStruc->TimeDensity3;
	m_pFlowParaStruc1->VehicleNumber3   =m_pFlowParaStruc->VehicleNumber3;

	return m_pFlowParaStruc1;
}
/************************************
       FX     四个通道的统计函数
************************************/
TRANSPORTATIONFLOWPARAMETER* CVehicleFlowCounterView::FourRoadway()
{
	CClientDC dc(this);
	m_pFlowParaStruc=m_pImageDeal->GetNextFrame(&dc,m_nLeftPos1,m_nRightPos1,m_nHeightPos1,
		                           m_nLeftPos2,m_nRightPos2,m_nHeightPos2,m_fSignal1,m_fSignal2,m_fSpace1,
								   m_nMaxErrorToler11,	m_nMinReliability11,m_nMaxErrorToler12,m_nMinReliability12,
								   m_nLineHeight,bIsPause,m_nFlag, bIsShow,bIsDisplay,m_pSaveImageRegion,m_pdwPos,bIsShowSignal1);	
	m_pFlowParaStruc1->MinuteVehicleNum1=m_pFlowParaStruc->MinuteVehicleNum1;
	m_pFlowParaStruc1->Speed1=m_pFlowParaStruc->Speed1;
	m_pFlowParaStruc1->TimeDensity1=m_pFlowParaStruc->TimeDensity1;
	m_pFlowParaStruc1->VehicleNumber1=m_pFlowParaStruc->VehicleNumber1;
	
	m_pFlowParaStruc=m_pImageDeal1->GetNextFrame(&dc,m_nLeftPos3,m_nRightPos3,m_nHeightPos3,m_nRoadWay11Width,
		                           m_nLeftPos4,m_nRightPos4,m_nHeightPos4,m_nRoadWay12Width,m_fSignal1,m_fSignal2,m_fSpace2,
								   m_nMaxErrorToler21,m_nMinReliability21,m_nMaxErrorToler22,m_nMinReliability22,
								   m_nLineHeight,bIsPause,m_nFlag,bIsShow,bIsDisplay,m_pSaveImageRegion,m_pdwPos,bIsShowSignal2);				
	m_pFlowParaStruc1->MinuteVehicleNum2=m_pFlowParaStruc->MinuteVehicleNum2;
	m_pFlowParaStruc1->Speed2=m_pFlowParaStruc->Speed2;
	m_pFlowParaStruc1->TimeDensity2=m_pFlowParaStruc->TimeDensity2;
	m_pFlowParaStruc1->VehicleNumber2=m_pFlowParaStruc->VehicleNumber2;

	m_pFlowParaStruc=m_pImageDeal2->GetNextFrame(&dc,m_nLeftPos5,m_nRightPos5,m_nHeightPos5,m_nRoadWay21Width,
		                           m_nLeftPos6,m_nRightPos6,m_nHeightPos6,m_nRoadWay22Width,m_fSignal1,m_fSignal2,m_fSpace3,
								   m_nMaxErrorToler31,m_nMinReliability31,m_nMaxErrorToler32,m_nMinReliability32,
								   m_nLineHeight,bIsPause,m_nFlag,bIsShow,bIsDisplay,m_pSaveImageRegion,m_pdwPos,bIsShowSignal3);				
	
	m_pFlowParaStruc1->MinuteVehicleNum3=m_pFlowParaStruc->MinuteVehicleNum3;
	m_pFlowParaStruc1->Speed3=m_pFlowParaStruc->Speed3;
	m_pFlowParaStruc1->TimeDensity3=m_pFlowParaStruc->TimeDensity3;
	m_pFlowParaStruc1->VehicleNumber3=m_pFlowParaStruc->VehicleNumber3;

	m_pFlowParaStruc=m_pImageDeal3->GetNextFrame(&dc,m_nLeftPos7,m_nRightPos7,m_nHeightPos7,m_nRoadWay31Width,
		                           m_nLeftPos8,m_nRightPos8,m_nHeightPos8,m_nRoadWay32Width,m_fSignal1,m_fSignal2,m_fSpace4,
								   m_nMaxErrorToler41,m_nMinReliability41,m_nMaxErrorToler42,m_nMinReliability42,
								   m_nLineHeight,bIsPause,m_nFlag,bIsShow,bIsDisplay,m_pSaveImageRegion,m_pdwPos,bIsShowSignal4);				
	
	m_pFlowParaStruc1->MinuteVehicleNum4=m_pFlowParaStruc->MinuteVehicleNum4;
	m_pFlowParaStruc1->Speed4=m_pFlowParaStruc->Speed4;
	m_pFlowParaStruc1->TimeDensity4=m_pFlowParaStruc->TimeDensity4;
	m_pFlowParaStruc1->VehicleNumber4=m_pFlowParaStruc->VehicleNumber4;

	return m_pFlowParaStruc1;
}
/************************************
       FX     打开视频播放
************************************/
void CVehicleFlowCounterView::OnDisplay() 
{
	if(bIsFileOpen==FALSE)
	{
		MessageBox("请首先打开视频文件!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
    if(bIsInitializtion==FALSE)
	{
		MessageBox("请先初始化参数!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
    SetTimer(0,m_nMillisecondPerFrame,NULL);
	bIsDisplay=TRUE;
	bIsPause=FALSE;
}
/************************************
       FX     暂停视频播放
************************************/
void CVehicleFlowCounterView::OnPause() 
{
	bIsDisplay=FALSE;
	bIsPause=TRUE;
}

//函数OnUpdateDisplay(CCmdUI *pCmdUI)使在Enable()括号中的值为真是才
//使OnDisplay()函数有效，否则为无效(菜单栏中字体为灰色)
void CVehicleFlowCounterView::OnUpdateDisplay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(bIsDisplay==FALSE);	
}
//函数OnUpdatePause(CCndUI *pCmdUI)的作用同上一函数
void CVehicleFlowCounterView::OnUpdatePause(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(bIsPause==FALSE);
}

/************************************
       FX     设置检测线
************************************/
void CVehicleFlowCounterView::OnSetline() 
{
	if(bIsFileOpen==FALSE)
	{
		MessageBox("请首先打开视频文件!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
	if(bIsSetRoadwayPara==FALSE)
	{
		MessageBox("请先设置车道参数!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
	//视频先暂停播放
	OnPause();	
	if(m_pSetCheckLineDlg->DoModal()==IDOK)
	{  
		//对话框按下OK，设置检测线
		m_pSetCheckLineDlg->SaveLinePos();
		bIsInitializtion=TRUE;		
		Invalidate();
		//设置完检测线，就开始播放视频
		bIsDisplay=TRUE;
		bIsPause=FALSE;		
	}	
}
/************************************
       FX     打开AVI交通视频
************************************/
void CVehicleFlowCounterView::OnFileOpen() 
{
	if(bIsFileOpen==TRUE)	
		OnPause();
	CString filePath;
	CFileDialog fileOpenDlg(TRUE,"avi,mpg","*.avi",NULL,"AVI Files(*.mpg)",NULL);	
	if(fileOpenDlg.DoModal()==IDCANCEL)
		return;
	filePath = fileOpenDlg.GetPathName();
	m_pImageDeal->Initial(filePath);
	bIsFileOpen=TRUE;
	SetTimer(0,m_nMillisecondPerFrame,NULL);
}

void CVehicleFlowCounterView::OnNextframe() 
{
	if(bIsFileOpen==FALSE)
	{
		MessageBox("请首先打开视频文件!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
	if(bIsInitializtion==FALSE)
	{
		MessageBox("请先初始化参数!","系统信息",MB_OK);
		return;
	}
	m_nFlag++;
	Invalidate();
}

void CVehicleFlowCounterView::OnPreviousframe() 
{
	if(bIsFileOpen==FALSE)
	{
		MessageBox("请首先打开视频文件!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
	if(bIsInitializtion==FALSE)
	{
		MessageBox("请先初始化参数!","系统信息",MB_OK);
		return;
	}
	m_nFlag--;
	Invalidate();		
}

void CVehicleFlowCounterView::OnNexttenframe() 
{
	if(bIsFileOpen==FALSE)
	{
		MessageBox("请首先打开视频文件!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
	if(bIsInitializtion==FALSE)
	{
		MessageBox("请先初始化参数!","系统信息",MB_OK);
		return;
	}
	m_nFlag=m_nFlag+10;
	Invalidate();	
}

void CVehicleFlowCounterView::OnPreviousframeten() 
{
	if(bIsFileOpen==FALSE)
	{
		MessageBox("请首先打开视频文件!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
	if(bIsInitializtion==FALSE)
	{
		MessageBox("请先初始化参数!","系统信息",MB_OK);
		return;
	}
	m_nFlag=m_nFlag-10;
	Invalidate();	
}
/***********************************
       FX    设置是否显示处理结果
	            (bIsShow)
************************************/
void CVehicleFlowCounterView::OnShowlinesignal() 
{
	if(bIsFileOpen==FALSE)
	{
		MessageBox("请首先打开视频文件!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
	bIsShow=TRUE;
	Invalidate();
}
void CVehicleFlowCounterView::OnHidelinesignal() 
{
	bIsShow=FALSE;
	Invalidate();
}
void CVehicleFlowCounterView::OnUpdateShowlinesignal(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(bIsShow==FALSE);
}
void CVehicleFlowCounterView::OnUpdateHidelinesignal(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(bIsShow==TRUE);
}

/***********************************
       FX     设置视频帧率
	       (多长时间处理一次计数)
************************************/
void CVehicleFlowCounterView::OnSetframerate() 
{
	if(bIsFileOpen==FALSE)
	{
		MessageBox("请首先打开视频文件!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
	KillTimer(0);
	CFrameRateDlg frameRateDlg;
	frameRateDlg.m_nMillisecondNum=m_nMillisecondPerFrame;
	if(frameRateDlg.DoModal()==IDOK)
		m_nMillisecondPerFrame=frameRateDlg.m_nMillisecondNum;
	SetTimer(0,m_nMillisecondPerFrame,NULL);
	Invalidate();
}

void CVehicleFlowCounterView::OpenDetectLineFile()
{
	CFile file;
	if(!file.Open("LinePos.Dat",CFile::modeRead,NULL))	return;
	file.Read(&m_nHeightPos1,sizeof(int));
	file.Read(&m_nLeftPos1,sizeof(int));
	file.Read(&m_nRightPos1,sizeof(int));
	file.Read(&m_nHeightPos2,sizeof(int));
	file.Read(&m_nLeftPos2,sizeof(int));
	file.Read(&m_nRightPos2,sizeof(int));
	file.Read(&m_nLineHeight,sizeof(int));
	file.Read(&m_nHeightPos3,sizeof(int));
	file.Read(&m_nLeftPos3,sizeof(int));
	file.Read(&m_nRightPos3,sizeof(int));
	file.Read(&m_nHeightPos4,sizeof(int));
	file.Read(&m_nLeftPos4,sizeof(int));
	file.Read(&m_nRightPos4,sizeof(int));
	file.Read(&m_nHeightPos5,sizeof(int));
	file.Read(&m_nLeftPos5,sizeof(int));
	file.Read(&m_nRightPos5,sizeof(int));
	file.Read(&m_nHeightPos6,sizeof(int));
	file.Read(&m_nLeftPos6,sizeof(int));
	file.Read(&m_nRightPos6,sizeof(int));
	file.Read(&m_nHeightPos7,sizeof(int));
	file.Read(&m_nLeftPos7,sizeof(int));
	file.Read(&m_nRightPos7,sizeof(int));
	file.Read(&m_nHeightPos8,sizeof(int));
	file.Read(&m_nLeftPos8,sizeof(int));
	file.Read(&m_nRightPos8,sizeof(int));
	file.Close();
}

/************************************
       FX     设置车道参数
************************************/
void CVehicleFlowCounterView::OnSetroadwayparameter() 
{
	if(bIsFileOpen==FALSE)
	{
		MessageBox("请首先打开视频文件!","系统信息",MB_ICONINFORMATION|MB_OK);
		return;
	}
	//先暂停视频播放
	OnPause();
	//车道参数对话框中参数初始化
	m_pSetRoadWayParaDlg->m_nHowManyRoadway =m_nHowManyRoadWay;
	m_pSetRoadWayParaDlg->m_nShowWhichSignal=m_nShowWhichSignal;
	m_pSetRoadWayParaDlg->m_fSignal1        =m_fSignal1;
	m_pSetRoadWayParaDlg->m_fSignal2        =m_fSignal2;
	m_pSetRoadWayParaDlg->m_fSpace1         =m_fSpace1;
	m_pSetRoadWayParaDlg->m_fSpace2         =m_fSpace2;
	m_pSetRoadWayParaDlg->m_fSpace3         =m_fSpace3;
	m_pSetRoadWayParaDlg->m_fSpace4         =m_fSpace4;
	m_pSetRoadWayParaDlg->m_nMinReliability11=m_nMinReliability11;
	m_pSetRoadWayParaDlg->m_nMinReliability12=m_nMinReliability12;
	m_pSetRoadWayParaDlg->m_nMaxErrorToler11=m_nMaxErrorToler11;
	m_pSetRoadWayParaDlg->m_nMaxErrorToler12=m_nMaxErrorToler12;
	m_pSetRoadWayParaDlg->m_nMinReliability21=m_nMinReliability21;
	m_pSetRoadWayParaDlg->m_nMinReliability22=m_nMinReliability22;
	m_pSetRoadWayParaDlg->m_nMaxErrorToler21=m_nMaxErrorToler21;
	m_pSetRoadWayParaDlg->m_nMaxErrorToler22=m_nMaxErrorToler22;
	m_pSetRoadWayParaDlg->m_nMinReliability31=m_nMinReliability31;
	m_pSetRoadWayParaDlg->m_nMinReliability32=m_nMinReliability32;
	m_pSetRoadWayParaDlg->m_nMaxErrorToler31=m_nMaxErrorToler31;
	m_pSetRoadWayParaDlg->m_nMaxErrorToler32=m_nMaxErrorToler32;
	m_pSetRoadWayParaDlg->m_nMinReliability41=m_nMinReliability41;
	m_pSetRoadWayParaDlg->m_nMinReliability42=m_nMinReliability42;
	m_pSetRoadWayParaDlg->m_nMaxErrorToler41=m_nMaxErrorToler41;
	m_pSetRoadWayParaDlg->m_nMaxErrorToler42=m_nMaxErrorToler42;
	//当该对话框按下OK键，车道相关参数重新设置
	if(m_pSetRoadWayParaDlg->DoModal()==IDOK)
	{  
		m_nHowManyRoadWay=m_pSetRoadWayParaDlg->m_nHowManyRoadway;
		m_nShowWhichSignal=m_pSetRoadWayParaDlg->m_nShowWhichSignal;
		m_fSignal1=m_pSetRoadWayParaDlg->m_fSignal1;
		m_fSignal2=m_pSetRoadWayParaDlg->m_fSignal2;
		m_fSpace1=m_pSetRoadWayParaDlg->m_fSpace1;
		m_fSpace2=m_pSetRoadWayParaDlg->m_fSpace2;
		m_fSpace3=m_pSetRoadWayParaDlg->m_fSpace3;
		m_fSpace4=m_pSetRoadWayParaDlg->m_fSpace4;
		m_nMinReliability11=m_pSetRoadWayParaDlg->m_nMinReliability11;
		m_nMinReliability12=m_pSetRoadWayParaDlg->m_nMinReliability12;
		m_nMaxErrorToler11=m_pSetRoadWayParaDlg->m_nMaxErrorToler11;
		m_nMaxErrorToler12=m_pSetRoadWayParaDlg->m_nMaxErrorToler12;
		m_nMinReliability21=m_pSetRoadWayParaDlg->m_nMinReliability21;
		m_nMinReliability22=m_pSetRoadWayParaDlg->m_nMinReliability22;
		m_nMaxErrorToler21=m_pSetRoadWayParaDlg->m_nMaxErrorToler21;
		m_nMaxErrorToler22=m_pSetRoadWayParaDlg->m_nMaxErrorToler22;
		m_nMinReliability31=m_pSetRoadWayParaDlg->m_nMinReliability31;
		m_nMinReliability32=m_pSetRoadWayParaDlg->m_nMinReliability32;
		m_nMaxErrorToler31=m_pSetRoadWayParaDlg->m_nMaxErrorToler31;
		m_nMaxErrorToler32=m_pSetRoadWayParaDlg->m_nMaxErrorToler32;
		m_nMinReliability41=m_pSetRoadWayParaDlg->m_nMinReliability41;
		m_nMinReliability42=m_pSetRoadWayParaDlg->m_nMinReliability42;
		m_nMaxErrorToler41=m_pSetRoadWayParaDlg->m_nMaxErrorToler41;
		m_nMaxErrorToler42=m_pSetRoadWayParaDlg->m_nMaxErrorToler42;
		//车道参数设置标志位置1
		bIsSetRoadwayPara=TRUE;	
		Invalidate();		
	}	
}


