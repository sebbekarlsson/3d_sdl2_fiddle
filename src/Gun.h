#include <tiny_obj_loader.h>
#include "SDLImageLoader.h"
#include "Instance.h"
#include <SDL2/SDL_opengl.h>

#ifndef GUN_H
#define GUN_H


class Gun: public Instance {
    public:
        SDLImageLoader * imageLoader;
        EasyImage * img;
        float angle;
        std::string inputfile;
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string err;
        bool ret;
        float xrot, yrot, zrot;
        float dxrot, dyrot, dzrot;
        float dx, dy, dz;
        float xsway;
        float zsway;

        Gun(float x, float y, float z);
        void draw(float delta);
        void tick(float delta);
};

#endif
