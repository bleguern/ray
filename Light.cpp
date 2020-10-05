#include "Light.h"


bool Light::LoadFromDAR(DarFile file)
{
	if(!file.PosAfterTAG("name=") || !file.GetStr(name) ||
		!file.PosAfterTAG("type=") || !file.GetStr(type) ||
		!file.PosAfterTAG("shadows=") || !file.GetStr(shadows) ||
		!file.PosAfterTAG("position=") || !file.Get4F(position) ||
		!file.PosAfterTAG("color=") || !file.Get4F(color) ||
		!file.PosAfterTAG("intensity=") || !file.GetF(intensity))
	{
		return false;
	}

	if(!strcmp(type, "Target"))
	{
		if(!file.PosAfterTAG("direction=") || !file.Get3F(direction) ||
			!file.PosAfterTAG("cut_off=") || !file.GetF(cut_off))
		{
			return false;
		}
	}

	return true;
}


void Light::Move(Vector4 Position)
{
	position = Position;

	glLightfv(GL_LIGHT0 + id, GL_POSITION, position);
}




void Light::Enable()
{
	glLightfv(GL_LIGHT0 + id, GL_POSITION, position);
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, color);

	glEnable(GL_LIGHT0 + id);
}


void Light::Disable()
{
	glDisable(GL_LIGHT0 + id);
}


void Light::Draw()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPointSize(4.0f);

	glBegin(GL_POINTS);
		glColor3f(color.x, color.y, color.z);
		glVertex3f(position.x, position.y, position.z);
	glEnd();

	glPointSize(1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}