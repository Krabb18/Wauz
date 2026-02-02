#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <iostream>
#include <vector>

using namespace std;

#include "raylib.h"

#include <math.h>

struct CollisionPoints
{
    Vector3 A;
    Vector3 B;
    Vector3 normal;
    float Depth;
    bool HasCollision;
};


//Colliders
enum ColliderType{
    SPHERE,
    PLANE,
    BOX
};

struct Collider{
    ColliderType type;
    virtual ~Collider() {}
};

struct SphereCollider : Collider {

    SphereCollider()
    {
        type = ColliderType::SPHERE;
    }

	Vector3 Center = {0.0f, 0.0f, 0.0f};;
	float Radius = 0.0f;
};

struct PlaneCollider : Collider {

    PlaneCollider()
    {
        type = ColliderType::PLANE;
    }

	Vector3 Normal= {0.0f, 0.0f, 0.0f};
	float Distance = 0.0f;
};

struct BoxCollider : Collider
{
    Vector3 position = {0.0f, 0.0f, 0.0f};
    Vector3 scale = {0.0f, 0.0f, 0.0f};

    Vector3 min = {0.0f, 0.0f, 0.0f};
    Vector3 max = {0.0f, 0.0f, 0.0f};

    Vector3 extends = {0.0f, 0.0f, 0.0f};

    BoxCollider()
    {
        type = ColliderType::BOX;
    }

    void Calc()
    {
        min.x = position.x;
        max.x = position.x + scale.x;    

        min.y = position.y;
        max.y = position.y + scale.y;  

        min.y = position.y;
        max.y = position.y + scale.y;  
    }

    void Calc2()
    {
        extends.x = scale.x / 2.0f;
        extends.y = scale.y / 2.0f;
        extends.z = scale.z / 2.0f;

        min.x = position.x - (scale.x / 2.0f);
        max.x = position.x + (scale.x / 2.0f);

        min.y = position.y - (scale.y / 2.0f);
        max.y = position.y + (scale.y / 2.0f);

        min.z = position.z - (scale.z / 2.0f);
        max.z = position.z + (scale.z / 2.0f);
    }
};

struct Object
{
    Vector3 force = {0.0f, 0.0f, 0.0f};
    float mass = 1.0f;
    Vector3 velocity= {0.0f, 0.0f, 0.0f};

    Vector3 position= {0.0f, 0.0f, 0.0f};

    Collider* collider;
};

class PhysicsWorld
{
private: 
    bool CheckCollisionSphere(SphereCollider *collider1, SphereCollider* collider2);
    bool CheckCollisionBox(BoxCollider* box1, BoxCollider *box2);
    bool CheckCollisionBoxSphere(SphereCollider *collider1, BoxCollider* collider2);

    void ResolveCollisionSphere(Object *collider1, Object* collider2);
    void ResolveCollisionBox(Object* box1, Object* box2);

public:
    Vector3 gravity= {0.0f, 0.0f, 0.0f};;
    vector<Object*> objects;

    void Init();
    void Step(float dt);

    void CollisionDetection();
};

#endif
