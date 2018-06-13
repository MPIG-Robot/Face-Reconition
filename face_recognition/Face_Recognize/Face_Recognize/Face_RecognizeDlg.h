
// Face_RecognizeDlg.h : ͷ�ļ�
//

#pragma once
#include <opencv.hpp>

// CFace_RecognizeDlg �Ի���
class CFace_RecognizeDlg : public CDialogEx
{
// ����
public:

	BOOL stop_capture;

	CFace_RecognizeDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void face_record(void);
	void check_close(cv::VideoCapture& cap);

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACE_RECOGNIZE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedInstance();
};
