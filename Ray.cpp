/**************************************************************************/
/*                                                                        */
/*                   THE RAY 3D ENGINE SOURCE CODE                        */
/*                              By DaRoN                                  */
/*                                                                        */
/**************************************************************************/



#include "Ray.h"

#include "Error.h"
#include "Config.h"
#include "Scene.h"
#include "Console.h"
#include "Input.h"


Config config;
Scene scene;
Console console;
Input input;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	config.hInstance = hInstance;
	config.nCmdShow = nCmdShow;

	if(!config.Init())
	{
		Warning("Init error");
		return false;
	}

	return MainLoop();
}


WPARAM MainLoop()
{
	while(1)
	{
		if(PeekMessage(&config.uMsg, NULL, 0, 0, PM_REMOVE)) 
        {
			if(config.uMsg.message == WM_QUIT)
				break;

            TranslateMessage(&config.uMsg);
            DispatchMessage(&config.uMsg);
        }
		else
		{
			if(config.launched)
			{
				input.Event(scene.camera, console, config);

				scene.Draw(config);
				if(console.active)
					console.Draw(config);
				SwapBuffers(config.hDC);
			}
        }
	}

	input.Quit();
	config.Quit();

	return config.uMsg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
    {
		case WM_DESTROY:
			input.Quit();
			config.Quit();
			break;
		case WM_CLOSE:
			input.Quit();
			config.Quit();
			break;
		case WM_CHAR:
			if(console.active)
				console.Input(wParam, config, scene);
			break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
    }

	return false;
}


LRESULT CALLBACK InitConfigProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hInitControl;

	unsigned int res;
	bool bpp;

	switch(uMsg) 
    {
	case WM_INITDIALOG:
		{
			SetWindowPos(hDlg, HWND_TOP, 320, 240, 0, 0, SWP_NOSIZE);

			switch(config.screen_width)
			{
			case 640:
				res = 0;
				break;
			case 800:
				res = 1;
				break;
			case 1024:
				res = 2;
				break;
			case 1280:
				res = 3;
				break;
			case 1600:
				res = 4;
				break;
			default:
				res = 0;
				break;
			}

			switch(config.screen_bpp)
			{
			case 16:
				bpp = false;
				break;
			case 32:
				bpp = true;
				break;
			default:
				bpp = false;
				break;
			}

			hInitControl = GetDlgItem(hDlg, IDC_RESOLUTION);
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "640x480");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "800x600");				
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "1024x768");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "1280x1024");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "1600x1200");
			SendMessage(hInitControl, CB_SETCURSEL, res, 0);

			hInitControl = GetDlgItem(hDlg, IDC_BPP);
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "16 Bpp");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "32 Bpp");
			SendMessage(hInitControl, CB_SETCURSEL, bpp, 0);

			hInitControl = GetDlgItem(hDlg, IDC_SHADOWS);
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "No");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "Projected");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "Volumetric");
			SendMessage(hInitControl, CB_SETCURSEL, config.shadows, 0);

			hInitControl = GetDlgItem(hDlg, IDC_TEXTURE_FILTERING);
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "Nearest");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "Linear");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "Mip Mapped");
			SendMessage(hInitControl, CB_SETCURSEL, config.texture_filtering, 0);

			CheckDlgButton(hDlg, IDC_BUMP_MAPPING, config.bump_mapping);
			CheckDlgButton(hDlg, IDC_FULLSCREEN, config.fullscreen);
			CheckDlgButton(hDlg, IDC_TEXTURING, config.texturing);
			CheckDlgButton(hDlg, IDC_FOG, config.fog);
			CheckDlgButton(hDlg, IDC_ANTIALIASING, config.antialiasing);
			CheckDlgButton(hDlg, IDC_GOURAUD_SHADING, config.gouraud_shading);

			break;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) 
			{
			case ID_SAVE:
				if(!config.Save())
				{
					Warning("Saving error");
					return false;
				}
				break;
			case ID_LAUNCH:
				EndDialog(config.hWnd, wParam);
				if(!config.Launch())
				{
					Warning("Launch error");
					return false;
				}
				if(!console.Init(config))
				{
					Warning("Console init error");
					return false;
				}
				if(!input.Init(config))
				{
					Warning("Input init error");
					return false;
				}
				break;
			case ID_QUIT:
				config.Quit();
				break;
			case ID_ABOUT:
				MessageBox(config.hWnd, "Ray 3D Engine 0.2a by DaRoN\nContact : daron@daron.tk", "About", MB_ICONINFORMATION | MB_OK);
				break;
			case IDC_FULLSCREEN:
				config.fullscreen = !config.fullscreen;
				break;
			case IDC_BUMP_MAPPING:
				config.bump_mapping = !config.bump_mapping;
				break;
			case IDC_TEXTURING:
				config.texturing = !config.texturing;
				break;
			case IDC_FOG:
				config.fog = !config.fog;
				break;
			case IDC_ANTIALIASING:
				config.antialiasing = !config.antialiasing;
				break;
			case IDC_GOURAUD_SHADING:
				config.gouraud_shading = !config.gouraud_shading;
				break;
			case IDC_RESOLUTION:
				hInitControl = GetDlgItem(hDlg, IDC_RESOLUTION);
				switch(SendMessage(hInitControl, CB_GETCURSEL, 0, 0))
				{
				case 0:
					config.screen_width = 640;
					config.screen_height = 480;
					break;
				case 1:
					config.screen_width = 800;
					config.screen_height = 600;
					break;
				case 2:
					config.screen_width = 1024;
					config.screen_height = 768;
					break;
				case 3:
					config.screen_width = 1280;
					config.screen_height = 1024;
					break;
				case 4:
					config.screen_width = 1600;
					config.screen_height = 1200;
					break;
				default:
					config.screen_width = 640;
					config.screen_height = 480;
					break;
				}
				break;
			case IDC_BPP:
				hInitControl = GetDlgItem(hDlg, IDC_BPP);
				switch(SendMessage(hInitControl, CB_GETCURSEL, 0, 0))
				{
				case 0:
					config.screen_bpp = 16;
					break;
				case 1:
					config.screen_bpp = 32;
					break;
				default:
					config.screen_bpp = 16;
					break;
				}
				break;
			case IDC_SHADOWS:
				hInitControl = GetDlgItem(hDlg, IDC_SHADOWS);
				config.shadows = SendMessage(hInitControl, CB_GETCURSEL, 0, 0);
				break;
			case IDC_TEXTURE_FILTERING:
				hInitControl = GetDlgItem(hDlg, IDC_TEXTURE_FILTERING);
				config.texture_filtering = SendMessage(hInitControl, CB_GETCURSEL, 0, 0);
				break;
			default:
				break;
			}
			break;
		}
	case WM_DESTROY:
		config.Quit();
		break;
	case WM_CLOSE:
		config.Quit();
		break;
	default:
		//return DefDlgProc(hDlg, uMsg, wParam, lParam);
		break;
    }

    return false;
}


