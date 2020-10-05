#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "Config.h"
#include "Scene.h"

#define FONT_HEIGHT         30



//Console commands
#define LOAD_OBJECT                     "lo"
#define DELETE_OBJECT_BY_ID             "doi"
#define DELETE_OBJECT_BY_NAME           "don"

#define BUMP_MAPPING                    "bump"
#define FOG                             "fog"
#define ANTIALIASING                    "aa"
#define GOURAUD_SHADING                 "gouraud"
#define TEXTURING                       "texturing"

#define SHADOWS                         "shadows"
#define TEXTURE_FILTERING               "text_filter"


//#define CLEAR                           "clr"
//#define HELP                            "help"
#define SAVE_CONFIG                     "save"


class Console
{
	char buffer[MAX_CHARS];
	int count;

	unsigned int FontListID;
	HFONT hOldFont;

public:

	bool active;

	Console():active(false),count(0),FontListID(0) {}
	~Console() {}

	void Draw(Config);

	bool Init(Config);
	void Quit(Config);

	void Input(WPARAM, Config&, Scene&);

	void PositionText(int, int, Config);

	void glDrawText(int, int, const char*, Config);

	unsigned int CreateOpenGLFont(LPSTR, int, Config);

	void Execute(Config&, Scene&);

	void ClearBuffer();
};




#endif