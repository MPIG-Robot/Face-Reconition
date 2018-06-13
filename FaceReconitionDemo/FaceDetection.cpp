#include "stdafx.h"

#include "FaceDetection.h"
#include "FaceRotate.h" 

#define DETECT_BUFFER_SIZE 0x20000

void Dlib_Predefine()
{
	deserialize("shape_predictor_68_face_landmarks.dat") >> sp;//�����ǵ��ļ�
}

cv::Mat FaceToOne(cv::Mat source)//��һ��������
{

	cv::equalizeHist(source, source);//ֱ��ͼ����
	cv::resize(source, source, cv::Size(92, 112));//�ü�
	cv::Mat Mask = cv::imread("mask.jpg", 0);
	cv::Mat changedMask;
	source.copyTo(changedMask, Mask);
	return changedMask;
}

cv::Mat FaceDetect(Mat frame)//���Ƿ����
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

	for (int i = 0; i < peopleNUM; i++)//�����м�������(pResults ? *pResults : 0)
	{
		short * p = ((short*)(pResults + 1)) + 6 * i;
		Rect opencvRect(p[0], p[1], p[2], p[3]);
		//gray = gray(opencvRect);
		cv::rectangle(frame, opencvRect, Scalar(230, 255, 0));
		dlib::rectangle dlibRect((long)opencvRect.tl().x, (long)opencvRect.tl().y, (long)opencvRect.br().x - 1, (long)opencvRect.br().y - 1);
		//�������뼼�������׼ȷ��
		dlib::full_object_detection shape = sp(dlib::cv_image<uchar>(gray), dlibRect);//��ǵ�
		std::vector<full_object_detection> shapes;
		shapes.push_back(shape);//�ѵ㱣������shape��
		dlib::array<array2d<rgb_pixel>>  face_chips;
		extract_image_chips(dlib::cv_image<uchar>(gray), get_face_chip_details(shapes), face_chips);
		Mat pic = toMat(face_chips[0]);
		cvtColor(pic, pic, CV_BGR2GRAY);
		return FaceToOne(pic);
	}
	return error;
}
