#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "3DMath.h"
#include "DarFile.h"
#include "Config.h"


#define MAX_OPENGL_LIGHTS            8

class Light
{
	unsigned int id;

	char* name;                      //NODE_NAME #

	char* type;                      //LIGHT_TYPE # (NULL)
	
	Vector4 position;                //TM_POS # # # (0.0f, 0.0f, 0.0f, 1.0f)

	Vector4 color;                   //LIGHT_COLOR # # # (1.0f, 1.0f, 1.0f, 1.0f)
	
	GLfloat intensity;               //LIGHT_INTENS # (1.0f)
	
	//Not in use for the moment
	char* att_type;                  //(NULL)
	GLfloat att_power;               //(0.0f)
	
	Vector3 direction;               //TM_POS # # # (0.0f, 0.0f, 0.0f)
	
	GLfloat cut_off;                 //LIGHT_HOTSPOT # (0.0f)

	char* shadows;                   //LIGHT_SHADOWS # (NULL)

public:

	Light():id(0),name(NULL),type(NULL),color(1.0f, 1.0f, 1.0f, 1.0f),
		position(0.0f, 0.0f, 0.0f, 1.0f),intensity(1.0f),att_type(NULL),att_power(0.0f),
		direction(0.0f, 0.0f, 0.0f),cut_off(0.0f),shadows(NULL) {}
	Light(unsigned int Id):id(Id),name(NULL),type(NULL),color(1.0f, 1.0f, 1.0f, 1.0f),
		position(0.0f, 0.0f, 0.0f, 1.0f),intensity(1.0f),att_type(NULL),att_power(0.0f),
		direction(0.0f, 0.0f, 0.0f),cut_off(0.0f),shadows(NULL) {}
	~Light() {}

	bool LoadFromDAR(DarFile);

	void Move(Vector4);
	void Enable();
	void Disable();
	void Draw();
};

static Light light_tmp;




#endif