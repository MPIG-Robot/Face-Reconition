
//
/*system include*/


/*MFC include*/
#include "stdafx.h"
#include "Face_Recognize.h"
#include "Face_RecognizeDlg.h"
#include "afxdialogex.h"

/*opencv include*/
#include <opencv.hpp>
#include "facedetect-dll.h"
#pragma comment(lib,"libfacedetect.lib")

#include "Face_recognition_dlib.h"
#include "Sort_method.h"
#include "Face_Record.h"


using namespace dlib;
using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DETECT_BUFFER_SIZE 0x20000



static int face_detect_count = 0;



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFace_RecognizeDlg 对话框



CFace_RecognizeDlg::CFace_RecognizeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FACE_RECOGNIZE_DIALOG, pParent)
{
	stop_capture = false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFace_RecognizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFace_RecognizeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFace_RecognizeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(CLOSE_INSTANCE, &CFace_RecognizeDlg::OnBnClickedInstance)
END_MESSAGE_MAP()


// CFace_RecognizeDlg 消息处理程序

BOOL CFace_RecognizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFace_RecognizeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFace_RecognizeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFace_RecognizeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int capture_face(Mat frame,Mat& out)
{
	Mat gray;
	Mat face;
	int rc = -1;

	if (frame.empty() || !frame.data) return -1;

	cvtColor(frame, gray, CV_BGR2GRAY);
	int * pResults = NULL;

	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	if (!pBuffer)
	{
		fprintf(stderr, "Can not alloc buffer.\n");
		return -1;
	}
	//pResults = facedetect_frontal_tmp((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
	//	1.2f, 5, 24);
	pResults = facedetect_multiview_reinforce(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
		1.2f, 2, 48, 0, 1);

	//printf("%d faces detected.\n", (pResults ? *pResults : 0));//重复运行
															   //print the detection results
	if (pResults != NULL)
	{
		for (int i = 0; i < (pResults ? *pResults : 0); i++)
		{
			short * p = ((short*)(pResults + 1)) + 6 * i;
			int x = p[0];
			int y = p[1];
			int w = p[2];
			int h = p[3];
			int neighbors = p[4];

			Rect_<float> face_rect = Rect_<float>(x, y, w, h);
			face = frame(face_rect);

			printf("face_rect=[%d, %d, %d, %d], neighbors=%d\n", x, y, w, h, neighbors);
			Point left(x, y);
			Point right(x + w, y + h);
			cv::rectangle(frame, left, right, Scalar(230, 255, 0), 4);		
		}
		//imshow("frame", frame);
		if (face.empty() || !face.data)
		{
			face_detect_count = 0;
			return -1;
		}
		if (face_detect_count++ > 30)
		{
#ifdef _FACE_RECOGNIZE_DEBUG
			imshow("face", face);
#endif
			out = face.clone();
			return 0;
		}
	}
	else
	{
		//face is moving, and reset the detect count
		face_detect_count = 0;
	}

	return rc;
}

void CFace_RecognizeDlg::face_record(void)
{
	INT_PTR nRes;
	Face_Record face_record;
	nRes = face_record.DoModal();
	if (IDOK == nRes)
	{
		UpdateData(TRUE);
		CString pre_fix(".\\faces\\");
		CString post_fix(".jpg");
		CString name = pre_fix + face_record.Get_face_name() + post_fix;
		MoveFile(CString(".\\cap.jpg"), name);
	}
}

void CFace_RecognizeDlg::check_close(VideoCapture& cap)
{
	if (stop_capture)
	{
		stop_capture = FALSE;

		if (MessageBox(_T("确定要退出吗？"), _T("提示"), MB_YESNO | MB_DEFBUTTON2) == IDYES)
		{
			cap.release();
			::SendMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);//
			OnClose();
			exit(0);
		}
	}
}
void CFace_RecognizeDlg::OnBnClickedButton1()
{
	face_detect_count = 0;

	namedWindow("view", WINDOW_FULLSCREEN);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

#if 1	
	CAPTURE:
	Mat frame;
	Mat face;
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		AfxMessageBox(_T("Please check your USB camera's interface num."));
	}

	try
	{
		while (1)
		{
			check_close(cap);
			cap >> frame;
			if (!frame.empty())
			{
				if (capture_face(frame, face) == 0)
				{
					//convert to IplImage format and then save with .jpg format
					IplImage face_Img;
					face_Img = IplImage(face);
					//save the capture face to the project directory
					cvSaveImage("./cap.jpg", &face_Img);
					break;
				}
				imshow("view", frame);
			}
	
			int c = waitKey(10);
			if ((char)c == 'c') { break; }
		}
	}
	catch (exception& e)
	{
		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;
#ifdef _CAPTURE_DEBUG
		MessageBox(CString(e.what()), NULL, MB_YESNO);
#endif
		goto CAPTURE;
	}

	matrix<rgb_pixel> face_cap;
	//save the capture in the project directory
	load_image(face_cap, ".\\cap.jpg");

	//Display the raw image on the screen
	image_window win1(face_cap);

	frontal_face_detector detector = get_frontal_face_detector();
	std::vector<matrix<rgb_pixel>> vect_faces;

	for (auto face : detector(face_cap))
	{
		auto shape = face_recognize.sp(face_cap, face);
		matrix<rgb_pixel> face_chip;
		extract_image_chip(face_cap, get_face_chip_details(shape, 150, 0.25), face_chip);
		vect_faces.push_back(move(face_chip));
		win1.add_overlay(face);
	}

	if (vect_faces.size() != 1)
	{
		cout <<"Capture face error! face number "<< vect_faces.size()  << endl;
		cap.release();
		goto CAPTURE;
	}

	//Use DNN and get the capture face's feature with 128D vector
	std::vector<matrix<float, 0, 1>> face_cap_desc = face_recognize.net(vect_faces);
	//Browse the face feature from the database, and find the match one
	std::pair<double,std::string> candidate_face;
	std::vector<double> len_vec;

	std::vector<std::pair<double, std::string>> candi_face_vec;
	candi_face_vec.reserve(256);

	for (size_t i = 0; i < face_recognize.face_desc_vec.size(); ++i)
	{
		auto len = length(face_cap_desc[0] - face_recognize.face_desc_vec[i].face_feature);
	    if (len < 0.45)
		{
			len_vec.push_back(len);
			candidate_face.first = len;
			candidate_face.second = face_recognize.face_desc_vec[i].name.c_str();
			candi_face_vec.push_back(candidate_face);

#ifdef _FACE_RECOGNIZE_DEBUG
			char buffer[256] = {0};
			sprintf_s(buffer, "Candidate face %s Euclid length %f",
				face_recognize.face_desc_vec[i].name.c_str(),
				len);
			MessageBox(CString(buffer), NULL, MB_YESNO);
#endif
		}
		else
		{
			cout << "This face from database is not match the capture face, continue!" << endl;
		}
	}

	//Find the most similar face
	if (len_vec.size() != 0)
	{
		shellSort(len_vec);

		int i(0);
		for (i = 0; i != len_vec.size(); i++)
		{
			if (len_vec[0] == candi_face_vec[i].first)
				break;
		}

		char buffer[256] = { 0 };
		sprintf_s(buffer, "The face is %s -- Euclid length %f",
			candi_face_vec[i].second.c_str(), candi_face_vec[i].first);
		if (MessageBox(CString(buffer), NULL, MB_YESNO) == IDNO)
		{
			face_record();
		}
	}
	else
	{
		if (MessageBox(CString("Not the similar face been found"), NULL, MB_YESNO) == IDYES)
		{
			face_record();
		}
	}	

	face_detect_count = 0;
	frame.release();
	face.release();	
	goto CAPTURE;
	
#else
	detection_static();
#endif

}


void CFace_RecognizeDlg::OnBnClickedInstance()
{
	stop_capture = TRUE;
}
