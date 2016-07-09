#pragma once
#include <iostream>
#include <typeinfo>
#include <string>
#include <iostream>
#ifndef INSTANCE_H
#define INSTANCE_H


using namespace std;

class Instance {
    public:
        float x, y, z;
        float w, h, l;
        float friction;
        string type;

        Instance (float x, float y, float z);

        virtual void tick(float delta) = 0;
        virtual void draw(float delta) = 0;
};

#endif
