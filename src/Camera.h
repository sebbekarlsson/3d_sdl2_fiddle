#pragma once


extern const Uint8 * state;
class Camera: public Instance {
    public:
        float zoom;
        float dx, dy, dz;
        float xrot, yrot, zrot;
        float friction;
        float lastXDirection;
        float lastZDirection;

        Camera (float x, float y, float z) : Instance(x, y, z) {
            this->friction = 0.98f;
            this->dx = 0.0f;
            this->dy = 0.0f;
            this->dz = 0.0f;
            this->xrot = 0.0f;
            this->yrot = 0.0f;
            this->zrot = 0.0f;
            this->lastXDirection = 0.0f;
            this->lastZDirection = 0.0f;
        }

        void tick(float delta) {
            if (state[SDL_SCANCODE_W]) {
                dx -= sin(this->yrot * (M_PI / 180)) * 1.3f;
                dz -= cos(this->yrot * (M_PI / 180)) * 1.3f;

                this->lastXDirection = sin(this->yrot * (M_PI / 180));
                this->lastZDirection = cos(this->yrot * (M_PI / 180));
            }
            if (state[SDL_SCANCODE_S]) {
                dx += sin(this->yrot * (M_PI / 180)) * 1.3f;
                dz += cos(this->yrot * (M_PI / 180)) * 1.3f;

                this->lastXDirection = sin(this->yrot * (M_PI / 180));
                this->lastZDirection = cos(this->yrot * (M_PI / 180));
            }

            if (state[SDL_SCANCODE_A]) {
                dx += sin((this->yrot - 90.0f) * (M_PI / 180)) * (1.3f);
                dz += cos((this->yrot - 90.0f) * (M_PI / 180)) * (1.3f);

                this->lastXDirection = sin((this->yrot - 90.0f) * (M_PI / 180));
                this->lastZDirection = cos((this->yrot - 90.0f) * (M_PI / 180));
            }
            if (state[SDL_SCANCODE_D]) {
                dx += sin((this->yrot + 90.0f) * (M_PI / 180)) * (1.3f);
                dz += cos((this->yrot + 90.0f) * (M_PI / 180)) * (1.3f);

                this->lastXDirection = sin((this->yrot + 90.0f) * (M_PI / 180));
                this->lastZDirection = cos((this->yrot + 90.0f) * (M_PI / 180));
            }

            this->updatePhysics(delta);
        }
        void draw(float delta) {
        }

        void updatePhysics (float delta) {
            if (lastZDirection < 0) {
                lastZDirection = lastZDirection * -1;
            }

            if (lastXDirection < 0) {
                lastXDirection = lastXDirection * -1;
            }

            if(dx > 0){
                if(dx - (lastXDirection * friction) < 0){
                    dx = 0;
                }else{
                    dx -= lastXDirection * friction;
                }
            }
            if(dx < 0){
                if(dx + (lastXDirection * friction) > 0){
                    dx = 0;
                }else{
                    dx += lastXDirection * friction;
                }
            }

            if(dy > 0){
                if(dy - friction < 0){
                    dy = 0;
                }else{
                    dy -= friction;
                }
            }
            if(dy < 0){
                if(dy + friction > 0){
                    dy = 0;
                }else{
                    dy += friction;
                }
            }

            if(dz > 0){
                if(dz - (lastZDirection * friction) < 0){
                    dz = 0;
                }else{
                    dz -= lastZDirection * friction;
                }
            }
            if(dz < 0){
                if(dz + (lastZDirection * friction) > 0){
                    dz = 0;
                }else{
                    dz += lastZDirection * friction;
                }
            }

            x += dx * delta;
            y += dy * delta;
            z += dz * delta;
        }

        void mouseMoveEvent(int mouseX, int mouseY, int deltaMouseX, int deltaMouseY) {
            xrot -= (deltaMouseY * 0.25f);
            yrot -= (deltaMouseX * 0.25f);
        }
};
