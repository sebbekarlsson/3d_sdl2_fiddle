#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#include "Camera.h"
#pragma once
#ifndef SCENE_H
#define SCENE_H


class Scene {
    public:
        Camera *camera;
        bool initialized;

        Scene();

        /**
         * This function is used to draw all instances in this scene.
        */
        void drawInstances(float delta) {
        }

        /**
         * This function is used to tick all instances in this scene.
        */
        void tickInstances(float delta) {
        }

        virtual void initialize(float delta) = 0;
        virtual void tick(float delta) = 0;
        virtual void draw(float delta) = 0;
        virtual void drawGUI(float delta) = 0;
        virtual void keyUpEvent(SDL_Event e) = 0;
};

#endif
