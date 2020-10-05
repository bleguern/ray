#ifndef _CAMERA_H_
#define _CAMERA_H_


#include "3DMath.h"

class Camera
{
public:

	Vector3 position;           //(0.0f, 0.0f, 0.0f)
	Vector3 direction;          //(0.0f, 0.0f, 0.0f)
	Vector3 rotation;           //(0.0f, 0.0f, 0.0f)


	Camera():position(0.0f, 0.0f, 200.0f),direction(0.0f, 0.0f, 0.0f),rotation(0.0f, 0.0f, 0.0f) {}
	~Camera() {}
};



#endif