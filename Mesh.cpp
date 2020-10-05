#include "Mesh.h"



//OK alpha
bool Mesh::LoadFromDAR(DarFile file, unsigned int Id)
{
	id = Id;

	if(!file.PosAfterTAG("name=") || !file.GetStr(name) ||
		!file.PosAfterTAG("weight=") || !file.GetF(weight) ||
		!file.PosAfterTAG("nb_vertex=") || !file.GetUInt(nb_vertex) ||
		!nb_vertex ||
		!file.PosAfterTAG("nb_vertex_map_coord=") || !file.GetUInt(nb_vertex_map_coord) ||
		!file.PosAfterTAG("nb_face=") || !file.GetUInt(nb_face) ||
		!nb_face ||
		!file.PosAfterTAG("nb_face_map_coord=") || !file.GetUInt(nb_face_map_coord) ||
		!file.PosAfterTAG("id_material=") || !file.GetInt(id_material))
	{
		return false;
	}


	if(!file.PosAfterTAG("vertex") || !file.EnterStream() ||
		!file.GetVertex(vertex, nb_vertex) || !file.ExitStream())
	{
		return false;
	}

	if(nb_vertex_map_coord)
	{
		if(!file.PosAfterTAG("vertex_map_coord") || !file.EnterStream() ||
			!file.GetVertexMapCoord(vertex_map_coord, nb_vertex_map_coord) || !file.ExitStream())
		{
			return false;
		}
	}


	if(!file.PosAfterTAG("face") || !file.EnterStream() ||
		!file.GetVertexFaceID(face_vertex_id, nb_face) || !file.ExitStream())
	{
		return false;
	}



	if(nb_face_map_coord)
	{
		if(!file.PosAfterTAG("face_map_coord") || !file.EnterStream() ||
			!file.GetFaceMapCoordID(face_map_coord_id, nb_face_map_coord) || !file.ExitStream())
		{
			return false;
		}
	}


	if(!file.PosAfterTAG("normal") || !file.EnterStream() ||
		!file.GetNormal(face_normal, vertex_normal, nb_face) ||
		!file.ExitStream())
	{
		return false;
	}

	return true;
}

void Mesh::BuildList(Config config, unsigned int display_list)
{
	unsigned int i, j;

	glNewList(display_list+id, GL_COMPILE);

	glLoadName(id+1);

	glBegin(GL_TRIANGLES);

		if(config.gouraud_shading)
		{
			if(nb_vertex_map_coord && nb_face_map_coord)
			{
				for(i = 0; i < nb_face; i++)
				{
					for(j = 0; j < 3; j++)
					{
						glNormal3f(vertex_normal[i].Vertex[j].x, vertex_normal[i].Vertex[j].y, vertex_normal[i].Vertex[j].z);
						glTexCoord3f(vertex_map_coord[face_map_coord_id[i].Num[j]].x, vertex_map_coord[face_map_coord_id[i].Num[j]].y, vertex_map_coord[face_map_coord_id[i].Num[j]].z);
						glVertex3f(vertex[face_vertex_id[i].Num[j]].x, vertex[face_vertex_id[i].Num[j]].y, vertex[face_vertex_id[i].Num[j]].z);
					}
				}
			}
			else
			{
				for(i = 0; i < nb_face; i++)
				{
					for(j = 0; j < 3; j++)
					{
						glNormal3f(vertex_normal[i].Vertex[j].x, vertex_normal[i].Vertex[j].y, vertex_normal[i].Vertex[j].z);
						glVertex3f(vertex[face_vertex_id[i].Num[j]].x, vertex[face_vertex_id[i].Num[j]].y, vertex[face_vertex_id[i].Num[j]].z);
					}
				}
			}
		}
		else
		{
			if(nb_vertex_map_coord && nb_face_map_coord)
			{
				for(i = 0; i < nb_face; i++)
				{
					glNormal3f(face_normal[i].x, face_normal[i].y, face_normal[i].z);

					for(j = 0; j < 3; j++)
					{
						glTexCoord3f(vertex_map_coord[face_map_coord_id[i].Num[j]].x, vertex_map_coord[face_map_coord_id[i].Num[j]].y, vertex_map_coord[face_map_coord_id[i].Num[j]].z);
						glVertex3f(vertex[face_vertex_id[i].Num[j]].x, vertex[face_vertex_id[i].Num[j]].y, vertex[face_vertex_id[i].Num[j]].z);
					}
				}
			}
			else
			{
				for(i = 0; i < nb_face; i++)
				{
					glNormal3f(face_normal[i].x, face_normal[i].y, face_normal[i].z);

					for(j = 0; j < 3; j++)
					{
						glVertex3f(vertex[face_vertex_id[i].Num[j]].x, vertex[face_vertex_id[i].Num[j]].y, vertex[face_vertex_id[i].Num[j]].z);
					}
				}
			}
		}

	glEnd();

	glEnd();

	glEndList();
}


void Mesh::Draw(unsigned int display_list)
{
	glCallList(display_list+id);
}

int Mesh::GetIdMaterial()
{
	return id_material;
}


unsigned int Mesh::GetNbFace()
{
	return nb_face;
}