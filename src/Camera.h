#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "MathHelper.h"
#include "Instance.h"
#ifndef CAMERA_H
#define CAMERA_H

extern const Uint8 * state;
class Camera: public Instance {
    public:
        float zoom;
        float dx, dy, dz;
        float xrot, yrot, zrot;
        float dxrot, dyrot, dzrot;
        float friction;
        float rotationFriction;
        float lastXDirection;
        float lastZDirection;
        float cameraBobSpeed;
        float bobTimer;
        float bobTime;
        bool bobUp;

        Camera (float x, float y, float z);

        void tick(float delta);
        void draw(float delta);
        void updatePhysics (float delta);
        void mouseMoveEvent(int mouseX, int mouseY, int deltaMouseX, int deltaMouseY);
        void cameraBob(float delta);
};

#endif
