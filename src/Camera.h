#pragma once


extern const Uint8 * state;
class Camera: public Instance {
    public:
        float zoom;
        float dx, dy, dz;
        float xrot, yrot, zrot;
        float friction;

        Camera (float x, float y, float z) : Instance(x, y, z) {
            this->friction = 3.2f;
            this->dx = 0.0f;
            this->dy = 0.0f;
            this->dz = 0.0f;
            this->xrot = 0.0f;
            this->yrot = 0.0f;
            this->zrot = 0.0f;
        }

        void tick(float delta) {
            //z -= 0.01f;
            this->updatePhysics(delta);

            if (state[SDL_SCANCODE_W]) {
                x -= sin(this->yrot * (M_PI / 180)) * 0.06f;
                z -= cos(this->yrot * (M_PI / 180)) * 0.06f;
            }
        }
        void draw(float delta) {
        }

        void updatePhysics (float delta) {
            if(dx > 0){
                if(dx - friction < 0){
                    dx = 0;
                }else{
                    dx -= friction;
                }
            }
            if(dx < 0){
                if(dx + friction > 0){
                    dx = 0;
                }else{
                    dx += friction;
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

            x += dx * delta;
            y += dy * delta;
        }

        void mouseMoveEvent(int mouseX, int mouseY, int deltaMouseX, int deltaMouseY) {
            xrot -= (deltaMouseY * 0.25f);
            yrot -= (deltaMouseX * 0.25f);
        }
};
