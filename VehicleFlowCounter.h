// VehicleFlowCounter.h : main header file for the VEHICLEFLOWCOUNTER application
//

#if !defined(AFX_VEHICLEFLOWCOUNTER_H__F12D31CE_7F8A_4E58_A3DF_3DC6E27BB86D__INCLUDED_)
#define AFX_VEHICLEFLOWCOUNTER_H__F12D31CE_7F8A_4E58_A3DF_3DC6E27BB86D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVehicleFlowCounterApp:
// See VehicleFlowCounter.cpp for the implementation of this class
//

class CVehicleFlowCounterApp : public CWinApp
{
public:
	CVehicleFlowCounterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVehicleFlowCounterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVehicleFlowCounterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEHICLEFLOWCOUNTER_H__F12D31CE_7F8A_4E58_A3DF_3DC6E27BB86D__INCLUDED_)
