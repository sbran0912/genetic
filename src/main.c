#include "lib_core.h"

typedef struct vehicle_t {
    Vector2 location;
    Vector2 velocity;
    Vector2 accel;
    Vector2 heading;
    float radius;
    float max_steer;
    float max_desired;
} Vehicle;

typedef struct target_t {
    Vector2 location;
    float zone;
} Target;

Vehicle createVehicle(float x, float y, float r) {
    Vehicle result = {
        .location = {x, y},
        .radius = r,
        .velocity = {0, 0},
        .accel = {0, 0},
        .max_steer = 5.0f,
        .max_desired = 8.0f
        };
    return result;
} 

Target createTarget(float x, float y, float z) {
    Target result = {
        .location = {x, y},
        .zone = z
    };
    return result;
}

void applyForce(Vehicle *vehic, Vector2 force) {
    vehic->accel = vec2_add(vehic->accel, vec2_div(force, vehic->radius*2));
}

void seek(Vehicle* vehic, Vector2 target) {

    Vector2 desired = vec2_setMag(vec2_sub(target, vehic->location), vehic->max_desired);
    Vector2 steer = vec2_limit(vec2_sub(desired, vehic->velocity), vehic->max_steer); 
    applyForce(vehic, steer);
}

void updateVehicle(Vehicle* vehic) {
    vehic->velocity = vec2_limit(vec2_add(vehic->velocity, vehic->accel), 13.0f);
    vehic->accel = (Vector2){0.0f, 0.0f};
    vehic->location = vec2_add(vehic->location, vehic->velocity);
}

void drawVehicle(Vehicle* vehic, Color c) {

    Vector2 points[3];
    Vector2 back = vec2_sub(vehic->location, vec2_setMag(vehic->velocity, vehic->radius));
    Vector2 perp = vec2_setMag((Vector2){-(vehic->velocity.y), vehic->velocity.x}, vehic->radius/2);
    
    points[0] = vehic->location;
    points[1] = vec2_add(back, perp);
    points[2] = vec2_sub(back, perp);

    DrawTriangle(points[0], points[2],points[1], c);
    
}

void drawTarget(Target* target, Color c1) {
    DrawCircleV(target->location, 5, c1);
}

Vector2* createFood(size_t count) {
    Vector2* food = dynarr_create(count, Vector2);
    for (size_t i = 0; i < count; i++)
    {
        Vector2 pos = {random_num(1, GetScreenWidth()), random_num(1, GetScreenHeight()) };
        arr_append(&food, &pos);
    }
    return food;
}

void drawFood(Vector2* food, Color c) {
    for (size_t i = 0; i < dynarr_len(food); i++)
    {
        DrawCircleV(food[i], 4, c);
    }
    
}

void eatFood() {

}

int main() {
    const int screenWidth = 1600;
    const int screenHeight = 1200; 
    InitWindow(screenWidth, screenHeight, "seeking and arrive");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Target target = createTarget(800, 600, 200);
    Vehicle mover = createVehicle(100, 400, 20);
    mover.velocity = (Vector2){12, -8};    
    Vector2* food = createFood(15);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        seek(&mover, target.location);
        updateVehicle(&mover);
        ClearBackground(DARKBLUE);
        drawVehicle(&mover, LIGHTGRAY);
        //drawTarget(&target, GREEN);
        drawFood(food, GREEN);
    	EndDrawing();
    }

    CloseWindow();   

    return EXIT_SUCCESS;
}
