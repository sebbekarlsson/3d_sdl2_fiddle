#include "Camera.h"


Camera::Camera(float x, float y, float z) : Instance(x, y, z) {
    this->friction = 0.75f;
    this->rotationFriction = 1.0f;
    this->dx = 0.0f;
    this->dy = 0.0f;
    this->dz = 0.0f;
    this->dxrot - 0.0f;
    this->xrot = 0.0f;
    this->yrot = 0.0f;
    this->zrot = 0.0f;
    this->lastXDirection = 0.0f;
    this->lastZDirection = 0.0f;
    this->cameraBobSpeed = 30.0f;
    this->bobTime = 30.0f;
    this->bobTimer = bobTime;
    this->bobUp = false;
}

void Camera::draw(float delta) {}

void Camera::tick(float delta) {
    float dir = yrot;
    float walk = 0.0f;
    float walkspeed = 0.82f;
    bool is_walk = false;
     
    this->bobTime = 60/(fabs(dx)+fabs(dz));

    if (state[SDL_SCANCODE_A]) {
        walk = walkspeed; 
        dir += 90.0f;

        this->lastXDirection = sin(MathHelper::toRadians(dir));
        this->lastZDirection = cos(MathHelper::toRadians(dir));
        is_walk = true;

    }
    if (state[SDL_SCANCODE_D]) {
        walk = walkspeed; 
        dir -= 90.0f;

        this->lastXDirection = sin(MathHelper::toRadians(dir));
        this->lastZDirection = cos(MathHelper::toRadians(dir));
        is_walk = true;
    }

    if (state[SDL_SCANCODE_W]) {
        walk = walkspeed;
        dir = yrot;

        if (state[SDL_SCANCODE_A]) {
            dir += 90.0f/2;

        }
        if (state[SDL_SCANCODE_D]) {
            dir -= 90.0f/2;
        }

        this->lastXDirection = sin(MathHelper::toRadians(dir));
        this->lastZDirection = cos(MathHelper::toRadians(dir));
        is_walk = true;
    }

    if (state[SDL_SCANCODE_S]) {
        walk = -walkspeed;
        dir = yrot;

        if (state[SDL_SCANCODE_A]) {
            dir -= 90.0f/2;

        }
        if (state[SDL_SCANCODE_D]) {
            dir += 90.0f/2;
        }

        this->lastXDirection = sin(MathHelper::toRadians(dir));
        this->lastZDirection = cos(MathHelper::toRadians(dir));
        is_walk = true;
    }

    if (state[SDL_SCANCODE_SPACE]) {
        if (y <= 8.0f) {
            dy += 25.0f;
        }
    }

    if (dx > 0 || dx < 0 || dz > 0 || dz < 0) {
        this->cameraBob(delta);
    }

    if (is_walk) {
        dx -= sin(MathHelper::toRadians(dir)) * walk;
        dz -= cos(MathHelper::toRadians(dir)) * walk;
    }

    this->updatePhysics(delta);
}

void Camera::updatePhysics(float delta) {
    if (lastZDirection < 0) {
        lastZDirection = lastZDirection * -1;
    }

    if (lastXDirection < 0) {
        lastXDirection = lastXDirection * -1;
    }

    if(dx > 0){
        if(dx - (lastXDirection * friction) < 0){
            dx = 0;
        }else{
            dx -= lastXDirection * friction;
        }
    }
    if(dx < 0){
        if(dx + (lastXDirection * friction) > 0){
            dx = 0;
        }else{
            dx += lastXDirection * friction;
        }
    }

    if(dz > 0){
        if(dz - (lastZDirection * friction) < 0){
            dz = 0;
        }else{
            dz -= lastZDirection * friction;
        }
    }
    if(dz < 0){
        if(dz + (lastZDirection * friction) > 0){
            dz = 0;
        }else{
            dz += lastZDirection * friction;
        }
    }


    if(dxrot > 0){
        if(dxrot - rotationFriction < 0){
            dxrot = 0;
        }else{
            dxrot -= rotationFriction;
        }
    }
    if(dxrot < 0){
        if(dxrot + rotationFriction > 0){
            dxrot = 0;
        }else{
            dxrot += rotationFriction;
        }
    }


    if (y > 8.0f) {
        dy -= 0.70f;
        if (y + dy*delta < 8.0f) {
            y = 8.0f;
            dy = 0.0f;
        }
    }

    x += dx * delta;
    y += dy * delta;
    z += dz * delta;

    xrot += dxrot * delta;
}

void Camera::mouseMoveEvent(
        int mouseX,
        int mouseY,
        int deltaMouseX,
        int deltaMouseY
        ) {
    xrot -= (deltaMouseY * 0.25f);
    yrot -= (deltaMouseX * 0.25f);
}

void Camera::cameraBob(float delta) {
    if (bobTimer > 0) {
        bobTimer -= 1.0f;
    } else {
        if (bobUp) {
            if (dxrot == 0) {
                dxrot += cameraBobSpeed;
                bobUp = false;
            }
        } else {
            if (dxrot == 0) {
                dxrot -= cameraBobSpeed;
                bobUp = true;
            }
        }
        bobTimer = bobTime;
    }
}
