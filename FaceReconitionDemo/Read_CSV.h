#pragma once


#include <opencv2\opencv.hpp>
#include <facedetect-dll.h>
#include <iostream>
#include <fstream>


#define DETECT_BUFFER_SIZE 0x20000
using namespace cv;
using namespace std;

static void read_csv(const string& filename, cv::vector<Mat>& images, cv::vector<int>& labels, char separator = ';') {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			cv::Mat picture = imread(path); 
			cv::resize(picture, picture, cv::Size(640, 480));
			auto gray = FaceDetect(picture);
			if (gray.rows == 0)
				continue;
			cv::resize(gray, gray, cv::Size(70, 70));
			images.push_back(gray);
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}