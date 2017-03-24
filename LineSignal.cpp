//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*                    FX调试记录
		  视频下方汽车信号检测显示处理的地方
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "VehicleFlowCounter.h"
#include "LineSignal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLineSignal::CLineSignal()
{	
	m_pTransFlowParaClass=new CTransFlowPara();

	m_pAVIProducer=new AVIProducer();	
	m_pFlowParaStruc=new TRANSPORTATIONFLOWPARAMETER[1];
	m_dwTotalSignal=0;
	m_nUnitary=32767;
	m_nUnitaryValue1=0;
	m_nUnitaryValue2=0;	
	m_nFramePosition=0;
}

CLineSignal::~CLineSignal()
{
	delete m_pTransFlowParaClass;

	delete m_pAVIProducer;
	delete[] m_pFlowParaStruc;
	m_pFlowParaStruc=NULL;
}
/************************************
   FX   检测线1和检测线2的处理
************************************/
TRANSPORTATIONFLOWPARAMETER* CLineSignal::StatLineSignal(CDC *pDC,int m_nLeftPos1,int m_nRightPos1,int m_nLeftPos2,int m_nRightPos2,
														          float fSignal1,float fSignal2,float m_fSpace,
																  int nMaxErrorToler11,int nMiniReliability11,int nMaxErrorToler12,int nMiniReliability12,
																  int m_nLineHeight,LPBYTE pDetectLine1,LPBYTE pDetectLine2,DWORD nPos,
																  BOOL bIsShowStatLineSignal,int DrivewayNum,BOOL bIsShowSignal)
{
	int lineWidth1=abs(m_nRightPos1-m_nLeftPos1);
	int lineWidth2=abs(m_nRightPos2-m_nLeftPos2);
	int tempNum;
	m_nFramePosition=nPos;
	m_dwTotalSignal=0;
	m_fSignal1=fSignal1;
	m_fSignal2=fSignal2;
	if(DrivewayNum==1)
	{
		m_nMaxErrorToler11=nMaxErrorToler11;
		m_nMiniReliability11=nMiniReliability11;
		m_nMaxErrorToler12=nMaxErrorToler12;
		m_nMiniReliability12=nMiniReliability12;
	}
	if(DrivewayNum==2)
	{
		m_nMaxErrorToler11=nMaxErrorToler11;
		m_nMiniReliability11=nMiniReliability11;
		m_nMaxErrorToler12=nMaxErrorToler12;
		m_nMiniReliability12=nMiniReliability12;
	}
	if(DrivewayNum==3)
	{
		m_nMaxErrorToler11=nMaxErrorToler11;
		m_nMiniReliability11=nMiniReliability11;
		m_nMaxErrorToler12=nMaxErrorToler12;
		m_nMiniReliability12=nMiniReliability12;
	}
	if(DrivewayNum==4)
	{
		m_nMaxErrorToler11=nMaxErrorToler11;
		m_nMiniReliability11=nMiniReliability11;
		m_nMaxErrorToler12=nMaxErrorToler12;
		m_nMiniReliability12=nMiniReliability12;
	}

	//计算检测线1每帧中的信号统计
	for(int i=0;i<m_nLineHeight;i++)
	{
		for(int j=0;j<lineWidth1;j+=3)
		{
			tempNum=0;
			tempNum+=*(pDetectLine1++);
			tempNum=tempNum<<8;
			tempNum+=*(pDetectLine1++);
			tempNum=tempNum<<8;
			tempNum+=*(pDetectLine1++);
			m_dwTotalSignal+=tempNum;			
		}
	}
	m_dwTotalSignal/=(m_nLineHeight*lineWidth1);
	if(m_nUnitary==0)
		m_nUnitary=1;
	m_nUnitaryValue1=(int)(m_dwTotalSignal/m_nUnitary*m_fSignal1);//进行归一化处理
	if(m_nUnitaryValue1<11)
		m_nUnitaryValue1=0;	
	m_dwTotalSignal=0;
	//计算检测线2每帧中的信号统计
    for(int i=0;i<m_nLineHeight;i++)
	{
		for(int j=0;j<lineWidth2;j+=3)
		{
			tempNum=0;
			tempNum+=*(pDetectLine2++);
			tempNum=tempNum<<8;
			tempNum+=*(pDetectLine2++);
			tempNum=tempNum<<8;
			tempNum+=*(pDetectLine2++);
			m_dwTotalSignal+=tempNum;			
		}
	}
	m_dwTotalSignal/=(m_nLineHeight*lineWidth2);
	m_nUnitaryValue2=(int)(m_dwTotalSignal/m_nUnitary*m_fSignal2);//减去一个阈值10去除阴影
	if(m_nUnitaryValue2<10)
		m_nUnitaryValue2=0;	
	m_dwTotalSignal=0;
	if(m_nUnitaryValue1>105)
		m_nUnitaryValue1=105;
	if(m_nUnitaryValue2>115)
		m_nUnitaryValue2=115;
	return ShowCoordinate(pDC,nPos,m_fSpace,m_nUnitaryValue1,m_nUnitaryValue2,bIsShowStatLineSignal,DrivewayNum,bIsShowSignal);
}
/************************************
   FX   bIsShowStatLineSignal
当其为1的时候，表示需要显示检测的结果
************************************/
TRANSPORTATIONFLOWPARAMETER* CLineSignal::ShowCoordinate(CDC *pDC,DWORD nPos,float m_fSpace,int m_nUnitaryValue1,int m_nUnitaryValue2,BOOL bIsShowStatLineSignal,int DrivewayNum,BOOL bIsShowSignal)
{

	CPoint oriPoint(35,580);
	int x=oriPoint.x;
	int y=oriPoint.y;
	int i=nPos%240;
	i=i*2;
	CPen pen;
	if(DrivewayNum==1)
	{
		m_pFlowParaStruc=m_pTransFlowParaClass->FlowCounter1(pDC,m_fSpace,
			                                                 m_nMaxErrorToler11,m_nMiniReliability11,m_nMaxErrorToler12,m_nMiniReliability12,
			                                                 m_nUnitaryValue1,m_nUnitaryValue2,nPos,bIsShowStatLineSignal,bIsShowSignal);	
	}
	if(DrivewayNum==2)
	{
		m_pFlowParaStruc=m_pTransFlowParaClass->FlowCounter2(pDC,m_fSpace,
		                                                 m_nMaxErrorToler11,m_nMiniReliability11,m_nMaxErrorToler12,m_nMiniReliability12,
		                                                 m_nUnitaryValue1,m_nUnitaryValue2,nPos,bIsShowStatLineSignal,bIsShowSignal);	
	}
	if(DrivewayNum==3)
	{
		m_pFlowParaStruc=m_pTransFlowParaClass->FlowCounter3(pDC,m_fSpace,
			                                                 m_nMaxErrorToler11,m_nMiniReliability11,m_nMaxErrorToler12,m_nMiniReliability12,
			                                                 m_nUnitaryValue1,m_nUnitaryValue2,nPos,bIsShowStatLineSignal,bIsShowSignal);	
	}
	if(DrivewayNum==4)
	{
		m_pFlowParaStruc=m_pTransFlowParaClass->FlowCounter4(pDC,m_fSpace,
			                                                 m_nMaxErrorToler11,m_nMiniReliability11,m_nMaxErrorToler12,m_nMiniReliability12,
			                                                 m_nUnitaryValue1,m_nUnitaryValue2,nPos,bIsShowStatLineSignal,bIsShowSignal);	
	}

	if(bIsShowStatLineSignal==TRUE)
	{
		int j;		
		/******************定义坐标轴************************/
		pen.CreatePen(PS_SOLID,2,RGB(0,0,0));//原来0,0，255
		pDC->SelectObject(pen);

		pDC->MoveTo(x,y-260);
		pDC->LineTo(x,y);
		pDC->LineTo(x+505,y);

		pDC->MoveTo(x,y-120);
		pDC->LineTo(x+505,y-120);
		pDC->MoveTo(x+498,y-124);
		pDC->LineTo(x+505,y-120);
		pDC->LineTo(x+498,y-116);

		pDC->MoveTo(x-4,y-252);
		pDC->LineTo(x,y-260);
		pDC->LineTo(x+4,y-252);

		pDC->MoveTo(x+498,y-4);
		pDC->LineTo(x+505,y);
		pDC->LineTo(x+498,y+4);
		pen.DeleteObject();
		//实坐标轴
		pen.CreatePen(PS_SOLID,1,RGB(0,0,0));//原来128,128,128
		pDC->SelectObject(pen);
		CString str;
		pDC->SetTextColor(RGB(0,0,0));
		for(j=0;j<500;j++)//X轴
		{
			if(j%20==0)
			{
				pDC->MoveTo(x+j,y);
				pDC->LineTo(x+j,y+6);
				pDC->MoveTo(x+j,y-120);
				pDC->LineTo(x+j,y-114);					
			}
			if(j%40==0)
			{
				str.Format("%d",(j/2));
				pDC->TextOut(x+j-10,y+6,str,str.GetLength());
			}
			if(j%10==0)
			{
				pDC->MoveTo(x+j,y);
				pDC->LineTo(x+j,y+4);
				pDC->MoveTo(x+j,y-120);
				pDC->LineTo(x+j,y-116);
			}		
		}
		for(j=1;j<120;j++)//y轴
		{
			if(j%20==0)
			{
				pDC->MoveTo(x-6,y-j);
				pDC->LineTo(x,y-j);
				str.Format("%d",j);
				pDC->TextOut(x-30,y-7-j,str,str.GetLength());
			}
			if(j%10==0)
			{
				pDC->MoveTo(x-4,y-j);
				pDC->LineTo(x,y-j);
			}		
		}
		for(j=120;j<256;j++)//y轴
		{
			if(j%20==0)
			{
				pDC->MoveTo(x-6,y-j);
				pDC->LineTo(x,y-j);
				str.Format("%d",j-120);
				pDC->TextOut(x-30,y-7-j,str,str.GetLength());
			}
			if(j%10==0)
			{
				pDC->MoveTo(x-4,y-j);
				pDC->LineTo(x,y-j);
			}		
		}//坐标标尺刻度
		pen.DeleteObject();
	
		pDC->SetTextColor(RGB(0,0,0));//原来255,0，255
		pDC->TextOut(260,y-116,"上检测线                                           帧数(F)",58);
		pDC->TextOut(260,y+20,"下检测线                                           帧数(F)",58);
	//	pDC->TextOut(x+160,y-280,/*str*/"虚拟检测线上的检测信号",22);//坐标轴名称
 		
		ShowSignal(pDC,nPos,m_nUnitaryValue1,m_nUnitaryValue2,bIsShowSignal);	
	}	
	return m_pFlowParaStruc;
}

void CLineSignal::ShowSignal(CDC *pDC,DWORD nPos,int m_nUnitaryValue1,int m_nUnitaryValue2,BOOL bIsShowSignal)
{
	CPoint oriPoint(35,580);
	int x=oriPoint.x;
	int y=oriPoint.y;
	int i=nPos%240;
	i=i*2;
	CPen pen;

	pen.CreatePen(PS_SOLID,1,RGB(0,0,0));//原来128,0，128
	pDC->SelectObject(pen);
	if(bIsShowSignal)
	{
		pDC->MoveTo(x+i,580);		
		pDC->LineTo(x+i,580-m_nUnitaryValue1);	
	}
	
	pen.DeleteObject();

	pen.CreatePen(PS_SOLID,1,RGB(0,0,0));//原来128,128,0
	pDC->SelectObject(pen);
	if(bIsShowSignal)
	{
		pDC->MoveTo(x+i,460);		
		pDC->LineTo(x+i,460-m_nUnitaryValue2);
	}
	
	pen.DeleteObject();
}

