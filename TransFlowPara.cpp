//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*                    FX调试记录
           通多阈值计算诸如车速，车流量等参数的地方
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "VehicleFlowCounter.h"
#include "TransFlowPara.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransFlowPara::CTransFlowPara()
{	
	m_pFlowParaStruc=new TRANSPORTATIONFLOWPARAMETER[1];	
//初始化各车道的参数
	m_nSpeedNum1=0;
	m_nSpeedNum2=0;
	m_nSpeedNum3=0;
	m_nSpeedNum4=0;

	m_nTempSufferancePos11=0;
	m_nSumSufferance11=0;
	m_nTempSufferancePos12=0;
	m_nSumSufferance12=0;

	m_nTempSufferancePos21=0;
	m_nSumSufferance21=0;
	m_nTempSufferancePos22=0;
	m_nSumSufferance22=0;

	m_nTempSufferancePos31=0;
	m_nSumSufferance31=0;
	m_nTempSufferancePos32=0;
	m_nSumSufferance32=0;

	m_nTempSufferancePos41=0;
	m_nSumSufferance41=0;
	m_nTempSufferancePos42=0;
	m_nSumSufferance42=0;
//1车道
	m_pFlowParaStruc->VehicleNumber1=0;
	m_pFlowParaStruc->Speed1=0;
	m_pFlowParaStruc->TimeDensity1=0.0;
	m_pFlowParaStruc->MinuteVehicleNum1=0;
	m_pFlowParaStruc->VehicleNumber2=0;
	m_pFlowParaStruc->Speed2=0;
	m_pFlowParaStruc->TimeDensity2=0.0;
	m_pFlowParaStruc->MinuteVehicleNum2=0;
	m_pFlowParaStruc->VehicleNumber3=0;
	m_pFlowParaStruc->Speed3=0;
	m_pFlowParaStruc->TimeDensity3=0.0;
	m_pFlowParaStruc->MinuteVehicleNum3=0;
	m_pFlowParaStruc->VehicleNumber4=0;
	m_pFlowParaStruc->Speed4=0;
	m_pFlowParaStruc->TimeDensity4=0.0;
	m_pFlowParaStruc->MinuteVehicleNum4=0;

	m_nVehicleNum11=0;
	m_nVehicleNum12=0;
	m_nVehicleNum21=0;
	m_nVehicleNum22=0;
	m_nVehicleNum31=0;
	m_nVehicleNum32=0;
	m_nVehicleNum41=0;
	m_nVehicleNum42=0;

	m_nVehicleTemp11=0;
	m_nVehicleTemp12=0;
	m_nVehicleTemp21=0;
	m_nVehicleTemp22=0;
	m_nVehicleTemp31=0;
	m_nVehicleTemp32=0;
	m_nVehicleTemp41=0;
	m_nVehicleTemp42=0;

	m_nOccupyFrame1=0;
	m_nOccupyFrame2=0;
	m_nOccupyFrame3=0;
	m_nOccupyFrame4=0;

	nTempHas1=0;
	nTempnPos1=0;
	nTempHas2=0;
	nTempnPos2=0;
	nTempHas3=0;
	nTempnPos3=0;
	nTempHas4=0;
	nTempnPos4=0;	
	
	m_nThresshold1=0;//信号的最小有效阈值
	m_nThresshold2=0;//需要时也要设置各个车道的（4个）

	m_nCredible11=0;//有效值(可信值)
	m_nSufferance11=0;//容错值(忍受值)
	m_nCredible12=0;
	m_nSufferance12=0;
	m_nCredible21=0;//有效值(可信值)
	m_nSufferance21=0;//容错值(忍受值)
	m_nCredible22=0;
	m_nSufferance22=0;
	m_nCredible31=0;//有效值(可信值)
	m_nSufferance31=0;//容错值(忍受值)
	m_nCredible32=0;
	m_nSufferance32=0;
	m_nCredible41=0;//有效值(可信值)
	m_nSufferance41=0;//容错值(忍受值)
	m_nCredible42=0;
	m_nSufferance42=0;
	
	m_bIsProcess11=FALSE;//用于判断是否有进程启动	
	m_bIsProcess12=FALSE;
	m_bIsProcess21=FALSE;//用于判断是否有进程启动	
	m_bIsProcess22=FALSE;	
	m_bIsProcess31=FALSE;//用于判断是否有进程启动	
	m_bIsProcess32=FALSE;	
	m_bIsProcess41=FALSE;//用于判断是否有进程启动	
	m_bIsProcess42=FALSE;
//2车道
	m_pFlowParaStruc->VehicleNumber2=0;
	m_pFlowParaStruc->Speed2=0;
	m_pFlowParaStruc->TimeDensity2=0;
	m_pFlowParaStruc->MinuteVehicleNum2=0;
//3车道
	m_pFlowParaStruc->VehicleNumber3=0;
	m_pFlowParaStruc->Speed3=0;
	m_pFlowParaStruc->TimeDensity3=0;
	m_pFlowParaStruc->MinuteVehicleNum3=0;
//4车道
	m_pFlowParaStruc->VehicleNumber4=0;
	m_pFlowParaStruc->Speed4=0;
	m_pFlowParaStruc->TimeDensity4=0;
	m_pFlowParaStruc->MinuteVehicleNum4=0;
//总的参数
	m_pFlowParaStruc->VehicleNumberSum=0;
	m_pFlowParaStruc->SpeedSum=0;
	m_pFlowParaStruc->TimeDensitySum=0;
	m_pFlowParaStruc->MinuteVehicleNumSum=0;
}

CTransFlowPara::~CTransFlowPara()
{
	delete[] m_pFlowParaStruc;
	m_pFlowParaStruc=NULL;
}
//车道1
TRANSPORTATIONFLOWPARAMETER* CTransFlowPara::FlowCounter1(CDC *pDC,float m_fSpace1,
														  int m_nMaxErrorToler11,int m_nMiniReliability11,int m_nMaxErrorToler12,int m_nMiniReliability12,
														  int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShowStatLineSignal,BOOL bIsShowSignal)
{
	//车道1上检测线计算开始	   
	if(nLineSignal2>m_nThresshold2)//线信号是否大于阈值
	{
		if(m_bIsProcess12==FALSE)  //判断是否有进程启动，如果没有则启动
			m_bIsProcess12=TRUE;		
		m_nCredible12++;           //分配奖赏值给进程
		if(m_nSufferance12>m_nMaxErrorToler12)//处罚值统计大于最大容错度
		{
			if((m_nCredible12+m_nSumSufferance12)>m_nMiniReliability12)//奖赏值大于最小可信度
			{
				m_nVehicleNum12++; //调试完了可能去掉
								
				nTempHas1=m_nCredible12+m_nSumSufferance12;
				nTempnPos1=nPos-nTempHas1;

				m_bIsProcess12=FALSE;
				m_nCredible12=0;
				m_nSufferance12=0;
				m_nSumSufferance12=0;
			}
			else                   //奖赏值不大于最小可信度
			{
				m_bIsProcess12=FALSE;
				m_nCredible12=0;
				m_nSufferance12=0;
				m_nSumSufferance12=0;
			}
		}
		else                       //处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
		{

		}
	}
	else                           //线信号是否不大于阈值
	{
		if(m_bIsProcess12==TRUE)   //有跟踪进程启动
		{
			if(m_nSufferance12==0)
			{
				m_nSufferance12++;
				m_nTempSufferancePos12=nPos;
			}
			else
			{
				if((nPos-m_nTempSufferancePos12)==1)
				{
					m_nSufferance12++;
					m_nTempSufferancePos12=nPos;
				}
				else
				{
					m_nSumSufferance12+=m_nSufferance12;
					m_nSufferance12=0;
				}
			}//以上这段代码可以使只有超过连续的几帧时才转入计数
			if(m_nSufferance12>m_nMaxErrorToler12)//处罚值统计大于最大容错度
			{
				if((m_nCredible12+m_nSumSufferance12)>m_nMiniReliability12)//奖赏值大于最小可信度
				{
					m_nVehicleNum12++;				
					nTempHas1=m_nCredible12+m_nSumSufferance12;
					nTempnPos1=nPos-nTempHas1;

					m_bIsProcess12=FALSE;
					m_nCredible12=0;
					m_nSufferance12=0;
					m_nSumSufferance12=0;
				}
				else//奖赏值不大于最小可信度
				{
					m_bIsProcess12=FALSE;
					m_nCredible12=0;
					m_nSufferance12=0;
					m_nSumSufferance12=0;
				}
			}
			else                            //处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
			{}
		}
		else                                //没有跟踪进程启动,什么也不作转入下一帧，继续跟踪
		{}
	}
	//车道1上检测线计算结束

	//车道1下检测线计算开始
	if(nLineSignal1>m_nThresshold1)//线信号是否大于阈值
	{
		if(m_bIsProcess11==FALSE)//判断是否有进程启动，如果没有则启动
			m_bIsProcess11=TRUE;		
		m_nCredible11++;//分配奖赏值给进程
		if(m_nSufferance11>m_nMaxErrorToler11)//处罚值统计大于最大容错度
		{
			if((m_nCredible11+m_nSumSufferance11)>m_nMiniReliability11)//奖赏值大于最小可信度
			{
				m_nVehicleNum11++;
				m_nOccupyFrame1+=m_nCredible11;
				m_nOccupyFrame1+=m_nSumSufferance11;				
				Speed1(nPos-m_nSufferance11-m_nCredible11-m_nSumSufferance11,nTempnPos1,m_fSpace1);
				m_bIsProcess11=FALSE;
				m_nCredible11=0;
				m_nSufferance11=0;
				m_nSumSufferance11=0;				
			}
			else//奖赏值不大于最小可信度
			{
				m_bIsProcess11=FALSE;
				m_nCredible11=0;
				m_nSufferance11=0;
				m_nSumSufferance11=0;
			}
		}
		else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
		{}
	}
	else//线信号是否不大于阈值
	{
		if(m_bIsProcess11==TRUE)     //有跟踪进程启动
		{
			if(m_nSufferance11==0)
			{
				m_nSufferance11++;
				m_nTempSufferancePos11=nPos;
			}
			else
			{
				if((nPos-m_nTempSufferancePos11)==1)
				{
					m_nSufferance11++;
					m_nTempSufferancePos11=nPos;
				}
				else
				{
					m_nSumSufferance11+=m_nSufferance11;
					m_nSufferance11=0;
				}
			}

			if(m_nSufferance11>m_nMaxErrorToler11)//处罚值统计大于最大容错度
			{
				if((m_nCredible11+m_nSumSufferance11)>m_nMiniReliability11)//奖赏值大于最小可信度
				{
					m_nVehicleNum11++;
					m_nOccupyFrame1+=m_nCredible11;
					m_nOccupyFrame1+=m_nSumSufferance11;					
					Speed1(nPos-m_nSufferance11-m_nCredible11-m_nSumSufferance11,nTempnPos1,m_fSpace1);
					m_bIsProcess11=FALSE;
					m_nCredible11=0;
					m_nSufferance11=0;
					m_nSumSufferance11=0;
				}
				else//奖赏值不大于最小可信度
				{
					m_bIsProcess11=FALSE;
					m_nCredible11=0;
					m_nSufferance11=0;
					m_nSumSufferance11=0;
				}
			}
			else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
			{}
		}
		else//没有跟踪进程启动,什么也不作转入下一帧，继续跟踪
		{}
	}
	//车道1下检测线计算结束
	if(nPos==1)
	{
		m_nVehicleNum11=0;
		m_nVehicleNum12=0;
		m_nSpeedNum1=0;
	}

	if(bIsShowStatLineSignal&&bIsShowSignal)
	{
		CString str;
		pDC->TextOut(380,45,"车道1参数:");		
		str.Format("检测线2容忍帧数:%d",m_nSufferance12);
		pDC->TextOut(380,65,str);
		str.Format("检测线2信任帧数:%d",m_nCredible12);
		pDC->TextOut(380,85,str);
		str.Format("检测线1容忍帧数:%d",m_nSufferance11);
		pDC->TextOut(380,105,str);
		str.Format("检测线1信任帧数:%d",m_nCredible11);
		pDC->TextOut(380,125,str);
		str.Format("上检测线车辆数:%d",m_nVehicleNum12);
		pDC->TextOut(380,145,str);
		str.Format("下检测线车辆数:%d",m_nVehicleNum11);
		pDC->TextOut(380,165,str);
		str.Format("测速%d次",m_nSpeedNum1);
		pDC->TextOut(380,225,str);		
	}//调试用	
	m_pFlowParaStruc->VehicleNumber1=m_nVehicleNum11;//计数

	MinuteVehicleNum1(nPos);//分钟交通量

	if(nPos==1)//速度
		m_pFlowParaStruc->Speed1=0;

	TimeDensity1(nPos);//时间占有率
	

	return m_pFlowParaStruc;
}

void CTransFlowPara::MinuteVehicleNum1(int nPos)
{
	if(nPos%1500==0)
	{
		m_nVehicleTemp12=m_nVehicleNum11;
		m_pFlowParaStruc->MinuteVehicleNum1=abs(m_nVehicleTemp12-m_nVehicleTemp11);					
		m_nVehicleTemp11=m_nVehicleTemp12;		
	}//分钟交通量
	if(nPos==1)
			m_pFlowParaStruc->MinuteVehicleNum1=0;
}

void CTransFlowPara::Speed1(int nStart1,int nStart2,float m_fSpace1)
{
	if(m_nVehicleNum12!=m_nVehicleNum11)
		m_nVehicleNum12=m_nVehicleNum11;
	else//检测线1迟于检测线2，而且两线相近不可能有两个车在，故在检测线1计数时调用该函数
	{	//若m_nVehicleNum12!=m_nVehicleNum11说明两检测线上检测的不是同一辆车，排除
		if(nStart1>nStart2)
		{
			m_pFlowParaStruc->Speed1=m_fSpace1*90/(float)(nStart1-nStart2);//即(6/1000)/((0.04*(nStart1-nStart2))/3600)
			m_nSpeedNum1++;
		}
		else
			;
	}	
}
 
void CTransFlowPara::TimeDensity1(int nPos)
{
	if(nPos==0)
		nPos=1;
	if(nPos==1)
		m_nOccupyFrame1=0;	
	m_pFlowParaStruc->TimeDensity1=(float)m_nOccupyFrame1/(float)nPos;
	//上面是时间占有率
}

//车道2
TRANSPORTATIONFLOWPARAMETER* CTransFlowPara::FlowCounter2(CDC *pDC,float m_fSpace2,
														  int m_nMaxErrorToler21,int m_nMiniReliability21,int m_nMaxErrorToler22,int m_nMiniReliability22,
														  int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShowStatLineSignal,BOOL bIsShowSignal)
{
	//车道1上检测线计算开始
	if(nLineSignal2>m_nThresshold2)//线信号是否大于阈值
	{
		if(m_bIsProcess22==FALSE)//判断是否有进程启动，如果没有则启动
			m_bIsProcess22=TRUE;		
		m_nCredible22++;//分配奖赏值给进程
		if(m_nSufferance22>m_nMaxErrorToler22)//处罚值统计大于最大容错度
		{
			if((m_nCredible22+m_nSumSufferance22)>m_nMiniReliability22)//奖赏值大于最小可信度
			{
				m_nVehicleNum22++;								
				nTempHas2=m_nCredible22+m_nSumSufferance22;
				nTempnPos2=nPos-nTempHas2;
				m_bIsProcess22=FALSE;
				m_nCredible22=0;
				m_nSufferance22=0;
				m_nSumSufferance22=0;
			}
			else//奖赏值不大于最小可信度
			{
				m_bIsProcess22=FALSE;
				m_nCredible22=0;
				m_nSufferance22=0;
				m_nSumSufferance22=0;
			}
		}
		else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
		{}
	}
	else//线信号是否不大于阈值
	{
		if(m_bIsProcess22==TRUE)//有跟踪进程启动
		{
			if(m_nSufferance22==0)
			{
				m_nSufferance22++;
				m_nTempSufferancePos22=nPos;
			}
			else
			{
				if((nPos-m_nTempSufferancePos22)==1)
				{
					m_nSufferance22++;
					m_nTempSufferancePos22=nPos;
				}
				else
				{
					m_nSumSufferance22+=m_nSufferance22;
					m_nSufferance22=0;
				}
			}
			
			if(m_nSufferance22>m_nMaxErrorToler22)//处罚值统计大于最大容错度
			{
				if((m_nCredible22+m_nSumSufferance22)>m_nMiniReliability22)//奖赏值大于最小可信度
				{
					m_nVehicleNum22++;					
					nTempHas2=m_nCredible22+m_nSumSufferance22;
					nTempnPos2=nPos-nTempHas2;
					m_bIsProcess22=FALSE;
					m_nCredible22=0;
					m_nSufferance22=0;
					m_nSumSufferance22=0;
				}
				else//奖赏值不大于最小可信度
				{
					m_bIsProcess22=FALSE;
					m_nCredible22=0;
					m_nSufferance22=0;
					m_nSumSufferance22=0;
				}
			}
			else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
			{}
		}
		else//没有跟踪进程启动,什么也不作转入下一帧，继续跟踪
		{}
	}
	//车道1上检测线计算结束

	//车道1下检测线计算开始
	if(nLineSignal1>m_nThresshold1)//线信号是否大于阈值
	{
		if(m_bIsProcess21==FALSE)//判断是否有进程启动，如果没有则启动
			m_bIsProcess21=TRUE;		
		m_nCredible21++;//分配奖赏值给进程
		if(m_nSufferance21>m_nMaxErrorToler21)//处罚值统计大于最大容错度
		{
			if((m_nCredible21+m_nSumSufferance21)>m_nMiniReliability21)//奖赏值大于最小可信度
			{
				m_nVehicleNum21++;
				m_nOccupyFrame2+=m_nCredible21;
				m_nOccupyFrame2+=m_nSumSufferance21;				
				Speed2(nPos-m_nSufferance21-m_nCredible21-m_nSumSufferance21,nTempnPos2,m_fSpace2);
				m_bIsProcess21=FALSE;
				m_nCredible21=0;
				m_nSufferance21=0;
				m_nSumSufferance21=0;				
			}
			else//奖赏值不大于最小可信度
			{
				m_bIsProcess21=FALSE;
				m_nCredible21=0;
				m_nSufferance21=0;
				m_nSumSufferance21=0;
			}
		}
		else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
		{}
	}
	else//线信号是否不大于阈值
	{
		if(m_bIsProcess21==TRUE)//有跟踪进程启动
		{
			if(m_nSufferance21==0)
			{
				m_nSufferance21++;
				m_nTempSufferancePos21=nPos;
			}
			else
			{
				if((nPos-m_nTempSufferancePos21)==1)
				{
					m_nSufferance21++;
					m_nTempSufferancePos21=nPos;
				}
				else
				{
					m_nSumSufferance21+=m_nSufferance21;
					m_nSufferance21=0;
				}
			}
			
			if(m_nSufferance21>m_nMaxErrorToler21)//处罚值统计大于最大容错度
			{
				if((m_nCredible21+m_nSumSufferance21)>m_nMiniReliability21)//奖赏值大于最小可信度
				{
					m_nVehicleNum21++;
					m_nOccupyFrame2+=m_nCredible21;
					m_nOccupyFrame2+=m_nSumSufferance21;					
					Speed2(nPos-m_nSufferance21-m_nCredible21-m_nSumSufferance21,nTempnPos2,m_fSpace2);
					m_bIsProcess21=FALSE;
					m_nCredible21=0;
					m_nSufferance21=0;
					m_nSumSufferance21=0;
				}
				else//奖赏值不大于最小可信度
				{
					m_bIsProcess21=FALSE;
					m_nCredible21=0;
					m_nSufferance21=0;
					m_nSumSufferance21=0;
				}
			}
			else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
			{}
		}
		else//没有跟踪进程启动,什么也不作转入下一帧，继续跟踪
		{}
	}
	//车道1前检测线计算结束
//	*/
	if(bIsShowStatLineSignal&&bIsShowSignal)
	{
		CString str;
		pDC->TextOut(380,45,"车道2参数:");		
		str.Format("上检测线容忍帧数:%d",m_nSufferance22);
		pDC->TextOut(380,65,str);
		str.Format("上检测线信任帧数:%d",m_nCredible22);
		pDC->TextOut(380,85,str);
		str.Format("下检测线容忍帧数:%d",m_nSufferance21);
		pDC->TextOut(380,105,str);
		str.Format("下检测线信任帧数:%d",m_nCredible21);
		pDC->TextOut(380,125,str);
		str.Format("上检测线车辆数:%d",m_nVehicleNum22);
		pDC->TextOut(380,145,str);
		str.Format("下检测线车辆数:%d",m_nVehicleNum21);
		pDC->TextOut(380,165,str);
		str.Format("测速%d次",m_nSpeedNum2);
		pDC->TextOut(380,225,str);
	}//调试用

	if(nPos==1)
	{
		m_nVehicleNum21=0;
		m_nVehicleNum22=0;
		m_nSpeedNum2=0;
	}
		
	m_pFlowParaStruc->VehicleNumber2=m_nVehicleNum21;//计数

	MinuteVehicleNum2(nPos);//分钟交通量

	if(nPos==1)//速度
		m_pFlowParaStruc->Speed2=0;

	TimeDensity2(nPos);//时间占有率
	

	return m_pFlowParaStruc;
}

void CTransFlowPara::MinuteVehicleNum2(int nPos)
{
	if(nPos%1500==0)
	{
		m_nVehicleTemp22=m_nVehicleNum21;
		m_pFlowParaStruc->MinuteVehicleNum2=abs(m_nVehicleTemp22-m_nVehicleTemp21);					
		m_nVehicleTemp21=m_nVehicleTemp22;		
	}//分钟交通量
	if(nPos==1)
			m_pFlowParaStruc->MinuteVehicleNum2=0;
}

void CTransFlowPara::Speed2(int nStart1,int nStart2,float m_fSpace2)
{
	if(m_nVehicleNum22!=m_nVehicleNum21)
		m_nVehicleNum22=m_nVehicleNum21;
	else//检测线1迟于检测线2，而且两线相近不可能有两个车在，故在检测线1计数时调用该函数
	{	//若m_nVehicleNum12!=m_nVehicleNum11说明两检测线上检测的不是同一辆车，排除
		if(nStart1>nStart2)
		{
			m_pFlowParaStruc->Speed2=m_fSpace2*90/(float)(nStart1-nStart2);//即(6/1000)/((0.04*(nStart1-nStart2))/3600)
			m_nSpeedNum2++;
		}
		else
			;
	}	
}

void CTransFlowPara::TimeDensity2(int nPos)
{
	if(nPos==0)
		nPos=1;
	if(nPos==1)
		m_nOccupyFrame2=0;	
	m_pFlowParaStruc->TimeDensity2=(float)m_nOccupyFrame2/(float)nPos;
}

//车道3
TRANSPORTATIONFLOWPARAMETER* CTransFlowPara::FlowCounter3(CDC *pDC,float m_fSpace3,
														  int m_nMaxErrorToler31,int m_nMiniReliability31,int m_nMaxErrorToler32,int m_nMiniReliability32,
														  int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShowStatLineSignal,BOOL bIsShowSignal)
{
	//车道1上检测线计算开始
	if(nLineSignal2>m_nThresshold2)//线信号是否大于阈值
	{
		if(m_bIsProcess32==FALSE)//判断是否有进程启动，如果没有则启动
			m_bIsProcess32=TRUE;		
		m_nCredible32++;//分配奖赏值给进程
		if(m_nSufferance32>m_nMaxErrorToler32)//处罚值统计大于最大容错度
		{
			if((m_nCredible32+m_nSumSufferance32)>m_nMiniReliability32)//奖赏值大于最小可信度
			{
				m_nVehicleNum32++;				
				nTempHas3=m_nCredible32+m_nSumSufferance32;
				nTempnPos3=nPos-nTempHas3;
				m_bIsProcess32=FALSE;
				m_nCredible32=0;
				m_nSufferance32=0;
				m_nSumSufferance32=0;
			}
			else//奖赏值不大于最小可信度
			{
				m_bIsProcess32=FALSE;
				m_nCredible32=0;
				m_nSufferance32=0;
				m_nSumSufferance32=0;
			}
		}
		else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
		{}
	}
	else//线信号是否不大于阈值
	{
		if(m_bIsProcess32==TRUE)//有跟踪进程启动
		{
			if(m_nSufferance32==0)
			{
				m_nSufferance32++;
				m_nTempSufferancePos32=nPos;
			}
			else
			{
				if((nPos-m_nTempSufferancePos32)==1)
				{
					m_nSufferance32++;
					m_nTempSufferancePos32=nPos;
				}
				else
				{
					m_nSumSufferance32+=m_nSufferance32;
					m_nSufferance32=0;
				}
			}

			if(m_nSufferance32>m_nMaxErrorToler32)//处罚值统计大于最大容错度
			{
				if((m_nCredible32+m_nSufferance32)>m_nMiniReliability32)//奖赏值大于最小可信度
				{
					m_nVehicleNum32++;					
					nTempHas3=m_nCredible32+m_nSumSufferance32;
					nTempnPos3=nPos-nTempHas3;
					m_bIsProcess32=FALSE;
					m_nCredible32=0;
					m_nSufferance32=0;
					m_nSumSufferance32=0;
					
				}
				else//奖赏值不大于最小可信度
				{
					m_bIsProcess32=FALSE;
					m_nCredible32=0;
					m_nSufferance32=0;
					m_nSumSufferance32=0;
				}
			}
			else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
			{}
		}
		else//没有跟踪进程启动,什么也不作转入下一帧，继续跟踪
		{}
	}
	//车道1上检测线计算结束

	//车道1下检测线计算开始
	if(nLineSignal1>m_nThresshold1)//线信号是否大于阈值
	{
		if(m_bIsProcess31==FALSE)//判断是否有进程启动，如果没有则启动
			m_bIsProcess31=TRUE;		
		m_nCredible31++;//分配奖赏值给进程
		if(m_nSufferance31>m_nMaxErrorToler31)//处罚值统计大于最大容错度
		{
			if((m_nCredible31+m_nSumSufferance31)>m_nMiniReliability31)//奖赏值大于最小可信度
			{
				m_nVehicleNum31++;
				m_nOccupyFrame3+=m_nCredible31;
				m_nOccupyFrame3+=m_nSumSufferance31;				
				Speed3(nPos-m_nSufferance31-m_nCredible31-m_nSumSufferance31,nTempnPos3,m_fSpace3);
				m_bIsProcess31=FALSE;
				m_nCredible31=0;
				m_nSufferance31=0;
				m_nSumSufferance31=0;				
			}
			else//奖赏值不大于最小可信度
			{
				m_bIsProcess31=FALSE;
				m_nCredible31=0;
				m_nSufferance31=0;
				m_nSumSufferance31=0;
			}
		}
		else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
		{}
	}
	else//线信号是否不大于阈值
	{
		if(m_bIsProcess31==TRUE)//有跟踪进程启动
		{
			if(m_nSufferance31==0)
			{
				m_nSufferance31++;
				m_nTempSufferancePos31=nPos;
			}
			else
			{
				if((nPos-m_nTempSufferancePos31)==1)
				{
					m_nSufferance31++;
					m_nTempSufferancePos31=nPos;
				}
				else
				{
					m_nSumSufferance31+=m_nSufferance31;
					m_nSufferance31=0;
				}
			}
			
			if(m_nSufferance31>m_nMaxErrorToler31)//处罚值统计大于最大容错度
			{
				if((m_nCredible31+m_nSumSufferance31)>m_nMiniReliability31)//奖赏值大于最小可信度
				{
					m_nVehicleNum31++;
					m_nOccupyFrame3+=m_nCredible31;
					m_nOccupyFrame3+=m_nSumSufferance31;					
					Speed3(nPos-m_nSufferance31-m_nCredible31-m_nSumSufferance31,nTempnPos3,m_fSpace3);
					m_bIsProcess31=FALSE;
					m_nCredible31=0;
					m_nSufferance31=0;
					m_nSumSufferance31=0;
				}
				else//奖赏值不大于最小可信度
				{
					m_bIsProcess31=FALSE;
					m_nCredible31=0;
					m_nSufferance31=0;
					m_nSumSufferance31=0;
				}
			}
			else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
			{}
		}
		else//没有跟踪进程启动,什么也不作转入下一帧，继续跟踪
		{}
	}
	//车道1前检测线计算结束
	if(nPos==1)
	{
		m_nVehicleNum31=0;
		m_nVehicleNum32=0;
		m_nSpeedNum3=0;
	}
		
	if(bIsShowStatLineSignal&&bIsShowSignal)
	{
		CString str;
		pDC->TextOut(380,45,"车道3参数:");		
		str.Format("上检测线容忍帧数:%d",m_nSufferance32);
		pDC->TextOut(380,65,str);
		str.Format("上检测线信任帧数:%d",m_nCredible32);
		pDC->TextOut(380,85,str);
		str.Format("下检测线容忍帧数:%d",m_nSufferance31);
		pDC->TextOut(380,105,str);
		str.Format("下检测线信任帧数:%d",m_nCredible31);
		pDC->TextOut(380,125,str);
		str.Format("上检测线车辆数:%d",m_nVehicleNum32);
		pDC->TextOut(380,145,str);
		str.Format("下检测线车辆数:%d",m_nVehicleNum31);
		pDC->TextOut(380,165,str);
		str.Format("测速%d次",m_nSpeedNum3);
		pDC->TextOut(380,225,str);

	}//调试用
	
	m_pFlowParaStruc->VehicleNumber3=m_nVehicleNum31;//计数

	MinuteVehicleNum3(nPos);//分钟交通量

	if(nPos==1)//速度
		m_pFlowParaStruc->Speed3=0;

	TimeDensity3(nPos);//时间占有率
	

	return m_pFlowParaStruc;
}

void CTransFlowPara::MinuteVehicleNum3(int nPos)
{
	if(nPos%1500==0)
	{
		m_nVehicleTemp32=m_nVehicleNum31;
		m_pFlowParaStruc->MinuteVehicleNum3=abs(m_nVehicleTemp32-m_nVehicleTemp31);					
		m_nVehicleTemp31=m_nVehicleTemp32;		
	}//分钟交通量
	if(nPos==1)
			m_pFlowParaStruc->MinuteVehicleNum3=0;
}

void CTransFlowPara::Speed3(int nStart1,int nStart2,float m_fSpace3)
{
	if(m_nVehicleNum32!=m_nVehicleNum31)
		m_nVehicleNum32=m_nVehicleNum31;
	else//检测线1迟于检测线2，而且两线相近不可能有两个车在，故在检测线1计数时调用该函数
	{	//若m_nVehicleNum12!=m_nVehicleNum11说明两检测线上检测的不是同一辆车，排除
		if(nStart1>nStart2)
		{
			m_pFlowParaStruc->Speed3=m_fSpace3*90/(float)(nStart1-nStart2);//即(6/1000)/((0.04*(nStart1-nStart2))/3600)
			m_nSpeedNum3++;
		}
		else
			;
	}	
}

void CTransFlowPara::TimeDensity3(int nPos)
{
	if(nPos==0)
		nPos=1;
	if(nPos==1)
		m_nOccupyFrame3=0;	
	m_pFlowParaStruc->TimeDensity3=(float)m_nOccupyFrame3/(float)nPos;
}

//车道4
TRANSPORTATIONFLOWPARAMETER* CTransFlowPara::FlowCounter4(CDC *pDC,float m_fSpace4,
														  int m_nMaxErrorToler41,int m_nMiniReliability41,int m_nMaxErrorToler42,int m_nMiniReliability42,
														  int nLineSignal1,int nLineSignal2,int nPos,BOOL bIsShowStatLineSignal,BOOL bIsShowSignal)
{
	//车道1上检测线计算开始
	if(nLineSignal2>m_nThresshold2)//线信号是否大于阈值
	{
		if(m_bIsProcess42==FALSE)//判断是否有进程启动，如果没有则启动
			m_bIsProcess42=TRUE;		
		m_nCredible42++;//分配奖赏值给进程
		if(m_nSufferance42>m_nMaxErrorToler42)//处罚值统计大于最大容错度
		{
			if((m_nCredible42+m_nSumSufferance42)>m_nMiniReliability42)//奖赏值大于最小可信度
			{
				m_nVehicleNum42++;				
				nTempHas4=m_nCredible42+m_nSumSufferance42;
				nTempnPos4=nPos-nTempHas4;
				m_bIsProcess42=FALSE;
				m_nCredible42=0;
				m_nSufferance42=0;
				m_nSumSufferance42=0;
			}
			else//奖赏值不大于最小可信度
			{
				m_bIsProcess42=FALSE;
				m_nCredible42=0;
				m_nSufferance42=0;
				m_nSumSufferance42=0;
			}
		}
		else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
		{}
	}
	else//线信号是否不大于阈值
	{
		if(m_bIsProcess42==TRUE)//有跟踪进程启动
		{
			if(m_nSufferance42==0)
			{
				m_nSufferance42++;
				m_nTempSufferancePos42=nPos;
			}
			else
			{
				if((nPos-m_nTempSufferancePos42)==1)
				{
					m_nSufferance42++;
					m_nTempSufferancePos42=nPos;
				}
				else
				{
					m_nSumSufferance42+=m_nSufferance42;
					m_nSufferance42=0;
				}
			}
			
			if(m_nSufferance42>m_nMaxErrorToler42)//处罚值统计大于最大容错度
			{
				if((m_nCredible42+m_nSumSufferance42)>m_nMiniReliability42)//奖赏值大于最小可信度
				{
					m_nVehicleNum42++;
					nTempHas4=m_nCredible42+m_nSumSufferance42;
					nTempnPos4=nPos-nTempHas4;
					m_bIsProcess42=FALSE;
					m_nCredible42=0;
					m_nSufferance42=0;
					m_nSumSufferance42=0;					
				}
				else//奖赏值不大于最小可信度
				{
					m_bIsProcess42=FALSE;
					m_nCredible42=0;
					m_nSufferance42=0;
					m_nSumSufferance42=0;
				}
			}
			else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
			{}
		}
		else//没有跟踪进程启动,什么也不作转入下一帧，继续跟踪
		{}
	}
	//车道1上检测线计算结束

	//车道1下检测线计算开始
	if(nLineSignal1>m_nThresshold1)//线信号是否大于阈值
	{
		if(m_bIsProcess41==FALSE)//判断是否有进程启动，如果没有则启动
			m_bIsProcess41=TRUE;		
		m_nCredible41++;//分配奖赏值给进程
		if(m_nSufferance41>m_nMaxErrorToler41)//处罚值统计大于最大容错度
		{
			if((m_nCredible41+m_nSumSufferance41)>m_nMiniReliability41)//奖赏值大于最小可信度
			{
				m_nVehicleNum41++;
				m_nOccupyFrame4+=m_nCredible41;
				m_nOccupyFrame4+=m_nSumSufferance41;				
				Speed4(nPos-m_nSufferance41-m_nCredible41-m_nSumSufferance41,nTempnPos4,m_fSpace4);
				m_bIsProcess41=FALSE;
				m_nCredible41=0;
				m_nSufferance41=0;
				m_nSumSufferance41=0;				
			}
			else//奖赏值不大于最小可信度
			{
				m_bIsProcess41=FALSE;
				m_nCredible41=0;
				m_nSufferance41=0;
				m_nSumSufferance41=0;
			}
		}
		else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
		{}
	}	
	else//线信号是否不大于阈值
	{
		if(m_bIsProcess41==TRUE)//有跟踪进程启动
		{
			if(m_nSufferance41==0)
			{
				m_nSufferance41++;
				m_nTempSufferancePos41=nPos;
			}
			else
			{
				if((nPos-m_nTempSufferancePos41)==1)
				{
					m_nSufferance41++;
					m_nTempSufferancePos41=nPos;
				}
				else
				{
					m_nSumSufferance41+=m_nSufferance41;
					m_nSufferance41=0;
				}
			}
			
			if(m_nSufferance41>m_nMaxErrorToler41)//处罚值统计大于最大容错度
			{
				if((m_nCredible41+m_nSumSufferance41)>m_nMiniReliability41)//奖赏值大于最小可信度
				{
					m_nVehicleNum41++;
					m_nOccupyFrame4+=m_nCredible41;
					m_nOccupyFrame4+=m_nSumSufferance41;					
					Speed4(nPos-m_nSufferance41-m_nCredible41-m_nSumSufferance41,nTempnPos4,m_fSpace4);
					m_bIsProcess41=FALSE;
					m_nCredible41=0;
					m_nSufferance41=0;
					m_nSumSufferance41=0;
				}
				else//奖赏值不大于最小可信度
				{
					m_bIsProcess41=FALSE;
					m_nCredible41=0;
					m_nSufferance41=0;
					m_nSumSufferance41=0;
				}
			}
			else//处罚值统计不大于最大容错度,什么也不作转入下一帧，继续跟踪
			{}
		}
		else//没有跟踪进程启动,什么也不作转入下一帧，继续跟踪
		{}		
	}
	//车道1下检测线计算结束
	if(nPos==1)
	{
		m_nVehicleNum41=0;
		m_nVehicleNum42=0;
		m_nSpeedNum4=0;
	}

	if(bIsShowStatLineSignal&&bIsShowSignal)
	{
		CString str;
		pDC->TextOut(380,45,"车道4参数:");		
		str.Format("上检测线容忍帧数:%d",m_nSufferance42);
		pDC->TextOut(380,65,str);
		str.Format("上检测线信任帧数:%d",m_nCredible42);
		pDC->TextOut(380,85,str);
		str.Format("下检测线容忍帧数:%d",m_nSufferance41);
		pDC->TextOut(380,105,str);
		str.Format("下检测线信任帧数:%d",m_nCredible41);
		pDC->TextOut(380,125,str);
		str.Format("上检测线车辆数:%d",m_nVehicleNum42);
		pDC->TextOut(380,145,str);
		str.Format("下检测线车辆数:%d",m_nVehicleNum41);
		pDC->TextOut(380,165,str);
		str.Format("测速%d次",m_nSpeedNum4);
		pDC->TextOut(380,225,str);		
	}//调试用
	
	m_pFlowParaStruc->VehicleNumber4=m_nVehicleNum41;//计数

	MinuteVehicleNum4(nPos);//分钟交通量

	if(nPos==1)//速度
		m_pFlowParaStruc->Speed4=0;

	TimeDensity4(nPos);//时间占有率
	

	return m_pFlowParaStruc;
}

void CTransFlowPara::MinuteVehicleNum4(int nPos)
{
	if(nPos%1500==0)
	{
		m_nVehicleTemp42=m_nVehicleNum41;
		m_pFlowParaStruc->MinuteVehicleNum4=abs(m_nVehicleTemp42-m_nVehicleTemp41);					
		m_nVehicleTemp41=m_nVehicleTemp42;		
	}//分钟交通量
	if(nPos==1)
			m_pFlowParaStruc->MinuteVehicleNum3=0;
}

void CTransFlowPara::Speed4(int nStart1,int nStart2,float m_fSpace4)
{
	if(m_nVehicleNum42!=m_nVehicleNum41)
		m_nVehicleNum42=m_nVehicleNum41;
	else//检测线1迟于检测线2，而且两线相近不可能有两个车在，故在检测线1计数时调用该函数
	{	//若m_nVehicleNum12!=m_nVehicleNum11说明两检测线上检测的不是同一辆车，排除
		if(nStart1>nStart2)
		{
			m_pFlowParaStruc->Speed4=m_fSpace4*90/(float)(nStart1-nStart2);//即(6/1000)/((0.04*(nStart1-nStart2))/3600)
			m_nSpeedNum4++;
		}
		else
			;
	}	
}

void CTransFlowPara::TimeDensity4(int nPos)
{
	if(nPos==0)
		nPos=1;
	if(nPos==1)
		m_nOccupyFrame4=0;	
	m_pFlowParaStruc->TimeDensity4=(float)m_nOccupyFrame4/(float)nPos;
}