// VehicleFlowCounterDoc.h : interface of the CVehicleFlowCounterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VEHICLEFLOWCOUNTERDOC_H__1E444833_FE1B_41D3_832F_B9DEED3368C6__INCLUDED_)
#define AFX_VEHICLEFLOWCOUNTERDOC_H__1E444833_FE1B_41D3_832F_B9DEED3368C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MacDefine.h"

class CVehicleFlowCounterDoc : public CDocument
{
protected: // create from serialization only
	CVehicleFlowCounterDoc();
	DECLARE_DYNCREATE(CVehicleFlowCounterDoc)

// Attributes
public:
	BOOL bOpen;
	TRANSPORTATIONFLOWPARAMETER* m_pFlowParaStruc;
	int m_nHowManyRoadWay;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVehicleFlowCounterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVehicleFlowCounterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVehicleFlowCounterDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEHICLEFLOWCOUNTERDOC_H__1E444833_FE1B_41D3_832F_B9DEED3368C6__INCLUDED_)
