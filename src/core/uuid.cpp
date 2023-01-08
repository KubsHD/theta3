#include "uuid.h"

#if WIN

#include <Windows.h>

String ID::get_uuid()
{
	UUID tmp;

	RPC_CSTR str = NULL;

	UuidCreate(&tmp);
	UuidToStringA(&tmp, &str);

	String s = (char*)str;

	return s;
}

#elif MAC

String ID::get_uuid()
{
	return "TODO";
}

#endif
