#pragma once

#include <core/types.h>

namespace gpu {
	enum class BindFlags {
		BIND_VERTEX_BUFFER,
		BIND_INDEX_BUFFER,
		BIND_CONSTANT_BUFFER
	};

	enum class UsageFlags {
		STATIC_DRAW,
		DYNAMIC_DRAW,
	};

	struct Input {
		int size;
		int type;
	};

	struct BufferDesc {
		Vector<Input> layout;
		BindFlags bindFlags;
		UsageFlags usageFlags;
		unsigned long long size;
		void* data;
	};

	struct Buffer {
		BufferDesc desc;
		GLuint vao;
		GLuint vbo;
	};
}