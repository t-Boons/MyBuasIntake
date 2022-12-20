// 2022 Tygo Boons

// Intersection normal calculation Inspired from:
// https://gamedev.stackexchange.com/questions/48816/how-to-calculate-collision-normal-between-two-axisalignedboxs 
// Old method did not work properly.

#pragma once

#include "glm/glm.hpp"
#include "Core/Core.h"

namespace Physics
{

	/*
				 -----------	|	
		       /|          /|	|	      y+	
		      / |         / |	|		  | z-
		     /  |        /  |	|     	  |/ 
		     ---A-------B   |	|  x- ----o---- x+ 
		    |  /        |  /	|	     /|
		    | /         | /		|	    z+| 
		    |/          |/		|	      y-
		     -----------		o--------------------
	  
			  AABB Collision box point reference &
			  Transformation axis reference.
			  
			  Points[0] is A.
			  Points[1] is B.
	*/

	struct Collision
	{
	public:
		Collision()
			: Normal({ 0, 0, 0 })
		{}

		glm::vec3 Normal;
		std::string ThisObjectName;
		std::string HitObjectName;
	};

	class AABB
	{
	public:
		AABB();

		// Set size of bounding box.
		void SetSize(const glm::vec3& size);

		// Set position of bounding box.
		void SetPosition(const glm::vec3& position);

		// Check if point is inside of AABB.
		bool IsPointInsideBounds(const glm::vec3& point) const;

		// Check if AABB is inside of AABB.
		RefPtr<Collision> Intersects(const AABB& aabb);

		// Returns if the AABB is inverted.
		bool IsInverted() const;

		// Recalculate bounding box points.
		void RecalculatePoints();

		glm::vec3 Center() const { return Points[0] + Points[1] - Points[0]; }

	public:
		// Overload getter operator to get AABB points.
		const glm::vec3& operator [](int i) const
		{
			ASSERT(i < 2, "Only 2 points on Bounding box")
			return Points[i];
		}

	private:
		glm::vec3 Normal;
		std::array<glm::vec3, 2> Points;
		glm::vec3 Position, Size;
	};
}
