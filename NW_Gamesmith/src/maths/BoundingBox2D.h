#pragma once

#include "vec2.h"

namespace gamesmith { namespace maths {

	class BoundingBox2D
	{
	private:
		vec2f m_Position;
		vec2f m_Size;

	public:
		BoundingBox2D(vec2f position, vec2f size) :
		m_Position(position), m_Size(size) {}

		inline const vec2f getTop() const { return vec2f(m_Position.x, m_Position.y - m_Size.y / 2.0f); }
		inline const vec2f getTopRight() const { return vec2f(m_Position.x + m_Size.x / 2.0f, m_Position.y - m_Size.y / 2.0f); }
		inline const vec2f getTopLeft() const { return vec2f(m_Position.x - m_Size.x / 2.0f, m_Position.y - m_Size.y / 2.0f); }
		inline const vec2f getBottom() const { return vec2f(m_Position.x, m_Position.y + m_Size.y / 2.0f); }
		inline const vec2f getBottomLeft() const { return vec2f(m_Position.x - m_Size.x / 2.0f, m_Position.y + m_Size.y / 2.0f); }
		inline const vec2f getBottomRight() const { return vec2f(m_Position.x + m_Size.x / 2.0f, m_Position.y + m_Size.y / 2.0f); }
		inline const vec2f getLeft() const { return vec2f(m_Position.x - m_Size.x / 2.0f, m_Position.y); }
		inline const vec2f getRight() const { return vec2f(m_Position.x + m_Size.x / 2.0f, m_Position.y); }

		inline const float getWidth() const { return m_Size.x; }
		inline const float getHeight() const { return m_Size.y; }

		inline const vec2f getPosition() const { return m_Position; }
		inline const vec2f getSize() const { return m_Size; }

		inline const bool contains(const vec2f& point) const { return (point.x >= getLeft().x && point.x <= getRight().x && point.y >= getTop().y && point.y <= getBottom().y); }
		inline const bool contains(const BoundingBox2D& other) const 
		{ 

			return (
				other.getLeft().x <= getRight().x && other.getLeft().x >= getLeft().x &&
				other.getRight().x >= getLeft().x && other.getRight().x <= getRight().x &&
				other.getTop().y >= getTop().y && other.getTop().y <= getBottom().y &&
				other.getBottom().y <= getBottom().y && other.getBottom().y >= getTop().y
				);
		}
		inline const bool intersects(const BoundingBox2D& other) const
		{

			return !(
				other.getLeft().x > getRight().x || other.getLeft().x < getLeft().x &&
				other.getRight().x < getLeft().x || other.getRight().x > getRight().x &&
				other.getTop().y < getTop().y || other.getTop().y > getBottom().y &&
				other.getBottom().y > getBottom().y || other.getBottom().y < getTop().y
				);
		}
	};

} }