#include "Physics.h"
#include "Entity.h"

static bool Intersect(Vector& a, Vector& endA, Vector& b){
    if (a.x < b.x && a.y < b.y){
        if (b.x < endA.x && b.y < endA.y){
            return true;
        }
    }
    return false;
}

namespace physics{
    bool AABB(Entity* a, Entity* b){
        Vector endA(a->GetPosition()->x + a->GetScale()->x, a->GetPosition()->y + a->GetScale()->y);
        Vector endB(b->GetPosition()->x + b->GetScale()->x, b->GetPosition()->y + b->GetScale()->y);

        if (Intersect(*a->GetPosition(), endA, *b->GetPosition())){
            if (Intersect(*b->GetPosition(), endB, *a->GetPosition())){
                return true;
            }
        }
        return false;
    }
} // namespace physics