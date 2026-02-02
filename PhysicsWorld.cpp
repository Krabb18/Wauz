#include "PhysicsWorld.h"

void PhysicsWorld::Init()
{
    gravity.x = 0.0f;
    gravity.y = -9.0f;
    gravity.z = 0.0f;
}

void PhysicsWorld::Step(float dt)
{

    for(auto &obj : objects)
    {

        if(obj->mass != 0.0f)
        {
            obj->force.x += obj->mass * gravity.x;
            obj->force.y += obj->mass * gravity.y;
            obj->force.z += obj->mass * gravity.z;

            obj->velocity.x += obj->force.x / obj->mass * dt;
            obj->velocity.y += obj->force.y / obj->mass * dt;
            obj->velocity.z += obj->force.z / obj->mass * dt;

            obj->position.x += obj->velocity.x * dt;
            obj->position.y += obj->velocity.y * dt;
            obj->position.z += obj->velocity.z * dt;

            obj->force.x = 0.0f; obj->force.y = 0.0f; obj->force.z = 0.0f;
        }
    }

    CollisionDetection();
    
}

void PhysicsWorld::CollisionDetection()
{
    for(auto &objA : objects)
    {
        for(auto &objB : objects)
        {
            if(objA == objB){continue;}

            if(objA->collider != nullptr && objB->collider != nullptr)
            {
                if(objA->collider->type == ColliderType::BOX && objB->collider->type == ColliderType::BOX)
                {
                    
                    BoxCollider* coll1 = dynamic_cast<BoxCollider*>(objA->collider);
                    BoxCollider* coll2 = dynamic_cast<BoxCollider*>(objB->collider);
                    bool didCollide = CheckCollisionBox(coll1, coll2);

                    if(didCollide)
                    {
                        cout << "Collision between boxes" << endl;
                        ResolveCollisionBox(objA,objB);
                    }
                }
                else if(objA->collider->type == ColliderType::SPHERE && objB->collider->type == ColliderType::SPHERE)
                {
                    SphereCollider* coll1 = dynamic_cast<SphereCollider*>(objA->collider);
                    SphereCollider* coll2 = dynamic_cast<SphereCollider*>(objB->collider);
                    bool didCollide = CheckCollisionSphere(coll1, coll2);

                    if(didCollide)
                    {
                        cout << "Collision between Spheres" << endl;
                    }
                }
                else if((objA->collider->type == ColliderType::SPHERE && objB->collider->type == ColliderType::BOX))
                {
                    SphereCollider* coll1 = dynamic_cast<SphereCollider*>(objA->collider);
                    BoxCollider* coll2 = dynamic_cast<BoxCollider*>(objB->collider);
                    bool didCollide = CheckCollisionBoxSphere(coll1, coll2);

                    if(didCollide)
                    {
                        cout << "Collision between Sphere and Box" << endl;
                    }
                }
            }
        }    
    }    
}


//COLLISION DETECTION FUNCTIONS
bool PhysicsWorld::CheckCollisionSphere(SphereCollider *collider1, SphereCollider* collider2)
{
    float dx = collider1->Center.x - collider2->Center.x;
    float dy = collider1->Center.y - collider2->Center.y;
    float dz = collider1->Center.z - collider2->Center.z;

    float distance = sqrtf(dx*dx + dy*dy + dz*dz);
    return distance <= (collider1->Radius + collider2->Radius);
}

bool PhysicsWorld::CheckCollisionBox(BoxCollider* box1, BoxCollider *box2)
{
    box1->Calc2();
    box2->Calc2();

    bool collision = true;

    if ((box1->max.x >= box2->min.x) && (box1->min.x <= box2->max.x))
    {
        if ((box1->max.y < box2->min.y) || (box1->min.y > box2->max.y)) collision = false;
        if ((box1->max.z < box2->min.z) || (box1->min.z > box2->max.z)) collision = false;
    }
    else collision = false;

    return collision;
}

bool PhysicsWorld::CheckCollisionBoxSphere(SphereCollider *collider1, BoxCollider* collider2)
{
    collider2->Calc();
}


//RESOLVE FUNCTIONS
void PhysicsWorld::ResolveCollisionSphere(Object *collider1, Object* collider2)
{

}

void PhysicsWorld::ResolveCollisionBox(Object* obj1, Object* obj2)
{
    BoxCollider* box1 = dynamic_cast<BoxCollider*>(obj1->collider);
    BoxCollider* box2 = dynamic_cast<BoxCollider*>(obj2->collider);

    Vector3 delta;
    delta.x = box2->position.x - box1->position.x;
    delta.y = box2->position.y - box1->position.y;
    delta.z = box2->position.z - box1->position.z;

    float xOverlap = (box1->extends.x + box2->extends.x) - abs(delta.x);
    float yOverlap = (box1->extends.y + box2->extends.y) - abs(delta.y);
    float zOverlap = (box1->extends.z + box2->extends.z) - abs(delta.z);

    float minOverlap = min(xOverlap, min(yOverlap, zOverlap));

    Vector3 correction = {0.0f, 0.0f, 0.0f};
    if(minOverlap == xOverlap)
    {
        correction.x = (delta.x > 0 ? -1 : 1) * xOverlap;
    }
    else if(minOverlap == yOverlap)
    {
        correction.y = (delta.y > 0 ? -1 : 1) * yOverlap;
    }
    else if(minOverlap == zOverlap)
    {
        correction.z = (delta.z > 0 ? -1 : 1) * zOverlap;
    }

    //Maybe later with velocity
    box1->position.x += correction.x;
    box1->position.y += correction.y;
    box1->position.z += correction.z;

    
    obj1->position.x += correction.x;
    obj1->position.y += correction.y;
    obj1->position.z += correction.z;

    obj1->velocity.x = 0.0f;
    obj1->velocity.y = 0.0f;
    obj1->velocity.z = 0.0f;
}
