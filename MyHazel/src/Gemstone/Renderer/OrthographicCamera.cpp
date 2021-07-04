#include "gspch.h"
#include "OrthographicCamera.h"

namespace Gemstone
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.f, 1.f)),
		m_ViewMatrix(glm::identity<glm::mat4>())
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::identity<glm::mat4>(), m_Position) *
			glm::rotate(glm::identity<glm::mat4>(), glm::radians(m_Rotation), glm::vec3(0.f, 0.f, 1.f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}