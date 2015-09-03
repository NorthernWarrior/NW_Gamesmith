#pragma once

#include "../../maths/Maths.h"

#include <vector>

namespace gamesmith { namespace graphics {

	class Renderable2D;

	class Transform2D
	{
	private:
		maths::vec2f m_Position;
		float m_Rotation;
		maths::vec2f m_Scale;

		const Renderable2D* m_Renderable;
		Transform2D* m_Parent;
		std::vector<Transform2D*> m_Children;

	public:
		Transform2D(maths::vec2f position, float rotation, maths::vec2f scale, const Renderable2D* renderable) :
			m_Position(position), m_Rotation(rotation), m_Scale(scale), m_Renderable(renderable), m_Parent(nullptr) {}
		
		Transform2D(maths::vec2f position, float rotation, maths::vec2f scale, const Renderable2D* renderable, Transform2D* parent) :
			m_Position(position), m_Rotation(rotation), m_Scale(scale), m_Renderable(renderable) {
			
			setParent(parent);
		}

		inline const Renderable2D* getRenderable() const { return m_Renderable; }
		inline const std::vector<Transform2D*> getChildren() const { return m_Children; }
		inline const maths::vec2f& getPosition() const { return m_Position; }
		inline float getRotation() const { return m_Rotation; }
		inline const maths::vec2f& getScale() const { return m_Scale; }
		inline const maths::mat4 getMatrix() const 
		{
			//return maths::mat4::identity().translate(m_Position); 
			maths::mat4 mat = maths::mat4::translate(maths::mat4::identity(), m_Position);
			mat = maths::mat4::rotate(mat, m_Rotation, maths::vec3f(0, 0, 1));
			return mat;
		}

		void setParent(Transform2D* parent)
		{
			if (m_Parent != nullptr)
				;	// TODO: Detach from old Parent

			m_Parent = parent;

			if (parent == nullptr)
				return;

			m_Parent->m_Children.push_back(this);
		}
		void setPosition(const maths::vec2f& position) { m_Position = position; }
		void setRotation(float rotation) { m_Rotation = rotation; }
		void setScale(const maths::vec2f& scale) { m_Scale = scale; }
	};

} }