#include "Console.h"


void Console::PositionText(int x, int y, Config config)
{
	glPushAttrib(GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);

	glMatrixMode( GL_PROJECTION );						// Set our matrix to our projection matrix
	glPushMatrix();										// Push on a new matrix to work with
	glLoadIdentity();									// reset the matrix
	glMatrixMode( GL_MODELVIEW );						// Set our matrix to our model view matrix
	glPushMatrix();										// Push on a new matrix to work with
	glLoadIdentity();									// Reset that matrix

	y = config.screen_height - FONT_HEIGHT - y;

	glViewport(x - 1, y - 1, 0, 0);

	glRasterPos4f(0, 0, 0, 1);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glPopAttrib();
}

void Console::glDrawText(int x, int y, const char *strString, Config config)
{
	char strText[MAX_CHARS];

	if(strString == "")
		return;

	sprintf(strText, strString);

	PositionText(x, y, config);

	glPushAttrib(GL_LIST_BIT);

	glListBase(FontListID);

	glCallLists(strlen(strText), GL_UNSIGNED_BYTE, strText);

	glPopAttrib();
}



bool Console::Init(Config config)
{
	FontListID = CreateOpenGLFont("Arial", FONT_HEIGHT, config);

	return true;
}

unsigned int Console::CreateOpenGLFont(LPSTR strFontName, int height, Config config)
{
	UINT	fontListID = 0;
	HFONT	hFont;

	fontListID = glGenLists(MAX_CHARS);

	hFont = CreateFont(	height,
						0,
						0,
						0,
						FW_BOLD,
						false,
						false,
						false,
						ANSI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FF_DONTCARE|DEFAULT_PITCH,
						strFontName);

	hOldFont = (HFONT)SelectObject(config.hDC, hFont);

	wglUseFontBitmaps(config.hDC, 0, MAX_CHARS - 1, fontListID);

	return fontListID;
}


void Console::Input(WPARAM wParam, Config& config, Scene& scene)
{
	switch(wParam)
	{
	case VK_RETURN:
		Execute(config, scene);
		break;
	case VK_BACK:
		if(count > 0)
		{
			count--;
			buffer[count] = '\0';
		}
		break;
	case VK_DELETE:
		ClearBuffer();
		break;
	default:
		TCHAR ch = (TCHAR) wParam;
		buffer[count] = ch;
		count++;
		break;
	}
}


void Console::Draw(Config config)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);					

	glPushMatrix();

	glLoadIdentity();

	glOrtho(0, config.screen_width, config.screen_height, 0, 0, 1);

	glMatrixMode(GL_MODELVIEW);								

	glLoadIdentity();

	//DRAWING
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);

    glColor4f(1, 1, 0, 1);
	glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(0, 70);
		glVertex2i(config.screen_width, 70);
		glVertex2i(config.screen_width, 0);
	glEnd();

	glDisable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);

	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glColor4f(0, 0, 1, 1);
	glDrawText(3, FONT_HEIGHT, ">", config);
	glDrawText(20, FONT_HEIGHT, buffer, config);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void Console::Quit(Config config)
{
	glDeleteLists(FontListID, MAX_CHARS);
	SelectObject(config.hDC, hOldFont);
}

void Console::Execute(Config& config, Scene& scene)
{
	char command[MAX_CHARS] = "";
	char arg[MAX_CHARS] = "";
	int id;

	sscanf(buffer, "%s", command);

	if(!strcmp(LOAD_OBJECT, command))
	{
		sscanf(buffer+strlen(command), "%s", arg);
		scene.LoadObject(config, arg);
	}
	else if (!strcmp(DELETE_OBJECT_BY_ID, command))
	{
		sscanf(buffer+strlen(command), "%i", &id);
		scene.DeleteObject(id);
	}
	else if(!strcmp(DELETE_OBJECT_BY_NAME, command))
	{
		sscanf(buffer+strlen(command), "%s", arg);
		scene.DeleteObject(arg);
	}
	else if(!strcmp(BUMP_MAPPING, command))
	{
		config.bump_mapping = !config.bump_mapping;
	}
	else if(!strcmp(FOG, command))
	{
		config.fog = !config.fog;
	}
	else if(!strcmp(ANTIALIASING, command))
	{
		config.antialiasing = !config.antialiasing;
	}
	else if(!strcmp(GOURAUD_SHADING, command))
	{
		config.gouraud_shading = !config.gouraud_shading;
	}
	else if(!strcmp(TEXTURING, command))
	{
		config.texturing = !config.texturing;
	}
	else if(!strcmp(SHADOWS, command))
	{
		sscanf(buffer+strlen(command), "%i", &id);
		if((id > -1) && (id < 3))
		{
			config.shadows = id;
		}
	}
	else if(!strcmp(TEXTURE_FILTERING, command))
	{
		sscanf(buffer+strlen(command), "%i", &id);
		if((id > -1) && (id < 3))
		{
			config.texture_filtering = id;
		}
	}
	else if(!strcmp(SAVE_CONFIG, command))
	{
		config.Save();
	}

	ClearBuffer();
}



void Console::ClearBuffer()
{
	unsigned int i;

	for(i = 0; i < MAX_CHARS; i++)
	{
		buffer[i] = '\0';
	}

	count = 0;
}