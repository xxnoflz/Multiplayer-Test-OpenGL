#pragma once
#include "player.h"
#include "../Camera/camera.h"

namespace Entities {

	class PlayableCharacter : public Player {
	public:
		enum PressedKey {
			W = 87,
			A = 65,
			S = 83,
			D = 68
		};

		PlayableCharacter(const glm::vec3 position = glm::vec3(0.0f), const glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f));

		void ProcessMouseInput(const float xPos, const float yPos);
		void ProcessKeyboardInput(PressedKey key, const float dTime);

		glm::vec3 GetDirection() const;
		glm::mat4& GetViewMatrix();
	private:
		Camera::Camera m_camera;
	};

}