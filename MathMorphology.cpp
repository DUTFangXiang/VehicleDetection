// MathMorphology.cpp: implementation of the CMathMorphology class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VehicleFlowCounter.h"
#include "MathMorphology.h"
#include "Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMathMorphology::CMathMorphology()
{	
	m_pME=new MORPHOLOGYELEMENT[9];
	m_nElementUsed=9;
}

CMathMorphology::~CMathMorphology()
{

}

void CMathMorphology::Dilate(short *pcxDataSrc, int nWidth, int nHeight,short *pcxDataDst)
//pcxDatasrc 输入的图像指针
//nWith 图像的宽
//nHeight 图像的高 
//pcxDataDst 运算的结果指针
{
	short *pcxDst=pcxDataDst;
	int nRowScan=3*nWidth;
	for(int i=0;i<nHeight;i++)
	{
		for(int j=0;j<nWidth;j++)
		{
			short cxMaxRed,cxMaxGreen,cxMaxBlue;
			cxMaxRed=cxMaxGreen=cxMaxBlue=-32767;
			for(int k=0;k<m_nElementUsed;k++)
			{
				int xr=m_pME[k].x;
				int yr=m_pME[k].y;
				int x=j-xr;
				int y=i-yr;//进行了反转
				
				x=(x<0)?0:((x>(nWidth-1))?(nWidth-1):x);
				y=(y<0)?0:((y>(nHeight-1))?(nHeight-1):y);

				short cxBlue=pcxDataSrc[(y*nRowScan+3*x)];
				short cxGreen=pcxDataSrc[(y*nRowScan+3*x+1)];
				short cxRed=pcxDataSrc[(y*nRowScan+3*x+2)];

				short cxB=cxBlue+m_pME[k].blue;
				short cxG=cxGreen+m_pME[k].green;
				short cxR=cxRed+m_pME[k].red;

				if(cxB>cxMaxBlue) cxMaxBlue=cxB;
				if(cxG>cxMaxGreen) cxMaxGreen=cxG;
				if(cxR>cxMaxRed) cxMaxRed=cxR;
			}//end k
			pcxDataDst[(i*nRowScan+3*j)]=cxMaxBlue;
			pcxDataDst[(i*nRowScan+3*j+1)]=cxMaxGreen;
			pcxDataDst[(i*nRowScan+3*j+2)]=cxMaxRed;
		}//end j
	}//end i
}//根据形态膨胀的定义设计：取结构元素与输入图像相重叠区域之和的最大值，运算结果加强了图像的亮度

BOOL CMathMorphology::Dilate(LPBYTE lpbyBits24,int nWidth,int nHeight)
//lpbyBits24 输入图像的指针
//nWidth nHieght 图像的宽、高
{
	ASSERT(lpbyBits24);
	ASSERT(m_pME);
	int nSize=nWidth*nHeight;

	short* pcxDataSrc=new short[(nSize*3)];
	if(pcxDataSrc==NULL) return FALSE;
	short* pcxDataDst=new short[(nSize*3)];
	if(pcxDataDst==NULL) return FALSE;

	DWORD dwWidthBytes=(DWORD)nWidth*3;
	DWORD dwBaseIndex=0;
	short* pcxDataFore=pcxDataSrc;
	int i,j;
	for(i=0;i<nHeight;i++)
	{
		BYTE* pbySrc=lpbyBits24+dwBaseIndex;
		for(j=0;j<nWidth;j++)
		{
			*pcxDataFore++=*pbySrc++;
			*pcxDataFore++=*pbySrc++;
			*pcxDataFore++=*pbySrc++;
		}//end j
		dwBaseIndex+=dwWidthBytes;
	}//end i
	Dilate(pcxDataSrc,nWidth,nHeight,pcxDataDst);
	pcxDataFore=pcxDataDst;
	dwBaseIndex=0;
	for(i=0;i<nHeight;i++)
	{
		BYTE* pbyDst=lpbyBits24+dwBaseIndex;
		for(j=0;j<nWidth;j++)
		{
			short cxBlue=*pcxDataFore++;
			short cxGreen=*pcxDataFore++;
			short cxRed=*pcxDataFore++;
			
			*pbyDst++=(BYTE)BOUND(cxBlue,0,255);
			*pbyDst++=(BYTE)BOUND(cxGreen,0,255);
			*pbyDst++=(BYTE)BOUND(cxRed,0,255);
		}//end j
		dwBaseIndex+=dwWidthBytes;
	}//end i
	delete[] pcxDataSrc;
	delete[] pcxDataDst;
	return TRUE;
}//反膨胀的结果输入了原来图像，既原来的图像被改变了

void CMathMorphology::Erode(short *pcxDataSrc, int nWidth, int nHeight, short *pcxDataDst)
//参数同Dilate
{
	short* pcxDst=pcxDataDst;
	int nRowScan=3*nWidth;
	for(int i=0;i<nHeight;i++)
	{
		for(int j=0;j<nWidth;j++)
		{
			short cxMinRed,cxMinGreen,cxMinBlue;
			cxMinRed=cxMinGreen=cxMinBlue=32767;
			for(int k=0;k<m_nElementUsed;k++)
			{
				int xr=m_pME[k].x;
				int yr=m_pME[k].y;

				int x=j+xr;
				int y=i+yr;//实现了反转
				
				x=(x<0)?0:((x>(nWidth-1))?(nWidth-1):x);
				y=(y<0)?0:((y>(nHeight-1))?(nHeight-1):y);

				short cxBlue=pcxDataSrc[(y*nRowScan+3*x)];
				short cxGreen=pcxDataSrc[(y*nRowScan+3*x+1)];
				short cxRed=pcxDataSrc[(y*nRowScan+3*x+2)];
				
				short cxB=abs(cxBlue-m_pME[k].blue);
				short cxG=abs(cxGreen-m_pME[k].green);
				short cxR=abs(cxRed-m_pME[k].red);

				if(cxB<cxMinBlue) cxMinBlue=cxB;
				if(cxG<cxMinGreen) cxMinGreen=cxG;
				if(cxR<cxMinRed) cxMinRed=cxR;
			}
			pcxDataDst[(i*nRowScan+3*j)]=cxMinBlue;
			pcxDataDst[(i*nRowScan+3*j+1)]=cxMinGreen;
			pcxDataDst[(i*nRowScan+3*j+2)]=cxMinRed;
		}//end j
	}//end i
}

BOOL CMathMorphology::Erode(LPBYTE lpbyBits24, int nWidth, int nHeight)
{
	ASSERT(lpbyBits24);
	ASSERT(m_pME);
	int nSize=nWidth*nHeight;

	short* pcxDataSrc=new short[(nSize*3)];
	if(pcxDataSrc==NULL) return FALSE;
	short* pcxDataDst=new short[(nSize*3)];
	if(pcxDataDst==NULL) return FALSE;

	DWORD dwWidthBytes=(DWORD)nWidth*3;
	DWORD dwBaseIndex=0;
	short* pcxDataFore=pcxDataSrc;
	int i,j;
	for(i=0;i<nHeight;i++)
	{
		BYTE* pbySrc=lpbyBits24+dwBaseIndex;
		for(j=0;j<nWidth;j++)
		{
			*pcxDataFore++=*pbySrc++;
			*pcxDataFore++=*pbySrc++;
			*pcxDataFore++=*pbySrc++;
		}//end j
		dwBaseIndex+=dwWidthBytes;
	}//end i
	Erode(pcxDataSrc,nWidth,nHeight,pcxDataDst);
	pcxDataFore=pcxDataDst;
	dwBaseIndex=0;
	for(i=0;i<nHeight;i++)
	{
		BYTE* pbyDst=lpbyBits24+dwBaseIndex;
		for(j=0;j<nWidth;j++)
		{
			short cxBlue=*pcxDataFore++;
			short cxGreen=*pcxDataFore++;
			short cxRed=*pcxDataFore++;
			
			*pbyDst++=(BYTE)BOUND(cxBlue,0,255);
			*pbyDst++=(BYTE)BOUND(cxGreen,0,255);
			*pbyDst++=(BYTE)BOUND(cxRed,0,255);
		}//end j
		dwBaseIndex+=dwWidthBytes;
	}//end i
	delete[] pcxDataSrc;
	delete[] pcxDataDst;
	return TRUE;	
}
BOOL CMathMorphology::Denoise(LPBYTE lpbyBits24,int nWidth,int nHeight)
{
	ASSERT(lpbyBits24);
	ASSERT(m_pME);
	int nSize=nWidth*nHeight;

	short* pcxDataSrc=new short[(nSize*3)];
	if(pcxDataSrc==NULL) return FALSE;
	short* pcxDataDst=new short[(nSize*3)];
	if(pcxDataDst==NULL) return FALSE;

	DWORD dwWidthBytes=(DWORD)nWidth*3;
	DWORD dwBaseIndex=0;
	short* pcxDataFore=pcxDataSrc;
	int i,j;
	for(i=0;i<nHeight;i++)
	{
		BYTE* pbySrc=lpbyBits24+dwBaseIndex;
		for(j=0;j<nWidth;j++)
		{
			*pcxDataFore++=*pbySrc++;
			*pcxDataFore++=*pbySrc++;
			*pcxDataFore++=*pbySrc++;
		}//end j
		dwBaseIndex+=dwWidthBytes;
	}//end i
	Erode(pcxDataSrc,nWidth,nHeight,pcxDataDst);
	Erode(pcxDataDst,nWidth,nHeight,pcxDataSrc);
	Erode(pcxDataSrc,nWidth,nHeight,pcxDataDst);
	Dilate(pcxDataDst,nWidth,nHeight,pcxDataSrc);
	pcxDataFore=pcxDataSrc;
	dwBaseIndex=0;
	for(i=0;i<nHeight;i++)
	{
		BYTE* pbyDst=lpbyBits24+dwBaseIndex;
		for(j=0;j<nWidth;j++)
		{
			short cxBlue=*pcxDataFore++;
			short cxGreen=*pcxDataFore++;
			short cxRed=*pcxDataFore++;
			
			*pbyDst++=(BYTE)BOUND(cxBlue,0,255);
			*pbyDst++=(BYTE)BOUND(cxGreen,0,255);
			*pbyDst++=(BYTE)BOUND(cxRed,0,255);
		}//end j
		dwBaseIndex+=dwWidthBytes;
	}//end i
	delete[] pcxDataSrc;
	delete[] pcxDataDst;
	return TRUE;
}
//边缘检测后对结果进行形态学的处理！
void CMathMorphology::Morph(CDC* pDC,LPBYTE lpbyBits24,int nWidth,int nHeight,int m_nRoadWayWidth,int nLineNum,
							int OpraType,BOOL bIsShowLineSignalCurvce,int DrivewayNum)
//其中参数OpraType用来选择形态学处理的类型，若为1则进行除噪操作，若为0进行腐蚀操作
{	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			m_pME[i*3+j].x=j;
			m_pME[i*3+j].y=i;
			m_pME[i*3+j].blue=m_pME[i*3+j].green=m_pME[i*3+j].red=0;
		}
	}//初始化结构单元
	
	if(OpraType==0)	
		Erode(lpbyBits24,nWidth,nHeight);	
	if(OpraType==1)
		Denoise(lpbyBits24,nWidth,nHeight);
	if(bIsShowLineSignalCurvce==TRUE)
	{
		CDib *pDib;
		pDib=new CDib(CSize(nWidth,nHeight),24);
		
		pDib->m_lpImage=lpbyBits24;
	
	//显示检测线2形态处理结果视频
		if(nLineNum==2)
		{
			if(DrivewayNum==1)
				pDib->Draw(pDC,CPoint(550,441),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==2)
				pDib->Draw(pDC,CPoint(555+m_nRoadWayWidth,441),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==3)
				pDib->Draw(pDC,CPoint(560+m_nRoadWayWidth,441),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==4)
				pDib->Draw(pDC,CPoint(565+m_nRoadWayWidth,441),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
		}			
	//显示检测线1形态处理结果视频
		if(nLineNum==1)
		{
			if(DrivewayNum==1)
				pDib->Draw( pDC,CPoint(550,489),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==2)
				pDib->Draw( pDC,CPoint(555+m_nRoadWayWidth,489),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==3)
				pDib->Draw( pDC,CPoint(560+m_nRoadWayWidth,489),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==4)
				pDib->Draw( pDC,CPoint(565+m_nRoadWayWidth,489),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
		}
		
		pDC->TextOut(550,421,"上检测线形态除噪结果:");
	//显示检测线1形态处理标题		
		pDC->TextOut(550,469,"下检测线形态除噪结果:");
		pDib->Empty();
		delete pDib;
	}

}