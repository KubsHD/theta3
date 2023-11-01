#pragma once

#include <core/types.h>

namespace gpu {
	enum class BindFlags {
		BIND_VERTEX_BUFFER,
		BIND_INDEX_BUFFER,
		BIND_CONSTANT_BUFFER
	};

	struct BufferDesc {
		BindFlags bindFlags;
		int byteWidth;
		void* data;
	};

	struct Buffer {
		BufferDesc desc;
		void* buf;
	};
}