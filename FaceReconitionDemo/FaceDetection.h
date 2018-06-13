#pragma once

#include <opencv2\opencv.hpp>
#include <facedetect-dll.h>

using namespace cv;
using namespace std;

Mat FaceDetect(Mat frame);
void Dlib_Predefine();//dlib 预定义的函数
  
 
 
