// VehicleFlowCounterDoc.cpp : implementation of the CVehicleFlowCounterDoc class
//

#include "stdafx.h"
#include "VehicleFlowCounter.h"
#include "VehicleFlowCounterDoc.h"
#include "LineSignal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVehicleFlowCounterDoc

IMPLEMENT_DYNCREATE(CVehicleFlowCounterDoc, CDocument)

BEGIN_MESSAGE_MAP(CVehicleFlowCounterDoc, CDocument)
	//{{AFX_MSG_MAP(CVehicleFlowCounterDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVehicleFlowCounterDoc construction/destruction

CVehicleFlowCounterDoc::CVehicleFlowCounterDoc()
{
	// TODO: add one-time construction code here
	bOpen=FALSE;
	m_pFlowParaStruc=new TRANSPORTATIONFLOWPARAMETER[1];

	m_pFlowParaStruc->VehicleNumber1=0;
	m_pFlowParaStruc->Speed1=0;
	m_pFlowParaStruc->TimeDensity1=0.0;
	m_pFlowParaStruc->MinuteVehicleNum1=0;

	m_pFlowParaStruc->VehicleNumber2=0;
	m_pFlowParaStruc->Speed2=0;
	m_pFlowParaStruc->TimeDensity2=0;
	m_pFlowParaStruc->MinuteVehicleNum2=0;

	m_pFlowParaStruc->VehicleNumber3=0;
	m_pFlowParaStruc->Speed3=0;
	m_pFlowParaStruc->TimeDensity3=0;
	m_pFlowParaStruc->MinuteVehicleNum3=0;
	
	m_pFlowParaStruc->VehicleNumber4=0;
	m_pFlowParaStruc->Speed4=0;
	m_pFlowParaStruc->TimeDensity4=0;
	m_pFlowParaStruc->MinuteVehicleNum4=0;
	
	m_pFlowParaStruc->VehicleNumberSum=0;
	m_pFlowParaStruc->SpeedSum=0;
	m_pFlowParaStruc->TimeDensitySum=0;
	m_pFlowParaStruc->MinuteVehicleNumSum=0;

	m_nHowManyRoadWay=3;
/**/
	
}

CVehicleFlowCounterDoc::~CVehicleFlowCounterDoc()
{
	delete[] m_pFlowParaStruc;
	m_pFlowParaStruc=NULL;

}

BOOL CVehicleFlowCounterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVehicleFlowCounterDoc serialization

void CVehicleFlowCounterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVehicleFlowCounterDoc diagnostics

#ifdef _DEBUG
void CVehicleFlowCounterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVehicleFlowCounterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVehicleFlowCounterDoc commands

