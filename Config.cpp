#include "Config.h"


void Config::LoadDefault()
{
	screen_width = 640;
	screen_height = 480;
	screen_bpp = 16;
	fullscreen = false;

	shadows = 0;

	bump_mapping = false;
	fog = false;
	antialiasing = false;
	gouraud_shading = true;

	texturing = true;
	texture_filtering = 2;

	view_depth = 100000.0f;
}

bool Config::Init()
{
	FILE *fd;

	if((fd = fopen(CONFIG_FILE, "r")) == NULL)
	{
		LoadDefault();
	}
	else
	{
		if(fscanf(fd, "screen_width=%i\nscreen_height=%i\nscreen_bpp=%i\nfullscreen=%i\n\nshadows=%i\n\nbump_mapping=%i\nfog=%i\nantialiasing=%i\ngouraud_shading=%i\n\ntexturing=%i\ntexture_filtering=%i\n\nview_depth=%f\n",
			&screen_width, &screen_height, &screen_bpp, &fullscreen, &shadows, &bump_mapping, &fog, &antialiasing, &gouraud_shading, &texturing, &texture_filtering, &view_depth) != 12)
		{
			return false;
		}
		
		fclose(fd);
	}

	hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_INIT), NULL, (DLGPROC) InitConfigProc);

	ShowWindow(hWnd, nCmdShow);

	SetFocus(hWnd);

	return true;
}


bool Config::Launch()
{
	hWC.cbSize = sizeof(hWC);
	hWC.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	hWC.lpfnWndProc = (WNDPROC) WndProc;
	hWC.cbClsExtra = 0;
	hWC.cbWndExtra = 0;
	hWC.hInstance = hInstance;
	hWC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	hWC.hCursor = LoadCursor(NULL, IDC_ARROW);
	hWC.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	hWC.lpszMenuName = NULL;
	hWC.lpszClassName = "RayWndClass";
	hWC.hIconSm = NULL;

	if(!RegisterClassEx(&hWC))
	{
		Warning("RegisterClass error");
		return launched;
	}

	if(fullscreen && !dwStyle)
	{
		dwStyle = WS_POPUP|WS_VISIBLE;
		ChangeToFullScreen();
		ShowCursor(false);
	}
	else if(!dwStyle)
		dwStyle = WS_TILED|WS_SYSMENU|WS_VISIBLE;

	hWnd = CreateWindow("RayWndClass",
					    "Ray 3D Engine 0.2a - (C) 2003 DaRoN",
					    dwStyle,
					    CW_USEDEFAULT,CW_USEDEFAULT,
					    screen_width,screen_height,
					    (HWND) NULL,
					    (HMENU) NULL,
					    hInstance,
					    (LPVOID) NULL);

	if(!hWnd)
	{
		Warning("hWnd error");
		return launched;
	}

	ShowWindow(hWnd, nCmdShow); 
    //UpdateWindow(hWnd);

	SetFocus(hWnd);

	hDC = GetDC(hWnd);
	SetupPixelFormat();
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	Init_GL();

	launched = true;

	return launched;
}


bool Config::Save()
{
	FILE* fd;

	if((fd = fopen(CONFIG_FILE, "w")) == NULL)
		return false;

	fprintf(fd, "screen_width=%i\nscreen_height=%i\nscreen_bpp=%i\nfullscreen=%i\n\nshadows=%i\n\nbump_mapping=%i\nfog=%i\nantialiasing=%i\ngouraud_shading=%i\n\ntexturing=%i\ntexture_filtering=%i\n\nview_depth=%.2f\n",
		screen_width, screen_height, screen_bpp, fullscreen, shadows, bump_mapping, fog, antialiasing, gouraud_shading, texturing, texture_filtering, view_depth);

	fclose(fd);

	return true;
}


void Config::Quit()
{
	if(hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRC);	
	}
	
	if(hDC)
		ReleaseDC(hWnd, hDC);
		
	if(fullscreen)
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(true);
	}

	DestroyWindow(hWnd);

	UnregisterClass("RayWndClass", hInstance);

	PostQuitMessage(0);
}

void Config::Init_GL()
{
	SizeOpenGLScreen();
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_LIGHTING);
}

void Config::SizeOpenGLScreen()
{
	if(screen_height == 0)
	{
		screen_height = 1;
	}

	glViewport(0, 0, screen_width, screen_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)screen_width/(GLfloat)screen_height, 1, view_depth);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


bool Config::ChangeToFullScreen()
{
	DEVMODE dmSettings;

	memset(&dmSettings, 0, sizeof(dmSettings));
	dmSettings.dmSize = sizeof(dmSettings);

	if(!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings))
	{
		Warning("Could Not Enum Display Settings");
		return false;
	}

	dmSettings.dmPelsWidth	= screen_width;
	dmSettings.dmPelsHeight	= screen_height;
	dmSettings.dmBitsPerPel = screen_bpp;
		

	if(ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		Warning("Display Mode Not Compatible");
		ChangeDisplaySettings(NULL,0);
		return false;
	}

	return true;
}



void Config::SetupPixelFormat()
{
	int PixelFormat;

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		screen_bpp,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	PixelFormat = ChoosePixelFormat(hDC, &pfd);

	SetPixelFormat(hDC, PixelFormat, &pfd);
}