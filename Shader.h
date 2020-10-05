#ifndef _SHADER_H_
#define _SHADER_H_

#include "3DMath.h"
#include "DarFile.h"

class Shader
{
	char* type;                      //MATERIAL_SHADING # (NULL)
	
	Vector4 ambient;                 //MATERIAL_AMBIENT # # # (1.0f, 1.0f, 1.0f, 1.0f)
	Vector4 diffuse;                 //MATERIAL_DIFFUSE # # # (1.0f, 1.0f, 1.0f, 1.0f)
	Vector4 specular;                //MATERIAL_SPECULAR # # # (1.0f, 1.0f, 1.0f, 1.0f)

	GLfloat shine;                   //MATERIAL_SHINE # (0.0f)
	GLfloat shine_strength;          //MATERIAL_SHINESTRENGTH # (0.0f)
	GLfloat transparency;            //MATERIAL_TRANSPARENCY # (0.0f)

public:
	Shader():type(NULL),ambient(1.0f, 1.0f, 1.0f, 1.0f),diffuse(1.0f, 1.0f, 1.0f, 1.0f),
		specular(1.0f, 1.0f, 1.0f, 1.0f),transparency(0.0f),shine_strength(0.0f),shine(0.0f) {}
	~Shader() {}

	bool LoadFromDAR(DarFile);

	void Draw(bool);
};


#endif