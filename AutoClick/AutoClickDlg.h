// AutoClickDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAutoClickDlg 对话框
class CAutoClickDlg : public CDialog
{
// 构造
public:
	CAutoClickDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AUTOCLICK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

    
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
    DECLARE_DYNCREATE(CAutoClickDlg);
public:
    // 左击|右击
    CComboBox m_wndDirection;
public:
    // 双击|单击
    CComboBox m_wndWay;
public:

public:
    afx_msg void OnClose();
public:
    void MyTest();

public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    UINT TimeThread(LPVOID pVoid);
public:
    // 结束快捷键
    CHotKeyCtrl m_wndHotKeyEnd;

public:
    afx_msg void OnBnClickedSet1();
public:
    afx_msg void OnBnClickedButton2();
public:
    // 开始快捷键
    CHotKeyCtrl m_wndHotKeyStart;

public:
     HANDLE Main;//线程句柄
     DWORD nThreadID;//线程ID
public:
    afx_msg void OnCbnEditupdateWay();
public:
    afx_msg void OnCbnEditupdateDirection();
public:
    CString strPath;
    BOOL m_bThread;//线程信息
public:
    afx_msg void OnEnUpdateTime();
public:
    afx_msg void OnCbnSelchangeWay();
public:
    afx_msg void OnCbnSelchangeDirection();
public:
    CEdit m_wndTimeEdit;
};
DWORD WINAPI ThreadProc(LPVOID lpParameter );