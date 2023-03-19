#pragma once
#include <glm/glm.hpp>
#include <limits>

#include "../Entities/player.h"
#include "../Entities/playable_character.h"
#include "../Utilities/resource_manager.h"

namespace Utilities {

	class IntersectionSolver {
	public:
		static bool RayObbIntersest(Entities::PlayableCharacter& main_player, Entities::Player& player);
	};

}