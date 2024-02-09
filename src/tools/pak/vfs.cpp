#include "vfs.h"

#include <core/log.h>

#include <stdio.h>
#include <stdlib.h>

#include <string>

PakToc VFS::toc;
FILE** VFS::data_pak_array;

bool VFS::init()
{
	std::ifstream file("data/game.thetatoc", std::ios::binary);

	if (!file.is_open())
	{
		log_error("Failed to open game.thetatoc");
		return false;
	}
	
	file.read((char*)&toc.magic, 4);
	file.read((char*)&toc.num_data_paks, sizeof(uint32_t));
	file.read((char*)&toc.num_files, sizeof(uint32_t));

	toc.data_entries = (PakEntry*)realloc(toc.data_entries, toc.num_files * sizeof(PakEntry));

	for (int i = 0; i < toc.num_files; i++)
	{
		file.read((char*)&toc.data_entries[i], sizeof(PakEntry));
	}
	
	file.close();
	
	data_pak_array = new FILE * [toc.num_data_paks];

	for (int i = 0; i < toc.num_data_paks; i++)
	{
		String path = ("data/game_" + std::to_string(i) + ".thetapak");

		data_pak_array[i] = fopen(path.c_str(), "rb");
		if (!data_pak_array[i])
		{
			log_error("Failed to open data pak: %s", path);
			abort();
			return false;
		}
	}

	log_info("Loaded content toc\n");
	return true;
}

Vector<char> VFS::get_file(String vpath)
{
	auto p = std::filesystem::proximate(std::filesystem::path(vpath)).string();
	std::replace(p.begin(), p.end(), '\\', '/');

	PakEntry ent = pakTocGetEntry(vpath.c_str());
	Vector<char> data;
	data.resize(ent.data_size);

	fseek(data_pak_array[ent.pak_number], ent.data_offset, SEEK_SET);
	fread(data.data(), ent.data_size, 1, data_pak_array[ent.pak_number]);

	return data;
}
