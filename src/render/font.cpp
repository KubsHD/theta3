#include "font.h"

#include <core/asset.h>
#include <core/log.h>
#include <render/Renderer.h>

Font::Font(String path)
{
	FILE* file = fopen(/*get_asset_path*/(path).c_str(), "r");
	if (file == NULL) {
		log_error("Font not found");
		assert(file == NULL);
	}
	char line[256];
	char buffer[1024] = { 0 };


	int curr_line = 0;



	while (fgets(line, sizeof(line), file))
	{
		curr_line++;

		if (curr_line == 3) {
			int w;
			int h;
			char img[129] = { 0 };

			sscanf(line, "page id=0 file=\"%128[^\"]\"", img);
			//log_info("%s", img);

			char path[200] = { 0 };

			sprintf(path, "font/%s", img);

			//log_info(path);

			atlas = /*asset_load_texture*/Asset::load_texture(path + String(".png"));
			name = path;
			curr_line++;
			continue;
		}

		if (curr_line > 3)
		{
			// parse glyph
			int charId, charX, charY, charWidth, charHeight, charOffsetX, charOffsetY, charAdvanceX;


			int isScanned = sscanf(line, "char id=%i x=%i y=%i width=%i height=%i xoffset=%i yoffset=%i xadvance=%i",
				&charId, &charX, &charY, &charWidth, &charHeight, &charOffsetX, &charOffsetY, &charAdvanceX);

			if (isScanned) {
				if (charId < 200)
				{
					this->glyphs[charId];
					this->glyphs[charId].x = charX;
					this->glyphs[charId].y = charY;
					this->glyphs[charId].w = charWidth;
					this->glyphs[charId].h = charHeight;
					this->glyphs[charId].xoff = charOffsetX;
					this->glyphs[charId].yoff = charOffsetY;
					this->glyphs[charId].xadv = charAdvanceX;
					this->glyphs[charId].subTex = CreateRef<Subtexture>(this->atlas, Vec2(charX, charY), Vec2(charWidth, charHeight));
				}
			}
			curr_line++;
		}
	}
}
