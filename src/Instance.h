#pragma once
#include <iostream>
#include <typeinfo>
#include <string>
#include <iostream>


using namespace std;

class Instance {
    public:
        float x, y, z;
        float w, h, l;
        float friction;
        string type;

        Instance (float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = 0;
            this->h = 0;
            this->l = 0;
            this->friction = 1.0f;
            this->type = "instance";
        }

        virtual void tick(float delta) = 0;
        virtual void draw(float delta) = 0;
};
