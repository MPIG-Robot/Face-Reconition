#pragma once


// Face_Record 对话框

class Face_Record : public CDialogEx
{
	DECLARE_DYNAMIC(Face_Record)

public:
	Face_Record(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Face_Record();
	CString Get_face_name(void) 
	{
		return m_face_name;
	}

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_face_name;
};
