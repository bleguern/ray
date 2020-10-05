#include "DarFile.h"

//OK
bool DarFile::Open()
{
	if(NULL == (input_fd = fopen(input_path, "r")))
		return false;

	if(fseek(input_fd, 0L, SEEK_SET))
		return false;

	if(fgetpos(input_fd, &pos))
		return false;

	return true;
}



bool DarFile::Close()
{
	if(fclose(input_fd))
		return false;

	return true;
}

bool DarFile::GetInt(int& number)
{
	if(fscanf(input_fd, "%i", &number) != 1)
		return false;

	return true;
}

bool DarFile::GetUInt(unsigned int& number)
{
	if(fscanf(input_fd, "%i", &number) != 1)
		return false;

	return true;
}

bool DarFile::Get3UInt(UInt3& vector)
{
	if(fscanf(input_fd, "%i %i %i", &vector.Num[0], &vector.Num[1], &vector.Num[2]) != 3)
		return false;

	return true;
}

bool DarFile::GetF(GLfloat& number)
{
	if(fscanf(input_fd, "%f", &number) != 1)
		return false;

	return true;
}

bool DarFile::Get3F(Vector3& vector)
{
	if(fscanf(input_fd, "%f %f %f", &vector.x, &vector.y, &vector.z) != 3)
		return false;

	return true;
}

bool DarFile::Get4F(Vector4& vector)
{
	if(fscanf(input_fd, "%f %f %f", &vector.x, &vector.y, &vector.z) != 3)
		return false;
	
	vector.t = 1.0f;

	return true;
}

bool DarFile::GetStr(char * &str)
{
	int i = 0;
	char c;

	if(fgetpos(input_fd, &pos))
		return false;

	while((!feof(input_fd)) && ((c != '<') && (c != '\n')))
	{
		fscanf(input_fd, "%c", &c);
		i++;
	}

	if(fsetpos(input_fd, &pos))
		return false;

	if(NULL == (str = (char*)malloc(i)))
		return false;

	if(fgets(str, i, input_fd) == NULL)
		return false;

	return true;
}


int DarFile::CountTAG(char* str, bool pass)
{
	if((strlen(str)) < 2)
		return 0;

	char *tmp;
	if(NULL == (tmp = (char*)malloc(strlen(str)-4)))
		return -1;

	int count = 0;

	if(pass)
	{
		if(fseek(input_fd, 0L, SEEK_SET))
			return -1;
	}
	else
	{
		if(fgetpos(input_fd, &pos))
			return false;
	}


	while(!feof(input_fd))
	{
		fscanf(input_fd, "%c", &tmp[0]);

		if(pass)
		{
			if(tmp[0] == str[0])
			{
				fgets(tmp+1, strlen(str), input_fd);

				if(!strcmp(tmp, str))
				{
					count++;
				}
			}
		}
		else
		{
			if(tmp[0] == '<')
			{
				if(!ExitStream())
					return false;
			}
			else if(tmp[0] == '>')
			{
				if(fsetpos(input_fd, &pos))
					return false;
				
				return count;
			}
			else if(tmp[0] == str[0])
			{
				fgets(tmp+1, strlen(str), input_fd);

				if(!strcmp(tmp, str))
				{
					count++;
				}
			}
		}
	}

	if(pass)
	{
		if(fseek(input_fd, 0L, SEEK_SET))
			return -1;
	}
	else
	{
		if(fsetpos(input_fd, &pos))
			return false;
	}

	return count;
}


bool DarFile::EnterStream()
{
	char c;

	fscanf(input_fd, "%c", &c);
	if(c != '<')
		return false;

	return true;
}

bool DarFile::PosAfterTAG(char *str)
{
	char *tmp;
	if(NULL == (tmp = (char*)malloc(strlen(str)-4)))
		return false;

	while(!feof(input_fd))
	{
		fscanf(input_fd, "%c", &tmp[0]);

		if(tmp[0] == '<')
		{
			if(!ExitStream())
				return false;
		}
		else if(tmp[0] == '>')
		{
			if(fgetpos(input_fd, &pos))
				return false;

			pos -= 2;

			if(fsetpos(input_fd, &pos))
				return false;
		}
		else if(tmp[0] == str[0])
		{
			fgets(tmp+1, strlen(str), input_fd);

			if(!strcmp(tmp, str))
				return true;
		}
	}

	return false;
}


bool DarFile::ExitStream()
{
	int depth = 1;
	char c;

	while(!feof(input_fd))
	{
		fscanf(input_fd, "%c", &c);

		if(c == '<')
		{
			depth++;
		}
		else if(c == '>')
		{
			depth--;
		}

		if(!depth)
			return true;
	}

	return false;
}


bool DarFile::GetNormal(Vector3* &vector, VertexNormal* &vertexnormal, unsigned int nb_face)
{
	unsigned int i;

	if(NULL == (vector = new Vector3[nb_face]))
		return false;

	if(NULL == (vertexnormal = new VertexNormal[nb_face]))
		return false;

	for(i = 0; i < nb_face; i++)
	{
		if(fscanf(input_fd, "%f %f %f	%f %f %f	%f %f %f	%f %f %f\n",
			&vector[i].x, &vector[i].y, &vector[i].z,
			&vertexnormal[i].Vertex[0].x, &vertexnormal[i].Vertex[0].y, &vertexnormal[i].Vertex[0].z,
			&vertexnormal[i].Vertex[1].x, &vertexnormal[i].Vertex[1].y, &vertexnormal[i].Vertex[1].z,
			&vertexnormal[i].Vertex[2].x, &vertexnormal[i].Vertex[2].y, &vertexnormal[i].Vertex[2].z) != 12)
		{
			return false;
		}
	}

	return true;
}

bool DarFile::GetVertex(Vector3* &vector, unsigned int nb_vertex)
{
	unsigned int i;
	if(NULL == (vector = new Vector3[nb_vertex]))
		return false;

	for(i = 0; i < nb_vertex; i++)
	{
		if(fscanf(input_fd, "%f %f %f\n", &vector[i].x, &vector[i].y, &vector[i].z) != 3)
			return false;
	}

	return true;
}


bool DarFile::GetVertexFaceID(UInt3* &uint, unsigned int nb_face)
{
	unsigned int i;
	if(NULL == (uint = new UInt3[nb_face]))
		return false;

	for(i = 0; i < nb_face; i++)
	{
		if(fscanf(input_fd, "%i %i %i\n", &uint[i].Num[0], &uint[i].Num[1], &uint[i].Num[2]) != 3)
			return false;
	}

	return true;
}

bool DarFile::GetVertexMapCoord(Vector3* &vector, unsigned int nb_vertex_map_coord)
{
	unsigned int i;
	if(NULL == (vector = new Vector3[nb_vertex_map_coord]))
		return false;

	for(i = 0; i < nb_vertex_map_coord; i++)
	{
		if(fscanf(input_fd, "%f %f %f\n", &vector[i].x, &vector[i].y, &vector[i].z) != 3)
			return false;
	}

	return true;
}

bool DarFile::GetFaceMapCoordID(UInt3* &uint, unsigned int nb_face_map_coord)
{
	unsigned int i;
	if(NULL == (uint = new UInt3[nb_face_map_coord]))
		return false;

	for(i = 0; i < nb_face_map_coord; i++)
	{
		if(fscanf(input_fd, "%i %i %i\n", &uint[i].Num[0], &uint[i].Num[1], &uint[i].Num[2]) != 3)
			return false;
	}

	return true;
}

/*bool DarFile::GoStart()
{
	if(fseek(input_fd, 0L, SEEK_SET))
		return false;

	if(fgetpos(input_fd, &pos))
		return false;

	return true;
}*/