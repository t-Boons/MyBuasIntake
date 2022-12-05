// 2022 Tygo Boons

#pragma once

#include "glm/glm.hpp"
#include "Core/core.h"

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

	class AABB
	{
	public:
		AABB();

		// Set size of bounding box.
		void SetSize(const glm::vec3& size);

		// Set position of bounding box.
		void SetPosition(const glm::vec3& position);

		// Check if point is inside of AABB.
		bool IsPointInsideBounds(const glm::vec3& point);

		// Check if AABB is inside of AABB.
		bool Intersects(const AABB& aabb);

		// Get the closest point to edge inside of aabb.
		glm::vec3 GetClosestPoint(const glm::vec3& point);

		// Returns if the AABB is inverted.
		bool IsInverted();

		// Recalculate bounding box points.
		void RecalculatePoints();

	public:
		// Overload getter operator to get AABB points.
		const glm::vec3& operator [](int i) const
		{
			ASSERT(i < 2, "Only 2 points on Bounding box")
			return Points[i];
		}

	private:
		std::array<glm::vec3, 2> Points;
		glm::vec3 Position, Size;
	};
}
