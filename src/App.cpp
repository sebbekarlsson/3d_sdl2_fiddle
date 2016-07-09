#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "App.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>


const int WIDTH = 640;
const int HEIGHT = WIDTH / 16 * 9;
const int SCALE = 2;

extern const Uint8 * state;


Cube * cube = new Cube(0, 0, 0);
Cube * cube1 = new Cube(0, 0, 8.0f);
Cube * cube2 = new Cube(8.0f, 0, 0);
Cube * cube3 = new Cube(0, 4.0f, 0);
Gun * gun = new Gun(1.0f, -1.5f, -2.0f);

std::string inputfile = "res/Police.obj";
tinyobj::attrib_t attrib;
std::vector<tinyobj::shape_t> shapes;
std::vector<tinyobj::material_t> materials;

float man_angle;

std::string err;

bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str(), NULL);

/**
 * Constructor
 */
App::App () {
    

    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    std::cout << "# of shapes    : " << shapes.size() << std::endl;
    std::cout << "# of materials : " << materials.size() << std::endl;

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
    man_angle += 0.1f;
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

    //gun->x = getCurrentScene()->camera->x;
    //gun->z = getCurrentScene()->camera->z;
    //gun->y = getCurrentScene()->camera->y - 1.0f;
    //gun->yrot = getCurrentScene()->camera->yrot + 90.0f;
    //gun->zrot = getCurrentScene()->camera->xrot;
    gun->tick(delta);
}

/**
 * This function is used to draw.
 */
void App::draw (float delta) {
    Scene * scene = this->getCurrentScene();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gun->draw(delta); 
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

    cube->draw(delta);
    cube1->draw(delta);
    cube2->draw(delta);
    cube3->draw(delta);

    textureRepeat = 10.0f;
    glPushMatrix();
    glTranslatef(-35.0f, 0.0f, -35.0f);
    glPushMatrix();
    this->img2->bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex3f(0, -2.0f, 0);

    glTexCoord2f(0, textureRepeat);
    glVertex3f(0, -2.0f, 70.0f);

    glTexCoord2f(textureRepeat, textureRepeat);
    glVertex3f(70.0f, -2.0f, 70.0f);

    glTexCoord2f(textureRepeat, 0);
    glVertex3f(70.0f, -2.0f, 0);

    glEnd();
    glPopMatrix();
    glPopMatrix();

    //The color of the sphere
GLfloat materialColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
//The specular (shiny) component of the material
GLfloat materialSpecular[] = { 1.0, 1.0, 1.0, 2.0 };
//The color emitted by the material
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

/*glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);


//Diffuse (non-shiny) light component
glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor2);
//Specular (shiny) light component
glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
glLightfv(GL_LIGHT0, GL_POSITION, lightPos);*/

glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);




    
    glTranslatef(14.0f, -1.5f, 0.0f);
    glRotatef(man_angle, 0.0f, 1.0f, 0.0f);
    glScalef(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    this->girl_image->bind();
    glBegin(GL_TRIANGLES);
    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                float vx = attrib.vertices[3*idx.vertex_index+0];
                float vy = attrib.vertices[3*idx.vertex_index+1];
                float vz = attrib.vertices[3*idx.vertex_index+2];
                float nx = attrib.normals[3*idx.normal_index+0];
                float ny = attrib.normals[3*idx.normal_index+1];
                float nz = attrib.normals[3*idx.normal_index+2];
                float tx = attrib.texcoords[2*idx.texcoord_index+0];
                float ty = attrib.texcoords[2*idx.texcoord_index+1];
               
                glNormal3f(nx, ny, nz); 
                glTexCoord2f(tx, ty);
                glVertex3f(vx, vy, vz);
            }
            index_offset += fv;

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); //The shininess parameter
            shapes[s].mesh.material_ids[f];
        }
    }
    glEnd();
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
