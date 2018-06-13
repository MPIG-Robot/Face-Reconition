
// Face_RecognizeDlg.h : 头文件
//

#pragma once
#include <opencv.hpp>

// CFace_RecognizeDlg 对话框
class CFace_RecognizeDlg : public CDialogEx
{
// 构造
public:

	BOOL stop_capture;

	CFace_RecognizeDlg(CWnd* pParent = NULL);	// 标准构造函数
	void face_record(void);
	void check_close(cv::VideoCapture& cap);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACE_RECOGNIZE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedInstance();
};
