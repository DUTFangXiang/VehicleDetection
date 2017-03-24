// AVIProducer.cpp: implementation of the AVIProducer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VehicleFlowCounter.h"
#include "AVIProducer.h"
//#include "FlowCounter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AVIProducer::AVIProducer()
{
	AVIFileInit();
	m_bAttached=FALSE;
}
//FXע�ͣ�����AVI���ж�Ӧ��ʼ������
AVIProducer::AVIProducer(CString strFileName)
{
	AVIFileInit();
	Attach(strFileName);	
}
AVIProducer::~AVIProducer()
{
	AVIFileExit();
}
/************************************
       FX  AVI�ļ��������Ϣ��ȡ
************************************/
HRESULT AVIProducer::Attach(CString strFileName)
{
	/*HRESULT hr=AVIStreamOpenFromFile(&m_pAVIStream,
		strFileName,0,0,OF_READ,NULL);
	m_pGetFrame=AVIStreamGetFrameOpen(m_pAVIStream,PBITMAPINFOHEADER(AVIGETFRAMEF_BESTDISPLAYFMT));
	if(m_pGetFrame==NULL)
	   return -1; */
	//FXע�ͣ�2016.6.1 �´���
	AVIFileOpen(&AVIFile,strFileName, OF_READ, NULL); 
    int res=AVIFileGetStream(AVIFile, &m_pAVIStream, streamtypeVIDEO, 0);
	if(res !=AVIERR_OK)
	{
	  if(m_pAVIStream!=NULL)
	         AVIStreamRelease(m_pAVIStream);
	  AVIFileExit();
	  return -1;
	}
    AVISTREAMINFO asi; 
	AVIStreamInfo(m_pAVIStream,&asi,sizeof(AVISTREAMINFO));
	AVIFILEINFO FileInfo; 
	AVIFileInfo(AVIFile, &FileInfo, sizeof(AVIFILEINFO));
    int start = AVIStreamStart(m_pAVIStream);

    BITMAPINFOHEADER BIH;
	BIH.biSize   = sizeof(BITMAPINFOHEADER);
	BIH.biWidth  = FileInfo.dwWidth;
	BIH.biHeight = FileInfo.dwHeight;
	BIH.biPlanes = 1;
	BIH.biBitCount = 24;         //λͼ����
	BIH.biCompression = BI_RGB; //ѹ������  BI_RGB=0��ʾ��ѹ��
	BIH.biSizeImage = (((BIH.biWidth*3)+3)&0xFFFC)*BIH.biHeight;
	BIH.biXPelsPerMeter = 0;
	BIH.biYPelsPerMeter = 0;
	BIH.biClrUsed       = 0;
	BIH.biClrImportant  = 0;
	//��AVI��Ƶ����֡
	m_pGetFrame = AVIStreamGetFrameOpen(m_pAVIStream,(LPBITMAPINFOHEADER)&BIH); 
    if(m_pGetFrame==NULL)
	   return -1; 
	m_rectFrame=asi.rcFrame;	
    m_dwRate=asi.dwRate;
    m_dwStart=asi.dwStart;
	m_dwLength=asi.dwLength;
	m_dwPos=m_dwStart;
	m_bAttached=TRUE;

	return S_OK;
}

LPVOID AVIProducer::GetNextStream(int nFlag)
{
	LPVOID	lpImage;
	if((m_dwPos+nFlag)>=m_dwLength-1)		
	{
		if(nFlag>0)
			m_dwPos=m_dwStart;
		else
			m_dwPos=m_dwStart-nFlag;		
	}
	lpImage=AVIStreamGetFrame(m_pGetFrame,(m_dwPos++)+nFlag);	
	return lpImage;
}

void AVIProducer::ResetFramePos()
{
	
}

LPVOID AVIProducer::GetCurFrame(int nFlag)
{
	if((m_dwPos+nFlag)>=m_dwLength-1)		
	{
		if(nFlag>0)
			m_dwPos=m_dwStart;
		else
			m_dwPos=m_dwStart-nFlag;		
	}
	if(nFlag)
		return AVIStreamGetFrame(m_pGetFrame,(m_dwPos+nFlag));
	else
		return AVIStreamGetFrame(m_pGetFrame,m_dwPos);

}
