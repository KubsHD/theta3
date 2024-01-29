#include "pak_format.h"

#include <stdlib.h>

PakEntry PakToc::get_entry_by_path(String path)
{
	for (int i = 0; i < num_files; i++)
	{
		if (strcmp(data_entries[i].path, path.c_str()) == 0)
		{
			return data_entries[i];
		}
	}
}

