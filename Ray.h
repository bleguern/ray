#ifndef _RAY_H_
#define _RAY_H_

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dinput.lib")
#pragma comment(lib, "dxguid.lib")


#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
//#include "glext.h"

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>




#include <stdlib.h>
#include <stdio.h>

#include "resource.h"

#define DAR_CURRENT_VERSION           100
#define MAX_CHARS           256

bool Init_GL();
void SizeOpenGLScreen(int, int);
void Quit();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
WPARAM MainLoop();
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK InitConfigProc(HWND, UINT, WPARAM, LPARAM);
bool ChangeToFullScreen();

#endif