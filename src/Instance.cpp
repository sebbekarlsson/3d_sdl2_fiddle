#include "Instance.h"

Instance::Instance(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 0;
    this->h = 0;
    this->l = 0;
    this->friction = 1.0f;
    this->type = "instance";
}
