#include "stdafx.h"
#include "io.h"
#include "Face_recognition_dlib.h"

using namespace dlib;
using namespace std;


// ----------------------------------------------------------------------------------------

FACE_RECOGNITION::FACE_RECOGNITION(int depth)
{
	face_desc_vec.reserve(depth);
}

int FACE_RECOGNITION::load_db_faces(void)
{
	int rc = -1;
	long  hFile = 0;
	struct _finddata_t fileinfo;

	frontal_face_detector detector = get_frontal_face_detector();
	// We will also use a face landmarking model to align faces to a standard pose:  (see face_landmark_detection_ex.cpp for an introduction)
	deserialize("shape_predictor_68_face_landmarks.dat") >> sp;

	// And finally we load the DNN responsible for face recognition.
	deserialize("dlib_face_recognition_resnet_model_v1.dat") >> net;

	if ((hFile = _findfirst(".\\faces\\*.jpg", &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_ARCH))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					if (!strcmp(strstr(fileinfo.name, ".") + 1 , "jpg"))
					{
						cout << "This file is an image file!" << fileinfo.name << endl;
						matrix<rgb_pixel> img;
						char path[260];
						sprintf_s(path,".\\faces\\%s", fileinfo.name);
						load_image(img, path);
						image_window win(img);

						for (auto face : detector(img))
						{
							auto shape = sp(img, face);
							matrix<rgb_pixel> face_chip;
							extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);

							//Record the all this face's information
							FACE_DESC sigle_face;
							sigle_face.face_chip = face_chip;
							sigle_face.name = fileinfo.name;

							std::vector<matrix<rgb_pixel>> face_chip_vec;
							std::vector<matrix<float, 0, 1>> face_all;

							face_chip_vec.push_back(move(face_chip));

							//Asks the DNN to convert each face image in faces into a 128D vector
							face_all = net(face_chip_vec);

							//Get the feature of this person
							std::vector<matrix<float, 0, 1>>::iterator iter_begin = face_all.begin(),
								iter_end = face_all.end();
							if (face_all.size() > 1) break;
							sigle_face.face_feature = *iter_begin;

							//all the person description into vector
							face_desc_vec.push_back(sigle_face);

							win.add_overlay(face);
						}
					}
					else
					{
						cout << "This file is not image file!" << fileinfo.name << endl;
					}					
				}
			}
			else
			{
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}

	return rc;
}





