#include "raylib.h"

#include "PhysicsWorld.h"

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

     
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    Vector3 cubePosition2 = { 0.0f, -1.0f, 0.0f };

    PhysicsWorld physicsWorld;
    physicsWorld.Init();

    //Initialize Physics Object
    Object cubeObject;
    BoxCollider boxCollider;
    boxCollider.scale = {2.0f, 2.0f, 2.0f};
    cubeObject.collider  = &boxCollider;
    cubeObject.position.x = 0.5f;
    physicsWorld.objects.push_back(&cubeObject);
    
    Object cubeObject2;
    cubeObject2.mass = 0.0f;
    BoxCollider boxCollider2;
    boxCollider2.scale = {10.0f, 2.0f, 10.0f};
    cubeObject2.collider  = &boxCollider2;
    cubeObject2.position.y = -2.0f;
    physicsWorld.objects.push_back(&cubeObject2);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

                BeginMode3D(camera);

                cubePosition.x = cubeObject.position.x;
                cubePosition.y = cubeObject.position.y;
                cubePosition.z = cubeObject.position.z;
                boxCollider.position = cubePosition;

                cubePosition2.x = cubeObject2.position.x;
                cubePosition2.y = cubeObject2.position.y;
                cubePosition2.z = cubeObject2.position.z;
                boxCollider2.position = cubePosition2;

                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                DrawCube(cubePosition2, 10.0f, 2.0f, 10.0f, BLUE);
                DrawCubeWires(cubePosition2, 10.0f, 2.0f, 10.0f, MAROON);

                //DrawGrid(10, 1.0f);

                EndMode3D();
            if(IsKeyDown(KEY_B))
            {
                
            }

            physicsWorld.Step(GetFrameTime()); 

            if(IsKeyPressed(KEY_A))
            {
                cout << cubeObject.force.y << endl;
                cubeObject.velocity.y += 10.0f;     
                cout << cubeObject.force.y << endl;           
            }
            

            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();

    return 0;
}