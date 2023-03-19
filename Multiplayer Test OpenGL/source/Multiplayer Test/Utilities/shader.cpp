#include "shader.h"

Utilities::Shader::Shader(std::string_view vertexCode, std::string_view fragmentCode) {
	CreateShader(vertexCode, fragmentCode);
}

void Utilities::Shader::CreateShader(std::string_view vertexCode, std::string_view fragmentCode) {
	const char* vertexCodeC{ vertexCode.data() };
	GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &vertexCodeC, nullptr);
	glCompileShader(vertexShader);

	const char* fragmentCodeC{ fragmentCode.data() };
	GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &fragmentCodeC, nullptr);
	glCompileShader(fragmentShader);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Utilities::Shader::Use() const {
	glUseProgram(m_ID);
}

void Utilities::Shader::ApplyProjectionMatrix(const float fov, const float aspect_ratio) {
	Use();
	glm::mat4 projection{ glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f) };
	SetMat4("projection", projection);
}

void Utilities::Shader::SetVec3(std::string_view name, const glm::vec3 value) {
	glUniform3fv(glGetUniformLocation(m_ID, name.data()), 1, &value[0]);
}

void Utilities::Shader::SetMat4(std::string_view name, const glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.data()), 1, GL_FALSE, &value[0][0]);
}