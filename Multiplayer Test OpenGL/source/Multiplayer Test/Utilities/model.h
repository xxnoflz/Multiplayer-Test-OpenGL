#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

#include "../Render/renderer.h"

namespace Utilities {

	class Model {
	public:
		struct AABB_box {
			glm::vec3 min;
			glm::vec3 max;
		};

		Model(std::vector<glm::vec4> vertices = {}, std::vector<uint32_t> indices = {});

		void Draw();

		std::vector<glm::vec4> GetVertices() const;
		std::vector<uint32_t> GetIndices() const;
		const AABB_box& GetAABB_box() const;
	private:
		std::vector<glm::vec4> m_vertices;
		std::vector<uint32_t> m_indices;
		AABB_box m_box;

		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;

		void Init();
		void GenerateAABB();
	};

}