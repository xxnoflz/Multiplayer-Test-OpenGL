#pragma once
#include <glm/glm.hpp>

#include <boost/serialization/map.hpp>
#include <boost/serialization/split_free.hpp>

namespace Entities {

	class BasicEntity {
	public:
		struct EulerAngles {
			float pitch;
			float yaw;
			float roll;

			friend class boost::serialization::access;

			template <typename Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar& pitch;
				ar& yaw;
				ar& roll;
			}
		};

		BasicEntity(glm::vec3 position = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), EulerAngles rotation= {});

		glm::vec3& GetPosition();
		glm::vec3& GetSize();
		EulerAngles& GetRotation();
		BasicEntity& GetBasicEntity();
	private:
		glm::vec3 m_position;
		glm::vec3 m_size;
		EulerAngles m_rotation;
	};

}