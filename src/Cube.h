#include "Instance.h"
#ifndef CUBE_H
#define CUBE_H

class Cube: public Instance {
    public:
        Cube(float x, float y, float z);
        void draw(float delta);
        void tick(float delta);
};

#endif
