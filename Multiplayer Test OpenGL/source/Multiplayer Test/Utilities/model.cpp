#include "model.h"

Utilities::Model::Model(std::vector<glm::vec4> vertices, std::vector<uint32_t> indices) :
	m_vertices(vertices), m_indices(indices)
{
	Init();
	GenerateAABB();
}

void Utilities::Model::Draw() {
	Render::Renderer::Draw(m_VAO, m_indices.size());
}

void Utilities::Model::Init() {
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size() * glm::vec4::length(), m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, glm::vec4::length(), GL_FLOAT, GL_FALSE, glm::vec4::length() * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Utilities::Model::GenerateAABB() {
	if (m_vertices.empty())
		return;
	m_box.min = *std::min_element(m_vertices.begin(), m_vertices.end(), [=](const glm::vec3& first, const glm::vec3& second) {
		return glm::lessThan(first, second).x && glm::lessThan(first, second).y && glm::lessThan(first, second).z;
		});
	m_box.max = *std::max_element(m_vertices.begin(), m_vertices.end(), [=](const glm::vec3& first, const glm::vec3& second) {
		return glm::greaterThan(second, first).x && glm::greaterThan(second, first).y && glm::greaterThan(second, first).z;
		});
}

std::vector<glm::vec4> Utilities::Model::GetVertices() const {
	return m_vertices;
}
std::vector<uint32_t> Utilities::Model::GetIndices() const {
	return m_indices;
}

const Utilities::Model::AABB_box& Utilities::Model::GetAABB_box() const {
	return m_box;
}