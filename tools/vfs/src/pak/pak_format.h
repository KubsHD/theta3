#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef unsigned int uint32_t;

#define MAX_PATH 128

typedef struct PakEntry {
	char path[MAX_PATH];
	uint32_t pak_number;
	uint32_t data_offset;
	uint32_t data_size;
	uint8_t  compressed;
	uint32_t compressed_size;
} PakEntry;

typedef struct PakToc {
	const char* magic;
	uint32_t num_data_paks;
	uint32_t num_files;
	PakEntry* data_entries;
	FILE** data_paks;
} PakToc;

void pakTocInit(PakToc* toc);
void pakTocEntryPush(PakToc* toc, PakEntry ent);
PakEntry pakTocGetEntry(const char* path);
