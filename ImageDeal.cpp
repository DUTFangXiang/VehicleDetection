// ImageDeal.cpp: implementation of the CImageDeal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageDeal.h"
//#include "AVIProducer.h"
#include "FlowCounter.h"
#include "KirschEdgeDetect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageDeal::CImageDeal()
{
	m_lpStoreBac1=new BYTE[150*320*20*3];//用存放用于背景更新的连续
	m_lpStoreBac2=new BYTE[150*320*20*3];//11帧背景，更新时用第6帧背景
	m_lpBacFrame1=new BYTE[320*20*3];//用存放用于背景更新的连续11帧背景，更新时用第6帧背景
	m_lpBacFrame2=new BYTE[320*20*3];	
	TemStoreBac1=m_lpStoreBac1;
	TemStoreBac2=m_lpStoreBac2;
}

CImageDeal::~CImageDeal()
{ 
	delete[] m_lpStoreBac1;//用存放用于背景更新的连续
	m_lpStoreBac1=NULL;
	delete[] m_lpStoreBac2;
	m_lpStoreBac2=NULL;
	KillClass();
}

/************************************
       FX     初始化AVI视频
************************************/
void CImageDeal::Initial(CString strAVIFilePath)
{
	m_pAvi=NULL;
	m_pDib1=NULL;
	m_pDib2=NULL;
	m_pLineSignal=new CLineSignal();
	m_pFlowParaStruc=new TRANSPORTATIONFLOWPARAMETER[1];
	m_pFlowParaStruc->VehicleNumber1=0;
	m_pFlowParaStruc->MinuteVehicleNum1=0;
	m_pFlowParaStruc->Speed1=0;
	m_pFlowParaStruc->TimeDensity1=0;		
	bIsStoreBac=TRUE;
	bIsNewCurFrame=TRUE;
	TempMemory1=0;
	TempMemory2=0;
	NoVehicle1=0;
	NoVehicle2=0;
	NoVehicleFramePos1=0;
	NoVehicleFramePos2=0;
	UpdateNum1=0;         //用于调试
	UpdateNum2=0;
	m_lpCurFrame1=NULL;   //用于存储当前帧
	m_lpCurFrame2=NULL;
	m_pSubResult1=NULL;   //public parameters
	m_pSubResult2=NULL;
	m_pFalseBackground1=NULL;
	m_pFalseBackground2=NULL;
	edge1=NULL;
	edge2=NULL;
	//FX注释：AVI文件读入并初始化
	m_pAvi   =(AVIProducer*)new AVIProducer(strAVIFilePath);
	//获取视频屏幕宽和高
	m_nWidth =m_pAvi->m_rectFrame.right-m_pAvi->m_rectFrame.left;
	m_nHeight=m_pAvi->m_rectFrame.bottom-m_pAvi->m_rectFrame.top;	
}

void CImageDeal::KillClass()
{	
	if(m_pAvi)
	{
		delete m_pAvi;
		m_pAvi=NULL;
	}

	if(m_lpBacFrame1)
	{
		delete[] m_lpBacFrame1;
		m_lpBacFrame1=NULL;		
	}
	if(m_lpBacFrame2)
	{
		delete[] m_lpBacFrame2;
		m_lpBacFrame2=NULL;		
	}
	m_pLineSignal=NULL;
	delete[] m_pFlowParaStruc;
	m_pFlowParaStruc=NULL;
}

/************************************
   FX   一通道的下一帧的视频处理
************************************/
TRANSPORTATIONFLOWPARAMETER* CImageDeal::GetNextFrame(CDC *pDC,int nLeftPos1,int nRightPos1,int nHeightPos1,
							  int nLeftPos2,int nRightPos2,int nHeightPos2,float m_fSignal1,float m_fSignal2,float m_fSpace1,
							  int m_nMaxErrorToler11,int m_nMiniReliability11,int m_nMaxErrorToler12,int m_nMiniReliability12,
							  int nLineHeight,BOOL bIsPause,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion,DWORD* m_pdwPos,BOOL bIsShowSignal1)
{
	//一通道的检测线信息设置
	m_nLeftPos1  =nLeftPos1;
	m_nRightPos1 =nRightPos1;
	m_nHeightPos1=nHeightPos1;
	m_nLeftPos2  =nLeftPos2;
	m_nRightPos2 =nRightPos2;
	m_nHeightPos2=nHeightPos2;
	m_nLineHeight=nLineHeight;
	m_nLine1Width=abs(m_nRightPos1-m_nLeftPos1);
	m_nLine2Width=abs(m_nRightPos2-m_nLeftPos2);
	TempMemory1  =m_nLineHeight*m_nLine1Width*3;
	TempMemory2  =m_nLineHeight*m_nLine2Width*3;
	
	m_dwPos=m_pAvi->m_dwPos;
	m_dwLength=m_pAvi->m_dwLength;
	*m_pdwPos=m_dwPos;
	if(bIsDisplay&&bIsShow)
	{
		pDC->TextOut(50,3,"视频车辆检测区:");
		CString str;		
		str.Format("当前帧号：%d",m_dwPos+nFlag);
		pDC->TextOut(380,25,str);
		str.Format("视频总帧数：%d ",m_dwLength-1);
		pDC->TextOut(380,5,str);
	}
//显示停止视频
	if(bIsPause)
		DisplayCurFrame(pDC,nFlag,bIsShow,bIsPause,m_pSaveImageRegion);
//显示连续视频
	if(bIsDisplay)
		DisplayContinuousVideo(pDC,nFlag,bIsShow,bIsPause,m_pSaveImageRegion);
	if(bIsShow)
	{
		//显示对应的检测线1和检测线2的地方
		SetDetectLine1(pDC,1,m_nHeightPos1,m_nLeftPos1,m_nRightPos1,m_nLineHeight,bIsShow);
		SetDetectLine2(pDC,2,m_nHeightPos2,m_nLeftPos2,m_nRightPos2,m_nLineHeight,bIsShow);
	}
	if(m_dwPos==1)
	{
		UpdateNum2=0;
		UpdateNum1=0;
	}
	CString str;	
	if(bIsDisplay&&bIsShow&&bIsShowSignal1)
	{
		str.Format("上检测线背景更新%d次",UpdateNum2);
		pDC->TextOut(380,185,str);
		str.Format("下检测线背景更新%d次",UpdateNum1);
		pDC->TextOut(380,205,str);
		pDC->TextOut(180,310,"车道1虚拟检测线上的检测信号",27);//坐标轴名称
	}
	if(bIsDisplay)
		m_pFlowParaStruc=DrawLineDealRes(pDC,m_nLeftPos1,m_nRightPos1,m_nHeightPos1,m_nLeftPos2,m_nRightPos2,m_nHeightPos2,
		                                 m_fSignal1,m_fSignal2,m_fSpace1,
		                                 m_nMaxErrorToler11,m_nMiniReliability11,m_nMaxErrorToler12,m_nMiniReliability12,
		                                 m_nLineHeight,bIsShow,bIsShowSignal1);
	return m_pFlowParaStruc;
}
/************************************
       FX     静态显示当前帧图像
************************************/
void CImageDeal::DisplayCurFrame(CDC *pDC,int nFlag,BOOL bIsShow,BOOL bIsPause,LPBYTE m_pSaveImageRegion)
{
	LPBYTE lpDetectLine1;
	LPBYTE lpDetectLine2;
	LPBYTE lpBacFrame1Tem;
	LPBYTE lpBacFrame2Tem;
	lpBacFrame1Tem=m_lpBacFrame1;
	lpBacFrame2Tem=m_lpBacFrame2;
	int MemoryNum=320*240*3;

	LPVOID pFrame=m_pAvi->GetCurFrame(nFlag);
	m_pDib1=(CDib*)new CDib(CSize(m_nWidth,m_nHeight),24);
	m_pDib1->m_lpImage=(LPBYTE)pFrame+sizeof(BITMAPINFOHEADER);
	for(int i=0;i<MemoryNum;i++)
	{
		m_pSaveImageRegion[i]=m_pDib1->m_lpImage[i];
	}
	m_pDib1->Draw(pDC,CPoint(50,22),CSize(m_nWidth,m_nHeight),bIsShow);
	
	lpDetectLine1=m_pDib1->m_lpImage+m_nWidth*m_nHeightPos1*3+m_nLeftPos1*3;
	for(int i=0;i<m_nLineHeight;i++)
	{
		memcpy(lpBacFrame1Tem,lpDetectLine1,m_nLine1Width*3);
		lpDetectLine1=lpDetectLine1+m_nWidth*3;
		lpBacFrame1Tem=lpBacFrame1Tem+m_nLine1Width*3;
	}
			
	lpDetectLine2=m_pDib1->m_lpImage+m_nWidth*m_nHeightPos2*3+m_nLeftPos2*3;
	for(int i=0;i<m_nLineHeight;i++)
	{
		memcpy(lpBacFrame2Tem,lpDetectLine2,m_nLine2Width*3);
		lpDetectLine2=lpDetectLine2+m_nWidth*3;
		lpBacFrame2Tem=lpBacFrame2Tem+m_nLine2Width*3;
	}
	m_pDib1->Empty();
	delete m_pDib1;
	m_pDib1=NULL;	

	lpDetectLine1=NULL;
	lpDetectLine2=NULL;
	lpBacFrame1Tem=NULL;
	lpBacFrame2Tem=NULL;
}
/************************************
       FX     连续显示视频
************************************/
void CImageDeal::DisplayContinuousVideo(CDC *pDC,int nFlag,BOOL bIsShow,BOOL bIsPause,LPBYTE m_pSaveImageRegion)
{
	LPBYTE lpDetectLine1;
	LPBYTE lpDetectLine2;
	LPBYTE lpCurFrame1Tem;
	LPBYTE lpCurFrame2Tem;

	LPVOID pFrame=m_pAvi->GetNextStream(nFlag);
	m_pDib1=(CDib*)new CDib(CSize(m_nWidth,m_nHeight),24);
	m_pDib1->m_lpImage=(LPBYTE)pFrame+sizeof(BITMAPINFOHEADER);
	m_pDib1->Draw(pDC,CPoint(50,22),CSize(m_nWidth,m_nHeight),bIsShow);
	for(int i=0;i<320*240*3;i++)
	{
		m_pSaveImageRegion[i]=m_pDib1->m_lpImage[i];
	}	
	if(bIsNewCurFrame)
	{
		m_lpCurFrame1=new BYTE[m_nLine1Width*m_nLineHeight*3];
		m_lpCurFrame2=new BYTE[m_nLine2Width*m_nLineHeight*3];
		bIsNewCurFrame=FALSE;
	}
		
	m_lpCurFrame1=(LPBYTE)pFrame+sizeof(BITMAPINFOHEADER)+m_nWidth*m_nLine1Width*3+m_nLeftPos1*3;//设置当前帧指针	
	m_lpCurFrame2=(LPBYTE)pFrame+sizeof(BITMAPINFOHEADER)+m_nWidth*m_nLine2Width*3+m_nLeftPos2*3;//设置当前帧指针

	lpCurFrame1Tem=m_lpCurFrame1;
	lpCurFrame2Tem=m_lpCurFrame2;

	lpDetectLine1=m_pDib1->m_lpImage+m_nWidth*m_nHeightPos1*3+m_nLeftPos1*3;
	for(int i=0;i<m_nLineHeight;i++)
	{
		memcpy(lpCurFrame1Tem,lpDetectLine1,m_nLine1Width*3);
		lpDetectLine1=lpDetectLine1+m_nWidth*3;
		lpCurFrame1Tem=lpCurFrame1Tem+m_nLine1Width*3;
	}			
	lpDetectLine2=m_pDib1->m_lpImage+m_nWidth*m_nHeightPos2*3+m_nLeftPos2*3;
	for(int i=0;i<m_nLineHeight;i++)
	{
		memcpy(lpCurFrame2Tem,lpDetectLine2,m_nLine2Width*3);
		lpDetectLine2=lpDetectLine2+m_nWidth*3;
		lpCurFrame2Tem=lpCurFrame2Tem+m_nLine2Width*3;
	}
	m_pDib1->Empty();
	delete m_pDib1;
	m_pDib1=NULL;
//用于显示当前的检测线上的图像
	m_pDib1=new CDib(CSize(m_nLine1Width,m_nLineHeight),24);
	m_pDib2=new CDib(CSize(m_nLine2Width,m_nLineHeight),24);
	if(bIsShow)
	{	
		//FX注释：显示检测线上对应的视频内容，在视频右侧
		m_pDib2->m_lpImage=m_lpCurFrame2;
		m_pDib2->Draw(pDC,CPoint(550,129),CSize(m_nLine2Width,m_nLineHeight),bIsShow);
		
		m_pDib1->m_lpImage=m_lpCurFrame1;
		m_pDib1->Draw(pDC,CPoint(550,177),CSize(m_nLine1Width,m_nLineHeight),bIsShow);
		
		pDC->TextOut(550,109,"上检测线上视频图像:");
		pDC->TextOut(550,157,"下检测线上视频图像:");
	}
	m_pDib1->Empty();
	delete m_pDib1;	
	m_pDib2->Empty();	
	delete m_pDib2;	

	LineDeal(pDC,bIsPause);
	UpdateBackground(pDC,bIsPause,bIsShow);	
	
	lpDetectLine1=NULL;
	lpDetectLine2=NULL;	
}

void CImageDeal::UpdateBackground(CDC* pDC,BOOL bIsPause,BOOL bIsShow)
{	
	//检测线1的代码
	if((m_pLineSignal->m_nUnitaryValue1==0)&&(m_pLineSignal->m_nFramePosition==(NoVehicleFramePos1+1)))
	{
		NoVehicle1++;
	//计入内存;
		memcpy(TemStoreBac1,m_lpCurFrame1,TempMemory1);
		TemStoreBac1+=TempMemory1;		
	}
	else
	{
		TemStoreBac1=m_lpStoreBac1;	
		NoVehicle1=0;
	//使内存的值全为0;
	}
	if(NoVehicle1==149)
	{
	//把当前的位置向后减6帧开始的存储的背景作为当前背景，可能使用卡尔曼滤波,然后再清临时内存
	TemStoreBac1-=120*TempMemory1;
		memcpy(m_lpBacFrame1,TemStoreBac1,TempMemory1);
		
		TemStoreBac1+=30*TempMemory1;
		for(int i=0;i<TempMemory1;i++)
		{	
			(*m_lpBacFrame1)=(*m_lpBacFrame1)/4+(*TemStoreBac1)/4;
			m_lpBacFrame1++;
			TemStoreBac1++;
		}
		m_lpBacFrame1-=TempMemory1;

		TemStoreBac1+=29*TempMemory1;
		for(int i=0;i<TempMemory1;i++)
		{	
			(*m_lpBacFrame1)+=(*TemStoreBac1)/4;
			m_lpBacFrame1++;
			TemStoreBac1++;
		}
		m_lpBacFrame1-=TempMemory1;

		TemStoreBac1+=29*TempMemory1;
		for(int i=0;i<TempMemory1;i++)
		{	
			(*m_lpBacFrame1)+=(*TemStoreBac1)/4;
			m_lpBacFrame1++;
			TemStoreBac1++;
		}
		m_lpBacFrame1-=TempMemory1;

		TemStoreBac1=m_lpStoreBac1;	
		NoVehicle1=0;
		UpdateNum1++;//用于调试		
	}
	NoVehicleFramePos1=m_pLineSignal->m_nFramePosition;//为下一次判断用

//检测线2更新
	if((m_pLineSignal->m_nUnitaryValue2<10)&&(m_pLineSignal->m_nFramePosition==(NoVehicleFramePos2+1)))
	{
		NoVehicle2++;
	//计入内存;
		memcpy(TemStoreBac2,m_lpCurFrame2,TempMemory2);
		TemStoreBac2+=TempMemory2;		
	}
	else
	{
		TemStoreBac2=m_lpStoreBac2;	
		NoVehicle2=0;
	//使内存的值全为0;
	}
	if(NoVehicle2==149)
	{
	//把当前的位置向后减6帧开始的存储的背景作为当前背景，可能使用卡尔曼滤波,然后再清临时内存
		TemStoreBac2-=120*TempMemory2;
		memcpy(m_lpBacFrame2,TemStoreBac2,TempMemory2);
		
		TemStoreBac2+=30*TempMemory2;
		for(int i=0;i<TempMemory2;i++)
		{	
			(*m_lpBacFrame2)=(*m_lpBacFrame2)/4+(*TemStoreBac2)/4;
			m_lpBacFrame2++;
			TemStoreBac2++;
		}
		m_lpBacFrame2-=TempMemory2;

		TemStoreBac2+=29*TempMemory2;
		for(int i=0;i<TempMemory2;i++)
		{	
			(*m_lpBacFrame2)+=(*TemStoreBac2)/4;
			m_lpBacFrame2++;
			TemStoreBac2++;
		}
		m_lpBacFrame2-=TempMemory2;

		TemStoreBac2+=29*TempMemory2;
		for(int i=0;i<TempMemory2;i++)
		{	
			(*m_lpBacFrame2)+=(*TemStoreBac2)/4;
			m_lpBacFrame2++;
			TemStoreBac2++;
		}
		m_lpBacFrame2-=TempMemory2;
		TemStoreBac2=m_lpStoreBac2;	
		NoVehicle2=0;
		UpdateNum2++;
	}
	NoVehicleFramePos2=m_pLineSignal->m_nFramePosition;//为下一次判断用

	m_pDib1=new CDib(CSize(m_nLine1Width,m_nLineHeight),24);
	m_pDib2=new CDib(CSize(m_nLine2Width,m_nLineHeight),24);
	//显示当前的背景//
	if(bIsShow)
	{	
		m_pDib2->m_lpImage=m_lpBacFrame2;
		m_pDib2->Draw(pDC,CPoint(550,25),CSize(m_nLine2Width,m_nLineHeight),bIsShow);

		m_pDib1->m_lpImage=m_lpBacFrame1;
		m_pDib1->Draw(pDC,CPoint(550,73),CSize(m_nLine1Width,m_nLineHeight),bIsShow);
	
		pDC->TextOut(550,5,"上检测线上背景图像:");
		pDC->TextOut(550,53,"下检测线上背景图像:");
	}	
		
	m_pDib1->Empty();
	delete m_pDib1;	
	m_pDib2->Empty();	
	delete m_pDib2;
}

//实现了背景差，其中阈值Threshold=15;设置相应的区域为
void CImageDeal::LineDeal(CDC *pDC,BOOL bIsPause)
{
	LPBYTE lpCur1=m_lpCurFrame1;
	LPBYTE lpCur2=m_lpCurFrame2;
	LPBYTE lpBac1=m_lpBacFrame1;
	LPBYTE lpBac2=m_lpBacFrame2;
	int r,g,b;
	//int i,j;
	int Threshold=15;
	if(bIsPause)//防止没有连续播放视频时，下一帧为无数据
	{
		lpCur1=m_lpBacFrame1;
		lpCur2=m_lpBacFrame2;
	}
		
	m_pSubResult1=(LPBYTE)new BYTE[m_nLine1Width*m_nLineHeight*3];
	m_pSubResult2=(LPBYTE)new BYTE[m_nLine2Width*m_nLineHeight*3];
	edge1=(LPBYTE)new BYTE[m_nLine1Width*m_nLineHeight*3];
	edge2=(LPBYTE)new BYTE[m_nLine2Width*m_nLineHeight*3];

	m_pFalseBackground1=(LPBYTE)new BYTE[m_nLine1Width*m_nLineHeight*3];
	m_pFalseBackground2=(LPBYTE)new BYTE[m_nLine2Width*m_nLineHeight*3];
//完成背景差和设置伪背景
	//检测线1
	for(int i=0;i<m_nLineHeight;i++)
	{
		for(int j=0;j<m_nLine1Width;j++)
		{	//blue component		
			b=abs(lpCur1[i*m_nLine1Width*3+j*3]-lpBac1[i*m_nLine1Width*3+j*3]);
			if(b<Threshold)
			{
				m_pSubResult1[i*m_nLine1Width*3+j*3]=0;
				m_pFalseBackground1[i*m_nLine1Width*3+j*3]=0;
			}
			else
			{
				m_pSubResult1[i*m_nLine1Width*3+j*3]=lpCur1[i*m_nLine1Width*3+j*3];
				m_pFalseBackground1[i*m_nLine1Width*3+j*3]=lpCur1[i*m_nLine1Width*3+j*3];
			}
			//green component
			g=abs(lpCur1[i*m_nLine1Width*3+j*3+1]-lpBac1[i*m_nLine1Width*3+j*3+1]);
			if(g<Threshold)
			{
				m_pSubResult1[i*m_nLine1Width*3+j*3+1]=0;
				m_pFalseBackground1[i*m_nLine1Width*3+j*3+1]=0;
			}
			else
			{
				m_pSubResult1[i*m_nLine1Width*3+j*3+1]=lpCur1[i*m_nLine1Width*3+j*3+1];
				m_pFalseBackground1[i*m_nLine1Width*3+j*3+1]=lpCur1[i*m_nLine1Width*3+j*3+1];
			}
			//red component
			r=abs(lpCur1[i*m_nLine1Width*3+j*3+2]-lpBac1[i*m_nLine1Width*3+j*3+2]);		
			if(r<Threshold)//没有目标，要实现背景更新
			{
				m_pSubResult1[i*m_nLine1Width*3+j*3+2]=0;
				m_pFalseBackground1[i*m_nLine1Width*3+j*3+2]=0;
			}
			else
			{
				m_pSubResult1[i*m_nLine1Width*3+j*3+2]=lpCur1[i*m_nLine1Width*3+j*3+2];
				m_pFalseBackground1[i*m_nLine1Width*3+j*3+2]=lpCur1[i*m_nLine1Width*3+j*3+2];
			}
		}
		//检测线2
		for(int j=0;j<m_nLine2Width;j++)
		{	//blue component		
			b=abs(lpCur2[i*m_nLine2Width*3+j*3]-lpBac2[i*m_nLine2Width*3+j*3]);
			if(b<Threshold)
			{
				m_pSubResult2[i*m_nLine2Width*3+j*3]=0;
				m_pFalseBackground2[i*m_nLine2Width*3+j*3]=0;
			}
			else
			{
				m_pSubResult2[i*m_nLine2Width*3+j*3]=lpCur2[i*m_nLine2Width*3+j*3];
				m_pFalseBackground2[i*m_nLine2Width*3+j*3]=lpBac2[i*m_nLine2Width*3+j*3];
			}
			//greed component
			g=abs(lpCur2[i*m_nLine2Width*3+j*3+1]-lpBac2[i*m_nLine2Width*3+j*3+1]);
			if(g<Threshold)
			{
				m_pSubResult2[i*m_nLine2Width*3+j*3+1]=0;
				m_pFalseBackground2[i*m_nLine2Width*3+j*3+1]=0;
			}
			else
			{
				m_pSubResult2[i*m_nLine2Width*3+j*3+1]=lpCur2[i*m_nLine2Width*3+j*3+1];
				m_pFalseBackground2[i*m_nLine2Width*3+j*3+1]=lpBac2[i*m_nLine2Width*3+j*3+1];
			}
			//red component
			r=abs(lpCur2[i*m_nLine2Width*3+j*3+2]-lpBac2[i*m_nLine2Width*3+j*3+2]);			
			if(r<Threshold)
			{
				m_pSubResult2[i*m_nLine2Width*3+j*3+2]=0;
				m_pFalseBackground2[i*m_nLine2Width*3+j*3+2]=0;
			}
			else
			{
				m_pSubResult2[i*m_nLine2Width*3+j*3+2]=lpCur2[i*m_nLine2Width*3+j*3+2];
				m_pFalseBackground2[i*m_nLine2Width*3+j*3+2]=lpBac2[i*m_nLine2Width*3+j*3+2];
			}
		}
	}
}
//显示处理的结果：背景差结果、伪背景的结果、调用了
//边缘检测函数kir.KirschEdgeDet()和信号统计函数m_pLineSignal->StatLineSignal()
//TRANSPORTATIONFLOWPARAMETER是在宏定义中定义的交通流参数结构
TRANSPORTATIONFLOWPARAMETER* CImageDeal::DrawLineDealRes(CDC *pDC,int m_nLeftPos1,int m_nRightPos1,int m_nHeightPos1,
																	int m_nLeftPos2,int m_nRightPos2,int m_nHeightPos2,
																	float m_fSignal1,float m_fSignal2,float m_fSpace1,
																	int m_nMaxErrorToler11,int m_nMiniReliability11,int m_nMaxErrorToler12,int m_nMiniReliability12,
																	int m_nLineHeight,BOOL bIsShow,BOOL bIsShowSignal1)
{
	m_nLine1Width=m_nRightPos1-m_nLeftPos1;
	m_nLine2Width=m_nRightPos2-m_nLeftPos2;
	m_pDib1=new CDib(CSize(m_nLine1Width,m_nLineHeight),24);
	m_pDib2=new CDib(CSize(m_nLine2Width,m_nLineHeight),24);

	LPBYTE tem3=m_pSubResult1;
	LPBYTE tem4=m_pSubResult2;	
    CKirschEdgeDetect kir;
	
	m_pDib1->m_lpImage=m_pSubResult1;
	m_pDib2->m_lpImage=m_pSubResult2;
	if(bIsShow==TRUE)
	{
		//显示试验检测线2区视频
		m_pDib2->Draw(pDC,CPoint(550,233),CSize(m_nLine2Width,m_nLineHeight),bIsShow);
		//显示试验检测线1区视频
		m_pDib1->Draw( pDC,CPoint(550,281),CSize(m_nLine1Width,m_nLineHeight),bIsShow);
		//显示试验检测线2区标题		
		pDC->TextOut(550,213,"上检测线目标分割结果:");
		//显示试验检测线1区标题		
		pDC->TextOut(550,261,"下检测线目标分割结果:");
	}

	m_pSubResult1=kir.KirschEdgeDet(pDC,m_nLeftPos1,m_nRightPos1,m_nLineHeight,0,m_pSubResult1,1,bIsShow,1);
	m_pSubResult2=kir.KirschEdgeDet(pDC,m_nLeftPos2,m_nRightPos2,m_nLineHeight,0,m_pSubResult2,2,bIsShow,1);
	delete[] tem3;//注意在调用边缘检测时，m_pSubResult1和m_pSubResult1指定的区域发生了变化
	tem3=NULL;//所以才设置中间的tem3和tem4删除原来的内存！
	delete[] tem4;
	tem4=NULL;
	//已经腐蚀过了
//进行轮廓的提出
	//对两块区域进行赋初值
	for(int i=0;i<m_nLineHeight;i++)
		{
			for(int j=0;j<m_nLine1Width;j++)
			{
				edge1[i*m_nLine1Width*3+j*3+0]=0;
				edge1[i*m_nLine1Width*3+j*3+1]=0;
				edge1[i*m_nLine1Width*3+j*3+2]=0;
			}
			for(int j=0;j<m_nLine2Width;j++)
			{
				edge2[i*m_nLine2Width*3+j*3+0]=0;
				edge2[i*m_nLine2Width*3+j*3+1]=0;
				edge2[i*m_nLine2Width*3+j*3+2]=0;
			}
	}
	int Threshold=5;
	BOOL flag=FALSE;
	for(int i=0;i<m_nLineHeight;i++)
		{
			for(int j=2;j<m_nLine1Width-2;j++)
			{	
				flag=((m_pFalseBackground1[i*m_nLine1Width*3+j*3-6]>Threshold)&&(m_pFalseBackground1[i*m_nLine1Width*3+j*3-5]>Threshold)&&(m_pFalseBackground1[i*m_nLine1Width*3+j*3-4]>Threshold)&&
					  (m_pFalseBackground1[i*m_nLine1Width*3+j*3-3]>Threshold)&&(m_pFalseBackground1[i*m_nLine1Width*3+j*3-2]>Threshold)&&(m_pFalseBackground1[i*m_nLine1Width*3+j*3-1]>Threshold)&&
					  (m_pFalseBackground1[i*m_nLine1Width*3+j*3+3]>Threshold)&&(m_pFalseBackground1[i*m_nLine1Width*3+j*3+4]>Threshold)&&(m_pFalseBackground1[i*m_nLine1Width*3+j*3+5]>Threshold)&&
					  (m_pFalseBackground1[i*m_nLine1Width*3+j*3+6]>Threshold)&&(m_pFalseBackground1[i*m_nLine1Width*3+j*3+7]>Threshold)&&(m_pFalseBackground1[i*m_nLine1Width*3+j*3+8]>Threshold));
				if(flag)
				{
					edge1[i*m_nLine1Width*3+j*3-6]=0;
					edge1[i*m_nLine1Width*3+j*3-5]=0;
					edge1[i*m_nLine1Width*3+j*3-4]=0;

					edge1[i*m_nLine1Width*3+j*3-3]=0;
					edge1[i*m_nLine1Width*3+j*3-2]=0;
					edge1[i*m_nLine1Width*3+j*3-1]=0;

					edge1[i*m_nLine1Width*3+j*3+0]=0;
					edge1[i*m_nLine1Width*3+j*3+1]=0;
					edge1[i*m_nLine1Width*3+j*3+2]=0;

					edge1[i*m_nLine1Width*3+j*3+3]=0;
					edge1[i*m_nLine1Width*3+j*3+4]=0;
					edge1[i*m_nLine1Width*3+j*3+5]=0;

					edge1[i*m_nLine1Width*3+j*3+6]=0;
					edge1[i*m_nLine1Width*3+j*3+7]=0;
					edge1[i*m_nLine1Width*3+j*3+8]=0;
				}
				else
				{
					edge1[i*m_nLine1Width*3+j*3+0]=m_pSubResult1[i*m_nLine1Width*3+j*3+0];
					edge1[i*m_nLine1Width*3+j*3+1]=m_pSubResult1[i*m_nLine1Width*3+j*3+1];
					edge1[i*m_nLine1Width*3+j*3+2]=m_pSubResult1[i*m_nLine1Width*3+j*3+2];
				}			
			}
			for(int j=2;j<m_nLine2Width-2;j++)
			{
				flag=((m_pFalseBackground2[i*m_nLine2Width*3+j*3-6]>Threshold)&&(m_pFalseBackground2[i*m_nLine2Width*3+j*3-5]>Threshold)&&(m_pFalseBackground2[i*m_nLine2Width*3+j*3-4]>Threshold)&&
					  (m_pFalseBackground2[i*m_nLine2Width*3+j*3-3]>Threshold)&&(m_pFalseBackground2[i*m_nLine2Width*3+j*3-2]>Threshold)&&(m_pFalseBackground2[i*m_nLine2Width*3+j*3-1]>Threshold)&&
					  (m_pFalseBackground2[i*m_nLine2Width*3+j*3+3]>Threshold)&&(m_pFalseBackground2[i*m_nLine2Width*3+j*3+4]>Threshold)&&(m_pFalseBackground2[i*m_nLine2Width*3+j*3+5]>Threshold)&&
					  (m_pFalseBackground2[i*m_nLine2Width*3+j*3+6]>Threshold)&&(m_pFalseBackground2[i*m_nLine2Width*3+j*3+7]>Threshold)&&(m_pFalseBackground2[i*m_nLine2Width*3+j*3+8]>Threshold));
				if(flag)
				{
					edge2[i*m_nLine2Width*3+j*3-6]=0;
					edge2[i*m_nLine2Width*3+j*3-5]=0;
					edge2[i*m_nLine2Width*3+j*3-4]=0;

					edge2[i*m_nLine2Width*3+j*3-3]=0;
					edge2[i*m_nLine2Width*3+j*3-2]=0;
					edge2[i*m_nLine2Width*3+j*3-1]=0;

					edge2[i*m_nLine2Width*3+j*3+0]=0;
					edge2[i*m_nLine2Width*3+j*3+1]=0;
					edge2[i*m_nLine2Width*3+j*3+2]=0;

					edge2[i*m_nLine2Width*3+j*3+3]=0;
					edge2[i*m_nLine2Width*3+j*3+4]=0;
					edge2[i*m_nLine2Width*3+j*3+5]=0;

					edge2[i*m_nLine2Width*3+j*3+6]=0;
					edge2[i*m_nLine2Width*3+j*3+7]=0;
					edge2[i*m_nLine2Width*3+j*3+8]=0;
				}
				else
				{
					edge2[i*m_nLine2Width*3+j*3+0]=m_pSubResult2[i*m_nLine2Width*3+j*3+0];
					edge2[i*m_nLine2Width*3+j*3+1]=m_pSubResult2[i*m_nLine2Width*3+j*3+1];
					edge2[i*m_nLine2Width*3+j*3+2]=m_pSubResult2[i*m_nLine2Width*3+j*3+2];
				}
			  }
		}
		//使用提取的轮廓和边缘检测后的结果进行对比从而去掉阴影的边缘
		Threshold=20;
	for(int i=0;i<m_nLineHeight;i++)
		{
			for(int j=0;j<m_nLine1Width;j++)
			{
				if(abs(edge1[i*m_nLine1Width*3+j*3+0]-m_pSubResult1[i*m_nLine1Width*3+j*3+0])<Threshold)
					edge1[i*m_nLine1Width*3+j*3+0]=0;
				else
					edge1[i*m_nLine1Width*3+j*3+0]=m_pSubResult1[i*m_nLine1Width*3+j*3+0];
				if(abs(edge1[i*m_nLine1Width*3+j*3+1]-m_pSubResult1[i*m_nLine1Width*3+j*3+1])<Threshold)
					edge1[i*m_nLine1Width*3+j*3+1]=0;
				else
					edge1[i*m_nLine1Width*3+j*3+1]=m_pSubResult1[i*m_nLine1Width*3+j*3+1];
				if(abs(edge1[i*m_nLine1Width*3+j*3+2]-m_pSubResult1[i*m_nLine1Width*3+j*3+2])<Threshold)
					edge1[i*m_nLine1Width*3+j*3+0]=0;
				else
					edge1[i*m_nLine1Width*3+j*3+2]=m_pSubResult1[i*m_nLine1Width*3+j*3+2];				
			}
			
			for(int j=0;j<m_nLine2Width;j++)
			{
				if(abs(edge2[i*m_nLine2Width*3+j*3+0]-m_pSubResult2[i*m_nLine2Width*3+j*3+0])<Threshold)
					edge2[i*m_nLine2Width*3+j*3+0]=0;
				else
					edge2[i*m_nLine2Width*3+j*3+0]=m_pSubResult2[i*m_nLine2Width*3+j*3+0];
				if(abs(edge2[i*m_nLine2Width*3+j*3+1]-m_pSubResult2[i*m_nLine2Width*3+j*3+1])<Threshold)
					edge2[i*m_nLine2Width*3+j*3+1]=0;
				else
					edge2[i*m_nLine2Width*3+j*3+1]=m_pSubResult2[i*m_nLine2Width*3+j*3+1];
				if(abs(edge2[i*m_nLine2Width*3+j*3+2]-m_pSubResult2[i*m_nLine2Width*3+j*3+2])<Threshold)
					edge2[i*m_nLine2Width*3+j*3+0]=0;
				else
					edge2[i*m_nLine2Width*3+j*3+2]=m_pSubResult2[i*m_nLine2Width*3+j*3+2];				
			}
		}


	m_pFlowParaStruc=m_pLineSignal->StatLineSignal(pDC,m_nLeftPos1,m_nRightPos1,m_nLeftPos2,m_nRightPos2,m_fSignal1,m_fSignal2,m_fSpace1,
													   m_nMaxErrorToler11,m_nMiniReliability11,m_nMaxErrorToler12,m_nMiniReliability12,
													   m_nLineHeight,edge1,edge2,m_pAvi->m_dwPos,bIsShow,1,bIsShowSignal1);
   	m_pDib1->Empty();
	delete m_pDib1;	
	m_pDib2->Empty();	
	delete m_pDib2;

	m_pDib1=new CDib(CSize(m_nLine1Width,m_nLineHeight),24);
	m_pDib2=new CDib(CSize(m_nLine2Width,m_nLineHeight),24);

	m_pDib1->m_lpImage=edge1;//*/m_pSubResult1;
	m_pDib2->m_lpImage=edge2;//*/m_pSubResult2;

	if(bIsShow==TRUE)
	{		
		m_pDib2->Draw(pDC,CPoint(550,545),CSize(m_nLine2Width,m_nLineHeight),bIsShow);
		m_pDib1->Draw(pDC,CPoint(550,593),CSize(m_nLine1Width,m_nLineHeight),bIsShow);
		
		pDC->TextOut(550,525,"上检测线阴影边缘去除:");	
		pDC->TextOut(550,573,"下检测线阴影边缘去除:");		
	}
	
	delete[] m_pFalseBackground1;
	m_pFalseBackground1=NULL;
	delete[] m_pFalseBackground2;
	m_pFalseBackground2=NULL;

	m_pDib1->Empty();
	delete m_pDib1;	
	m_pDib2->Empty();	
	delete m_pDib2;		

	delete[] edge1;
	edge1=NULL;
	delete[] edge2;
	edge2=NULL;

	return m_pFlowParaStruc;
}
/************************************
    FX  视频上显示检测线1的位置
************************************/
void CImageDeal::SetDetectLine1(CDC *pDC,int nLineNum,
								 int nHeightPos1,int nLeftPos1,int nRightPos1,int nWidthLine,BOOL bIsShow)
{	
	CPoint oriPoint;
	oriPoint=CPoint(50,20);
	CBrush brush1(RGB(255,0,0) );     //red line	
	int temp = 0;
	if(nLeftPos1 > nRightPos1)
	{
		temp      =nLeftPos1;
		nLeftPos1 =nRightPos1;
		nRightPos1=temp;
	}
	m_rect1.left  =oriPoint.x+nLeftPos1;
	m_rect1.right =oriPoint.x+nRightPos1;	
	m_rect1.bottom=oriPoint.y+m_nHeight-nHeightPos1;	
	m_rect1.top   =oriPoint.y+m_nHeight-nHeightPos1-nWidthLine;	
	pDC->SelectObject(brush1);
	pDC->Rectangle(m_rect1);	
		
}
/************************************
   FX  视频上显示检测线2的位置
************************************/
void CImageDeal::SetDetectLine2(CDC *pDC,int nLineNum,
								 int nHeightPos2,int nLeftPos2,int nRightPos2,int nWidthLine,BOOL bIsShow)
{	
	CPoint oriPoint;
	oriPoint=CPoint(50,20);
	CBrush brush2(RGB(0,255,0));//green line
	int temp =0;
	if(nLeftPos2>=nRightPos2)
	{
		temp      =nLeftPos2;
		nLeftPos2 =nRightPos2;
		nRightPos2=temp;
	}

	m_rect2.left=oriPoint.x+nLeftPos2;
	m_rect2.right=oriPoint.x+nRightPos2;
	m_rect2.bottom=oriPoint.y+m_nHeight-nHeightPos2;
	m_rect2.top=oriPoint.y+m_nHeight-nHeightPos2-nWidthLine;

	pDC->SelectObject(brush2);
	pDC->Rectangle(m_rect2);	
}
