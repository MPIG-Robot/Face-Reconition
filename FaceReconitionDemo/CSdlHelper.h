#pragma once

#include "../SDL2/include/SDL.h" 
#include "FaceDetection.h"
#include "resource.h"

const int dw_width = 640;
const int dw_height = 480;
class CSdlHelper
{
public:
	CSdlHelper();
	~CSdlHelper();


	static void initSDL();
	static void ShowPicture(cv::Mat mat,SDL_Rect rect);
private:

	static SDL_Window* _screen;
	static SDL_Renderer* _sdlRenderer;
	static SDL_Texture* _sdlTexture;
	static SDL_Rect _dstrect;
};

