
// FaceReconitionDemoDlg.h: 头文件
//

#pragma once
#include "afxcmn.h"

#include "FaceDetection.h" 
#include "Read_CSV.h"


// CFaceReconitionDemoDlg 对话框
class CFaceReconitionDemoDlg : public CDialog
{
// 构造
public:
	CFaceReconitionDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACERECONITIONDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	Ptr<FaceRecognizer> _model;

	void thread_face_recontion(); 
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMfcbuttonTestPicture();
	afx_msg void OnBnClickedMfcbuttonButton2();
	afx_msg void OnBnClickedMfcbuttonButton5();
	CListCtrl m_ctlList;
	afx_msg void OnBnClickedMfcbuttonButton4();
	CString m_strlog;
};
