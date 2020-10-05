#include "Material.h"

//OK alpha
bool Material::LoadFromDAR(DarFile file, Config config)
{
	unsigned int i;
	int nb_map;

	if(((nb_map = file.CountTAG("map_", false)) < 0) ||
		!file.PosAfterTAG("name=") || !file.GetStr(name) ||
		!file.PosAfterTAG("type=") || !file.GetStr(type))
	{
		return false;
	}

	if(!file.PosAfterTAG("shader") || !file.EnterStream() ||
		!shader.LoadFromDAR(file) || !file.ExitStream())
	{
		return false;
	}


	if(nb_map)
	{
		for(i = 0; i < (unsigned int)nb_map; i++)
		{
			char *tmp, id[3];
			if(NULL == (tmp = (char*)malloc(strlen("map_")+3)))
				return false;

			strcpy(tmp, "map_");
			sprintf(id, "%i", i);
			strcat(tmp, id);
			
			if(!file.PosAfterTAG(tmp) || !file.EnterStream())
				return false;

				map_tmp = *new Map();

				if(map_tmp.LoadFromDAR(file))
				{
					if(!map_tmp.LoadTexture(config) || !map.Add(map_tmp))
						return false;
				}

			if(!file.ExitStream())
				return false;
		}
	}

	return true;
}

void Material::Draw(Config config)
{
	unsigned int i;

	if(map.GetNbNode())
	{
		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		shader.Draw(true);
	}
	else
	{
		glEnable(GL_COLOR_MATERIAL);
		glDisable(GL_TEXTURE_2D);
		shader.Draw(false);

		for(i = 0; i < map.GetNbNode(); i++)
		{
			map[i].Draw();
		}
	}
}


unsigned int Material::GetNbMap()
{
	return nb_map;
}