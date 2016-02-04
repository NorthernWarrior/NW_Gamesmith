#include "Camera.h"

#include <GL/glew.h>

using namespace nw;
using namespace gfx;
using namespace math;

Camera::Camera(float left, float right, float top, float bottom)
{
	l = left;
	r = right;
	t = top;
	b = bottom;

	m_ProjMatrix = Matrix4::Orthographic(0, right, bottom, 0, -1, 1);
	m_ViewMatrix = Matrix4::Identity();

	m_Transform.SetChangedCallback([this](auto t) { 
		m_ViewMatrix = Matrix4::Translate(-Vector3(m_Transform.GetPosition()));
	});

	// Always set the first as the main camera
	if (s_ActiveCamera == nullptr)
		SetActive();
}

void Camera::SetActive()
{
	s_ActiveCamera = this;

	// TODO: NOPE!
	glViewport(l, t, r, b);
}

Camera* Camera::s_ActiveCamera = nullptr;