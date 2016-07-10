#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#include "TestScene.h"


TestScene::TestScene() : Scene() {
    this->handHeld =  new Gun(1.0f, -1.5f, -2.0f);
}

void TestScene::tick(float delta) {
    this->camera->tick(delta);
    this->tickInstances(delta);
}

void TestScene::draw(float delta) {
    this->drawInstances(delta);
}

void TestScene::drawGUI(float delta) {
    this->handHeld->draw(delta);
}

void TestScene::initialize(float delta) {
    for (int i = 0; i < 10; i++) {
        for (int ii = 0; ii < 10; ii++) {
            if (rand() % 3 + 0 == 0) {
                this->instantiate(new Cube(i*6,0,ii*6));
                if (rand() % 3 + 0 == 0) {
                    this->instantiate(new Cube(i*6,4,ii*6));
                }
            }
        }
    }
}

void TestScene::keyUpEvent(SDL_Event e) {}
