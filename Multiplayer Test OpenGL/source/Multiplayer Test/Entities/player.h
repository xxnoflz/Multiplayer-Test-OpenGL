#pragma once
#include "basic_entity.h"
#include "../Utilities/resource_manager.h"
#include "../Render/renderer.h"

#include <string>
#include <string_view>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <boost/serialization/map.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost::serialization {
	template <typename Ar>
	void serialize(Ar& ar, glm::vec3& v, unsigned /*unused*/) {
		ar& make_nvp("x", v.x)& make_nvp("y", v.y)& make_nvp("z", v.z);
	}
}

namespace Entities {

	class Player : public BasicEntity {
	public:
		friend class boost::serialization::access;

		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& GetPosition();
			ar& GetSize();
			ar& GetRotation();
			ar& m_model_name;
		}

		Player(const glm::vec3 position = glm::vec3(0.0f), std::string_view model_name = "");
		Player(const BasicEntity& entity, std::string_view model_name = "");

		void Draw(std::string_view shader_name);

		std::string_view GetModelName() const;
		const glm::mat4& GetModelMatrix() const;
		glm::vec3& GetColor();
		void UpdateModelMatrix();
	private:
		std::string m_model_name;

		glm::vec3 m_color;
		glm::mat4 m_model_matrix;
	};

}