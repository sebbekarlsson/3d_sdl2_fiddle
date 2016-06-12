#include "Instance.h"
#include "Camera.h"
#include "Scene.h"


#ifndef TESTSCENE_H
#define TESTSCENE_H

class TestScene: public Scene {
    public:
        TestScene();
        void tick (float delta);
        void initialize(float delta);
        void keyUpEvent(SDL_Event e);
        void draw(float delta);
        void drawGUI(float delta);
};

#endif
