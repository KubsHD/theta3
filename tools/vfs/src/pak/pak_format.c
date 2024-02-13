#include "pak_format.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void pakTocInit(PakToc* toc) {
	toc->data_entries = (PakEntry*)calloc(1, sizeof(PakEntry));

	toc->magic = "TPK";
	toc->num_data_paks = 1;
	toc->num_files = 0;
}

void pakTocEntryPush(PakToc* toc, PakEntry ent)
{
	toc->num_files++;
	toc->data_entries = (PakEntry*)realloc(toc->data_entries, sizeof(PakEntry) * toc->num_files);

	memcpy(&toc->data_entries[toc->num_files - 1], &ent, sizeof(PakEntry));
}

VFS_BOOL pakTocGetEntry(PakToc toc, const char* path, PakEntry* ent)
{
	for (int i = 0; i < toc.num_files; i++)
	{
		if (strcmp(toc.data_entries[i].path, path) == 0)
		{
			ent = &toc.data_entries[i];
			return 1;
		}
	}
	
	return 0;
}
