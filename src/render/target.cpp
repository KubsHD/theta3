#include "target.h"

#include <core/types.h>
#include <lib/glad/glad.h>

void Target::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glViewport(0, 0, target_size.x, target_size.y);
}