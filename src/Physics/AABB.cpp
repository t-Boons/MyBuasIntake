// 2022 Tygo Boons

#include "mypch.h"

#include "AABB.h"

namespace Physics
{
	AABB::AABB()
	{
		// Assign 0 to all points.
		memset(&Points, 0, sizeof(Points));
		Position = { 0, 0, 0 };
		Size = { 1, 1, 1 };
	}

	void AABB::SetSize(const glm::vec3& size)
	{
		ASSERT((size.x > 0 && size.y > 0 && size.z > 0), "Size cannot be negative.")
		Size = size;

		RecalculatePoints();
	}

	void AABB::SetPosition(const glm::vec3& position)
	{
		Position = position;

		RecalculatePoints();
	}

	bool AABB::IsPointInsideBounds(const glm::vec3& point) const
	{
		// Check if collider is not inverted
		ASSERT(!IsInverted(), "Collider can not be negative")

			// Calculate if point intersects with aabb.
			return(
				point.x >= Points[0].x && point.x <= Points[1].x &&
				point.y >= Points[0].x && point.y <= Points[1].y &&
				point.z >= Points[0].x && point.z <= Points[1].z
				);
	}

	bool AABB::Intersects(const AABB& aabb) const
	{
		// Check if collider is not inverted
		ASSERT(!IsInverted(), "Collider can not be negative")

			// Calculates if 2 aabbs are intersecting.
			return (
				aabb.Points[0].x <= Points[1].x && aabb.Points[1].x >= Points[0].x &&
				aabb.Points[0].y <= Points[1].y && aabb.Points[1].y >= Points[0].y &&
				aabb.Points[0].z <= Points[1].z && aabb.Points[1].z >= Points[0].z
				);
	}

	glm::vec3 AABB::GetClosestPoint(const glm::vec3& point) const
	{ 
		// Check if collider is not inverted
		ASSERT(!IsInverted(), "Collider can not be negative")

		// Get the center of the AABB.
		glm::vec3 center = (Points[1] - Points[0]) * 0.5f + Points[0];

		// Calculate closest points on the edge of aabb.
		float x = (point.x < center.x ? -(point.x - Points[0].x) + point.x : Points[1].x - point.x + point.x);
		float y = (point.y < center.y ? -(point.y - Points[0].y) + point.y : Points[1].y - point.y + point.y);
		float z = (point.z < center.z ? -(point.z - Points[0].z) + point.z : Points[1].z - point.z + point.z);

		// Calculate the minimum offset.
		return { x, y, z };
	}

	bool AABB::IsInverted() const
	{	
		// See if point B is lower than point a because that is invalid.
		return Points[0].x > Points[1].x ||
			   Points[0].y > Points[1].y ||	
			   Points[0].z > Points[1].z;
	}

	void AABB::RecalculatePoints()
	{
		// Calculate bounding box points
		Points[0] = Position - Size * 0.5f;
		Points[1] = Position + Size * 0.5f;
	}
}