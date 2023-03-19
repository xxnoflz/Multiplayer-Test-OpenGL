#include "player.h"

Entities::Player::Player(const glm::vec3 position, std::string_view model_name) :
	BasicEntity(position), m_model_name(model_name)
{

}

Entities::Player::Player(const Entities::BasicEntity& entity, std::string_view model_name) :
	BasicEntity(entity), m_model_name(model_name)
{

}

void Entities::Player::Draw(std::string_view shader_name) {
	if (!m_model_name.empty()) {
		UpdateModelMatrix();
		Utilities::ResourceManager::GetShader(shader_name).SetMat4("model", m_model_matrix);
		Utilities::ResourceManager::GetShader(shader_name).SetVec3("objectColor", m_color);
		Utilities::ResourceManager::GetModel(m_model_name).Draw();
	}
}

void Entities::Player::UpdateModelMatrix() {
	m_model_matrix = glm::mat4(1.0f);
	m_model_matrix = glm::translate(m_model_matrix, GetPosition());
	m_model_matrix *= glm::yawPitchRoll(glm::radians(GetRotation().yaw), glm::radians(-GetRotation().pitch), glm::radians(GetRotation().roll));
	m_model_matrix = glm::scale(m_model_matrix, GetSize());
}

std::string_view Entities::Player::GetModelName() const {
	return m_model_name;
}

const glm::mat4& Entities::Player::GetModelMatrix() const {
	return m_model_matrix;
}

glm::vec3& Entities::Player::GetColor() {
	return m_color;
}