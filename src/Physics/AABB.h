// 2022 Tygo Boons

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
		glm::vec3 Normal;
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
