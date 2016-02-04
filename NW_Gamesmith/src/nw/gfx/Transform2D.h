#pragma once

#include <nw/CommonMacros.h>
#include <nw/Types.h>

#include <nw/math/Vector2.h>

#include <functional>

namespace nw { namespace gfx {

class NW_API Transform2D
{
public:
	Transform2D();
	Transform2D(const math::Vector2& position);

	void SetPosition(const math::Vector2& position);

	inline const math::Vector2& GetPosition() const { return m_Position; }

	void Translate(const math::Vector2& dir);

	void SetChangedCallback(std::function<void(const Transform2D&)> callback);

private:
	inline void CallChangedCallback() { if (m_Changed != nullptr) m_Changed(*this); }

private:
	// TODO: Make an event system with callback wrapper, not the "simple" std::funtions
	std::function<void(const Transform2D&)> m_Changed;

	math::Vector2 m_Position;
};

} }