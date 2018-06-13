#pragma once
 
#include "dlib-19.4\dlib\image_io.h"
 

#include "dlib-19.4\dlib\image_processing\frontal_face_detector.h"
#include "dlib-19.4\dlib\image_processing\render_face_detections.h"
#include "dlib-19.4\dlib\\image_processing.h"
#include "dlib-19.4\dlib\gui_widgets.h"
#include "dlib-19.4\dlib\opencv\cv_image.h"
#include "dlib-19.4\dlib\opencv.h"

using namespace dlib;

frontal_face_detector detector = get_frontal_face_detector();
shape_predictor sp;//Already get