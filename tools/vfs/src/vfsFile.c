#include "vfs.h"

#include <string.h>

VFS_RESULT VFS_API vfsInit(struct vfsInitArgs* args, struct vfsSystem* system)
{
	//system = (vfsSystem*)malloc(sizeof(vfsSystem));
	system->root = args->root;
	system->packed = args->packed;
	

	if (system->packed)
	{
		PakToc* toc = (PakToc*)malloc(sizeof(PakToc));

		const char* tocPath = args->root;
		strcat(tocPath, "/game.thetatoc");

		// 1. Load TOC file
		FILE* pTocFile = fopen(tocPath, "rb");
		if (!pTocFile)
		{
			return VFS_PAK_FAILED_TO_LOAD;
		}
		
		fread((char*)&toc->magic, 4, 1, pTocFile);
		fread((char*)&toc->num_data_paks, sizeof(uint32_t), 1, pTocFile);
		fread((char*)&toc->num_files, sizeof(uint32_t), 1, pTocFile);


		toc->data_entries = (PakEntry*)realloc(toc->data_entries, toc->num_files * sizeof(PakEntry));

		for (int i = 0; i < toc->num_files; i++)
		{
			fread((char*)&toc->data_entries[i], sizeof(PakEntry), 1, pTocFile);
		}
		
		fclose(pTocFile);

		system->data_paks = (FILE**)malloc(toc->num_data_paks * sizeof(FILE*));

		for (int i = 0; i < toc->num_data_paks; i++)
		{
			const char* pakPath;

			sprintf(pakPath, "data/game_%d.thetapak", i);

			system->data_paks[i] = fopen(pakPath, "rb");
			if (!system->data_paks[i])
			{
				log_error("Failed to open data pak: %s", pakPath);
				abort();
				return VFS_PAK_FAILED_TO_LOAD;
			}
		}

		log_info("Loaded content toc\n");
		return VFS_OK;
	}
}

void replaceChar(char* str, char oldChar, char newChar) {
	while (*str != '\0') {
		if (*str == oldChar)
			*str = newChar;
		str++;
	}
}

VFS_RESULT VFS_API vfsReadFile(struct vfsSystem* system, const char* path, struct vfsFile* file)
{
	char* p[256];
	strcpy(p, path);
	replaceChar(p, '\\', '/');

	PakEntry ent = pakTocGetEntry(p);

	
	//file = (vfsFile*)malloc(sizeof(vfsFile));
	file->data = (char*)malloc(ent.data_size * sizeof(char));
	file->size = ent.data_size;
	file->path = ent.path;

	fseek(system->data_paks[ent.pak_number], ent.data_offset, SEEK_SET);
	fread(file->data, ent.data_size, 1, system->data_paks[ent.pak_number]);

	return VFS_OK;
}