#pragma once
#include "MathHelper.h"


extern const Uint8 * state;
class Camera: public Instance {
    public:
        float zoom;
        float dx, dy, dz;
        float xrot, yrot, zrot;
        float friction;
        float lastXDirection;
        float lastZDirection;

        Camera (float x, float y, float z) : Instance(x, y, z) {
            this->friction = 0.99f;
            this->dx = 0.0f;
            this->dy = 0.0f;
            this->dz = 0.0f;
            this->xrot = 0.0f;
            this->yrot = 0.0f;
            this->zrot = 0.0f;
            this->lastXDirection = 0.0f;
            this->lastZDirection = 0.0f;
        }

        void tick(float delta) {
            float dir = yrot;
            float walk = 0.0f;

            if (state[SDL_SCANCODE_A]) {
                walk = 1.3f; 
                dir += 90.0f;

                this->lastXDirection = sin(MathHelper::toRadians(dir));
                this->lastZDirection = cos(MathHelper::toRadians(dir));

            }
            if (state[SDL_SCANCODE_D]) {
                walk = 1.3f; 
                dir -= 90.0f;

                this->lastXDirection = sin(MathHelper::toRadians(dir));
                this->lastZDirection = cos(MathHelper::toRadians(dir));
            }

            if (state[SDL_SCANCODE_W]) {
                walk = 1.3f;
                dir = yrot;

                if (state[SDL_SCANCODE_A]) {
                    dir += 90.0f/2;

                }
                if (state[SDL_SCANCODE_D]) {
                    dir -= 90.0f/2;
                }

                this->lastXDirection = sin(MathHelper::toRadians(dir));
                this->lastZDirection = cos(MathHelper::toRadians(dir));
            }

            if (state[SDL_SCANCODE_S]) {
                walk = -1.3f;
                dir = yrot;

                if (state[SDL_SCANCODE_A]) {
                    dir -= 90.0f/2;

                }
                if (state[SDL_SCANCODE_D]) {
                    dir += 90.0f/2;
                }

                this->lastXDirection = sin(MathHelper::toRadians(dir));
                this->lastZDirection = cos(MathHelper::toRadians(dir));
            }

            if (state[SDL_SCANCODE_SPACE]) {
                if (y <= 8.0f) {
                    dy += 50.0f;
                }
            }

            dx -= sin(MathHelper::toRadians(dir)) * walk;
            dz -= cos(MathHelper::toRadians(dir)) * walk;

            this->updatePhysics(delta);
        }
        void draw(float delta) {
        }

        void updatePhysics (float delta) {
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

            /*if(dy > 0){
                if(dy - friction < 0){
                    dy = 0;
                }else{
                    dy -= friction;
                }
            }
            if(dy < 0){
                if(dy + friction > 0){
                    dy = 0;
                }else{
                    dy += friction;
                }
            }*/

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


            if (y > 8.0f) {
                dy -= 0.40f;
                if (y + dy*delta < 8.0f) {
                    y = 8.0f;
                    dy = 0.0f;
                }
            }

            x += dx * delta;
            y += dy * delta;
            z += dz * delta;
        }

        void mouseMoveEvent(int mouseX, int mouseY, int deltaMouseX, int deltaMouseY) {
            xrot -= (deltaMouseY * 0.25f);
            yrot -= (deltaMouseX * 0.25f);
        }
};
