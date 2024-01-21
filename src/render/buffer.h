#pragma once

#include <core/types.h>

namespace gpu {

	/// <summary>
	/// GPU Buffer Bind Flag
	/// </summary>
	enum class BindFlags {
		BIND_VERTEX_BUFFER,
		BIND_INDEX_BUFFER,
		BIND_CONSTANT_BUFFER
	};

	/// <summary>
	/// GPU Buffer Usage Flag
	/// </summary>
	enum class UsageFlags {
		STATIC_DRAW,
		DYNAMIC_DRAW,
	};

	/// <summary>
	/// GPU Buffer Input
	/// </summary>
	struct Input {
		int size;
		int type;
	};

	/// <summary>
	/// GPU Buffer Descriptor
	/// </summary>
	struct BufferDesc {
		Vector<Input> layout;
		BindFlags bindFlags;
		UsageFlags usageFlags;
		unsigned long long size;
		void* data;
	};

	/// <summary>
	/// GPU Buffer Handle
	/// </summary>
	struct Buffer {
		BufferDesc desc;
		GLuint vao;
		GLuint vbo;
	};
}