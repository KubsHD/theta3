#include "render_system.h"

#include <render/device.h>
#include <render/buffer.h>
#include <render/Shader.h>
#include <render/texture.h>

#include <lib/glad/glad.h>
#include <utils/profiler.h>


void RenderSystem::submit_drawcall(DrawCall& dc)
{
	THETA_PROFILE;

	m_draw_calls.push_back(dc);
}

void RenderSystem::work()
{
	THETA_PROFILE;

	while (!m_draw_calls.empty())
	{
		DrawCall dc = m_draw_calls.back();

		// render somehow
		glUseProgram(dc.shader->get_id());
		glBindVertexArray(dc.buffer->vao);

		GLuint bindingPoint = 1; // This should match the binding point in your shader
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, dc.uniform->buf->ubo);

		GLuint blockIndex = glGetUniformBlockIndex(dc.shader->get_id(), dc.uniform->name.c_str());
		glUniformBlockBinding(dc.shader->get_id(), blockIndex, bindingPoint);

		for (int i = 0; i < dc.textures.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D + i, dc.textures[i]->id);
		}

		if (dc.index_buffer != nullptr)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dc.index_buffer->ibo);
			glDrawElements(GL_TRIANGLES, dc.indices_count, GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, dc.vertices_count);
		}

		glUseProgram(0);
		glBindVertexArray(0);

		m_draw_calls.pop_back();
	}
}
