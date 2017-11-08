// AutoClickDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAutoClickDlg �Ի���
class CAutoClickDlg : public CDialog
{
// ����
public:
	CAutoClickDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUTOCLICK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

    
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
    DECLARE_DYNCREATE(CAutoClickDlg);
public:
    // ���|�һ�
    CComboBox m_wndDirection;
public:
    // ˫��|����
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
    // ������ݼ�
    CHotKeyCtrl m_wndHotKeyEnd;

public:
    afx_msg void OnBnClickedSet1();
public:
    afx_msg void OnBnClickedButton2();
public:
    // ��ʼ��ݼ�
    CHotKeyCtrl m_wndHotKeyStart;

public:
     HANDLE Main;//�߳̾��
     DWORD nThreadID;//�߳�ID
public:
    afx_msg void OnCbnEditupdateWay();
public:
    afx_msg void OnCbnEditupdateDirection();
public:
    CString strPath;
    BOOL m_bThread;//�߳���Ϣ
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