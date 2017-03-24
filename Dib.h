// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__66B33FF8_E989_43A8_BB2E_81617A49E77D__INCLUDED_)
#define      AFX_DIB_H__66B33FF8_E989_43A8_BB2E_81617A49E77D__INCLUDED_

class CDib : public CObject
{
	enum Alloc {noAlloc, crtAlloc, heapAlloc};
	DECLARE_SERIAL(CDib)
public:
	LPVOID m_lpvColorTable;   //Color table
	HBITMAP m_hBitmap;   
	LPBYTE m_lpImage;  // starting address of DIB bits
	LPBITMAPINFOHEADER m_lpBMIH; //  buffer containing the BITMAPINFOHEADER
	
private:
	HGLOBAL m_hGlobal; // For external windows we need to free;
	                   //  could be allocated by this class or allocated externally
	Alloc m_nBmihAlloc;
	Alloc m_nImageAlloc;
	DWORD m_dwSizeImage; // of bits -- not BITMAPINFOHEADER or BITMAPFILEHEADER
	int m_nColorTableEntries;
	
	HANDLE m_hFile;     //handle of bmp file name
	HANDLE m_hMap;
	LPVOID m_lpvFile;  
	HPALETTE m_hPalette;   //Palette
public:
	CDib();
	CDib(CSize size, int nBitCount);	// builds BITMAPINFOHEADER
	~CDib();
	int GetSizeImage() {return m_dwSizeImage;}     //The size(area) of this image
	int GetSizeHeader()                           //The head of the bmp file (2 parts)
		{return sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;}
	CSize GetDimensions();                       //The size of image(width & height)  
	BOOL AttachMapFile(const char* strPathname, BOOL bShare = FALSE);
	BOOL CopyToMapFile(const char* strPathname);
	BOOL AttachMemory(LPVOID lpvMem, BOOL bMustDelete = FALSE, HGLOBAL hGlobal = NULL);
	BOOL Draw(CDC* pDC, CPoint origin, CSize size,BOOL bIsShowLineSignalCurvce);  // until we implemnt CreateDibSection
	HBITMAP CreateSection(CDC* pDC = NULL);
	UINT UsePalette(CDC* pDC, BOOL bBackground = FALSE);
	BOOL MakePalette();
	BOOL SetSystemPalette(CDC* pDC);
	BOOL Compress(CDC* pDC, BOOL bCompress = TRUE); // FALSE means decompress
	HBITMAP CreateBitmap(CDC* pDC);
	BOOL Read(CFile* pFile);
	BOOL ReadSection(CFile* pFile, CDC* pDC = NULL);
	BOOL Write(CFile* pFile);
	void Serialize(CArchive& ar);
	void Empty();
	BOOL CutDIB(CDC *pDC,LPRECT lpRect);
private:
	void DetachMapFile();
	void ComputePaletteSize(int nBitCount);
	void ComputeMetrics();
};


#endif // !defined(AFX_DIB_H__66B33FF8_E989_43A8_BB2E_81617A49E77D__INCLUDED_)
