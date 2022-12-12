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

	RefPtr<Collision> AABB::Intersects(const AABB& aabb)
	{
		// Check if collider is not inverted
		ASSERT(!IsInverted(), "Collider can not be negative")

		// Calculates if 2 aabbs are intersecting.
		bool intersects = (
			aabb.Points[0].x <= Points[1].x && aabb.Points[1].x >= Points[0].x &&
			aabb.Points[0].y <= Points[1].y && aabb.Points[1].y >= Points[0].y &&
			aabb.Points[0].z <= Points[1].z && aabb.Points[1].z >= Points[0].z
			);

		// Update if not intersecting.
		if (!intersects)
		{
			// Calculate and update normal values.
			glm::vec3 normal = { 0, 0, 0 };

			// Update Y axis.
			if (aabb.Points[0].x <= Points[1].x && aabb.Points[1].x >= Points[0].x)
			{
				normal.y = aabb.Points[0].y < Points[0].y ? 1 : -1;
			}

			// Update X Axis.
			if (aabb.Points[0].y <= Points[1].y && aabb.Points[1].y >= Points[0].y)
			{
				normal.x = aabb.Points[0].x < Points[0].x ? 1 : -1;
			}

			// Update Z Axis.
			if (normal.x != 0 && normal.y != 0)
			{
				normal.y = 0;
				normal.x = 0;
				normal.z = aabb.Points[0].z < Points[0].z ? 1 : -1;
			}

			// Set reference normal.
			Normal = normal;

			return nullptr;
		}

		// Create and assign collision object.
		RefPtr<Collision> col = std::make_shared<Collision>();
		col->Normal = Normal;
		return col;
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