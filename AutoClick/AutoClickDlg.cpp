// AutoClickDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoClick.h"
#include "AutoClickDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoClickDlg 对话框
int m_data1;//保存左|右
int m_data2;//保存单|双
int m_nTimeData;// 间隔时间


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


// CAutoClickDlg 消息处理程序

BOOL CAutoClickDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



    //获取程序的当前目录
    
    WCHAR szCurrent[MAX_PATH] = { 0 };
    GetCurrentDirectory( MAX_PATH, szCurrent);
    strPath.Format(_T("%s\\AutoClick.ini"),szCurrent);
    
   

    int nDirection;//左|右
    int Way;//单|双
    int nNtart;//开始
    int nEnd;//结束
    int nTime;
    nDirection = GetPrivateProfileInt(_T("Config"),_T("Direction"),0,strPath);//获取变量
    Way = GetPrivateProfileInt(_T("Config"),_T("Way"),0,strPath);//获取变量
    nNtart = GetPrivateProfileInt(_T("Config"),_T("Ntart"),VK_F10,strPath);
    nEnd = GetPrivateProfileInt(_T("Config"),_T("End"),VK_F11,strPath);
    nTime = GetPrivateProfileInt(_T("Config"),_T("Time"),1000,strPath);
    int nNtart2;//开始
    int nEnd2;//结束
    nNtart2 = GetPrivateProfileInt(_T("Config"),_T("nNtart2"),0,strPath);
    nEnd2 = GetPrivateProfileInt(_T("Config"),_T("nEnd2"),0,strPath);

    //设置开始默认选择
    m_wndHotKeyStart.SetHotKey(nNtart,nNtart2);
    //设置结束默认选择
    m_wndHotKeyEnd.SetHotKey(nEnd,nEnd2);
    //设置左|右默认选择
    m_wndDirection.SetCurSel(nDirection);
    //设置单|双默认选择
    m_wndWay.SetCurSel(Way);
    //初始化时间
    m_nTimeData = nTime;
    UpdateData(FALSE);
  
    
    
    if(RegisterHotKey(this->GetSafeHwnd(),4001,nNtart2,nNtart)==0)//窗口句柄|消息ID|修正标识|键码
    {
        AfxMessageBox(_T("开始快捷键注册失败"));
    }

    if(RegisterHotKey(this->GetSafeHwnd(),4002,nEnd2,nEnd)==0)//窗口句柄|消息ID|修正标识|键码
    {
        AfxMessageBox(_T("结束快捷键注册失败"));
    }
    m_data1 = m_wndDirection.GetCurSel();//保存左|右
    m_data2 = m_wndWay.GetCurSel();//保存单|双
    
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAutoClickDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CAutoClickDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAutoClickDlg::OnClose()
{
    UnregisterHotKey(this->GetSafeHwnd(),4001);//卸载开始
    UnregisterHotKey(this->GetSafeHwnd(),4002);//卸载结束
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    
    CDialog::OnClose();
}
void CAutoClickDlg::MyTest()
{
    AfxMessageBox(_T(""));

}

BOOL CAutoClickDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    if(pMsg->message==WM_HOTKEY)
    {
        //AfxMessageBox(_T(""));
        if (pMsg->wParam==4001)//开始
        {
            //CAutoClickDlg Dlg = AfxBeginThread(TimeThread,this);
            //AfxMessageBox(_T("开始"));
            if (m_bThread==TRUE)
            {
                m_bThread = FALSE;
                m_wndTimeEdit.EnableWindow(m_bThread);
                Main = CreateThread(NULL,0,::ThreadProc,NULL,0,&nThreadID);//创建一个立刻执行的线程
                
            }
            
            return TRUE;
        }

        if(pMsg->wParam==4002)//结束
        {
            //AfxMessageBox(_T("结束"));
            if (m_bThread == FALSE)
            {
                m_bThread = TRUE;
                m_wndTimeEdit.EnableWindow(m_bThread);
//                CloseHandle(&Main);//挂起线程
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
    UpdateData();//每次线程重新启动刷新变量数据
    while (1)//无限循环
    {
        

        AfxMessageBox(_T(""));
        
        
    }
}


void CAutoClickDlg::OnBnClickedSet1()//开始热键设置
{
    UnregisterHotKey(this->GetSafeHwnd(),4001);//卸载旧热键
    
    WORD vir,mod;
    m_wndHotKeyStart.GetHotKey(vir,mod);//获取键码|修正标识
    if(RegisterHotKey(this->GetSafeHwnd(),4001,mod,vir)==0)//窗口句柄|消息ID|键码|修正标识
    {
        AfxMessageBox(_T("开始快捷键注册失败"));
    }else
    {
        CString str,str2;
        str.Format(_T("%d"),vir);
        str2.Format(_T("%d"),mod);
        ::WritePrivateProfileString(_T("Config"),_T("Ntart"),str,strPath);//写入变量
        ::WritePrivateProfileString(_T("Config"),_T("nNtart2"),str2,strPath);//写入变量
    }
}

void CAutoClickDlg::OnBnClickedButton2()//停止热键设置
{
    UnregisterHotKey(this->GetSafeHwnd(),4002);//卸载旧热键

    WORD vir,mod;
    m_wndHotKeyEnd.GetHotKey(vir,mod);//获取键码|修正标识
    if(RegisterHotKey(this->GetSafeHwnd(),4002,mod,vir)==0)//窗口句柄|消息ID|键码|修正标识
    {
        AfxMessageBox(_T("结束快捷键注册失败"));
    }else
    {
        CString str,str2;
        str.Format(_T("%d"),vir);
        str2.Format(_T("%d"),mod);
        ::WritePrivateProfileString(_T("Config"),_T("End"),str,strPath);//写入变量
        ::WritePrivateProfileString(_T("Config"),_T("nEnd2"),str2,strPath);//写入变量
    }
    // TODO: 在此添加控件通知处理程序代码
}


void CAutoClickDlg::OnCbnEditupdateDirection()//左|右下拉框内容改变
{



}

void CAutoClickDlg::OnCbnEditupdateWay()//单|双下拉框内容改变
{

}

DWORD WINAPI ThreadProc(LPVOID lpParameter )
{
    while(1)
    {
        if(m_data1)
        {//右击
            if(m_data2)
            {//单击
                mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);//点下右键
                mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);//松开右键
            }else
            {//双击
                mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);//点下右键
                mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);//松开右键
                mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);//点下右键
                mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);//松开右键
            }

        }else
        {//左击
            if(m_data2)
            {//单击
                mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
                mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
            }else
            {//双击
                mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
                mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
                mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
                mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
            }
        }
        Sleep(m_nTimeData);//睡眠
    }
    return 0;
}
void CAutoClickDlg::OnEnUpdateTime()//更新时间Edit控件
{
    UpdateData();
    CString str;
    str.Format(_T("%d"),m_nTimeData);
    ::WritePrivateProfileString(_T("Config"),_T("Time"),str,strPath);//写入变量
    // TODO:  如果该控件是 RICHEDIT 控件，则它将不会
    // 发送该通知，除非重写 CDialog::OnInitDialog()
    // 函数，将 EM_SETEVENTMASK 消息发送到控件，
    // 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

    // TODO:  在此添加控件通知处理程序代码
}

void CAutoClickDlg::OnCbnSelchangeWay()
{
    m_data2 = m_wndWay.GetCurSel();//保存单|双
    CString str;
    str.Format(_T("%d"),m_data2);
    ::WritePrivateProfileString(_T("Config"),_T("Way"),str,strPath);//写入变量
}

void CAutoClickDlg::OnCbnSelchangeDirection()
{
    m_data1 = m_wndDirection.GetCurSel();//保存左|右
    CString str;
    str.Format(_T("%d"),m_data1);
    ::WritePrivateProfileString(_T("Config"),_T("Direction"),str,strPath);//写入变量
}
