// ImageDeal2.cpp: implementation of the CImageDeal2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageDeal2.h"
#include "AVIProducer.h"
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

CImageDeal2::CImageDeal2()
{
	m_lpStoreBac1=new BYTE[150*320*20*3];//�ô�����ڱ������µ�����
	m_lpStoreBac2=new BYTE[150*320*20*3];//11֡����������ʱ�õ�6֡����
	
	m_lpBacFrame1=new BYTE[320*20*3];//�ô�����ڱ������µ�����11֡����������ʱ�õ�6֡����
	m_lpBacFrame2=new BYTE[320*20*3];
	
	TemStoreBac1=m_lpStoreBac1;
	TemStoreBac2=m_lpStoreBac2;
	
	Initial();
}

CImageDeal2::~CImageDeal2()
{ 
	delete[] m_lpStoreBac1;//�ô�����ڱ������µ�����
	m_lpStoreBac1=NULL;
	delete[] m_lpStoreBac2;
	m_lpStoreBac2=NULL;	
	KillClass();
}

void CImageDeal2::Initial()
{
	m_pLineSignal=new CLineSignal();
	m_pFlowParaStruc=new TRANSPORTATIONFLOWPARAMETER[1];
	m_pFlowParaStruc->VehicleNumber3=0;
	m_pFlowParaStruc->MinuteVehicleNum3=0;
	m_pFlowParaStruc->Speed3=0;
	m_pFlowParaStruc->TimeDensity3=0;

		
	
	bIsStoreBac=TRUE;
	bIsNewCurFrame=TRUE;

	TempMemory1=0;
	TempMemory2=0;
	NoVehicle1=0;
	NoVehicle2=0;
	NoVehicleFramePos1=0;
	NoVehicleFramePos2=0;
	UpdateNum1=0;//���ڵ���
	UpdateNum2=0;

	m_lpCurFrame1=NULL;//���ڴ洢��ǰ֡
	m_lpCurFrame2=NULL;

	m_pSubResult1=NULL;//public parameters
	m_pSubResult2=NULL;
	m_pFalseBackground1=NULL;
	m_pFalseBackground2=NULL;
	edge1=NULL;
	edge2=NULL;

}

void CImageDeal2::KillClass()
{	
	
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

TRANSPORTATIONFLOWPARAMETER* CImageDeal2::GetNextFrame(CDC *pDC,int nLeftPos5,int nRightPos5,int nHeightPos5,int m_nRoadWay21Width,
							  int nLeftPos6,int nRightPos6,int nHeightPos6,int m_nRoadWay22Width,
							  float m_fSignal1,float m_fSignal2,float m_fSpace3,
							  int m_nMaxErrorToler31,int m_nMiniReliability31,int m_nMaxErrorToler32,int m_nMiniReliability32,
							  int nLineHeight,BOOL bIsPause,int nFlag,BOOL bIsShow,BOOL bIsDisplay,LPBYTE m_pSaveImageRegion,DWORD* m_pdwPos,BOOL bIsShowSignal3)
{
	m_nLeftPos5=nLeftPos5;
	m_nRightPos5=nRightPos5;
	m_nHeightPos5=nHeightPos5;
	m_nLeftPos6=nLeftPos6;
	m_nRightPos6=nRightPos6;
	m_nHeightPos6=nHeightPos6;
	m_nLineHeight=nLineHeight;
	m_nLine1Width=abs(m_nRightPos5-m_nLeftPos5);
	m_nLine2Width=abs(m_nRightPos6-m_nLeftPos6);
	TempMemory1=m_nLineHeight*m_nLine1Width*3;
	TempMemory2=m_nLineHeight*m_nLine2Width*3;
//��ʾֹͣ��Ƶ
	if(bIsPause)
		DisplayCurFrame(pDC,nFlag,bIsShow,bIsPause,m_pSaveImageRegion);

//��ʾ������Ƶ
	if(bIsDisplay)
		DisplayContinuousVideo(pDC,m_nRoadWay21Width,m_nRoadWay22Width,nFlag,bIsShow,bIsPause,m_pSaveImageRegion);
	if(bIsShow)
	{
		SetDetectLine1(pDC,1,m_nHeightPos5,m_nLeftPos5,m_nRightPos5,m_nLineHeight,bIsShow);
		SetDetectLine2(pDC,2,m_nHeightPos6,m_nLeftPos6,m_nRightPos6,m_nLineHeight,bIsShow);
	}

	if((*m_pdwPos)==1)
	{
		UpdateNum2=0;
		UpdateNum1=0;
	}

	CString str;	
	if(bIsDisplay&&bIsShow&&bIsShowSignal3)
	{
		str.Format("�ϼ���߱�������%d��",UpdateNum2);
		pDC->TextOut(380,185,str);
		str.Format("�¼���߱�������%d��",UpdateNum1);
		pDC->TextOut(380,205,str);
		pDC->TextOut(180,310,"����3���������ϵļ���ź�",27);//����������
	}
	if(bIsDisplay)
		m_pFlowParaStruc=DrawLineDealRes(pDC,m_nLeftPos5,m_nRightPos5,m_nHeightPos5,m_nRoadWay21Width,m_nLeftPos6,m_nRightPos6,m_nHeightPos6,m_nRoadWay22Width,
		                                 m_fSignal1,m_fSignal2,m_fSpace3,
		                                 m_nMaxErrorToler31,m_nMiniReliability31,m_nMaxErrorToler32,m_nMiniReliability32,
		                                 m_nLineHeight,bIsShow,m_pdwPos,bIsShowSignal3);
	return m_pFlowParaStruc;
}

void CImageDeal2::DisplayCurFrame(CDC *pDC,int nFlag,BOOL bIsShow,BOOL bIsPause,LPBYTE m_pSaveImageRegion)
{
	LPBYTE lpDetectLine1;
	LPBYTE lpDetectLine2;
	LPBYTE lpBacFrame1Tem;
	LPBYTE lpBacFrame2Tem;

	lpBacFrame1Tem=m_lpBacFrame1;
	lpBacFrame2Tem=m_lpBacFrame2;

	lpDetectLine1=m_pSaveImageRegion+320*m_nHeightPos5*3+m_nLeftPos5*3;
	for(int i=0;i<m_nLineHeight;i++)
	{
		memcpy(lpBacFrame1Tem,lpDetectLine1,m_nLine1Width*3);
		lpDetectLine1=lpDetectLine1+320*3;
		lpBacFrame1Tem=lpBacFrame1Tem+m_nLine1Width*3;
	}
			
	lpDetectLine2=m_pSaveImageRegion+320*m_nHeightPos6*3+m_nLeftPos6*3;
	for(int i=0;i<m_nLineHeight;i++)
	{
		memcpy(lpBacFrame2Tem,lpDetectLine2,m_nLine2Width*3);
		lpDetectLine2=lpDetectLine2+320*3;
		lpBacFrame2Tem=lpBacFrame2Tem+m_nLine2Width*3;
	}
		
	lpDetectLine1=NULL;
	lpDetectLine2=NULL;
	lpBacFrame1Tem=NULL;
	lpBacFrame2Tem=NULL;
}

void CImageDeal2::DisplayContinuousVideo(CDC *pDC,int m_nRoadWay21Width,int m_nRoadWay22Width,int nFlag,BOOL bIsShow,BOOL bIsPause,LPBYTE m_pSaveImageRegion)
{
	LPBYTE lpDetectLine1;
	LPBYTE lpDetectLine2;
	LPBYTE lpCurFrame1Tem;
	LPBYTE lpCurFrame2Tem;

	if(bIsNewCurFrame)
	{
		m_lpCurFrame1=new BYTE[m_nLine1Width*m_nLineHeight*3];
		m_lpCurFrame2=new BYTE[m_nLine2Width*m_nLineHeight*3];
		bIsNewCurFrame=FALSE;
	}
		
	lpCurFrame1Tem=m_lpCurFrame1;
	lpCurFrame2Tem=m_lpCurFrame2;

	lpDetectLine1=m_pSaveImageRegion+320*m_nHeightPos5*3+m_nLeftPos5*3;
	for(int i=0;i<m_nLineHeight;i++)
	{
		memcpy(lpCurFrame1Tem,lpDetectLine1,m_nLine1Width*3);
		lpDetectLine1=lpDetectLine1+320*3;
		lpCurFrame1Tem=lpCurFrame1Tem+m_nLine1Width*3;
	}	
		
	lpDetectLine2=m_pSaveImageRegion+320*m_nHeightPos6*3+m_nLeftPos6*3;
	for(int i=0;i<m_nLineHeight;i++)
	{
		memcpy(lpCurFrame2Tem,lpDetectLine2,m_nLine2Width*3);
		lpDetectLine2=lpDetectLine2+320*3;
		lpCurFrame2Tem=lpCurFrame2Tem+m_nLine2Width*3;
	}
//������ʾ��ǰ�ļ�����ϵ�ͼ��
	m_pDib1=new CDib(CSize(m_nLine1Width,m_nLineHeight),24);
	m_pDib2=new CDib(CSize(m_nLine2Width,m_nLineHeight),24);
//����ߵ�ǰ��Ƶ
	if(bIsShow)
	{	
		m_pDib2->m_lpImage=m_lpCurFrame2;
		m_pDib2->Draw(pDC,CPoint(560+m_nRoadWay22Width,129),CSize(m_nLine2Width,m_nLineHeight),bIsShow);
		
		m_pDib1->m_lpImage=m_lpCurFrame1;
		m_pDib1->Draw(pDC,CPoint(560+m_nRoadWay21Width,177),CSize(m_nLine1Width,m_nLineHeight),bIsShow);
	}
	
	LineDeal(pDC,bIsPause);

	UpdateBackground(pDC,m_nRoadWay21Width,m_nRoadWay22Width,bIsPause,bIsShow);	
	
	lpDetectLine1=NULL;
	lpDetectLine2=NULL;	
}

void CImageDeal2::UpdateBackground(CDC* pDC,int m_nRoadWay21Width,int m_nRoadWay22Width,BOOL bIsPause,BOOL bIsShow)
{	
	//�����1�Ĵ���
	if((m_pLineSignal->m_nUnitaryValue1==0)&&(m_pLineSignal->m_nFramePosition==(NoVehicleFramePos1+1)))
	{
		NoVehicle1++;
	//�����ڴ�;
		memcpy(TemStoreBac1,m_lpCurFrame1,TempMemory1);
		TemStoreBac1+=TempMemory1;		
	}
	else
	{
		TemStoreBac1=m_lpStoreBac1;	
		NoVehicle1=0;
	}
	if(NoVehicle1==149)
	{
	//�ѵ�ǰ��λ������6֡��ʼ�Ĵ洢�ı�����Ϊ��ǰ����������ʹ�ÿ������˲�,Ȼ��������ʱ�ڴ�
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
		UpdateNum1++;//���ڵ���		
	}
	NoVehicleFramePos1=m_pLineSignal->m_nFramePosition;//Ϊ��һ���ж���

//�����2����
	if((m_pLineSignal->m_nUnitaryValue2<10)&&(m_pLineSignal->m_nFramePosition==(NoVehicleFramePos2+1)))
	{
		NoVehicle2++;
	//�����ڴ�;
		memcpy(TemStoreBac2,m_lpCurFrame2,TempMemory2);
		TemStoreBac2+=TempMemory2;		
	}
	else
	{
		TemStoreBac2=m_lpStoreBac2;
		NoVehicle2=0;
	}
	if(NoVehicle2==149)
	{
	//�ѵ�ǰ��λ������6֡��ʼ�Ĵ洢�ı�����Ϊ��ǰ����������ʹ�ÿ������˲�,Ȼ��������ʱ�ڴ�
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
		/*	//�ռ���
		TemStoreBac2+=29*TempMemory2;
		for(i=0;i<TempMemory2;i++)
		{	
			(*m_lpBacFrame2)+=(*TemStoreBac2)/8;
			m_lpBacFrame2++;
			TemStoreBac2++;
		}
		m_lpBacFrame2-=TempMemory2;
		//�������*/
		TemStoreBac2=m_lpStoreBac2;
		NoVehicle2=0;
		UpdateNum2++;
	}
	NoVehicleFramePos2=m_pLineSignal->m_nFramePosition;//Ϊ��һ���ж���

	m_pDib1=new CDib(CSize(m_nLine1Width,m_nLineHeight),24);
	m_pDib2=new CDib(CSize(m_nLine2Width,m_nLineHeight),24);
	//��ʾ��ǰ�ı���//
	if(bIsShow)
	{	
		m_pDib2->m_lpImage=m_lpBacFrame2;
		m_pDib2->Draw(pDC,CPoint(560+m_nRoadWay22Width,25),CSize(m_nLine2Width,m_nLineHeight),bIsShow);

		m_pDib1->m_lpImage=m_lpBacFrame1;
		m_pDib1->Draw(pDC,CPoint(560+m_nRoadWay21Width,73),CSize(m_nLine1Width,m_nLineHeight),bIsShow);
		
	}	
		
	m_pDib1->Empty();
	delete m_pDib1;	
	m_pDib2->Empty();	
	delete m_pDib2;
}

//ʵ���˱����������ֵThreshold=15;������Ӧ������Ϊ
void CImageDeal2::LineDeal(CDC *pDC,BOOL bIsPause)
{
	LPBYTE lpCur1=m_lpCurFrame1;
	LPBYTE lpCur2=m_lpCurFrame2;
	LPBYTE lpBac1=m_lpBacFrame1;
	LPBYTE lpBac2=m_lpBacFrame2;
	int r,g,b;
	//int i,j;
	int Threshold=15;
	if(bIsPause)//��ֹû������������Ƶʱ����һ֡Ϊ������
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
//��ɱ����������α����
	//�����1
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
			if(r<Threshold)//û��Ŀ�꣬Ҫʵ�ֱ�������
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
		//�����2
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
//��ʾ����Ľ��������������α�����Ľ����������
//��Ե��⺯��kir.KirschEdgeDet()���ź�ͳ�ƺ���m_pLineSignal->StatLineSignal()
//TRANSPORTATIONFLOWPARAMETER���ں궨���ж���Ľ�ͨ�������ṹ
TRANSPORTATIONFLOWPARAMETER* CImageDeal2::DrawLineDealRes(CDC *pDC,int m_nLeftPos5,int m_nRightPos5,int m_nHeightPos5,int m_nRoadWay21Width,
																	int m_nLeftPos6,int m_nRightPos6,int m_nHeightPos6,int m_nRoadWay22Width,
																	float m_fSignal1,float m_fSignal2,float m_fSpace3,
																	int m_nMaxErrorToler31,int m_nMiniReliability31,int m_nMaxErrorToler32,int m_nMiniReliability32,
																	int m_nLineHeight,BOOL bIsShow,DWORD* m_pdwPos,BOOL bIsShowSignal3)
{
	m_nLine1Width=m_nRightPos5-m_nLeftPos5;
	m_nLine2Width=m_nRightPos6-m_nLeftPos6;
	m_pDib1=new CDib(CSize(m_nLine1Width,m_nLineHeight),24);
	m_pDib2=new CDib(CSize(m_nLine2Width,m_nLineHeight),24);

	LPBYTE tem3=m_pSubResult1;
	LPBYTE tem4=m_pSubResult2;	
    CKirschEdgeDetect kir;
	
	m_pDib1->m_lpImage=m_pSubResult1;
	m_pDib2->m_lpImage=m_pSubResult2;
	if(bIsShow==TRUE)
	{
		//��ʾ��������2����Ƶ
		m_pDib2->Draw(pDC,CPoint(560+m_nRoadWay22Width,233),CSize(m_nLine2Width,m_nLineHeight),bIsShow);
		//��ʾ��������1����Ƶ
		m_pDib1->Draw( pDC,CPoint(560+m_nRoadWay21Width,281),CSize(m_nLine1Width,m_nLineHeight),bIsShow);		
	}

	m_pSubResult1=kir.KirschEdgeDet(pDC,m_nLeftPos5,m_nRightPos5,m_nLineHeight,m_nRoadWay21Width,m_pSubResult1,1,bIsShow,3);
	m_pSubResult2=kir.KirschEdgeDet(pDC,m_nLeftPos6,m_nRightPos6,m_nLineHeight,m_nRoadWay22Width,m_pSubResult2,2,bIsShow,3);
	delete[] tem3;//ע���ڵ��ñ�Ե���ʱ��m_pSubResult1��m_pSubResult1ָ�����������˱仯
	tem3=NULL;//���Բ������м��tem3��tem4ɾ��ԭ�����ڴ棡
	delete[] tem4;
	tem4=NULL;
	//�Ѿ���ʴ����
//�������������
	//������������и���ֵ
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
		//ʹ����ȡ�������ͱ�Ե����Ľ�����жԱȴӶ�ȥ����Ӱ�ı�Ե
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

	
	m_pFlowParaStruc=m_pLineSignal->StatLineSignal(pDC,m_nLeftPos5,m_nRightPos5,m_nLeftPos6,m_nRightPos6,
		                                               m_fSignal1,m_fSignal2,m_fSpace3,
													   m_nMaxErrorToler31,m_nMiniReliability31,m_nMaxErrorToler32,m_nMiniReliability32,
													   m_nLineHeight,edge1,edge2, *m_pdwPos,bIsShow,3,bIsShowSignal3);
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
		m_pDib2->Draw(pDC,CPoint(560+m_nRoadWay22Width,545),CSize(m_nLine2Width,m_nLineHeight),bIsShow);
		m_pDib1->Draw(pDC,CPoint(560+m_nRoadWay21Width,593),CSize(m_nLine1Width,m_nLineHeight),bIsShow);		
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

void CImageDeal2::SetDetectLine1(CDC *pDC,int nLineNum,
								 int nHeightPos5,int nLeftPos5,int nRightPos5,int nWidthLine,BOOL bIsShow)
{	
	CPoint oriPoint;
	oriPoint=CPoint(50,20);
	CBrush brush1(RGB(255,0,0) );//red line	
	int temp;
	if(nLeftPos5>=nRightPos5)
	{
		temp=nLeftPos5;
		nLeftPos5=nRightPos5;
		nRightPos5=temp;
	}

	m_rect1.left=oriPoint.x+nLeftPos5;
	m_rect1.right=oriPoint.x+nRightPos5;	
	m_rect1.bottom=oriPoint.y+240-nHeightPos5;//	
	m_rect1.top=oriPoint.y+240-nHeightPos5-nWidthLine;//
	
	pDC->SelectObject(brush1);

//	if(bIsShow==TRUE)
		pDC->Rectangle(m_rect1);	
		
}

void CImageDeal2::SetDetectLine2(CDC *pDC,int nLineNum,
								 int nHeightPos6,int nLeftPos6,int nRightPos6,int nWidthLine,BOOL bIsShow)
{	
	CPoint oriPoint;
	oriPoint=CPoint(50,20);
	CBrush brush2(RGB(0,255,0));//green line
	int temp;
	if(nLeftPos6>=nRightPos6)
	{
		temp=nLeftPos6;
		nLeftPos6=nRightPos6;
		nRightPos6=temp;
	}

	m_rect2.left=oriPoint.x+nLeftPos6;
	m_rect2.right=oriPoint.x+nRightPos6;
	m_rect2.bottom=oriPoint.y+240-nHeightPos6;
	m_rect2.top=oriPoint.y+240-nHeightPos6-nWidthLine;

	pDC->SelectObject(brush2);

//	if(bIsShow==TRUE)
		pDC->Rectangle(m_rect2);	

}
