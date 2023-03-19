#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string_view>

namespace Utilities {

	class Shader {
	public:
		Shader(std::string_view vertexCode = "", std::string_view fragmentCode = "");

		void Use() const;
		void ApplyProjectionMatrix(const float fov, const float aspect_ratio);
		void SetVec3(std::string_view name, const glm::vec3 value);
		void SetMat4(std::string_view name, const glm::mat4 value);
	private:
		GLuint m_ID;
		void CreateShader(std::string_view vertexCode, std::string_view fragmentCode);
	};

}
