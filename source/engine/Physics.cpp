#include "Physics.h"
#include "Entity.h"

namespace physics{
    bool AABB(Entity& a, Entity& b){
        /* Axis-Aligned Bounding Box Algorithm */

        Vector endA = a.GetPosition() + a.GetScale();
        Vector endB = b.GetPosition() + b.GetScale();

        if (a.GetPosition().x < endB.x && endA.x > b.GetPosition().x){
            if (a.GetPosition().y < endB.y && endA.y > b.GetPosition().y)
                return true;
        }
        return false;
    }
} // namespace physics