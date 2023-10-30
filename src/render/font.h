#pragma once

#include <core/types.h>

class Subtexture;
class Texture;

/// <summary>
/// Describes a letter in a font file
/// </summary>
struct Glyph
{
	int id;
	int x;
	int y;
	int w;
	int h;
	int xoff;
	int yoff;
	int xadv;
	// not used

	int page;
	int chnl;

	Ref<Subtexture> subTex;

	/* data */
};

/// <summary>
/// Font class
/// </summary>
class Font {
private:
	friend class Asset;

	/// <summary>
	/// Create a font from a .fnt file
	/// </summary>
	/// <param name="path">Path to file</param>
	Font(String path);
public:

	String name;
	Texture* atlas;
	Glyph glyphs[200];
};