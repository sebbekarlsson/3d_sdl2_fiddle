#include "SDLImageLoader.h"
#include "Instance.h"
#include <SDL2/SDL_opengl.h>

#ifndef CUBE_H
#define CUBE_H


class Cube: public Instance {
    public:
        SDLImageLoader * imageLoader;
        EasyImage * img;
        float angle;

        Cube(float x, float y, float z);
        void draw(float delta);
        void tick(float delta);
};

#endif
