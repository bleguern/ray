#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_


#include "Map.h"


class Heightmap
{

	Map heightmap;
	Map* texture;                 //(NULL)

	unsigned int nb_texture;      //(0)

public:

	Heightmap():texture(NULL),nb_texture(0) {}
	~Heightmap()
	{
		if(texture)
			delete [] texture;
	}

	bool Load();
	void Draw(Config);
};














#endif