#include "camera.h"

namespace minecraft
{
	namespace ent
	{
		Camera::Camera(void)
			: UP(0.0f, 1.0f, 0.0f)
		{
		}
		Camera::Camera(glm::vec2 originalCursorPosition)
			: UP(0.0f, 1.0f, 0.0f), m_currentCursorPosition(originalCursorPosition)
		{
		}
		void Camera::Bind(Entity* ent)
		{
			m_boundEntity = ent;
		}
		glm::mat4& Camera::ViewMatrix(void)
		{
			m_viewMatrix = glm::lookAt(*m_boundEntity->EntityWorldPosition(), 
				*m_boundEntity->EntityWorldPosition() + *m_boundEntity->EntityViewDirection(), UP);
			return m_viewMatrix;
		}
		void Camera::Look(glm::vec2 newCursorPosition, float sensitivity)
		{
			if (m_currentCursorPosition != newCursorPosition)
			{
				glm::vec2 mouseDelta = newCursorPosition - m_currentCursorPosition;
				/* rotating around the y axis*/
				*m_boundEntity->EntityViewDirection() = glm::mat3(glm::rotate(glm::radians(-mouseDelta.x) * sensitivity, UP)) * 
					*m_boundEntity->EntityViewDirection();
				/* rotating around the x axis */
				glm::vec3 toRotateAround = glm::cross(*(m_boundEntity->EntityViewDirection()), UP);
				*(m_boundEntity->EntityViewDirection()) = glm::mat3(glm::rotate(glm::radians(-mouseDelta.y) * 0.02f, toRotateAround))
					* *(m_boundEntity->EntityViewDirection());
				m_currentCursorPosition = newCursorPosition;
			}
		}
		Camera& Camera::operator=(const Camera&& cam)
		{
			m_boundEntity = cam.m_boundEntity;
			m_currentCursorPosition = cam.m_currentCursorPosition;
			m_viewMatrix = cam.m_viewMatrix;

			return *this;
		}
	}
}