// AVIProducer.h: interface for the AVIProducer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AVIPRODUCER_H__F3BCAE45_109F_4C36_AA48_922A49B8EE39__INCLUDED_)
#define AFX_AVIPRODUCER_H__F3BCAE45_109F_4C36_AA48_922A49B8EE39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vfw.h"
#pragma comment(lib, "vfw32") 

class AVIProducer  
{
public:
	LPVOID GetCurFrame(int nFlag);
	void ResetFramePos();
	LPVOID GetNextStream(int nFlag);
	CRect m_rectFrame;
	PGETFRAME m_pGetFrame;
	
	PAVISTREAM m_pAVIStream;
	//FX
	PAVIFILE AVIFile;
	PAVISTREAM AVIStream;
	int cx,cy;
	BITMAPINFO* m_pBitMapInfo;
	HANDLE handle;
	BYTE* pData;

    DWORD m_dwRate; 
    DWORD m_dwStart;
	DWORD m_dwLength;
	DWORD  m_dwPos;
	BOOL m_bAttached;
	HRESULT Attach(CString strFileName);
	AVIProducer();
	AVIProducer(CString strFileName);
	virtual ~AVIProducer();
};

#endif // !defined(AFX_AVIPRODUCER_H__F3BCAE45_109F_4C36_AA48_922A49B8EE39__INCLUDED_)
