#pragma once

#include <pak/pak_format.h>

class VFS {
public:
	VFS();

	static bool init();

	static Vector<char> get_file(String vpath);

private:
	static PakToc toc;
	static FILE** data_pak_array;
};
