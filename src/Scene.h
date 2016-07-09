#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#include <vector>
#include "Camera.h"
#pragma once
#ifndef SCENE_H
#define SCENE_H


using namespace std;

class Scene {
    public:
        Camera *camera;
        bool initialized;
        std::vector<Instance *> instances;

        Scene();

        void instantiate(Instance * instance);

        virtual void initialize(float delta) = 0;
        virtual void tick(float delta) = 0;
        virtual void draw(float delta) = 0;
        virtual void drawGUI(float delta) = 0;
        virtual void keyUpEvent(SDL_Event e) = 0;
};

#endif
