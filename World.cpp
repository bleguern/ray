#include "World.h"


unsigned int World::ReturnNbFace()
{
	return nb_face;
}

unsigned int World::ReturnNbMesh()
{
	return nb_mesh;
}

unsigned int World::ReturnNbLight()
{
	return nb_light;
}



bool World::Load(char* file_name)
{
	object.LoadFromDAR();






	return true;
}









void World::Draw(Config config)
{
	object.Draw(config);





}