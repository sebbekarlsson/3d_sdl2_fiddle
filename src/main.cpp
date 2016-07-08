#include "SDLImageLoader.h"
#include <string>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <memory>
#include <list>
#include <iterator>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#include "Instance.h"
#include "App.h"
#include "TestScene.h"


const Uint8 *keys;
const Uint8 *state = SDL_GetKeyboardState(NULL);

int main (int argc, char* args[]) {
    keys = SDL_GetKeyboardState(NULL);
    App * app = new App();
    srand(time(NULL));
    app->init();

    app->scenes.insert(app->scenes.begin(), new TestScene());

    SDL_Event e;
    float delta;
    int newTime;
    int oldTime = SDL_GetTicks(); 
    while (!app->quit) {
        newTime = SDL_GetTicks(); 
        delta = (float) (newTime - oldTime) / 1000;

        SDL_PumpEvents();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_TEXTINPUT) {
            }
            if (e.type == SDL_KEYUP) {
                app->keyUpEvent(e);
            }
            if (e.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
                app->quit = true;
            }
            if(e.type == SDL_MOUSEMOTION) {
                app->mouseMoveEvent(
                        e.motion.x,
                        e.motion.y,
                        e.motion.xrel,
                        e.motion.yrel
                        );
            }
        }

        app->tick(delta);
        app->draw(delta);

        SDL_GL_SwapWindow(app->_display);
        SDL_Delay(1);
        oldTime = newTime; 
    }
    app->close();

    return 0;
}
