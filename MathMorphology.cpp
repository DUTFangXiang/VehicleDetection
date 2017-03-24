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
//pcxDatasrc �����ͼ��ָ��
//nWith ͼ��Ŀ�
//nHeight ͼ��ĸ� 
//pcxDataDst ����Ľ��ָ��
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
				int y=i-yr;//�����˷�ת
				
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
}//������̬���͵Ķ�����ƣ�ȡ�ṹԪ��������ͼ�����ص�����֮�͵����ֵ����������ǿ��ͼ�������

BOOL CMathMorphology::Dilate(LPBYTE lpbyBits24,int nWidth,int nHeight)
//lpbyBits24 ����ͼ���ָ��
//nWidth nHieght ͼ��Ŀ���
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
}//�����͵Ľ��������ԭ��ͼ�񣬼�ԭ����ͼ�񱻸ı���

void CMathMorphology::Erode(short *pcxDataSrc, int nWidth, int nHeight, short *pcxDataDst)
//����ͬDilate
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
				int y=i+yr;//ʵ���˷�ת
				
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
//��Ե����Խ��������̬ѧ�Ĵ���
void CMathMorphology::Morph(CDC* pDC,LPBYTE lpbyBits24,int nWidth,int nHeight,int m_nRoadWayWidth,int nLineNum,
							int OpraType,BOOL bIsShowLineSignalCurvce,int DrivewayNum)
//���в���OpraType����ѡ����̬ѧ��������ͣ���Ϊ1����г����������Ϊ0���и�ʴ����
{	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			m_pME[i*3+j].x=j;
			m_pME[i*3+j].y=i;
			m_pME[i*3+j].blue=m_pME[i*3+j].green=m_pME[i*3+j].red=0;
		}
	}//��ʼ���ṹ��Ԫ
	
	if(OpraType==0)	
		Erode(lpbyBits24,nWidth,nHeight);	
	if(OpraType==1)
		Denoise(lpbyBits24,nWidth,nHeight);
	if(bIsShowLineSignalCurvce==TRUE)
	{
		CDib *pDib;
		pDib=new CDib(CSize(nWidth,nHeight),24);
		
		pDib->m_lpImage=lpbyBits24;
	
	//��ʾ�����2��̬��������Ƶ
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
	//��ʾ�����1��̬��������Ƶ
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
		
		pDC->TextOut(550,421,"�ϼ������̬������:");
	//��ʾ�����1��̬�������		
		pDC->TextOut(550,469,"�¼������̬������:");
		pDib->Empty();
		delete pDib;
	}

}