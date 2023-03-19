#pragma once
#include <map>
#include <string_view>
#include <string>
#include <fstream>
#include <sstream>

#include "shader.h"
#include "model.h"
#include "../Model Parser/ModelParser.h"

namespace Utilities {

	class ResourceManager {
	public:
		static void CreateShader(std::string_view vertexPath, std::string_view fragmentPath, std::string_view name);
		static Shader& GetShader(std::string_view name);

		static void LoadModel(std::string_view modelPath, std::string_view name);
		static Model& GetModel(std::string_view name);
	private:
		static std::map<std::string_view, Shader> m_Shaders;
		static std::map<std::string_view, Model> m_Models;
	};

}