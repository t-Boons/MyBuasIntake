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
		     ---A-------B   |	|  x+ ----o---- x+ 
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
		glm::vec3 HitOffset;
	};

	struct AABB
	{
		AABB();

		// Check if point is inside of AABB.
		bool Intersects(const glm::vec3& point);

		// Check if AABB is inside of AABB.
		RefPtr<Collision> Intersects(const RefPtr<AABB>& aabb);

		// Get the closest point to edge inside of aabb.
		glm::vec3 GetClosestPoint(const glm::vec3& point);

		// Returns if the AABB is inverted.
		bool IsInverted();

		std::array<glm::vec3, 2> Points;
	};
}
