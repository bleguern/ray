#ifndef _SCENE_H_
#define _SCENE_H_

#include "Camera.h"
#include "List.h"
#include "Object.h"
#include "Config.h"




class Scene
{
	List<Object> object;             //()

	unsigned int nb_object;          //(0)
	unsigned int nb_material;        //(0)
	unsigned int nb_map;             //(0)
	unsigned int nb_mesh;            //(0)
	unsigned int nb_face;            //(0)
	unsigned int nb_light;           //(0)

	float nb_fps;                    //(0.0f)

public:

	Camera camera;

	Scene():object(),camera(),nb_object(0),nb_material(0),nb_map(0),nb_mesh(0),nb_face(0),nb_light(0),nb_fps(0.0f) {}
	~Scene() {}

	void Draw(Config);

	bool LoadObject(Config, char*);
	bool DeleteObject(unsigned short);
	bool DeleteObject(char*);

	unsigned int GetNbObject();
	unsigned int GetNbMaterial();
	unsigned int GetNbMap();
	unsigned int GetNbMesh();
	unsigned int GetNbFace();
	unsigned int GetNbLight();
	float GetNbFps();
};




#endif