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
    this->img = this->imgLoader->load("res/crate.jpg");
    this->img2 = this->imgLoader->load("res/ground.jpg");
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
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW); 
    //glOrtho(0, (WIDTH * SCALE), (HEIGHT * SCALE), 0, 1, -1);



    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
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

    //angle += 0.1; if(angle > 360) {angle -= 360;}

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
    glPushMatrix();
    glRotatef(-scene->camera->xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(-scene->camera->yrot, 0.0f, 1.0f, 0.0f);
    glRotatef(-scene->camera->zrot, 0.0f, 0.0f, 1.0f);
    glTranslatef(-scene->camera->x, -scene->camera->y, -scene->camera->z);
    scene->draw(delta);

    glPushMatrix();
    float size = 4.0f;
    float width = size;
    float height = size;
    float length = size;
    float angle = 180.0f;
    float textureRepeat = 1.0f;

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glTranslatef(-size/2, -size/2, -size/2);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    //back
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, 0);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, 0);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, 0);


    glTexCoord2f(0, 0);
    glVertex3f(0, height, 0);

    glEnd();
    glPopMatrix();

    //front
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, length);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, length);


    glTexCoord2f(0, 0);
    glVertex3f(0, height, length);

    glEnd();
    glPopMatrix();

    //left
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, 0);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(0, 0, length);

    glTexCoord2f(textureRepeat,0);
    glVertex3f(0, height, length);

    glTexCoord2f(0, 0);
    glVertex3f(0, height, 0);

    glEnd();
    glPopMatrix();

    //right
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(width, 0, 0);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, length);

    glTexCoord2f(0, 0);
    glVertex3f(width, height, 0);

    glEnd();
    glPopMatrix();

    //bottom
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);


    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, length);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, 0, 0);

    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);

    glEnd();
    glPopMatrix();

    //top
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, height, length);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, height, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, 0);

    glTexCoord2f(0, 0);
    glVertex3f(0, height, 0);

    glEnd();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();


    // 2
    angle = 20.0f;
    glPushMatrix();
    glTranslatef(size*2, 0.0f, size*2);
    glTranslatef(-size/2, -size/2, -size/2);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    //back
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, 0);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, 0);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, 0);


    glTexCoord2f(0, 0);
    glVertex3f(0, height, 0);

    glEnd();
    glPopMatrix();

    //front
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, length);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, length);


    glTexCoord2f(0, 0);
    glVertex3f(0, height, length);

    glEnd();
    glPopMatrix();

    //left
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, 0);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(0, 0, length);

    glTexCoord2f(textureRepeat,0);
    glVertex3f(0, height, length);

    glTexCoord2f(0, 0);
    glVertex3f(0, height, 0);

    glEnd();
    glPopMatrix();

    //right
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(width, 0, 0);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, length);

    glTexCoord2f(0, 0);
    glVertex3f(width, height, 0);

    glEnd();
    glPopMatrix();

    //bottom
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);


    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, length);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, 0, 0);

    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);

    glEnd();
    glPopMatrix();

    //top
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, height, length);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, height, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, 0);

    glTexCoord2f(0, 0);
    glVertex3f(0, height, 0);

    glEnd();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    // 3
    angle = -20.0f;
    glPushMatrix();
    glTranslatef(size, 0.0f, -size);
    glTranslatef(-size/2, -size/2, -size/2);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    //back
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, 0);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, 0);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, 0);


    glTexCoord2f(0, 0);
    glVertex3f(0, height, 0);

    glEnd();
    glPopMatrix();

    //front
    
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, length);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, length);


    glTexCoord2f(0, 0);
    glVertex3f(0, height, length);

    glEnd();
    glPopMatrix();

    //left
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, 0);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(0, 0, length);

    glTexCoord2f(textureRepeat,0);
    glVertex3f(0, height, length);

    glTexCoord2f(0, 0);
    glVertex3f(0, height, 0);

    glEnd();
    glPopMatrix();

    //right
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(width, 0, 0);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, length);

    glTexCoord2f(0, 0);
    glVertex3f(width, height, 0);

    glEnd();
    glPopMatrix();

    //bottom
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);


    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, 0, length);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, 0, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, 0, 0);

    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);

    glEnd();
    glPopMatrix();

    //top
    glPushMatrix();
    this->img->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, height, length);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(width, height, length);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(width, height, 0);

    glTexCoord2f(0, 0);
    glVertex3f(0, height, 0);

    glEnd();
    glPopMatrix();
    glPopMatrix();





    textureRepeat = 4.0f;
    glPushMatrix();
    glTranslatef(-10.0f, 0.0f, -10.0f);
    glPushMatrix();
    this->img2->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex3f(0, -2.0f, 0);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, -2.0f, 20.0f);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(20.0f, -2.0f, 20.0f);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(20.0f, -2.0f, 0);

    glEnd();
    glPopMatrix();
    glPopMatrix();










    glPopMatrix();
    glPopMatrix();

    //glPushMatrix();
    //glTranslatef(0.0f, 0.0f, -0.4f);
    //scene->drawGUI(delta);
    //glPopMatrix();

    //glPushMatrix();
    //scene->camera->draw(delta);
    //glPopMatrix();
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
