#include "resource_manager.h"

std::map<std::string_view, Utilities::Shader> Utilities::ResourceManager::m_Shaders;
std::map<std::string_view, Utilities::Model> Utilities::ResourceManager::m_Models;

void Utilities::ResourceManager::CreateShader(std::string_view vertexPath, std::string_view fragmentPath, std::string_view name) {
	std::fstream vertexFile{ vertexPath.data() };
	std::stringstream vertexStream{};

	vertexStream << vertexFile.rdbuf();
	std::string vertexCode{ vertexStream.str() };

	std::fstream fragmentFile{ fragmentPath.data() };
	std::stringstream fragmentStream{};

	fragmentStream << fragmentFile.rdbuf();
	std::string fragmentCode{ fragmentStream.str() };

	m_Shaders[name] = Shader{ vertexCode, fragmentCode };
}

Utilities::Shader& Utilities::ResourceManager::GetShader(std::string_view name) {
	return m_Shaders[name];
}

void Utilities::ResourceManager::LoadModel(std::string_view modelPath, std::string_view name) {
	ModelParser::ParsedModel model{ ModelParser::LoadOBJ(modelPath.data()) };
	std::vector<uint32_t> indices{ };
	for (auto& [first, second, third] : model.p_indices) {
		indices.push_back(first.vertex - 1);
		indices.push_back(second.vertex - 1);
		indices.push_back(third.vertex - 1);
	}
	m_Models[name] = Utilities::Model(model.p_vertices, indices);
}

Utilities::Model& Utilities::ResourceManager::GetModel(std::string_view name) {
	return m_Models[name];
}