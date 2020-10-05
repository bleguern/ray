#ifndef _INPUT_H_
#define _INPUT_H_

#include "Ray.h"
#include "Camera.h"
#include "Console.h"
#include "Config.h"

class Input
{

	LPDIRECTINPUT8			object;
	LPDIRECTINPUTDEVICE8	keyboard;
	LPDIRECTINPUTDEVICE8	mouse;

public:

	Input() {}
	~Input() {}

	bool Init(Config&);
	void Quit();

	bool Event(Camera&, Console&, Config&);
};



#endif