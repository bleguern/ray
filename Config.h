#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "Error.h"


#define CONFIG_FILE         "config.ini"


class Config
{
public:

	unsigned int screen_width;
	unsigned int screen_height;
	unsigned int screen_bpp;
	bool fullscreen;

	unsigned int shadows;

	bool bump_mapping;
	bool fog;
	bool antialiasing;
	bool gouraud_shading;

	bool texturing;
	unsigned int texture_filtering;

	GLfloat view_depth;

	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
	HINSTANCE hInstance;
	MSG uMsg;
	WNDCLASSEX hWC;
	DWORD dwStyle;
	int nCmdShow;

	bool launched;

	Config():screen_width(640),screen_height(480),screen_bpp(16),fullscreen(false),shadows(0),
		bump_mapping(false),fog(false),antialiasing(false),gouraud_shading(true),
		texturing(true),texture_filtering(2),view_depth(100000.0f),
		hWnd(NULL),hDC(NULL),hRC(NULL),hInstance(NULL),dwStyle(NULL),
		launched(false) {}
	~Config() {}

	void LoadDefault();
	bool Init();
	bool Launch();
	bool Save();
	void Quit();
	void Init_GL();
	void SizeOpenGLScreen();
	bool ChangeToFullScreen();
	void SetupPixelFormat();
};



#endif