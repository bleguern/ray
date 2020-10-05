#include "Map.h"



bool Map::LoadFromDAR(DarFile file)
{
	if(!file.PosAfterTAG("name=") || !file.GetStr(name) ||
		!file.PosAfterTAG("file_type=") || !file.GetStr(file_type) ||
		!file.PosAfterTAG("file_path=")|| !file.GetStr(file_path) ||
		!file.PosAfterTAG("type=") || !file.GetStr(type) ||
		!file.PosAfterTAG("amount=") || !file.GetF(amount) ||
		!file.PosAfterTAG("u_offset=") || !file.GetF(u_offset) ||
		!file.PosAfterTAG("v_offset=") || !file.GetF(v_offset) ||
		!file.PosAfterTAG("u_tiling=") || !file.GetF(u_tiling) ||
		!file.PosAfterTAG("v_tiling=") || !file.GetF(v_tiling) ||
		!file.PosAfterTAG("blur=") || !file.GetF(blur))
	{
		return false;
	}

	return true;
}


void Map::Draw()
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

bool Map::LoadTexture(Config config)
{
	if(!strcmp(file_type, "BMP"))
	{
		return LoadBMPTexture(config);
	}
	else if(!strcmp(file_type, "JPG"))
	{
		return LoadJPGTexture(config);
	}
	else if(!strcmp(file_type, "TGA"))
	{
		return LoadTGATexture(config);
	}
	
	return false;
}


bool Map::LoadBMPTexture(Config config)
{
	AUX_RGBImageRec *image = NULL;

	if((image = auxDIBImageLoad(file_path)) == NULL)
		return false;

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, texture_id);

	switch(config.texture_filtering)
	{
	case 0:
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
			break;
		}
	case 1:
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
			break;
		}
	case 2:
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image->data);
			break;
		}
	default:
		break;
	}

	if(image)
	{
		if(image->data)
			free(image->data);

		free(image);
	}

	return true;
}


bool Map::LoadJPGTexture(Config config)
{
	return true;
}


bool Map::LoadTGATexture(Config config)
{
	/*GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};			// Uncompressed TGA Header
	GLubyte		TGAcompare[12];							// Used To Compare TGA Header
	GLubyte		header[6];							// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;							// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;								// Temporary Variable
	GLuint		type=GL_RGBA;

	FILE *file = fopen(file_path, "rb");						// Open The TGA File

	if(	file==NULL ||								// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0		||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))			// If So Read Next 6 Header Bytes
	{
		if (file == NULL)							// Did The File Even Exist? *Added Jim Strong*
			return false;							// Return False
		else
		{
			fclose(file);							// If Anything Failed, Close The File
			return false;							// Return False
		}
	}

	texture->width  = header[1] * 256 + header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	texture->width	<=0	||						// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||						// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);								// If Anything Failed, Close The File
		return false;								// Return False
	}









*/
	return true;
}