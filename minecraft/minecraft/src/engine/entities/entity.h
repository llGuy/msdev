#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include <glm/glm.hpp>

#include "../data/time_data.h"

namespace minecraft
{
	namespace ent
	{
		class Entity
		{
		public:
			enum class move_t
			{
				FORWARD,

				BACKWARD,

				TOPLAYER		// for zombies if they get implemented
			};

			enum class strafe_t
			{
				RIGHT,

				LEFT
			};

			/* so that the camera can bind to a certain entity */
			virtual glm::vec3* EntityViewDirection(void) { return nullptr; }
			virtual glm::vec3* EntityWorldPosition(void) { return nullptr; }

			virtual void UpdData(void) {}
			virtual void Move(const move_t&& movement, data::Time* time) {}
			virtual void Strafe(const strafe_t&& strafe, data::Time* time) {}
		};
	}
}

#endif