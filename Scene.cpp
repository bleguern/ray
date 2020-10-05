#include "Scene.h"


void Scene::Draw(Config config)
{
	unsigned int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(camera.position.x, camera.position.y, camera.position.z,
			  camera.direction.x, camera.direction.y, camera.direction.z,
		      0, 1.0f, 0);

	glPushMatrix();
		glRotatef(camera.rotation.x, 1.0f, 0.0f, 0.0f);
		glRotatef(camera.rotation.y, 0.0f, 1.0f, 0.0f);
		glRotatef(camera.rotation.z, 0.0f, 0.0f, 1.0f);

		if(object.GetNbNode())
		{
			for(i = 0; i < object.GetNbNode(); i++)
			{
				object[i].Draw(config);
			}
		}

	glPopMatrix();
}

bool Scene::LoadObject(Config config, char* path)
{
	char* tmp;
	
	if(NULL == (tmp = (char*)malloc(strlen(path)-4)))
		return false;

	strcpy(tmp, path);
	strcat(tmp, ".dar");

	object_tmp = *new Object(tmp);

	if(object_tmp.LoadFromDAR(config))
	{
		return object.Add(object_tmp);
	}

	return false;
}

bool Scene::DeleteObject(unsigned short id)
{
	if(!object.GetNbNode())
		return false;

	return object.Delete(id);
}

bool Scene::DeleteObject(char *name)
{
	unsigned int i;

	if(!object.GetNbNode())
		return false;

	for(i = 0; i < object.GetNbNode(); i++)
	{
		if(!strcmp(object[i].GetName(), name))
			return object.Delete(i);
	}

	return true;
}


unsigned int Scene::GetNbObject()
{
	return nb_object;
}

unsigned int Scene::GetNbMaterial()
{
	return nb_material;
}

unsigned int Scene::GetNbMap()
{
	return nb_map;
}

unsigned int Scene::GetNbMesh()
{
	return nb_mesh;
}

unsigned int Scene::GetNbFace()
{
	return nb_face;
}

unsigned int Scene::GetNbLight()
{
	return nb_light;
}

float Scene::GetNbFps()
{
	return nb_fps;
}
