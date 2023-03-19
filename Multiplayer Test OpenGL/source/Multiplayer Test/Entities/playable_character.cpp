#include "playable_character.h"

Entities::PlayableCharacter::PlayableCharacter(const glm::vec3 position, const glm::vec3 direction) :
	Player(position, ""), m_camera(position, direction)
{

}

void Entities::PlayableCharacter::ProcessMouseInput(const float xPos, const float yPos) {
	m_camera.ProcessMouseInput(xPos, yPos);
	GetRotation() = m_camera.GetRotation();
}

void Entities::PlayableCharacter::ProcessKeyboardInput(PressedKey key, float dTime) {
	float player_speed{ dTime * 5.0f };
	switch (key) {
	case W:
		GetPosition() += m_camera.GetDirection() * player_speed;
		break;
	case S:
		GetPosition() -= m_camera.GetDirection() * player_speed;
		break;
	case A:
		GetPosition() -= glm::cross(m_camera.GetDirection(), glm::vec3(0.0f, 1.0f, 0.0f)) * player_speed;
		break;
	case D:
		GetPosition() += glm::cross(m_camera.GetDirection(), glm::vec3(0.0f, 1.0f, 0.0f)) * player_speed;
		break;
	}
	m_camera.UpdatePosition(GetPosition());
}

glm::vec3 Entities::PlayableCharacter::GetDirection() const {
	return m_camera.GetDirection();
}

glm::mat4& Entities::PlayableCharacter::GetViewMatrix() {
	return m_camera.GetViewMatrix();
}