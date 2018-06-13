#include "stdafx.h"
#include "CSdlHelper.h" 
#include "FaceReconitionDemoDlg.h"
extern CFaceReconitionDemoDlg *g_pMainDlg;

SDL_Window * CSdlHelper::_screen;
SDL_Renderer *CSdlHelper::_sdlRenderer;
SDL_Texture *CSdlHelper::_sdlTexture;
SDL_Rect CSdlHelper::_dstrect;
 

CSdlHelper::CSdlHelper()
{
}


CSdlHelper::~CSdlHelper()
{
}


void CSdlHelper::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return;
	}
	_screen = SDL_CreateWindowFrom((void *)(g_pMainDlg->GetDlgItem(IDC_STATIC_PICTURE)->GetSafeHwnd()));
	if (!_screen) {
		printf("SDL: could not set video mode - exiting\n");
		return;
	}
	//获取当前可用画图驱动 window中有4个，第一个为d3d，第二个为opengl，第三个为opglse2 ,第四个software
	int draw_device_num = SDL_GetNumRenderDrivers();
	_sdlRenderer = SDL_CreateRenderer(_screen, 3, SDL_RENDERER_ACCELERATED);
	SDL_RendererInfo info;
	SDL_GetRendererInfo(_sdlRenderer, &info);
	SDL_GetRenderDriverInfo(0, &info);    //d3d
	SDL_GetRenderDriverInfo(1, &info);    //opgl
	SDL_GetRenderDriverInfo(2, &info);    //opglse2
	SDL_GetRenderDriverInfo(3, &info);    // software

	_sdlTexture = SDL_CreateTexture(
		_sdlRenderer,
		SDL_PIXELFORMAT_BGR24,
		SDL_TEXTUREACCESS_STREAMING,
		dw_width,
		dw_height);

	SDL_GetWindowSize(_screen, &_dstrect.w, &_dstrect.h);
	//////////////////////////////////////////////////////////////////////////// 

}

void CSdlHelper::ShowPicture(cv::Mat picture,SDL_Rect rect)
{ 
	SDL_UpdateTexture(_sdlTexture, &rect, picture.data, picture.cols * 3);
	SDL_RenderClear(_sdlRenderer);
	SDL_RenderCopy(_sdlRenderer, _sdlTexture, &rect, &_dstrect);
	SDL_RenderPresent(_sdlRenderer); 
}