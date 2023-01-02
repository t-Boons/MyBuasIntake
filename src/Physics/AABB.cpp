// 2022 Tygo Boons

#include "mypch.h"

#include "AABB.h"

namespace Physics
{
	AABB::AABB()
	{
		// Assign 0 to all points.
		memset(&m_Points, 0, sizeof(m_Points));
		m_Position = { 0, 0, 0 };
		m_Size = { 1, 1, 1 };
	}

	void AABB::SetSize(const glm::vec3& size)
	{
		ASSERT((size.x > 0 && size.y > 0 && size.z > 0), "Size cannot be negative.")
		m_Size = size;

		RecalculatePoints();
	}

	void AABB::SetPosition(const glm::vec3& position)
	{
		m_Position = position;

		RecalculatePoints();
	}

	bool AABB::IsPointInsideBounds(const glm::vec3& point) const
	{
		// Check if collider is not inverted
		ASSERT(!IsInverted(), "Collider can not be negative")

			// Calculate if point intersects with aabb.
			return(
				point.x >= m_Points[0].x && point.x <= m_Points[1].x &&
				point.y >= m_Points[0].x && point.y <= m_Points[1].y &&
				point.z >= m_Points[0].x && point.z <= m_Points[1].z
				);
	}

	RefPtr<Collision> AABB::Intersects(const AABB& aabb)
	{
		// Check if collider is not inverted
		ASSERT(!IsInverted(), "Collider can not be negative")

			// Calculates if 2 aabbs are intersecting.
			bool intersects = (
				aabb.m_Points[0].x <= m_Points[1].x && aabb.m_Points[1].x >= m_Points[0].x &&
				aabb.m_Points[0].y <= m_Points[1].y && aabb.m_Points[1].y >= m_Points[0].y &&
				aabb.m_Points[0].z <= m_Points[1].z && aabb.m_Points[1].z >= m_Points[0].z
				);

		// Return nullptr if object does not intersect.
		if (!intersects)
		{
			return nullptr;
		}

		glm::vec3 size;

		// Calculate which reference point you measure from for all axis.
		short xIndex = Center().x > aabb.Center().x ? 1 : 0;
		size.x = m_Points[xIndex].x - aabb.m_Points[xIndex].x;

		short yIndex = Center().y > aabb.Center().y ? 1 : 0;
		size.y = m_Points[yIndex].y - aabb.m_Points[yIndex].y;

		short zIndex = Center().z > aabb.Center().z ? 1 : 0;
		size.z = m_Points[zIndex].z - aabb.m_Points[zIndex].z;

		// Get intersection depth.
		float ax = glm::abs(size.x);
		float ay = glm::abs(size.y);
		float az = glm::abs(size.z);

		// Calculate which side is the right normal.
		float sx = Center().x < aabb.Center().x ? -1.0f : 1.0f;
		float sy = Center().y < aabb.Center().y ? -1.0f : 1.0f;
		float sz = Center().z < aabb.Center().z ? -1.0f : 1.0f;

		glm::vec3 normal = glm::vec3(0.0f);

		// Calculate which normal has the closest intersection depth.
		if (ax <= ay && ax <= az)
			normal = glm::vec3(sx, 0.0f, 0.0f);
		else if (ay <= az)
			normal = glm::vec3(0.0f, sy, 0.0f);
		else
			normal = glm::vec3(0.0f, 0.0f, sz);

		// Create and assign collision object.
		RefPtr<Collision> col = std::make_shared<Collision>();
		col->Normal = normal;
		return col;
	}

	bool AABB::IsInverted() const
	{	
		// See if point B is lower than point a because that is invalid.
		return m_Points[0].x > m_Points[1].x ||
			   m_Points[0].y > m_Points[1].y ||	
			   m_Points[0].z > m_Points[1].z;
	}

	void AABB::RecalculatePoints()
	{
		// Calculate bounding box points
		m_Points[0] = m_Position - m_Size * 0.5f;
		m_Points[1] = m_Position + m_Size * 0.5f;
	}
}