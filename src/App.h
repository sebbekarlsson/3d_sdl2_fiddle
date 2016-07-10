#include "SDLImageLoader.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include "Scene.h"


#ifndef APP_H
#define APP_H

class App {
    public:
        bool quit;
        SDL_GLContext context;
        std::vector<Scene*> scenes;
        int sceneIndex;
        SDL_Window* _display = NULL;
        SDL_Renderer* _renderer = NULL;
        int mouseX;
        int mouseY;
        SDL_bool mouseTrap;
        SDLImageLoader * imgLoader;
        EasyImage * img2;
        EasyImage * girl_image;

        App();

        bool init();
        bool initGL();
        void mouseEvent(int &mouseX, int &mouseY);
        void mouseMoveEvent(
                int &mouseX,
                int &mouseY,
                int &deltaMouseX,
                int &deltaMouseY
                );
        Scene* getCurrentScene();
        void tick(float delta);
        void draw(float delta);
        bool keyUpEvent(SDL_Event &e);
        void close();
};

#endif
