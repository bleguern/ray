#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "DarFile.h"
#include "List.h"
#include "Mesh.h"
#include "Material.h"
#include "Light.h"
#include "Config.h"


class Object
{
	char* name;                      //SCENE_FILENAME # (NULL)

	DarFile file;
	
	List<Mesh> mesh;                 //GEOMOBJECT (NULL)
	List<Material> material;         //MATERIAL # (NULL)
	List<Light> light;               //LIGHTOBJECT (NULL)
	
	//unsigned int id_frame;         //(0)
	//unsigned int nb_frame;         //SCENE_LASTFRAME # (1)

	GLfloat weight;                  //(0.0f)

	Vector3 position;
	Vector3 rotation;

	unsigned int display_list;

	unsigned int nb_material;
	unsigned int nb_map;
	unsigned int nb_mesh;
	unsigned int nb_face;
	unsigned int nb_light;

public:
	Object():name(NULL),file(),mesh(),material(),light(),/*id_frame(0),nb_frame(1),*/weight(0.0f),position(0.0f, 0.0f, 0.0f),rotation(0.0f, 0.0f, 0.0f),display_list(0),nb_material(0),nb_map(0),nb_mesh(0),nb_face(0),nb_light(0) {}
	Object(char *object_path):name(NULL),file(object_path),mesh(),material(),light(),/*id_frame(0),nb_frame(1),*/weight(0.0f),position(0.0f, 0.0f, 0.0f),rotation(0.0f, 0.0f, 0.0f),display_list(0),nb_material(0),nb_map(0),nb_mesh(0),nb_face(0),nb_light(0) {}
	~Object() {}

	bool LoadFromDAR(Config);
	void Draw(Config);
	void Move(Vector3, Vector3);

	char* GetName();
	unsigned int GetNbMaterial();
	unsigned int GetNbMap();
	unsigned int GetNbMesh();
	unsigned int GetNbFace();
	unsigned int GetNbLight();
};

static Object object_tmp;


#endif