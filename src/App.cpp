#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "App.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>


const int WIDTH = 640;
const int HEIGHT = WIDTH / 16 * 9;
const int SCALE = 2;

extern const Uint8 * state;
/**
 * Constructor
 */
App::App () {
    this->sceneIndex = 0;
    this->quit = false;
    this->mouseTrap = SDL_TRUE;
    this->imgLoader = new SDLImageLoader();
    this->img2 = this->imgLoader->load("res/grass.jpg");
    this->girl_image = this->imgLoader->load("res/metrocop_sheet.tga");
}


/**
 * This function is used to initialize the openGL.
 * @return <bool>
 */
bool App::initGL () {
    bool success = true;
    GLenum error = GL_NO_ERROR;

    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);

    //glViewport(0, 0, (WIDTH * SCALE), (HEIGHT * SCALE));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(65.0f, (float)((WIDTH * SCALE)/(HEIGHT * SCALE)), 0.1f, 1000);
    gluPerspective(80,640.0/(640/16*9),0.001f,500.0);
    glMatrixMode(GL_MODELVIEW); 
    //glOrtho(0, (WIDTH * SCALE), (HEIGHT * SCALE), 0, 1, -1);

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glLoadIdentity();    

    glClearColor(
            (float)(0/255),
            (float)(0/255),
            (float)(0/255),
            1.0f
            );


    return success;
}

/**
 * This function is used to initialize the display/window with
 * the OpenGL context.
 * @return <bool>
 */
bool App::init () {
    bool success = true;

    if (!SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize video", SDL_GetError());
        success = false;
    } else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        _display = SDL_CreateWindow (
                "App Title",
                0,
                0,
                WIDTH * SCALE,
                HEIGHT * SCALE,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
                );
        _renderer = SDL_CreateRenderer(_display, -1, SDL_RENDERER_ACCELERATED);

        if (_display == NULL) {
            printf("Could not create display", SDL_GetError());
        } else {
            context = SDL_GL_CreateContext(_display);

            if (context == NULL) {
                printf("Could not create context", SDL_GetError());
                success = false;
            } else {
                if (!initGL()) {
                    printf("Could not initialize OpenGL", SDL_GetError());
                    success = false;
                }
            }
        }
    }

    int argc = 1;
    char *argv[1] = {(char*)"Something"};
    glutInit(&argc, argv);

    return success;
}

Scene* App::getCurrentScene() {
    return scenes[sceneIndex];
}

void App::mouseEvent(int &mouseX, int &mouseY) {
}

void App::mouseMoveEvent(
        int &mouseX,
        int &mouseY,
        int &deltaMouseX,
        int &deltaMouseY
        ) {
    this->getCurrentScene()->camera->mouseMoveEvent(
            mouseX,
            mouseY,
            deltaMouseX,
            deltaMouseY
            );
}

/**
 * Tick/Update function.
 */
void App::tick (float delta) {
    Scene * scene = getCurrentScene();
    if (scene->initialized == false) {
        scene->initialize(delta);
        scene->initialized = true;
    }

    scene->tick(delta);

    if (SDL_GetMouseState(&this->mouseX, &this->mouseY)) {
        this->mouseEvent(this->mouseX, this->mouseY);
    }

    SDL_SetRelativeMouseMode(this->mouseTrap);

    if (state[SDL_SCANCODE_K]) {
        if (this->mouseTrap == SDL_TRUE) {
            this->mouseTrap = SDL_FALSE;
        } else {
            this->mouseTrap = SDL_TRUE;
        }
    }
}

/**
 * This function is used to draw.
 */
void App::draw (float delta) {
    Scene * scene = this->getCurrentScene();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    scene->drawGUI(delta);
    glLoadIdentity();
    glPushMatrix();
    glRotatef(-scene->camera->xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(-scene->camera->yrot, 0.0f, 1.0f, 0.0f);
    glRotatef(-scene->camera->zrot, 0.0f, 0.0f, 1.0f);
    glTranslatef(-scene->camera->x, -scene->camera->y, -scene->camera->z);
    glPushMatrix();
    scene->draw(delta);

    GLfloat materialColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat materialSpecular[] = { 1.0, 1.0, 1.0, 2.0 };
    GLfloat materialEmission[] = {0.0f,0.0f,0.0f, 1.0f};

    GLfloat shininess = 60;

    GLfloat ambientLight[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightColor2[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat lightPos[] = { 1.0, 1.0, 1.0, 0.0 };

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glPopMatrix();
}

/**
 * This function is called on when the user releases a key.
 */
bool App::keyUpEvent(SDL_Event &e) {
    this->getCurrentScene()->keyUpEvent(e);
}

/**
 * This function is used to terminating and killing the program.
 */
void App::close () {
    SDL_DestroyWindow(_display);
    _display = NULL;
    SDL_Quit(); 
}
