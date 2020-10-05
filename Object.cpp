#include "Object.h"


bool Object::LoadFromDAR(Config config)
{
	unsigned int i;
	int dar_tag, nb_material, nb_mesh, nb_light;

	if(!file.Open())
		return false;

	if(!file.PosAfterTAG("#DAR_FILE") || !file.GetInt(dar_tag) ||
		(dar_tag != DAR_CURRENT_VERSION) ||
		((nb_material = file.CountTAG("material_", true)) < 0) ||
		((nb_mesh = file.CountTAG("mesh_", true)) < 0) ||
		((nb_light = file.CountTAG("light_", true)) < 0) ||
		!file.PosAfterTAG("name=") || !file.GetStr(name))
	{
		return false;
	}

	if(nb_material)
	{
		for(i = 0; i < (unsigned int)nb_material; i++)
		{
			char *tmp, id[3];
			if(NULL == (tmp = (char*)malloc(strlen("material_")+3)))
				return false;

			strcpy(tmp, "material_");
			sprintf(id, "%i", i);
			strcat(tmp, id);
			
			if(!file.PosAfterTAG(tmp) || !file.EnterStream())
				return false;

				material_tmp = *new Material();

				if(material_tmp.LoadFromDAR(file, config))
				{
					if(!material.Add(material_tmp))
						return false;
				}

			if(!file.ExitStream())
				return false;
		}
	}

	if(nb_mesh)
	{
		display_list = glGenLists(nb_mesh);

		for(i = 0; i < (unsigned int)nb_mesh; i++)
		{
			char *tmp, id[3];
			if(NULL == (tmp = (char*)malloc(strlen("mesh_")+3)))
				return false;

			strcpy(tmp, "mesh_");
			sprintf(id, "%i", i);
			strcat(tmp, id);
			
			if(!file.PosAfterTAG(tmp) || !file.EnterStream())
				return false;

				mesh_tmp = *new Mesh();

				if(mesh_tmp.LoadFromDAR(file, i))
				{
					mesh_tmp.BuildList(config, display_list);
					
					if(!mesh.Add(mesh_tmp))
						return false;
				}

			if(!file.ExitStream())
				return false;
		}
	}

	if(nb_light)
	{
		for(i = 0; i < (unsigned int)nb_light; i++)
		{
			char *tmp, id[3];
			if(NULL == (tmp = (char*)malloc(strlen("light_")+3)))
					return false;

			strcpy(tmp, "light_");
			sprintf(id, "%i", i);
			strcat(tmp, id);
			
			if(!file.PosAfterTAG(tmp) || !file.EnterStream())
				return false;

				light_tmp = *new Light(i);

				if(light_tmp.LoadFromDAR(file))
				{
					light_tmp.Enable();
					
					if(!light.Add(light_tmp))
						return false;
				}

			if(!file.ExitStream())
				return false;
		}
	}

	return file.Close();
}



void Object::Draw(Config config)
{
	unsigned int i;

	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	glTranslatef(position.x, position.y, position.z);

	for(i = 0; i < light.GetNbNode(); i++)
	{
		light[i].Draw();
	}

	for(i = 0; i < mesh.GetNbNode(); i++)
	{
		material[mesh[i].GetIdMaterial()].Draw(config);
		mesh[i].Draw(display_list);
	}
}


void Object::Move(Vector3 Position, Vector3 Rotation)
{
	position += Position;
	rotation += Rotation;
}


char* Object::GetName()
{
	return name;
}


unsigned int Object::GetNbMaterial()
{
	return nb_material;
}

unsigned int Object::GetNbMap()
{
	return nb_map;
}

unsigned int Object::GetNbMesh()
{
	return nb_mesh;
}

unsigned int Object::GetNbFace()
{
	return nb_face;
}

unsigned int Object::GetNbLight()
{
	return nb_light;
}