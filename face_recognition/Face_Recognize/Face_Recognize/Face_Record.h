#pragma once


// Face_Record �Ի���

class Face_Record : public CDialogEx
{
	DECLARE_DYNAMIC(Face_Record)

public:
	Face_Record(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Face_Record();
	CString Get_face_name(void) 
	{
		return m_face_name;
	}

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_face_name;
};
