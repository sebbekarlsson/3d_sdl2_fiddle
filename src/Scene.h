#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#include <vector>
#include "macros.h"
#include "Camera.h"


#ifndef SCENE_H
#define SCENE_H

using namespace std;

class Scene {
    public:
        Camera *camera;
        bool initialized;
        std::vector<Instance*> instances;
        std::vector<Instance*>::iterator instanceIter;

        Scene();

        void instantiate(Instance * instance);
        void tickInstances(float delta);
        void drawInstances(float delta);

        virtual void initialize(float delta) = 0;
        virtual void tick(float delta) = 0;
        virtual void draw(float delta) = 0;
        virtual void drawGUI(float delta) = 0;
        virtual void keyUpEvent(SDL_Event e) = 0;
};

#endif
