#include "Scene.h"


Scene::Scene () {
    this->initialized = false;
    this->camera = new Camera(0.0f, 8.0f, 24.0f);
}

void Scene::instantiate(Instance * instance) {
    this->instances.push_back(instance);
}
