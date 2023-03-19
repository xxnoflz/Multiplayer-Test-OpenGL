#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Entities/basic_entity.h"

namespace Camera {

	class Camera : public Entities::BasicEntity {
	public:
		struct MousePosition {
			float lastX;
			float lastY;
		};

		Camera(const glm::vec3 position, const glm::vec3 direction);

		void ProcessMouseInput(float xPos, float yPos);

		void UpdatePosition(const glm::vec3 new_position);

		glm::mat4& GetViewMatrix();

		glm::vec3 GetDirection() const;
	private:
		glm::vec3 m_direction;
		glm::mat4 m_view;
		MousePosition m_mouse;

		void UpdateDirection();
		void UpdateMatrix();
	};

}