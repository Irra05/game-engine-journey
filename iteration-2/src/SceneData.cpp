#include <engine/SceneData.hpp>

#include <GLFW/glfw3.h>

game::SceneData::SceneData() :
    player(), camera(), floorBoxes() {}

game::SceneData::~SceneData() {}

void game::SceneData::setupPlayer(game::Player player) {
    this->player = player;
}

void game::SceneData::setupCamera(game::Camera camera) {
    this->camera = camera;
}

void game::SceneData::updateDeltaTime() {
    static float elapsedTime, oldElapsedTime = 0.f;

    elapsedTime = glfwGetTime();

    deltaTime = elapsedTime - oldElapsedTime;

    oldElapsedTime = elapsedTime;
}

void game::SceneData::updateScene() {
    player.update();
    camera.update();
}
