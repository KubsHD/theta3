#include "vfs.h"

#include <string.h>

#include <sys/stat.h>

VFS_RESULT VFS_API vfsInit(struct vfsSystem* system, struct vfsInitArgs args)
{
	//system = (vfsSystem*)malloc(sizeof(vfsSystem));
	system->root = args.root;
	system->packed = args.packed;
	

	if (system->packed)
	{
		PakToc* toc = (PakToc*)malloc(sizeof(PakToc));

		char tocPath[1000];
		sprintf(tocPath, "%s/game.thetatoc", system->root);


		// 1. Load TOC file
		FILE* pTocFile = fopen(tocPath, "rb");
		if (!pTocFile)
		{
			// fallback to unpacked
			system->packed = 0;
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
			char pakPath[1000];

			sprintf(pakPath, "data/game_%d.thetapak", i);

			system->data_paks[i] = fopen(pakPath, "rb");
			if (!system->data_paks[i])
			{
				//log_error("Failed to open data pak: %s", pakPath);
				abort();
				return VFS_PAK_FAILED_TO_LOAD;
			}
		}

		//log_info("Loaded content toc\n");
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

	int failedToLoadFromPak = 0;

	if (system->packed)
	{
		PakEntry ent;

		if (!pakTocGetEntry(*system->pToc, p, &ent))
		{
			failedToLoadFromPak = 1;
		}
		else {
			//file = (vfsFile*)malloc(sizeof(vfsFile));
			file->data = (char*)malloc(ent.data_size * sizeof(char));
			file->size = ent.data_size;
			file->path = ent.path;

			fseek(system->data_paks[ent.pak_number], ent.data_offset, SEEK_SET);
			fread(file->data, ent.data_size, 1, system->data_paks[ent.pak_number]);
		}
	}

	if (!system->packed || failedToLoadFromPak)
	{
		// read from real fs

		char real_path[1000];
		sprintf(real_path, "%s%s", system->root, p);

		FILE* f = fopen(real_path, "rb");

		struct stat buf;

		fstat(fileno(f), &buf);
		file->size = buf.st_size;

		file->data = (char*)calloc(file->size, sizeof(char));
		fread(file->data, file->size, 1, f);
		fclose(f);

		
		file->path = p;
		
	}
	
	return VFS_OK;
}