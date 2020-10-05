#include "Input.h"


bool Input::Init(Config& config)
{
	DIPROPDWORD dipdw;

	if(DirectInput8Create(config.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&object, NULL) < 0)
		return false;

	if((object->CreateDevice(GUID_SysKeyboard, &keyboard, NULL) < 0) ||
		(keyboard->SetDataFormat(&c_dfDIKeyboard) < 0) ||
		(keyboard->SetCooperativeLevel(config.hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) < 0) ||
		(keyboard->Acquire() < 0))
	{
		return false;
	}

	if((object->CreateDevice(GUID_SysMouse, &mouse, NULL) < 0) ||
		(mouse->SetDataFormat(&c_dfDIMouse) < 0) ||
		(mouse->SetCooperativeLevel(config.hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND) < 0))
	{
		return false;
	}

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;
	
	if((mouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph) < 0) || (mouse->Acquire() < 0))
		return false;

	return true;
}



void Input::Quit()
{
	if(object)
	{
		if(keyboard)
		{
			keyboard->Unacquire();
			keyboard->Release();
			keyboard = NULL;
		}

		if(mouse)
		{
			mouse->Unacquire();
			mouse->Release();
			mouse = NULL;
		}

		object->Release();
		object = NULL;
	}
}


bool Input::Event(Camera& camera, Console& console, Config& config)
{
	unsigned char buffer[MAX_CHARS];
	DIMOUSESTATE mouse_state;

	if((keyboard->GetDeviceState(sizeof(buffer), (LPVOID)&buffer) < 0) ||
		(mouse->GetDeviceState(sizeof(mouse_state), (LPVOID)&mouse_state) < 0))
	{
		return false;
	}

	if(buffer[DIK_TAB] & 0x80)
	{
		console.active = !console.active;
	}
	else if(buffer[DIK_ESCAPE] & 0x80)
	{
		config.Quit();
	}

	if(mouse_state.rgbButtons[0] & 0x80)
	{
		if(mouse_state.lX)
		{
			camera.position.z += mouse_state.lY/5;
		}
	}
	else
	{
		if(mouse_state.lX)
		{
			camera.rotation.y += mouse_state.lX/2;
		}
		
		if(mouse_state.lY)
		{
			camera.rotation.x += mouse_state.lY/2;
		}

		if(mouse_state.lZ)
		{
			camera.rotation.z += mouse_state.lZ/2;
		}
	}

	return true;
}