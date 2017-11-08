// AutoClickDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoClick.h"
#include "AutoClickDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoClickDlg �Ի���
int m_data1;//������|��
int m_data2;//���浥|˫
int m_nTimeData;// ���ʱ��


IMPLEMENT_DYNCREATE(CAutoClickDlg,CDialog)
CAutoClickDlg::CAutoClickDlg(CWnd* pParent /*=NULL*/): CDialog(CAutoClickDlg::IDD, pParent) , m_bThread(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoClickDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DIRECTION, m_wndDirection);
    DDX_Control(pDX, IDC_WAY, m_wndWay);
    DDX_Text(pDX, IDC_TIME, m_nTimeData);
    DDX_Control(pDX, IDC_ENDHOTKEY, m_wndHotKeyEnd);
    DDX_Control(pDX, IDC_START, m_wndHotKeyStart);

    DDX_Control(pDX, IDC_TIME, m_wndTimeEdit);
}

BEGIN_MESSAGE_MAP(CAutoClickDlg, CDialog)
    //ON_COMMAND(0xFFF1,CAutoClickDlg::MyTest)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
   ON_WM_CLOSE()
   ON_BN_CLICKED(IDC_SET1, &CAutoClickDlg::OnBnClickedSet1)
   ON_BN_CLICKED(IDC_BUTTON2, &CAutoClickDlg::OnBnClickedButton2)
  
   ON_CBN_EDITUPDATE(IDC_WAY, &CAutoClickDlg::OnCbnEditupdateWay)
   ON_CBN_EDITUPDATE(IDC_DIRECTION, &CAutoClickDlg::OnCbnEditupdateDirection)
   ON_EN_UPDATE(IDC_TIME, &CAutoClickDlg::OnEnUpdateTime)
   ON_CBN_SELCHANGE(IDC_WAY, &CAutoClickDlg::OnCbnSelchangeWay)
   ON_CBN_SELCHANGE(IDC_DIRECTION, &CAutoClickDlg::OnCbnSelchangeDirection)
END_MESSAGE_MAP()


// CAutoClickDlg ��Ϣ�������

BOOL CAutoClickDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��



    //��ȡ����ĵ�ǰĿ¼
    
    WCHAR szCurrent[MAX_PATH] = { 0 };
    GetCurrentDirectory( MAX_PATH, szCurrent);
    strPath.Format(_T("%s\\AutoClick.ini"),szCurrent);
    
   

    int nDirection;//��|��
    int Way;//��|˫
    int nNtart;//��ʼ
    int nEnd;//����
    int nTime;
    nDirection = GetPrivateProfileInt(_T("Config"),_T("Direction"),0,strPath);//��ȡ����
    Way = GetPrivateProfileInt(_T("Config"),_T("Way"),0,strPath);//��ȡ����
    nNtart = GetPrivateProfileInt(_T("Config"),_T("Ntart"),VK_F10,strPath);
    nEnd = GetPrivateProfileInt(_T("Config"),_T("End"),VK_F11,strPath);
    nTime = GetPrivateProfileInt(_T("Config"),_T("Time"),1000,strPath);
    int nNtart2;//��ʼ
    int nEnd2;//����
    nNtart2 = GetPrivateProfileInt(_T("Config"),_T("nNtart2"),0,strPath);
    nEnd2 = GetPrivateProfileInt(_T("Config"),_T("nEnd2"),0,strPath);

    //���ÿ�ʼĬ��ѡ��
    m_wndHotKeyStart.SetHotKey(nNtart,nNtart2);
    //���ý���Ĭ��ѡ��
    m_wndHotKeyEnd.SetHotKey(nEnd,nEnd2);
    //������|��Ĭ��ѡ��
    m_wndDirection.SetCurSel(nDirection);
    //���õ�|˫Ĭ��ѡ��
    m_wndWay.SetCurSel(Way);
    //��ʼ��ʱ��
    m_nTimeData = nTime;
    UpdateData(FALSE);
  
    
    
    if(RegisterHotKey(this->GetSafeHwnd(),4001,nNtart2,nNtart)==0)//���ھ��|��ϢID|������ʶ|����
    {
        AfxMessageBox(_T("��ʼ��ݼ�ע��ʧ��"));
    }

    if(RegisterHotKey(this->GetSafeHwnd(),4002,nEnd2,nEnd)==0)//���ھ��|��ϢID|������ʶ|����
    {
        AfxMessageBox(_T("������ݼ�ע��ʧ��"));
    }
    m_data1 = m_wndDirection.GetCurSel();//������|��
    m_data2 = m_wndWay.GetCurSel();//���浥|˫
    
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAutoClickDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CAutoClickDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAutoClickDlg::OnClose()
{
    UnregisterHotKey(this->GetSafeHwnd(),4001);//ж�ؿ�ʼ
    UnregisterHotKey(this->GetSafeHwnd(),4002);//ж�ؽ���
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    
    CDialog::OnClose();
}
void CAutoClickDlg::MyTest()
{
    AfxMessageBox(_T(""));

}

BOOL CAutoClickDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: �ڴ����ר�ô����/����û���
    if(pMsg->message==WM_HOTKEY)
    {
        //AfxMessageBox(_T(""));
        if (pMsg->wParam==4001)//��ʼ
        {
            //CAutoClickDlg Dlg = AfxBeginThread(TimeThread,this);
            //AfxMessageBox(_T("��ʼ"));
            if (m_bThread==TRUE)
            {
                m_bThread = FALSE;
                m_wndTimeEdit.EnableWindow(m_bThread);
                Main = CreateThread(NULL,0,::ThreadProc,NULL,0,&nThreadID);//����һ������ִ�е��߳�
                
            }
            
            return TRUE;
        }

        if(pMsg->wParam==4002)//����
        {
            //AfxMessageBox(_T("����"));
            if (m_bThread == FALSE)
            {
                m_bThread = TRUE;
                m_wndTimeEdit.EnableWindow(m_bThread);
//                CloseHandle(&Main);//�����߳�
                TerminateThread(Main,0);
                
            }
            
            return TRUE;
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}
UINT CAutoClickDlg::TimeThread(LPVOID pVoid)
{
    CAutoClickDlg* pThis = (CAutoClickDlg*)pVoid;
    UpdateData();//ÿ���߳���������ˢ�±�������
    while (1)//����ѭ��
    {
        

        AfxMessageBox(_T(""));
        
        
    }
}


void CAutoClickDlg::OnBnClickedSet1()//��ʼ�ȼ�����
{
    UnregisterHotKey(this->GetSafeHwnd(),4001);//ж�ؾ��ȼ�
    
    WORD vir,mod;
    m_wndHotKeyStart.GetHotKey(vir,mod);//��ȡ����|������ʶ
    if(RegisterHotKey(this->GetSafeHwnd(),4001,mod,vir)==0)//���ھ��|��ϢID|����|������ʶ
    {
        AfxMessageBox(_T("��ʼ��ݼ�ע��ʧ��"));
    }else
    {
        CString str,str2;
        str.Format(_T("%d"),vir);
        str2.Format(_T("%d"),mod);
        ::WritePrivateProfileString(_T("Config"),_T("Ntart"),str,strPath);//д�����
        ::WritePrivateProfileString(_T("Config"),_T("nNtart2"),str2,strPath);//д�����
    }
}

void CAutoClickDlg::OnBnClickedButton2()//ֹͣ�ȼ�����
{
    UnregisterHotKey(this->GetSafeHwnd(),4002);//ж�ؾ��ȼ�

    WORD vir,mod;
    m_wndHotKeyEnd.GetHotKey(vir,mod);//��ȡ����|������ʶ
    if(RegisterHotKey(this->GetSafeHwnd(),4002,mod,vir)==0)//���ھ��|��ϢID|����|������ʶ
    {
        AfxMessageBox(_T("������ݼ�ע��ʧ��"));
    }else
    {
        CString str,str2;
        str.Format(_T("%d"),vir);
        str2.Format(_T("%d"),mod);
        ::WritePrivateProfileString(_T("Config"),_T("End"),str,strPath);//д�����
        ::WritePrivateProfileString(_T("Config"),_T("nEnd2"),str2,strPath);//д�����
    }
    // TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CAutoClickDlg::OnCbnEditupdateDirection()//��|�����������ݸı�
{



}

void CAutoClickDlg::OnCbnEditupdateWay()//��|˫���������ݸı�
{

}

DWORD WINAPI ThreadProc(LPVOID lpParameter )
{
    while(1)
    {
        if(m_data1)
        {//�һ�
            if(m_data2)
            {//����
                mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);//�����Ҽ�
                mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);//�ɿ��Ҽ�
            }else
            {//˫��
                mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);//�����Ҽ�
                mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);//�ɿ��Ҽ�
                mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);//�����Ҽ�
                mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);//�ɿ��Ҽ�
            }

        }else
        {//���
            if(m_data2)
            {//����
                mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//�������
                mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//�ɿ����
            }else
            {//˫��
                mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//�������
                mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//�ɿ����
                mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//�������
                mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//�ɿ����
            }
        }
        Sleep(m_nTimeData);//˯��
    }
    return 0;
}
void CAutoClickDlg::OnEnUpdateTime()//����ʱ��Edit�ؼ�
{
    UpdateData();
    CString str;
    str.Format(_T("%d"),m_nTimeData);
    ::WritePrivateProfileString(_T("Config"),_T("Time"),str,strPath);//д�����
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
    // ���͸�֪ͨ��������д CDialog::OnInitDialog()
    // �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
    // ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CAutoClickDlg::OnCbnSelchangeWay()
{
    m_data2 = m_wndWay.GetCurSel();//���浥|˫
    CString str;
    str.Format(_T("%d"),m_data2);
    ::WritePrivateProfileString(_T("Config"),_T("Way"),str,strPath);//д�����
}

void CAutoClickDlg::OnCbnSelchangeDirection()
{
    m_data1 = m_wndDirection.GetCurSel();//������|��
    CString str;
    str.Format(_T("%d"),m_data1);
    ::WritePrivateProfileString(_T("Config"),_T("Direction"),str,strPath);//д�����
}
