#pragma once

#include <nw/CommonMacros.h>
#include <nw/Types.h>

#include <nw/gfx/Transform2D.h>

#include <nw/math/Matrix4.h>

namespace nw { namespace gfx {

class NW_API Camera
{ 
public:
	static inline const Camera* GetActiveCamera() { return s_ActiveCamera; }
private:
	static Camera* s_ActiveCamera;

public:
	// TODO: I actually want a constructor without parameters, and as standard values it fills the whole screen.
	// The sides of the viewport retangle will go from 0 to 1.
	Camera(float left, float right, float top, float bottom);

	void SetActive();

	inline const math::Matrix4& GetProjectionMatrix() const { return m_ProjMatrix; }
	inline const math::Matrix4& GetViewMatrix() const { return m_ViewMatrix; }

	inline Transform2D* GetTransform() { return (&m_Transform); }

protected:
	float l, r, t, b; // TODO: ViewPort Struct or sth like that
	math::Matrix4 m_ProjMatrix;
	math::Matrix4 m_ViewMatrix;

	Transform2D m_Transform;
};

} }