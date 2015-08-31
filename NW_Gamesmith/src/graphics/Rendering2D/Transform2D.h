#pragma once

#include "../../maths/Maths.h"

namespace gamesmith { namespace graphics {

	class Transform2D
	{
	private:
		maths::vec2f m_Position;
		float m_Rotation;
		maths::vec2f m_Scale;

	public:
		Transform2D(maths::vec2f position, float rotation, maths::vec2f scale) :
			m_Position(position), m_Rotation(rotation), m_Scale(scale) {}

		inline const maths::vec2f& getPosition() const { return m_Position; }
		inline float getRotation() const { return m_Rotation; }
		inline const maths::vec2f& getScale() const { return m_Scale; }

		void setPosition(const maths::vec2f& position) { m_Position = position; }
		void setRotation(float rotation) { m_Rotation = rotation; }
		void setScale(const maths::vec2f& scale) { m_Scale = scale; }
	};

} }