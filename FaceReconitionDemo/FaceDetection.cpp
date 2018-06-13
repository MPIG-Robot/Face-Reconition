#include "stdafx.h"

#include "FaceDetection.h"
#include "FaceRotate.h" 

#define DETECT_BUFFER_SIZE 0x20000

void Dlib_Predefine()
{
	deserialize("shape_predictor_68_face_landmarks.dat") >> sp;//读入标记点文件
}

cv::Mat FaceToOne(cv::Mat source)//归一化处理函数
{

	cv::equalizeHist(source, source);//直方图均衡
	cv::resize(source, source, cv::Size(92, 112));//裁剪
	cv::Mat Mask = cv::imread("mask.jpg", 0);
	cv::Mat changedMask;
	source.copyTo(changedMask, Mask);
	return changedMask;
}

cv::Mat FaceDetect(Mat frame)//脸是否存在
{
	Mat gray, error;
	cvtColor(frame, gray, CV_BGR2GRAY);
	int * pResults = NULL;
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	if (!pBuffer)
	{
		fprintf(stderr, "Can not alloc buffer.\n");
		
	}

	int doLandmark = 1;

	pResults = facedetect_multiview_reinforce(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
		1.2f, 2, 48, 0, doLandmark);
	int peopleNUM = (pResults ? *pResults : 0);

	for (int i = 0; i < peopleNUM; i++)//代表有几张人脸(pResults ? *pResults : 0)
	{
		short * p = ((short*)(pResults + 1)) + 6 * i;
		Rect opencvRect(p[0], p[1], p[2], p[3]);
		//gray = gray(opencvRect);
		cv::rectangle(frame, opencvRect, Scalar(230, 255, 0));
		dlib::rectangle dlibRect((long)opencvRect.tl().x, (long)opencvRect.tl().y, (long)opencvRect.br().x - 1, (long)opencvRect.br().y - 1);
		//人脸对齐技术提高了准确率
		dlib::full_object_detection shape = sp(dlib::cv_image<uchar>(gray), dlibRect);//标记点
		std::vector<full_object_detection> shapes;
		shapes.push_back(shape);//把点保存在了shape中
		dlib::array<array2d<rgb_pixel>>  face_chips;
		extract_image_chips(dlib::cv_image<uchar>(gray), get_face_chip_details(shapes), face_chips);
		Mat pic = toMat(face_chips[0]);
		cvtColor(pic, pic, CV_BGR2GRAY);
		return FaceToOne(pic);
	}
	return error;
}
