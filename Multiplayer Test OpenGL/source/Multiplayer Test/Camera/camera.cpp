#include "camera.h"

Camera::Camera::Camera(const glm::vec3 position, const glm::vec3 direction) :
	BasicEntity(position, glm::vec3(0.0f)), m_direction(direction)
{
	UpdateDirection();
}

void Camera::Camera::UpdateMatrix() {
	m_view = glm::lookAt(GetPosition(), GetPosition() + m_direction, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::Camera::ProcessMouseInput(float xPos, float yPos) {
	float deltaX{ xPos - m_mouse.lastX };
	float deltaY{ m_mouse.lastY - yPos };
	m_mouse.lastX = xPos;
	m_mouse.lastY = yPos;

	GetRotation().pitch += deltaY * 0.1f;
	GetRotation().yaw += deltaX * 0.1f;

	UpdateDirection();
}

void Camera::Camera::UpdateDirection() {
	glm::vec3 new_direction{};
	new_direction.x = glm::cos(glm::radians(GetRotation().pitch)) * glm::cos(glm::radians(GetRotation().yaw));
	new_direction.y = glm::sin(glm::radians(GetRotation().pitch));
	new_direction.z = glm::cos(glm::radians(GetRotation().pitch)) * glm::sin(glm::radians(GetRotation().yaw));
	m_direction = glm::normalize(new_direction);

	UpdateMatrix();
}

void Camera::Camera::UpdatePosition(const glm::vec3 new_position) {
	GetPosition() = new_position;

	UpdateMatrix();
}

glm::mat4& Camera::Camera::GetViewMatrix() {
	return m_view;
}

glm::vec3 Camera::Camera::GetDirection() const {
	return m_direction;
}
