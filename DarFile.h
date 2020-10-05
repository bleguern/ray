#ifndef _DARFILE_H_
#define _DARFILE_H_

#include "3DMath.h"

class DarFile
{
	FILE *input_fd;
	char *input_path;
	fpos_t pos;

public:
	DarFile():input_fd(NULL),input_path(NULL),pos(0) {}
	DarFile(char *file_path):input_fd(NULL),input_path(NULL),pos(0)
	{
		input_path = (char*)malloc(strlen(file_path)-4);
		input_path = file_path;
	}
	~DarFile() {}

	//NEW!!!
	bool Open();
	bool Close();

	//bool GoStart();

	bool PosAfterTAG(char*);
	int CountTAG(char*, bool);

	bool GetInt(int&);
	bool GetUInt(unsigned int&);
	bool Get3UInt(UInt3&);
	bool GetF(GLfloat&);
	bool Get3F(Vector3&);
	bool Get4F(Vector4&);
	bool GetStr(char*&);

	bool EnterStream();
	bool ExitStream();

	bool GetVertex(Vector3*&, unsigned int);
	bool GetVertexMapCoord(Vector3*&, unsigned int);
	bool GetVertexFaceID(UInt3*&, unsigned int);
	bool GetFaceMapCoordID(UInt3*&, unsigned int);
	bool GetNormal(Vector3*&, VertexNormal*&, unsigned int);
};


#endif