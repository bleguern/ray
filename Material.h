#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Shader.h"
#include "List.h"
#include "Map.h"
#include "DarFile.h"
#include "Config.h"


class Material
{
	char* name;                      //MATERIAL_NAME # (NULL)
	char* type;                      //MATERIAL_CLASS # (NULL)
	
	Shader shader;
	
	List<Map> map;                        //MAP_# (NULL)

	unsigned int nb_map;

public:
	Material():name(NULL),type(NULL),shader(),map(),nb_map(0) {}
	~Material() {}

	bool LoadFromDAR(DarFile, Config);

	void Draw(Config);

	unsigned int GetNbMap();
};

static Material material_tmp;



#endif