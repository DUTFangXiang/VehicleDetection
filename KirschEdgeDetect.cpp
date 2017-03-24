// KirschEdgeDetect.cpp: implementation of the CKirschEdgeDetect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VehicleFlowCounter.h"
#include "KirschEdgeDetect.h"
#include "Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKirschEdgeDetect::CKirschEdgeDetect()
{
	pbyResult1=new BYTE[320*20*3];
	pbyResult2=new BYTE[320*20*3];

	m_nHeightPos1=0;
	m_nLeftPos1=0;
	m_nRightPos1=0;
	m_nHeightPos2=0;
	m_nLeftPos2=0;
	m_nRightPos2=0;
	m_nLineHeight=0;
	nWidth=0;
	nWidthBytes=0;
	m_nRoadWayWidth=0;
	m_pMathMorph=new CMathMorphology();
}

CKirschEdgeDetect::~CKirschEdgeDetect()
{
	delete[] pbyResult1;	
	pbyResult1=NULL;
	delete[] pbyResult2;	
	pbyResult2=NULL;

	m_pMathMorph=NULL;
}

PIXELCOLORRGB CKirschEdgeDetect::Kirsch(BYTE *pbyRed,BYTE *pbyGreen,BYTE *pbyBlue)
{
	int nRed[8], nGreen[8], nBlue[8];

	//Ҳ��, ��Щ�����ȷ�ܳ�, �ܶ���, ������ȫ������������ʵ��
	//����, ��Ҫ�ļ����������������
	//��Ȼ��, ��Ч������ߵġ�
	//������˳ʱ����ת��
	//ԭʼKirsch����
	
	//	���0	
	nRed[0] =(5 * ((int)pbyRed[0] + (int)pbyRed[1] + (int)pbyRed[2]) - 
		  3 * ((int)pbyRed[3] + (int)pbyRed[5] + (int)pbyRed[6] +
		  (int)pbyRed[7] + (int)pbyRed[8]));
	nGreen[0] = (5 * ((int)pbyGreen[0] + (int)pbyGreen[1] + (int)pbyGreen[2]) - 
		  3 * ((int)pbyGreen[3] + (int)pbyGreen[5] + (int)pbyGreen[6] +
		  (int)pbyGreen[7] + (int)pbyGreen[8]));
	nBlue[0] = (5 * ((int)pbyBlue[0] + (int)pbyBlue[1] + (int)pbyBlue[2]) - 
		  3 * ((int)pbyBlue[3] + (int)pbyBlue[5] + (int)pbyBlue[6] +
		  (int)pbyBlue[7] + (int)pbyBlue[8]));
	
	//	���1
	nRed[1] = (5 * ((int)pbyRed[1] + (int)pbyRed[2] + (int)pbyRed[5]) - 
		  3 * ((int)pbyRed[0] + (int)pbyRed[3] + (int)pbyRed[6] +
		  (int)pbyRed[7] + (int)pbyRed[8]));
	nGreen[1] = (5 * ((int)pbyGreen[1] + (int)pbyGreen[2] + (int)pbyGreen[5]) - 
		  3 * ((int)pbyGreen[0] + (int)pbyGreen[3] + (int)pbyGreen[6] +
		  (int)pbyGreen[7] + (int)pbyGreen[8]));
	nBlue[1] =(5 * ((int)pbyBlue[1] + (int)pbyBlue[2] + (int)pbyBlue[5]) - 
		  3 * ((int)pbyBlue[0] + (int)pbyBlue[3] + (int)pbyBlue[6] +
		  (int)pbyBlue[7] + (int)pbyBlue[8]));

	//	���2
	nRed[2] = (5 * ((int)pbyRed[2] + (int)pbyRed[5] + (int)pbyRed[8]) - 
		  3 * ((int)pbyRed[0] + (int)pbyRed[3] + (int)pbyRed[6] +
		  (int)pbyRed[7] + (int)pbyRed[1]));
	nGreen[2] = (5 * ((int)pbyGreen[2] + (int)pbyGreen[5] + (int)pbyGreen[8]) - 
		  3 * ((int)pbyGreen[0] + (int)pbyGreen[3] + (int)pbyGreen[6] +
		  (int)pbyGreen[7] + (int)pbyGreen[1]));
	nBlue[2] = (5 * ((int)pbyBlue[2] + (int)pbyBlue[5] + (int)pbyBlue[8]) - 
		  3 * ((int)pbyBlue[0] + (int)pbyBlue[3] + (int)pbyBlue[6] +
		  (int)pbyBlue[7] + (int)pbyBlue[1]));

	//	���3
	nRed[3] = (5 * ((int)pbyRed[7] + (int)pbyRed[5] + (int)pbyRed[8]) - 
		  3 * ((int)pbyRed[0] + (int)pbyRed[3] + (int)pbyRed[6] +
		  (int)pbyRed[2] + (int)pbyRed[1]));
	nGreen[3] = (5 * ((int)pbyGreen[7] + (int)pbyGreen[5] + (int)pbyGreen[8]) - 
		  3 * ((int)pbyGreen[0] + (int)pbyGreen[3] + (int)pbyGreen[6] +
		  (int)pbyGreen[2] + (int)pbyGreen[1]));
	nBlue[3] =(5 * ((int)pbyBlue[7] + (int)pbyBlue[5] + (int)pbyBlue[8]) - 
		  3 * ((int)pbyBlue[0] + (int)pbyBlue[3] + (int)pbyBlue[6] +
		  (int)pbyBlue[2] + (int)pbyBlue[1]));

	//	���4
	nRed[4] = (5 * ((int)pbyRed[7] + (int)pbyRed[6] + (int)pbyRed[8]) - 
		  3 * ((int)pbyRed[0] + (int)pbyRed[3] + (int)pbyRed[5] +
		  (int)pbyRed[2] + (int)pbyRed[1]));
	nGreen[4] = (5 * ((int)pbyGreen[7] + (int)pbyGreen[6] + (int)pbyGreen[8]) - 
		  3 * ((int)pbyGreen[0] + (int)pbyGreen[3] + (int)pbyGreen[5] +
		  (int)pbyGreen[2] + (int)pbyGreen[1]));
	nBlue[4] = (5 * ((int)pbyBlue[7] + (int)pbyBlue[6] + (int)pbyBlue[8]) - 
		  3 * ((int)pbyBlue[0] + (int)pbyBlue[3] + (int)pbyBlue[5] +
		  (int)pbyBlue[2] + (int)pbyBlue[1]));
	
	//	���5
	nRed[5] = (5 * ((int)pbyRed[7] + (int)pbyRed[6] + (int)pbyRed[3]) - 
		  3 * ((int)pbyRed[0] + (int)pbyRed[8] + (int)pbyRed[5] +
		  (int)pbyRed[2] + (int)pbyRed[1]));
	nGreen[5] =(5 * ((int)pbyGreen[7] + (int)pbyGreen[6] + (int)pbyGreen[3]) - 
		  3 * ((int)pbyGreen[0] + (int)pbyGreen[8] + (int)pbyGreen[5] +
		  (int)pbyGreen[2] + (int)pbyGreen[1]));
	nBlue[5] =(5 * ((int)pbyBlue[7] + (int)pbyBlue[6] + (int)pbyBlue[3]) - 
		  3 * ((int)pbyBlue[0] + (int)pbyBlue[8] + (int)pbyBlue[5] +
		  (int)pbyBlue[2] + (int)pbyBlue[1]));
	//	���6
	nRed[6] = (5 * ((int)pbyRed[0] + (int)pbyRed[6] + (int)pbyRed[3]) - 
		  3 * ((int)pbyRed[7] + (int)pbyRed[8] + (int)pbyRed[5] +
		  (int)pbyRed[2] + (int)pbyRed[1]));
	nGreen[6] = (5 * ((int)pbyGreen[0] + (int)pbyGreen[6] + (int)pbyGreen[3]) - 
		  3 * ((int)pbyGreen[7] + (int)pbyGreen[8] + (int)pbyGreen[5] +
		  (int)pbyGreen[2] + (int)pbyGreen[1]));
	nBlue[6] = (5 * ((int)pbyBlue[0] + (int)pbyBlue[6] + (int)pbyBlue[3]) - 
		  3 * ((int)pbyBlue[7] + (int)pbyBlue[8] + (int)pbyBlue[5] +
		  (int)pbyBlue[2] + (int)pbyBlue[1]));

	//	���7
	nRed[7] = (5 * ((int)pbyRed[0] + (int)pbyRed[1] + (int)pbyRed[3]) - 
		  3 * ((int)pbyRed[7] + (int)pbyRed[8] + (int)pbyRed[5] +
		  (int)pbyRed[2] + (int)pbyRed[6]));
	nGreen[7] = (5 * ((int)pbyGreen[0] + (int)pbyGreen[1] + (int)pbyGreen[3]) - 
		  3 * ((int)pbyGreen[7] + (int)pbyGreen[8] + (int)pbyGreen[5] +
		  (int)pbyGreen[2] + (int)pbyGreen[6]));
	nBlue[7] = (5 * ((int)pbyBlue[0] + (int)pbyBlue[1] + (int)pbyBlue[3]) - 
		  3 * ((int)pbyBlue[7] + (int)pbyBlue[8] + (int)pbyBlue[5] +
		  (int)pbyBlue[2] + (int)pbyBlue[6]));

	//�õ�һ��Ԫ�ؼ�¼�����
	for(int i = 1;i < 8;i++)
	{
		if(nRed[i] > nRed[0]) nRed[0] = nRed[i];
		if(nGreen[i] > nGreen[0]) nGreen[0] = nGreen[i];
		if(nBlue[i] > nBlue[0]) nBlue[0] = nBlue[i];
	}


	PIXELCOLORRGB rgb;
	rgb.red = (BYTE)BOUND(nRed[0], 0, 255);
	rgb.green = (BYTE)BOUND(nGreen[0], 0, 255);
	rgb.blue = (BYTE)BOUND(nBlue[0], 0, 255);

	return rgb;
}

PIXELCOLORRGB CKirschEdgeDetect::FilterPixelOnBorder(LPBYTE lpbyBitsSrc24,int x,int y,int nWidth,int nHeight)
{
	int nWidthBytes=nWidth*3;
	BYTE *pbyRed=new BYTE[9];
	BYTE *pbyGreen=new BYTE[9];
	BYTE *pbyBlue=new BYTE[9];

	int xx=x-1;
	int yy=y-1;
	int index=0;

	for(int i=0;i<3;i++)
	{
		int nY=yy+i;
		nY=(nY<0)?0:((nY>(nHeight-1))?(nHeight-1):nY);
		BYTE *pbySrc=lpbyBitsSrc24+nY*nWidthBytes;

		for(int j=0;j<3;j++)
		{
			int nX=xx+j;
			nX=(nX<0)?0:((nX>(nWidth-1))?(nWidth-1):nX);
			BYTE *pbyRaw=pbySrc+3*nX;
			pbyBlue[index]=*pbyRaw++;
			pbyGreen[index]=*pbyRaw++;
			pbyRed[index]=*pbyRaw++;
			index++;
		}
	}
	PIXELCOLORRGB rgb=Kirsch(pbyRed,pbyGreen,pbyBlue);
	delete[] pbyBlue;
	delete[] pbyGreen;
	delete[] pbyRed;
	return rgb;	
}

PIXELCOLORRGB CKirschEdgeDetect::FilterPixelInner(LPBYTE lpbyBitsSrc24,int x,int y,int nWidth,int nHeight)
{
	
	//���ֽ���
	int nWidthBytes = nWidth * 3;

	//�洢һ�����������RGB������
	BYTE* pbyRed = new BYTE[9];
	BYTE* pbyGreen = new BYTE[9];
	BYTE* pbyBlue = new BYTE[9];

	//�����е����Ͻǵ�.
	int xx = x - 1;
	int yy = y - 1;

	//��������pnRed, pnGreen, pnBlue������ֵ
	int index = 0;

	//��Ƕ��ѭ����ȡС��������.
	
	for(int i = 0;i < 3;i++)
	{
		//y����
		int nY = yy + i;

		//ָ��, ָ��������
		BYTE* pbySrc=lpbyBitsSrc24+nY*nWidthBytes+3*xx;

		for(int j = 0;j <3;j++)
		{
			//x����	
			//��¼��ɫ����
			pbyBlue[index] = *pbySrc++; 
			pbyGreen[index] = *pbySrc++;
			pbyRed[index] = *pbySrc++;			
			index++;
		}
	}
	//RGB��ɫ�ṹ, �� MacDefine.H �ж���
	//�������
	PIXELCOLORRGB rgb = Kirsch(pbyRed, pbyGreen, pbyBlue);

	delete[] pbyBlue;
	delete[] pbyGreen;
	delete[] pbyRed;
	return rgb;
}
//��ɱ�Ե��Ⲣ����ͳ���ź���ʾ����ѧ��̬ѧ�ļ���
BYTE* CKirschEdgeDetect::KirschEdgeDet(CDC *pDC,int m_nLeftPos1,int m_nRightPos1,int m_nLineHeight,int nRoadWayWidth,
									   LPBYTE lpbyBits24,int nLineNum,BOOL bIsShowStatLineSignal,int DrivewayNum)
{
	int i,j;
	int nWidth, nHeight,nWidthBytes;
	BYTE *pbyDst;
	BYTE *pbyResult;		
	nWidth=abs(m_nRightPos1-m_nLeftPos1);
	nWidthBytes=nWidth*3;
	nHeight=m_nLineHeight;
	m_nRoadWayWidth=nRoadWayWidth;
	if(nLineNum==1)
	{
		pbyDst=pbyResult=pbyResult1;
	}
	if(nLineNum==2)
	{
		pbyDst=pbyResult=pbyResult2;
	}
		
	//�ϱ߽�
	int nBorderH=1;	
	for(j=0;j<nWidth;j++)
	{
		PIXELCOLORRGB rgb=FilterPixelOnBorder(lpbyBits24,j,0,nWidth,nHeight);
		*pbyDst++=rgb.blue;
		*pbyDst++=rgb.green;
		*pbyDst++=rgb.red;
	}
	//�±߽�
	int nYBottom=nHeight-1;
	pbyDst=pbyResult+nYBottom*nWidthBytes;
	for(j=0;j<nWidth;j++)
	{
		PIXELCOLORRGB rgb=FilterPixelOnBorder(lpbyBits24,j,nYBottom,nWidth,nHeight);
		*pbyDst++=rgb.blue;
		*pbyDst++=rgb.green;
		*pbyDst++=rgb.red;
	}	
	//��߽�
	int nBorderW=1;
	int nRemnantH=(nHeight-nBorderH);
	for(i=nBorderH;i<nRemnantH;i++)
	{
		pbyDst=pbyResult+i*nWidthBytes;
		PIXELCOLORRGB rgb=FilterPixelOnBorder(lpbyBits24,0,i,nWidth,nHeight);
		*pbyDst++=rgb.blue;
		*pbyDst++=rgb.green;
		*pbyDst++=rgb.red;
	}
	//�ұ߽�
	int nXRight=nWidth-nBorderW;
	for(i=nBorderH;i<nRemnantH;i++)
	{
		pbyDst=pbyResult+i*nWidthBytes+3*nXRight;
		PIXELCOLORRGB rgb=FilterPixelOnBorder(lpbyBits24,nXRight,i,nWidth,nHeight);
		*pbyDst++=rgb.blue;
		*pbyDst++=rgb.green;
		*pbyDst++=rgb.red;
	}
	//�м�Ԫ��
	int nInnerW=nWidth-nBorderW;

	for(i=nBorderH;i<nRemnantH;i++)
	{
		pbyDst=pbyResult+i*nWidthBytes;		
		for(j=0;j<nInnerW;j++)
		{
			PIXELCOLORRGB rgb=FilterPixelInner(lpbyBits24,j,i,nWidth,nHeight);
			*pbyDst++=rgb.blue;
			*pbyDst++=rgb.green;
			*pbyDst++=rgb.red;
		}
	}

	pbyResult=DrawEdgeDetectRes(pDC,pbyResult,nWidth,nHeight,nLineNum,bIsShowStatLineSignal,DrivewayNum);
	return pbyResult;
}
//ע������������ֻ���б�Ե���
BYTE* CKirschEdgeDetect::KirschEdgeDet(LPBYTE lpbyBits24,int nLineNum)
{
	int nWidth, nHeight,nWidthBytes;
	BYTE *pbyDst;
	BYTE *pbyResult;
	nWidth=abs(m_nRightPos1-m_nLeftPos1);
	nWidthBytes=nWidth*3;
	pbyDst=pbyResult=pbyResult1;

	nHeight=m_nLineHeight;
	int i,j;
	//�ϱ߽�
	int nBorderH=1;	
	for(j=0;j<nWidth;j++)
	{
		PIXELCOLORRGB rgb=FilterPixelOnBorder(lpbyBits24,j,0,nWidth,nHeight);
		*pbyDst++=rgb.blue;
		*pbyDst++=rgb.green;
		*pbyDst++=rgb.red;
	}
	//�±߽�
	int nYBottom=nHeight-1;
	pbyDst=pbyResult+nYBottom*nWidthBytes;
	for(j=0;j<nWidth;j++)
	{
		PIXELCOLORRGB rgb=FilterPixelOnBorder(lpbyBits24,j,nYBottom,nWidth,nHeight);
		*pbyDst++=rgb.blue;
		*pbyDst++=rgb.green;
		*pbyDst++=rgb.red;
	}	
	//��߽�
	int nBorderW=1;
	int nRemnantH=(nHeight-nBorderH);
	for(i=nBorderH;i<nRemnantH;i++)
	{
		pbyDst=pbyResult+i*nWidthBytes;
		PIXELCOLORRGB rgb=FilterPixelOnBorder(lpbyBits24,0,i,nWidth,nHeight);
		*pbyDst++=rgb.blue;
		*pbyDst++=rgb.green;
		*pbyDst++=rgb.red;
	}
	//�ұ߽�
	int nXRight=nWidth-nBorderW;
	for(i=nBorderH;i<nRemnantH;i++)
	{
		pbyDst=pbyResult+i*nWidthBytes+3*nXRight;
		PIXELCOLORRGB rgb=FilterPixelOnBorder(lpbyBits24,nXRight,i,nWidth,nHeight);
		*pbyDst++=rgb.blue;
		*pbyDst++=rgb.green;
		*pbyDst++=rgb.red;
	}
	//�м�Ԫ��
	int nInnerW=nWidth-nBorderW;

	for(i=nBorderH;i<nRemnantH;i++)
	{
		pbyDst=pbyResult+i*nWidthBytes;		
		for(j=0;j<nInnerW;j++)
		{
			PIXELCOLORRGB rgb=FilterPixelInner(lpbyBits24,j,i,nWidth,nHeight);
			*pbyDst++=rgb.blue;
			*pbyDst++=rgb.green;
			*pbyDst++=rgb.red;
		}
	}

	lpbyBits24=new BYTE[nHeight*nWidth*3];
	for(i=0;i<nHeight;i++)
	{
		for(j=0;j<nWidth;j++)
		{	
			lpbyBits24[i*nWidth*3+j*3+0]=pbyResult[i*nWidth*3+j*3+0];
			lpbyBits24[i*nWidth*3+j*3+1]=pbyResult[i*nWidth*3+j*3+1];
			lpbyBits24[i*nWidth*3+j*3+2]=pbyResult[i*nWidth*3+j*3+2];
		}
	}
	return lpbyBits24;
}

//������ʾ��Ե����������Խ��������̬ѧ����
BYTE* CKirschEdgeDetect::DrawEdgeDetectRes(CDC *pDC,BYTE *pbyResult,int nWidth,int nHeight,int nLineNum,BOOL bIsShowLineSignalCurvce,int DrivewayNum)
{
	CDib *pDib;
	pDib=new CDib(CSize(nWidth,nHeight),24);		
	pDib->m_lpImage=pbyResult;

//��ʾ�����2��Ե�����Ƶ
	if(bIsShowLineSignalCurvce==TRUE)
	{
		if(nLineNum==2)
		{
			if(DrivewayNum==1)
				pDib->Draw(pDC,CPoint(550,337),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==2)
				pDib->Draw(pDC,CPoint(555+m_nRoadWayWidth,337),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==3)
				pDib->Draw(pDC,CPoint(560+m_nRoadWayWidth,337),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==4)
				pDib->Draw(pDC,CPoint(565+m_nRoadWayWidth,337),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);

		}//�������һ������1Ϊȥ�롢0Ϊ����
		//��ʾ�����1��Ե�����Ƶ
		if(nLineNum==1)
		{
			if(DrivewayNum==1)
				pDib->Draw( pDC,CPoint(550,385),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==2)
				pDib->Draw( pDC,CPoint(555+m_nRoadWayWidth,385),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==3)
				pDib->Draw( pDC,CPoint(560+m_nRoadWayWidth,385),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
			if(DrivewayNum==4)
				pDib->Draw( pDC,CPoint(565+m_nRoadWayWidth,385),CSize(nWidth,nHeight),bIsShowLineSignalCurvce);
		}

		//��ʾ�����2��Ե�����Ƶ����		
		pDC->TextOut(550,317,"�ϼ���߱�Ե�����:");
		//��ʾ�����1��Ե������		
		pDC->TextOut(550,365,"�¼���߱�Ե�����:");		
			
	}
	//Morph�����еĵ����ڶ���������������ѧ��̬ѧ��������ͣ�1Ϊ���������0Ϊ�Ÿ�ʴ����
	if(nLineNum==2)
		m_pMathMorph->Morph(pDC,pbyResult,nWidth,nHeight,m_nRoadWayWidth,2,1,bIsShowLineSignalCurvce,DrivewayNum);
	if(nLineNum==1)
		m_pMathMorph->Morph(pDC,pbyResult,nWidth,nHeight,m_nRoadWayWidth,1,1,bIsShowLineSignalCurvce,DrivewayNum);

	pDib->Empty();
	delete pDib;
	return pbyResult;
}

