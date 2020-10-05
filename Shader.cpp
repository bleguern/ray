#include "Shader.h"


bool Shader::LoadFromDAR(DarFile file)
{
	if(!file.PosAfterTAG("type=") || !file.GetStr(type) ||
		!file.PosAfterTAG("ambient=") || !file.Get4F(ambient) ||
		!file.PosAfterTAG("diffuse=") || !file.Get4F(diffuse) ||
		!file.PosAfterTAG("specular=") || !file.Get4F(specular) ||
		!file.PosAfterTAG("transparency=") || !file.GetF(transparency) ||
		!file.PosAfterTAG("shine_strength=") || !file.GetF(shine_strength) ||
		!file.PosAfterTAG("shine=") || !file.GetF(shine))
	{
		return false;
	}

	return true;
}



void Shader::Draw(bool map)
{
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	if(!map)
		glColor3f(diffuse.x, diffuse.y, diffuse.z);
}
