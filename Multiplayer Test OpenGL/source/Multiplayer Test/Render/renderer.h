#pragma once
#include <glad/glad.h>

namespace Render {
	class Renderer {
	public:
		static void Draw(GLuint VAO, size_t vertexAmount);
	};
}