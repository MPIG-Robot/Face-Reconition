
// FaceReconitionDemoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FaceReconitionDemo.h"
#include "FaceReconitionDemoDlg.h"
#include "afxdialogex.h"
#include "CSdlHelper.h"
#include <thread>

const int namenumber = 9;//测试的人脸数量
const string textname[namenumber] = { "CML", "GJ", "GYQ", "LZM" , "QLY" , "SSY" , "XS" , "ZR", "ZZL" };//做一个储存人脸名字的数组
const string RegisterList[namenumber] = { "曹溟烁", "高九", "郭延青", "刘兆铭" , "阙禄颖" , "宋思雨" , "肖洒" , "钟蕊", "朱桢磊" };//做一个储存人脸名字的数组

CFaceReconitionDemoDlg *g_pMainDlg;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CFaceReconitionDemoDlg 对话框



CFaceReconitionDemoDlg::CFaceReconitionDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_FACERECONITIONDEMO_DIALOG, pParent)
	, m_strlog(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFaceReconitionDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctlList);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strlog);
}

BEGIN_MESSAGE_MAP(CFaceReconitionDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MFCBUTTON_TEST_PICTURE, &CFaceReconitionDemoDlg::OnBnClickedMfcbuttonTestPicture)
	ON_BN_CLICKED(IDC_MFCBUTTON_BUTTON2, &CFaceReconitionDemoDlg::OnBnClickedMfcbuttonButton2)
	ON_BN_CLICKED(IDC_MFCBUTTON_BUTTON5, &CFaceReconitionDemoDlg::OnBnClickedMfcbuttonButton5)
	ON_BN_CLICKED(IDC_MFCBUTTON_BUTTON4, &CFaceReconitionDemoDlg::OnBnClickedMfcbuttonButton4)
END_MESSAGE_MAP()


// CFaceReconitionDemoDlg 消息处理程序

BOOL CFaceReconitionDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	g_pMainDlg = this;

	Dlib_Predefine();//加载dlib的文件

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFaceReconitionDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFaceReconitionDemoDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFaceReconitionDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFaceReconitionDemoDlg::OnBnClickedMfcbuttonTestPicture()
{
	CString Field[2] = { "用户名","是否签到" };						//列表视的表头
	for (int j = 0; j<2; j++)
	{
		m_ctlList.InsertColumn(j, Field[j], LVCFMT_LEFT, 75);				//插入表头标题
	}

	int index = 0;
	for (auto i : RegisterList)
	{
		m_ctlList.InsertItem(index,  i.c_str());

		m_ctlList.SetItemText(index, 1, "未签到");

		index++;
	}
	m_strlog += "载入用户库完成\r\n";
	
	UpdateData(FALSE);

//	using namespace cv;
//	// TODO: 在此添加控件通知处理程序代码
// 
//
////	//load an image and convert it to gray (single-channel)
//	Mat image = imread("20180425194158.jpg");
//	if (image.empty())
//	{
////		fprintf(stderr, "Can not load the image file %s.\n", argv[1]);
//		return ;
//	}
//	//resize(image, image, cv::Size(720, 560));
//	Mat gray;
//	cvtColor(image, gray, CV_BGR2GRAY);
//
//
//	int * pResults = NULL;
//	//pBuffer is used in the detection functions.
//	//If you call functions in multiple threads, please create one buffer for each thread!
//	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
//	if (!pBuffer)
//	{
//		fprintf(stderr, "Can not alloc buffer.\n");
//		return ;
//	}
//
//	int doLandmark = 1;
//
//	///////////////////////////////////////////
//	// frontal face detection / 68 landmark detection
//	// it's fast, but cannot detect side view faces
//	//////////////////////////////////////////
//	//!!! The input image must be a gray one (single-channel)
//	//!!! DO NOT RELEASE pResults !!!
//	pResults = facedetect_frontal(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
//		1.2f, 2, 48, 0, doLandmark);
//
//	printf("%d faces detected.\n", (pResults ? *pResults : 0));
//	Mat result_frontal = image.clone();
//	//print the detection results
//	for (int i = 0; i < (pResults ? *pResults : 0); i++)
//	{
//		short * p = ((short*)(pResults + 1)) + 142 * i;
//		int x = p[0];
//		int y = p[1];
//		int w = p[2];
//		int h = p[3];
//		int neighbors = p[4];
//		int angle = p[5];
//
//		printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
//		rectangle(result_frontal, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
//		if (doLandmark)
//		{
//			for (int j = 0; j < 68; j++)
//				circle(result_frontal, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, Scalar(0, 255, 0));
//		}
//	}
//	namedWindow("Results_frontal", 0);
//	imshow("Results_frontal", result_frontal);
//
////
////	///////////////////////////////////////////
////	// frontal face detection designed for video surveillance / 68 landmark detection
////	// it can detect faces with bad illumination.
////	//////////////////////////////////////////
////	//!!! The input image must be a gray one (single-channel)
////	//!!! DO NOT RELEASE pResults !!!
//	pResults = facedetect_frontal_surveillance(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
//		1.2f, 2, 48, 0, doLandmark);
//	printf("%d faces detected.\n", (pResults ? *pResults : 0));
//	Mat result_frontal_surveillance = image.clone();;
//	//print the detection results
//	for (int i = 0; i < (pResults ? *pResults : 0); i++)
//	{
//		short * p = ((short*)(pResults + 1)) + 142 * i;
//		int x = p[0];
//		int y = p[1];
//		int w = p[2];
//		int h = p[3];
//		int neighbors = p[4];
//		int angle = p[5];
//
//		printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
//		rectangle(result_frontal_surveillance, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
//		if (doLandmark)
//		{
//			for (int j = 0; j < 68; j++)
//				circle(result_frontal_surveillance, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, Scalar(0, 255, 0));
//		}
//	}
//	imshow("Results_frontal_surveillance", result_frontal_surveillance);
//
//
//	///////////////////////////////////////////
//	// multiview face detection / 68 landmark detection
//	// it can detect side view faces, but slower than facedetect_frontal().
//	//////////////////////////////////////////
//	//!!! The input image must be a gray one (single-channel)
//	//!!! DO NOT RELEASE pResults !!!
//	pResults = facedetect_multiview(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
//		1.2f, 2, 48, 0, doLandmark);
//
//	printf("%d faces detected.\n", (pResults ? *pResults : 0));
//	Mat result_multiview = image.clone();;
//	//print the detection results
//	for (int i = 0; i < (pResults ? *pResults : 0); i++)
//	{
//		short * p = ((short*)(pResults + 1)) + 142 * i;
//		int x = p[0];
//		int y = p[1];
//		int w = p[2];
//		int h = p[3];
//		int neighbors = p[4];
//		int angle = p[5];
//
//		printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
//		rectangle(result_multiview, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
//		if (doLandmark)
//		{
//			for (int j = 0; j < 68; j++)
//				circle(result_multiview, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, Scalar(0, 255, 0));
//		}
//	}
//	imshow("Results_multiview", result_multiview);
//
//
//	/////////////////////////////////////////////
//	//// reinforced multiview face detection / 68 landmark detection
//	//// it can detect side view faces, better but slower than facedetect_multiview().
//	////////////////////////////////////////////
//	////!!! The input image must be a gray one (single-channel)
//	////!!! DO NOT RELEASE pResults !!!
//	pResults = facedetect_multiview_reinforce(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
//		1.2f, 3, 48, 0, doLandmark);
//
//	printf("%d faces detected.\n", (pResults ? *pResults : 0));
//	Mat result_multiview_reinforce = image.clone();;
//	//print the detection results
//	for (int i = 0; i < (pResults ? *pResults : 0); i++)
//	{
//		short * p = ((short*)(pResults + 1)) + 142 * i;
//		int x = p[0];
//		int y = p[1];
//		int w = p[2];
//		int h = p[3];
//		int neighbors = p[4];
//		int angle = p[5];
//
//		printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
//		rectangle(result_multiview_reinforce, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
//		if (doLandmark)
//		{
//			for (int j = 0; j < 68; j++)
//				circle(result_multiview_reinforce, Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, Scalar(0, 255, 0));
//		}
//	}
//
//	//可以识别
//	imshow("Results_multiview_reinforce", result_multiview_reinforce);
//	waitKey(0);
//
//	//release the buffer
//	free(pBuffer);
}

Ptr<FaceRecognizer>  GetTrainModel(string fn_csv)//输入CSV文件的路径名
{
	vector<Mat> images;
	vector<int> labels;
	try {
		read_csv(fn_csv, images, labels);
	}
	catch (cv::Exception& e) {
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		// 文件有问题，我们啥也做不了了，退出了
		exit(1);
	}
	// 如果没有读取到足够图片，我们也得退出.
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
	}
	try
	{
		Ptr<FaceRecognizer> model = createFisherFaceRecognizer(80);//创建人脸识别类 可修改 LBPHFace、EigenFace、FisherFace
		model->train(images, labels);		//训练灰度人脸和标签
 
		//model->load("MyFaceFisherModel.xml");
		model->save("MyFaceFisherModel.xml");		//保存模型 下次调用

		return model;

	}
	catch (cv::Exception &e)
	{
		e.what();

	}

}


void CFaceReconitionDemoDlg::OnBnClickedMfcbuttonButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	_model = createFisherFaceRecognizer(80); //GetTrainModel("filelist.csv");//获得模型		
	_model->load("MyFaceFisherModel.xml");

	m_strlog += "载入模型库完成\r\n"; 
	UpdateData(FALSE);
}


void CFaceReconitionDemoDlg::thread_face_recontion()
{
	VideoCapture capture(0);

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = dw_width;
	rect.h = dw_height;
	CSdlHelper::initSDL();

	Mat frame, gray;  //定义一个Mat变量，用于存储每一帧的图像
	auto count = -1;
	//【2】循环显示每一帧
	while (1)
	{
		capture >> frame;  //读取当前帧
		resize(frame, frame, cv::Size(dw_width, dw_height));
		try
		{
			if (!frame.empty())
			{
				gray = FaceDetect(frame);
				cv::resize(gray, gray, cv::Size(70, 70));/*
														 namedWindow("Gray Face Recogniton", 0);
														 imshow("Gray Face Recogniton", gray);*/
				if (!gray.empty())		//此处判断识别结果  如果连续多少次结果为某人  则进行签到
				{
					int predicted_label = -1;
					double predicted_confidence = 0;
					_model->predict(gray, predicted_label, predicted_confidence);	//识别结果
					string result_message = format("Predicted class = %d / Actual class = %d.", predicted_label, predicted_confidence);
					putText(frame, textname[predicted_label], Point(50, 50), FONT_HERSHEY_DUPLEX, 3, Scalar(230, 255, 0), 2);//model->predict(frame) = predictLabel 名字写在 1 1

					for (auto i : textname)
					{

						if (textname[predicted_label] == i)			//找到列表相同	如果连续多少次  则刷新列表
						{

							 m_ctlList.SetItemText(predicted_label, 1, "已签到");
							  
						}
						else
						{

							m_ctlList.SetItemText(predicted_label, 1, "未签到");
						}
					}
				}
				CSdlHelper::ShowPicture(frame, rect);
				waitKey(1);
			}
		}
		catch (cv::Exception &e)
		{
			e.what();
		}
		waitKey(25);  //延时25ms
	}


}
void CFaceReconitionDemoDlg::OnBnClickedMfcbuttonButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	thread face_thread(&CFaceReconitionDemoDlg::thread_face_recontion,this);
	face_thread.detach();

	m_strlog += "开启图像采集线程!";
}


void CFaceReconitionDemoDlg::OnBnClickedMfcbuttonButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tempMsg;
	try {

		_model = GetTrainModel("filelist.csv");		//训练的模型
	}
	catch (cv::Exception &e)
	{
		tempMsg.Format("训练发生错误:%s\r\n", e.msg);
		m_strlog += tempMsg;
		return;
	}

	m_strlog += "训练成功!";
}
