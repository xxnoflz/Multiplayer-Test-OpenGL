#include "basic_entity.h"

Entities::BasicEntity::BasicEntity(glm::vec3 position, glm::vec3 size, EulerAngles rotation):
	m_position(position), m_size(size), m_rotation(rotation)
{

}

glm::vec3& Entities::BasicEntity::GetPosition() {
	return m_position;
}

glm::vec3& Entities::BasicEntity::GetSize() {
	return m_size;
}

Entities::BasicEntity::EulerAngles& Entities::BasicEntity::GetRotation() {
	return m_rotation;
}

Entities::BasicEntity& Entities::BasicEntity::GetBasicEntity() {
	return *this;
}