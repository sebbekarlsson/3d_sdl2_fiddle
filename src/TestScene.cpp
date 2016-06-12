#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#include "TestScene.h"

TestScene::TestScene() : Scene() {}

void TestScene::tick(float delta) {
    this->camera->tick(delta);
}

void TestScene::draw(float delta) {}

void TestScene::drawGUI(float delta) {}

void TestScene::initialize(float delta) {}

void TestScene::keyUpEvent(SDL_Event e) {}
