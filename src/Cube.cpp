#include "Cube.h"


Cube::Cube(float x, float y, float z) : Instance (x, y, z) {
    this->imageLoader = new SDLImageLoader();
    this->img = this->imageLoader->load("res/crate.jpg");
    this->angle = rand() % 360 + 0;;
}

void Cube::draw(float delta) {
    float size = 4.0f;
    float width = size;
    float height = size;
    float length = size;
    float textureRepeat = 1.0f;

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-size/2, -size/2, -size/2);
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    //back
    glPushMatrix();
    glNormal3f(0.0f, 0.0f, -1.0f);
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
    glNormal3f(0.0f, 0.0f, 1.0f);
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
    glNormal3f(-1.0f, 0.0f, 0.0f);
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
    glNormal3f(1.0f, 0.0f, 0.0f);
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
    glNormal3f(0.0f, -1.0f, 0.0f);
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
    glNormal3f(0.0f, 1.0f, 0.0f);
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
}

void Cube::tick(float delta) {}
