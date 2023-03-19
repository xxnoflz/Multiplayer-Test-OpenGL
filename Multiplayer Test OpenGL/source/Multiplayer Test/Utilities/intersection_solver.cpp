#include "intersection_solver.h"

bool Utilities::IntersectionSolver::RayObbIntersest(Entities::PlayableCharacter& main_player, Entities::Player& player) {
	player.UpdateModelMatrix();
	glm::mat4 modelMatrix{ player.GetModelMatrix() };

	glm::vec3 AABB_box_min{ ResourceManager::GetModel(player.GetModelName()).GetAABB_box().min };
	glm::vec3 AABB_box_max{ ResourceManager::GetModel(player.GetModelName()).GetAABB_box().max };

	float tMin{};
	float tMax{ std::numeric_limits<float>::max() };
	glm::vec3 OBBPosition{ modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z };
	glm::vec3 delta{ OBBPosition - main_player.GetPosition() };

	for (uint32_t iterator{}; iterator < glm::vec3::length(); ++iterator) {
		glm::vec3 Axis{ modelMatrix[iterator].x, modelMatrix[iterator].y, modelMatrix[iterator].z };
		float num{ glm::dot(Axis, delta) };
		float denom{ glm::dot(main_player.GetDirection(), Axis) };
		if (std::fabs(denom) < 1e-6f)
			break;
		float t1{ (num + AABB_box_min[iterator]) / denom };
		float t2{ (num + AABB_box_max[iterator]) / denom };
		if (t1 > t2)
			std::swap(t1, t2);
		tMax = std::min(t2, tMax);
		tMin = std::max(t1, tMin);
		if (tMax < tMin)
			return false;
	}
	return true;
}
