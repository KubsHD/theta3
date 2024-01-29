#pragma once

#include <stdlib.h>

typedef unsigned int uint32_t;

#define MAX_PATH 128

struct PakEntry {
	char path[MAX_PATH] = {};
	uint32_t pak_number;
	uint32_t data_offset;
	uint32_t data_size;
	uint8_t  compressed;
	uint32_t compressed_size;
};

struct PakToc {
	const char* magic = "TPK";
	uint32_t num_data_paks = 1;
	uint32_t num_files = 0;
	PakEntry* data_entries;

	PakToc() {
		data_entries = (PakEntry*)calloc(1, sizeof(PakEntry));
	}

	void push(PakEntry ent)
	{
		num_files++;
		data_entries = (PakEntry*)realloc(data_entries, sizeof(PakEntry) * num_files);
		
		memcpy(&data_entries[num_files - 1], &ent, sizeof(PakEntry));
		
		//data_entries[num_files - 1] = ent;
	}

	PakEntry get_entry_by_path(String path);
};

