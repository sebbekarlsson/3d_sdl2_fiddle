#include "Gun.h"

Gun::Gun(float x, float y, float z) : Instance (x, y, z) {
    this->xrot = 0.0f;
    this->yrot = 90.0f;
    this->zrot = 0.0f;
    this->xsway = 0.0f;
    this->zsway = 0.0f;
    this->imageLoader = new SDLImageLoader();
    this->img = this->imageLoader->load("res/Handgun/Handgun_Obj/textures/handgun_C.jpg");
    this->angle = rand() % 360 + 0;

    this->inputfile = "res/Handgun/Handgun_Obj/Handgun_obj.obj";
    this->ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str(), NULL);

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    std::cout << "# of shapes    : " << shapes.size() << std::endl;
    std::cout << "# of materials : " << materials.size() << std::endl;
}

void Gun::draw(float delta) {
    glPushMatrix();
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

    glTranslatef(x, y, z);
    //glScalef(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);
    
    this->img->bind();
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

}

void Gun::tick(float delta) { 
    if (x > 0) {
        if(x - xsway == 0) {
            x = 0;
        } else {
            x -= xsway;
        }
    }

    if (z > 0) {
        if(z - zsway == 0) {
            z = 0;
        } else {
            z -= zsway;
        }
    }

    x += xsway * delta;
    z += zsway * delta;

}
