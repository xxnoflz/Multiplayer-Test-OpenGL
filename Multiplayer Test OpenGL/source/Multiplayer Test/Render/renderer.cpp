#include "renderer.h"
#include <glm/glm.hpp>
void Render::Renderer::Draw(GLuint VAO, size_t vertexAmount) {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vertexAmount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}