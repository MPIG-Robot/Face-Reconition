// Face_Record.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Face_Recognize.h"
#include "Face_Record.h"
#include "afxdialogex.h"


// Face_Record �Ի���

IMPLEMENT_DYNAMIC(Face_Record, CDialogEx)

Face_Record::Face_Record(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RECORD, pParent)
	, m_face_name(_T(""))
{

}

Face_Record::~Face_Record()
{
}

void Face_Record::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FACE_RECORD, m_face_name);
}


BEGIN_MESSAGE_MAP(Face_Record, CDialogEx)
END_MESSAGE_MAP()


// Face_Record ��Ϣ�������
