/////////////////////////////////////
/////////////////////////////////////
/*      FX���Լ�¼
1�����ü����
    ��ȣ�          m_nLineHeight��4��20��
	�����Ƶ�ĸ߶ȣ�m_nHeightPos1��30��211-m_nLineHeight��
	�����Ƶ����ࣺm_nLeftPos1��  0��320��
	�����Ƶ���Ҿࣺm_nRightPos1�� 0��320��
*/
/////////////////////////////////////
/////////////////////////////////////
#include "stdafx.h"
#include "VehicleFlowCounter.h"
#include "SetCheckLineDlg.h"
#include "VehicleFlowCounterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetCheckLineDlg dialog
CSetCheckLineDlg::CSetCheckLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetCheckLineDlg::IDD, pParent)
{	
	//{{AFX_DATA_INIT(CSetCheckLineDlg)
	
	//}}AFX_DATA_INIT
}


void CSetCheckLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetCheckLineDlg)
	DDX_Control(pDX, IDC_SLIDER_LINEHEIGHT, m_sliderLineHeight);
	DDX_Control(pDX, IDC_SLIDER_RIGHT, m_sliderRightPos);
	DDX_Control(pDX, IDC_SLIDER_LEFT, m_sliderLeftPos);
	DDX_Control(pDX, IDC_SLIDER_HEIGHT, m_sliderHeightPos);
	DDX_Control(pDX, IDC_COMBO_LINENUM, m_comLineNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetCheckLineDlg, CDialog)
	//{{AFX_MSG_MAP(CSetCheckLineDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_LINENUM, OnSelchangeComboLinenum)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
/************************************
  FX   �����OK�ͱ������ߵ�λ��
	   (д�뵽LinePos.dat�ļ���)
************************************/
void CSetCheckLineDlg::OnOK() 
{
    SaveLinePos();
	CDialog::OnOK();	
}
void CSetCheckLineDlg::SaveLinePos()
{  
	file.Open("LinePos.dat",CFile::modeCreate|CFile::modeWrite,NULL);
	file.Close();	
	if(!file.Open("LinePos.dat", CFile::modeReadWrite | CFile::modeNoTruncate|CFile::typeBinary))
		return;
	file.SeekToEnd();		
/*	m_nHeightPos3=10;//��Щ������Ϊû������LinePos.dat�ļ�
	m_nLeftPos3=0;//ʱ��һ�γ�ʼ����ʱ�ã��ڵ���Ի���ȷ����
	m_nRightPos3=20;//���Ͱ�֮���յ�
	m_nHeightPos4=10;//
	m_nLeftPos4=0;
	m_nRightPos4=20;
    
	m_nHeightPos5=10;//��Щ������Ϊû������LinePos.dat�ļ�
	m_nLeftPos5=180;//ʱ��һ�γ�ʼ����ʱ�ã��ڵ���Ի���ȷ����
	m_nRightPos5=200;//���Ͱ�֮���յ�
	m_nHeightPos6=10;//
	m_nLeftPos6=180;
	m_nRightPos6=200;
   
	m_nHeightPos7=10;//��Щ������Ϊû������LinePos.dat�ļ�
	m_nLeftPos7=200;//ʱ��һ�γ�ʼ����ʱ�ã��ڵ���Ի���ȷ����
	m_nRightPos7=220;//���Ͱ�֮���յ�
	m_nHeightPos8=10;//
	m_nLeftPos8=200;
	m_nRightPos8=220;
   	*/
	file.Write(&m_nHeightPos1,sizeof(int));
	file.Write(&m_nLeftPos1,sizeof(int));
	file.Write(&m_nRightPos1,sizeof(int));
	file.Write(&m_nHeightPos2,sizeof(int));
	file.Write(&m_nLeftPos2,sizeof(int));
	file.Write(&m_nRightPos2,sizeof(int));
	file.Write(&m_nLineHeight,sizeof(int));			
	file.Write(&m_nHeightPos3,sizeof(int));
	file.Write(&m_nLeftPos3,sizeof(int));
	file.Write(&m_nRightPos3,sizeof(int));
	file.Write(&m_nHeightPos4,sizeof(int));
	file.Write(&m_nLeftPos4,sizeof(int));
	file.Write(&m_nRightPos4,sizeof(int));	
	file.Write(&m_nHeightPos5,sizeof(int));
	file.Write(&m_nLeftPos5,sizeof(int));
	file.Write(&m_nRightPos5,sizeof(int));
	file.Write(&m_nHeightPos6,sizeof(int));
	file.Write(&m_nLeftPos6,sizeof(int));
	file.Write(&m_nRightPos6,sizeof(int));	
	file.Write(&m_nHeightPos7,sizeof(int));
	file.Write(&m_nLeftPos7,sizeof(int));
	file.Write(&m_nRightPos7,sizeof(int));
	file.Write(&m_nHeightPos8,sizeof(int));
	file.Write(&m_nLeftPos8,sizeof(int));
	file.Write(&m_nRightPos8,sizeof(int));	
	file.Close();
}

/************************************
 FX  ����߶Ի����ϻ�������ʾ
************************************/
void CSetCheckLineDlg::OnSelchangeComboLinenum() 
{
	//�Ȼ�ö�Ӧ��Ҫ�����ļ���߱�ǩ
	int nLineNum=m_comLineNum.GetCurSel();
	if(nLineNum==0)
	{
		m_sliderLineHeight.SetRange(4,20,TRUE);		
		m_sliderLineHeight.SetPos(m_nLineHeight);
		SetDlgItemInt(IDC_STATIC_WIDTH,m_nLineHeight,FALSE);
	
		m_sliderHeightPos.SetRange(30,211-m_nLineHeight,TRUE);
		m_sliderHeightPos.SetPos(m_nHeightPos1);
		SetDlgItemInt(IDC_STATIC_HEIGHT,m_nHeightPos1,FALSE);

		m_sliderLeftPos.SetRange(0,320,TRUE);//���û��˵ķ�Χ
		m_sliderLeftPos.SetPos(m_nLeftPos1);//���û��˵�λ��
		SetDlgItemInt(IDC_STATIC_LEFT,m_nLeftPos1,FALSE);//��ʾ���õ�λ�ã�FALSEΪ�޷��ţ�TRUEΪ�з�����

		m_sliderRightPos.SetRange(0,320,TRUE);
		m_sliderRightPos.SetPos(m_nRightPos1);
		SetDlgItemInt(IDC_STATIC_RIGHT,m_nRightPos1,FALSE);
	}
	if(nLineNum==1)
	{
		m_sliderLineHeight.SetRange(4,20,TRUE);
		m_sliderLineHeight.SetPos(m_nLineHeight);
		SetDlgItemInt(IDC_STATIC_WIDTH,m_nLineHeight,FALSE);
	
		m_sliderHeightPos.SetRange(30,211-m_nLineHeight,TRUE);
		m_sliderHeightPos.SetPos(m_nHeightPos2);
		SetDlgItemInt(IDC_STATIC_HEIGHT,m_nHeightPos2,FALSE);

		m_sliderLeftPos.SetRange(0,320,TRUE);            //���û��˵ķ�Χ
		m_sliderLeftPos.SetPos(m_nLeftPos2);             //���û��˵�λ��
		SetDlgItemInt(IDC_STATIC_LEFT,m_nLeftPos2,FALSE);//��ʾ���õ�λ�ã�FALSEΪ�޷��ţ�TRUEΪ�з�����

		m_sliderRightPos.SetRange(0,320,TRUE);
		m_sliderRightPos.SetPos(m_nRightPos2);
		SetDlgItemInt(IDC_STATIC_RIGHT,m_nRightPos2,FALSE);
	}
	if(nLineNum==2)
	{
		m_sliderLineHeight.SetRange(4,20,TRUE);		
		m_sliderLineHeight.SetPos(m_nLineHeight);
		SetDlgItemInt(IDC_STATIC_WIDTH,m_nLineHeight,FALSE);
	
		m_sliderHeightPos.SetRange(30,211-m_nLineHeight,TRUE);
		m_sliderHeightPos.SetPos(m_nHeightPos3);
		SetDlgItemInt(IDC_STATIC_HEIGHT,m_nHeightPos3,FALSE);

		m_sliderLeftPos.SetRange(0,320,TRUE);//���û��˵ķ�Χ
		m_sliderLeftPos.SetPos(m_nLeftPos3);//���û��˵�λ��
		SetDlgItemInt(IDC_STATIC_LEFT,m_nLeftPos3,FALSE);//��ʾ���õ�λ�ã�FALSEΪ�޷��ţ�TRUEΪ�з�����

		m_sliderRightPos.SetRange(0,320,TRUE);
		m_sliderRightPos.SetPos(m_nRightPos3);
		SetDlgItemInt(IDC_STATIC_RIGHT,m_nRightPos3,FALSE);
	}
	if(nLineNum==3)
	{
		m_sliderLineHeight.SetRange(4,20,TRUE);		
		m_sliderLineHeight.SetPos(m_nLineHeight);
		SetDlgItemInt(IDC_STATIC_WIDTH,m_nLineHeight,FALSE);
	
		m_sliderHeightPos.SetRange(30,211-m_nLineHeight,TRUE);
		m_sliderHeightPos.SetPos(m_nHeightPos4);
		SetDlgItemInt(IDC_STATIC_HEIGHT,m_nHeightPos4,FALSE);

		m_sliderLeftPos.SetRange(0,320,TRUE);            //���û��˵ķ�Χ
		m_sliderLeftPos.SetPos(m_nLeftPos4);             //���û��˵�λ��
		SetDlgItemInt(IDC_STATIC_LEFT,m_nLeftPos4,FALSE);//��ʾ���õ�λ�ã�FALSEΪ�޷��ţ�TRUEΪ�з�����

		m_sliderRightPos.SetRange(0,320,TRUE);
		m_sliderRightPos.SetPos(m_nRightPos4);
		SetDlgItemInt(IDC_STATIC_RIGHT,m_nRightPos4,FALSE);
	}
	if(nLineNum==4)
	{
		m_sliderLineHeight.SetRange(4,20,TRUE);		
		m_sliderLineHeight.SetPos(m_nLineHeight);
		SetDlgItemInt(IDC_STATIC_WIDTH,m_nLineHeight,FALSE);
	
		m_sliderHeightPos.SetRange(30,211-m_nLineHeight,TRUE);
		m_sliderHeightPos.SetPos(m_nHeightPos5);
		SetDlgItemInt(IDC_STATIC_HEIGHT,m_nHeightPos5,FALSE);

		m_sliderLeftPos.SetRange(0,320,TRUE);            //���û��˵ķ�Χ
		m_sliderLeftPos.SetPos(m_nLeftPos5);             //���û��˵�λ��
		SetDlgItemInt(IDC_STATIC_LEFT,m_nLeftPos5,FALSE);//��ʾ���õ�λ�ã�FALSEΪ�޷��ţ�TRUEΪ�з�����

		m_sliderRightPos.SetRange(0,320,TRUE);
		m_sliderRightPos.SetPos(m_nRightPos5);
		SetDlgItemInt(IDC_STATIC_RIGHT,m_nRightPos5,FALSE);
	}
	if(nLineNum==5)
	{
		m_sliderLineHeight.SetRange(4,20,TRUE);		
		m_sliderLineHeight.SetPos(m_nLineHeight);
		SetDlgItemInt(IDC_STATIC_WIDTH,m_nLineHeight,FALSE);
	
		m_sliderHeightPos.SetRange(30,211-m_nLineHeight,TRUE);
		m_sliderHeightPos.SetPos(m_nHeightPos6);
		SetDlgItemInt(IDC_STATIC_HEIGHT,m_nHeightPos6,FALSE);

		m_sliderLeftPos.SetRange(0,320,TRUE);//���û��˵ķ�Χ
		m_sliderLeftPos.SetPos(m_nLeftPos6);//���û��˵�λ��
		SetDlgItemInt(IDC_STATIC_LEFT,m_nLeftPos6,FALSE);//��ʾ���õ�λ�ã�FALSEΪ�޷��ţ�TRUEΪ�з�����

		m_sliderRightPos.SetRange(0,320,TRUE);
		m_sliderRightPos.SetPos(m_nRightPos6);
		SetDlgItemInt(IDC_STATIC_RIGHT,m_nRightPos6,FALSE);
	}
	if(nLineNum==6)
	{
		m_sliderLineHeight.SetRange(4,20,TRUE);		
		m_sliderLineHeight.SetPos(m_nLineHeight);
		SetDlgItemInt(IDC_STATIC_WIDTH,m_nLineHeight,FALSE);
	
		m_sliderHeightPos.SetRange(30,211-m_nLineHeight,TRUE);
		m_sliderHeightPos.SetPos(m_nHeightPos7);
		SetDlgItemInt(IDC_STATIC_HEIGHT,m_nHeightPos7,FALSE);

		m_sliderLeftPos.SetRange(0,320,TRUE);//���û��˵ķ�Χ
		m_sliderLeftPos.SetPos(m_nLeftPos7);//���û��˵�λ��
		SetDlgItemInt(IDC_STATIC_LEFT,m_nLeftPos7,FALSE);//��ʾ���õ�λ�ã�FALSEΪ�޷��ţ�TRUEΪ�з�����

		m_sliderRightPos.SetRange(0,320,TRUE);
		m_sliderRightPos.SetPos(m_nRightPos7);
		SetDlgItemInt(IDC_STATIC_RIGHT,m_nRightPos7,FALSE);
	}
	if(nLineNum==7)
	{
		m_sliderLineHeight.SetRange(4,20,TRUE);		
		m_sliderLineHeight.SetPos(m_nLineHeight);
		SetDlgItemInt(IDC_STATIC_WIDTH,m_nLineHeight,FALSE);
	
		m_sliderHeightPos.SetRange(30,211-m_nLineHeight,TRUE);
		m_sliderHeightPos.SetPos(m_nHeightPos8);
		SetDlgItemInt(IDC_STATIC_HEIGHT,m_nHeightPos8,FALSE);

		m_sliderLeftPos.SetRange(0,320,TRUE);//���û��˵ķ�Χ
		m_sliderLeftPos.SetPos(m_nLeftPos8);//���û��˵�λ��
		SetDlgItemInt(IDC_STATIC_LEFT,m_nLeftPos8,FALSE);//��ʾ���õ�λ�ã�FALSEΪ�޷��ţ�TRUEΪ�з�����

		m_sliderRightPos.SetRange(0,320,TRUE);
		m_sliderRightPos.SetPos(m_nRightPos8);
		SetDlgItemInt(IDC_STATIC_RIGHT,m_nRightPos8,FALSE);
	}
}
/************************************
    FX    ���򿪼�������ý���
��ʼ����LinePos.Dat�ļ��ж�ȡ�������
************************************/
BOOL CSetCheckLineDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	OpenDetectLineFile();
	//�����1	
	m_comLineNum.SetCurSel(0);
	m_sliderLineHeight.SetRange(4,20,TRUE);
	m_sliderLineHeight.SetPos(m_nLineHeight);
	SetDlgItemInt(IDC_STATIC_WIDTH,m_nLineHeight,FALSE);
	
	m_sliderHeightPos.SetRange(30,211-m_nLineHeight,TRUE);
	m_sliderHeightPos.SetPos(m_nHeightPos1);
	SetDlgItemInt(IDC_STATIC_HEIGHT,m_nHeightPos1,FALSE);

	m_sliderLeftPos.SetRange(0,320,TRUE);              //���û��˵ķ�Χ
	m_sliderLeftPos.SetPos(m_nLeftPos1);               //���û��˵�λ��
	SetDlgItemInt(IDC_STATIC_LEFT,m_nLeftPos1,FALSE);  //��ʾ���õ�λ�ã�FALSEΪ�޷��ţ�TRUEΪ�з�����

	m_sliderRightPos.SetRange(0,320,TRUE);
	m_sliderRightPos.SetPos(m_nRightPos1);
	SetDlgItemInt(IDC_STATIC_RIGHT,m_nRightPos1,FALSE);
	
	return TRUE; 
}
/************************************
    FX     ��ʼ������ߵ�λ��
(��LinePos.Dat�ļ��ж�ȡ�����������
 �ϴ����ý�� )
************************************/
void CSetCheckLineDlg::OpenDetectLineFile()
{
	CFile file;
	if(!file.Open("LinePos.Dat",CFile::modeRead,NULL))	return;
	file.Read(&m_nHeightPos1,sizeof(int));
	file.Read(&m_nLeftPos1,sizeof(int));
	file.Read(&m_nRightPos1,sizeof(int));
	file.Read(&m_nHeightPos2,sizeof(int));
	file.Read(&m_nLeftPos2,sizeof(int));
	file.Read(&m_nRightPos2,sizeof(int));
	file.Read(&m_nLineHeight,sizeof(int));
	file.Read(&m_nHeightPos3,sizeof(int));
	file.Read(&m_nLeftPos3,sizeof(int));
	file.Read(&m_nRightPos3,sizeof(int));
	file.Read(&m_nHeightPos4,sizeof(int));
	file.Read(&m_nLeftPos4,sizeof(int));
	file.Read(&m_nRightPos4,sizeof(int));
	file.Read(&m_nHeightPos5,sizeof(int));
	file.Read(&m_nLeftPos5,sizeof(int));
	file.Read(&m_nRightPos5,sizeof(int));
	file.Read(&m_nHeightPos6,sizeof(int));
	file.Read(&m_nLeftPos6,sizeof(int));
	file.Read(&m_nRightPos6,sizeof(int));
	file.Read(&m_nHeightPos7,sizeof(int));
	file.Read(&m_nLeftPos7,sizeof(int));
	file.Read(&m_nRightPos7,sizeof(int));
	file.Read(&m_nHeightPos8,sizeof(int));
	file.Read(&m_nLeftPos8,sizeof(int));
	file.Read(&m_nRightPos8,sizeof(int));
	file.Close();
}

/************************************
    FX   ���»��˱仯���λ�ã�
	     ��ʾ�µ�λ�ý��
************************************/
void CSetCheckLineDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CString strText;
	int nLineNum=m_comLineNum.GetCurSel();   //��ȡ��ǰѡ�����
//����߿���������ͳһ������
	if(pScrollBar->m_hWnd==m_sliderLineHeight.m_hWnd)
	{		
		m_nLineHeight=m_sliderLineHeight.GetPos();
		strText.Format("%3d",m_nLineHeight);		
		SetDlgItemText(IDC_STATIC_WIDTH,strText);	
	}
//��1
	if(nLineNum==0)
	{   //��1���±���ʼ�߶�
		if(pScrollBar->m_hWnd==m_sliderHeightPos.m_hWnd)
		{
			m_nHeightPos1=m_sliderHeightPos.GetPos();			
			strText.Format("%3d",m_nHeightPos1);
			SetDlgItemText(IDC_STATIC_HEIGHT,strText);		
		}
	    //��1��������
		if(pScrollBar->m_hWnd==m_sliderLeftPos.m_hWnd)
		{
			m_nLeftPos1=m_sliderLeftPos.GetPos();
			while((m_nRightPos1-m_nLeftPos1)%4!=0)
			{
				m_nRightPos1--;				

			}//Ҫ���ߵĿ��Ϊ4��������
			strText.Format("%3d",m_nLeftPos1);
			SetDlgItemText(IDC_STATIC_LEFT,strText);		
		}
	    //��1���ұ��յ�
		if(pScrollBar->m_hWnd==m_sliderRightPos.m_hWnd)
		{
			m_nRightPos1=m_sliderRightPos.GetPos();
			while((m_nRightPos1-m_nLeftPos1)%4!=0)
			{
				m_nRightPos1--;
				
			}//Ҫ���ߵĿ��Ϊ4��������
			strText.Format("%3d",m_nRightPos1);
			SetDlgItemText(IDC_STATIC_RIGHT,strText);	
		}		
	}
//��2	
	if(nLineNum==1)
	{
		if(pScrollBar->m_hWnd==m_sliderHeightPos.m_hWnd)
		{
			m_nHeightPos2=m_sliderHeightPos.GetPos();
			strText.Format("%3d",m_nHeightPos2);
			SetDlgItemText(IDC_STATIC_HEIGHT,strText);		
		}

		if(pScrollBar->m_hWnd==m_sliderLeftPos.m_hWnd)
		{
			m_nLeftPos2=m_sliderLeftPos.GetPos();
			while((m_nRightPos2-m_nLeftPos2)%4!=0)
			{
				m_nRightPos2--;				

			}
			strText.Format("%3d",m_nLeftPos2);
			SetDlgItemText(IDC_STATIC_LEFT,strText);		
		}

		if(pScrollBar->m_hWnd==m_sliderRightPos.m_hWnd)
		{
			m_nRightPos2=m_sliderRightPos.GetPos();
			while((m_nRightPos2-m_nLeftPos2)%4!=0)
			{
				m_nRightPos2--;				
			}
			strText.Format("%3d",m_nRightPos2);
			SetDlgItemText(IDC_STATIC_RIGHT,strText);		
		}
	}
	if(nLineNum==2)
	{
		if(pScrollBar->m_hWnd==m_sliderHeightPos.m_hWnd)
		{
			m_nHeightPos3=m_sliderHeightPos.GetPos();			
			strText.Format("%3d",m_nHeightPos3);
			SetDlgItemText(IDC_STATIC_HEIGHT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderLeftPos.m_hWnd)
		{
			m_nLeftPos3=m_sliderLeftPos.GetPos();
			while((m_nRightPos3-m_nLeftPos3)%4!=0)
			{
				m_nRightPos3--;				
			}
			strText.Format("%3d",m_nLeftPos3);
			SetDlgItemText(IDC_STATIC_LEFT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderRightPos.m_hWnd)
		{
			m_nRightPos3=m_sliderRightPos.GetPos();
			while((m_nRightPos3-m_nLeftPos3)%4!=0)
			{
				m_nRightPos3--;				
			}
			strText.Format("%3d",m_nRightPos3);
			SetDlgItemText(IDC_STATIC_RIGHT,strText);	
		}		
	}
	if(nLineNum==3)
	{
		if(pScrollBar->m_hWnd==m_sliderHeightPos.m_hWnd)
		{
			m_nHeightPos4=m_sliderHeightPos.GetPos();			
			strText.Format("%3d",m_nHeightPos4);
			SetDlgItemText(IDC_STATIC_HEIGHT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderLeftPos.m_hWnd)
		{
			m_nLeftPos4=m_sliderLeftPos.GetPos();
			while((m_nRightPos4-m_nLeftPos4)%4!=0)
			{
				m_nRightPos4--;				
			}
			strText.Format("%3d",m_nLeftPos4);
			SetDlgItemText(IDC_STATIC_LEFT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderRightPos.m_hWnd)
		{
			m_nRightPos4=m_sliderRightPos.GetPos();
			while((m_nRightPos4-m_nLeftPos4)%4!=0)
			{
				m_nRightPos4--;				
			}
			strText.Format("%3d",m_nRightPos4);
			SetDlgItemText(IDC_STATIC_RIGHT,strText);	
		}		
	}
	if(nLineNum==4)
	{
		if(pScrollBar->m_hWnd==m_sliderHeightPos.m_hWnd)
		{
			m_nHeightPos5=m_sliderHeightPos.GetPos();			
			strText.Format("%3d",m_nHeightPos5);
			SetDlgItemText(IDC_STATIC_HEIGHT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderLeftPos.m_hWnd)
		{
			m_nLeftPos5=m_sliderLeftPos.GetPos();
			while((m_nRightPos5-m_nLeftPos5)%4!=0)
			{
				m_nRightPos5--;				
			}
			strText.Format("%3d",m_nLeftPos5);
			SetDlgItemText(IDC_STATIC_LEFT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderRightPos.m_hWnd)
		{
			m_nRightPos5=m_sliderRightPos.GetPos();
			while((m_nRightPos5-m_nLeftPos5)%4!=0)
			{
				m_nRightPos5--;				
			}
			strText.Format("%3d",m_nRightPos5);
			SetDlgItemText(IDC_STATIC_RIGHT,strText);	
		}		
	}
	if(nLineNum==5)
	{
		if(pScrollBar->m_hWnd==m_sliderHeightPos.m_hWnd)
		{
			m_nHeightPos6=m_sliderHeightPos.GetPos();			
			strText.Format("%3d",m_nHeightPos6);
			SetDlgItemText(IDC_STATIC_HEIGHT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderLeftPos.m_hWnd)
		{
			m_nLeftPos6=m_sliderLeftPos.GetPos();
			while((m_nRightPos6-m_nLeftPos6)%4!=0)
			{
				m_nRightPos6--;				
			}
			strText.Format("%3d",m_nLeftPos6);
			SetDlgItemText(IDC_STATIC_LEFT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderRightPos.m_hWnd)
		{
			m_nRightPos6=m_sliderRightPos.GetPos();
			while((m_nRightPos6-m_nLeftPos6)%4!=0)
			{
				m_nRightPos6--;				
			}
			strText.Format("%3d",m_nRightPos6);
			SetDlgItemText(IDC_STATIC_RIGHT,strText);	
		}		
	}
	if(nLineNum==6)
	{
		if(pScrollBar->m_hWnd==m_sliderHeightPos.m_hWnd)
		{
			m_nHeightPos7=m_sliderHeightPos.GetPos();			
			strText.Format("%3d",m_nHeightPos7);
			SetDlgItemText(IDC_STATIC_HEIGHT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderLeftPos.m_hWnd)
		{
			m_nLeftPos7=m_sliderLeftPos.GetPos();
			while((m_nRightPos7-m_nLeftPos7)%4!=0)
			{
				m_nRightPos7--;				
			}
			strText.Format("%3d",m_nLeftPos7);
			SetDlgItemText(IDC_STATIC_LEFT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderRightPos.m_hWnd)
		{
			m_nRightPos7=m_sliderRightPos.GetPos();
			while((m_nRightPos7-m_nLeftPos7)%4!=0)
			{
				m_nRightPos7--;				
			}
			strText.Format("%3d",m_nRightPos7);
			SetDlgItemText(IDC_STATIC_RIGHT,strText);	
		}		
	}
	if(nLineNum==7)
	{
		if(pScrollBar->m_hWnd==m_sliderHeightPos.m_hWnd)
		{
			m_nHeightPos8=m_sliderHeightPos.GetPos();			
			strText.Format("%3d",m_nHeightPos8);
			SetDlgItemText(IDC_STATIC_HEIGHT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderLeftPos.m_hWnd)
		{
			m_nLeftPos8=m_sliderLeftPos.GetPos();
			while((m_nRightPos8-m_nLeftPos8)%4!=0)
			{
				m_nRightPos8--;				
			}
			strText.Format("%3d",m_nLeftPos8);
			SetDlgItemText(IDC_STATIC_LEFT,strText);		
		}
		if(pScrollBar->m_hWnd==m_sliderRightPos.m_hWnd)
		{
			m_nRightPos8=m_sliderRightPos.GetPos();
			while((m_nRightPos8-m_nLeftPos8)%4!=0)
			{
				m_nRightPos8--;				
			}
			strText.Format("%3d",m_nRightPos8);
			SetDlgItemText(IDC_STATIC_RIGHT,strText);	
		}		
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
