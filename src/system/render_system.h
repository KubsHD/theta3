#pragma once

#include <core/types.h>
#include <render/buffer.h>

class Texture;
class Font;

struct Shader;
struct Target;


// we should probably wrap those pointers or use references since they only contain reference to the gpu api object's id


// what does the drawcall need?
// main triangle buffer
// some kind of dynamic buffer for uniforms
// textures
// shader
// target

struct ConstantBufferHandle {
	String name;
	gpu::Buffer* buf;
};

struct DrawCall {
	gpu::Buffer* buffer = nullptr;
	gpu::Buffer* index_buffer = nullptr;
	ConstantBufferHandle* uniform = nullptr;
	Vector<Texture*> textures;
	Shader* shader = nullptr;
	Target* target = nullptr;
	int indices_count;
	int vertices_count;
};


// store drawcalls in smth like a queue?
// std::vector<DrawCall> m_drawcalls;
// submitted to gpu on frame end

// replace renderer api or maybe make an underlying layer for it
// that the 3d path will also use?
// abstract passes here or somewhere higher?


// this class will serve as a base for any rendering done on the gpu
// both 2d and 3d
class RenderSystem {
public:
	void submit_drawcall(DrawCall& dc);
	void work();

private:
	Vector<DrawCall> m_draw_calls;
};