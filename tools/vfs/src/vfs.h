#pragma once

#include "pak/pak_format.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef uint8_t VFS_BOOL;

	typedef struct vfsSystem {
		const char* root;
		VFS_BOOL packed;

		// used only if packed
		PakToc* pToc;
		FILE** data_paks;

	} vfsSystem;

	typedef struct vfsFile {
		const char* path;
		const char* data;
		uint8_t size;
	} vfsFile;

	typedef struct vfsInitArgs {
		const char* root;
		VFS_BOOL packed;
	} vfsInitArgs;

	typedef enum VFS_RESULT {
		VFS_OK = 0,
		VFS_FILE_NOT_FOUND = 1,
		VFS_PAK_FAILED_TO_LOAD = 2
	} VFS_RESULT;

#if (defined(_WIN32) || defined(_WIN64))
#define VFS_API __stdcall
#endif


	// Runtime api
	VFS_RESULT VFS_API vfsInit(struct vfsSystem* system, struct vfsInitArgs args);
	VFS_RESULT VFS_API vfsReadFile(struct vfsSystem* system, const char* path, struct vfsFile* file);
	VFS_RESULT VFS_API vfsReadFileText(const char* path, struct vfsFile* file);

	// Offline api

#ifdef __cplusplus
}
#endif