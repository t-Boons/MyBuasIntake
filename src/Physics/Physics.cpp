// 2023 Tygo Boons

// Raycast algorithm reference.
// https://gdbooks.gitbooks.io/3dcollisions/content/Chapter3/raycast_aabb.html

#include "mypch.h"
#include "Physics.h"
#include "AABB.h"

namespace Physics
{
    RefPtr<PhysicsEnviroment> Physics::s_Enviroment = nullptr;

    std::vector<RefPtr<RaycastHit>> Physics::RayCastAll(const glm::vec3& origin, const glm::vec3& direction, float distance)
    {
        std::vector<RefPtr<RaycastHit>> hits;

        // Loop through all colliders.
        for (auto& colliderComponent : s_Enviroment->GetColliderComponents())
        {
            // Get AABB points.
            std::array<glm::vec3, 2> points = colliderComponent->GetAABB().GetPoints();

            // Normalize direction just in case.
            glm::vec3 nDirection = glm::normalize(direction);

            // Calculate potential intersection points for all faces.
            float t1 = (points[0].x - origin.x) / nDirection.x;
            float t2 = (points[1].x - origin.x) / nDirection.x;
            float t3 = (points[0].y - origin.y) / nDirection.y;
            float t4 = (points[1].y - origin.y) / nDirection.y;
            float t5 = (points[0].z - origin.z) / nDirection.z;
            float t6 = (points[1].z - origin.z) / nDirection.z;

            // Calculate closest and furthest intersection points.
            float tmin = glm::max(glm::max(glm::min(t1, t2), glm::min(t3, t4)), glm::min(t5, t6));
            float tmax = glm::min(glm::min(glm::max(t1, t2), glm::max(t3, t4)), glm::max(t5, t6));

            // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
            if (tmax < 0) {
                continue;
            }

            // if tmin > tmax, ray doesn't intersect AABB
            if (tmin > tmax) {
                continue;
            }

            // Intersection.
            if (tmin < 0.0f)
            {
                // Create raycast hit.
                RefPtr<RaycastHit> hit = RaycastHit::Create();
                hit->Point = origin + direction * tmax;
                hit->HitObject = colliderComponent->Parent;
                hit->Distance = tmax;
                hits.push_back(hit);
            }
            else
            {
                // Create raycast hit.
                RefPtr<RaycastHit> hit = RaycastHit::Create();
                hit->Point = origin + direction * tmin;
                hit->HitObject = colliderComponent->Parent;
                hit->Distance = tmin;
                hits.push_back(hit);
            }
        }

        return hits;
    }

    RefPtr<RaycastHit> Physics::RayCast(const glm::vec3& origin, const glm::vec3& direction, float distance)
    {
        // Pretty inefficient but it works for now;
        std::vector<RefPtr<RaycastHit>> hits = RayCastAll(origin, direction, distance);

        // Return null if no hits are found.
        if (hits.size() == 0)
        {
            return nullptr;
        }

        RefPtr<RaycastHit> closestHit = hits[0];

        // Gets the closest object to the origin.
        for (auto& hit : hits)
        {
            if (hit->Distance < closestHit->Distance)
            {
                closestHit = hit;
            }
        }

        return closestHit;
    }
}