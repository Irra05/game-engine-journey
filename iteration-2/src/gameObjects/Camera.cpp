#include <engine/gameObjects/Camera.hpp>

#include <engine/SceneData.hpp>

game::Camera::Camera() {}

game::Camera::Camera(game::Player& targetPlayer, float width, float height, game::SceneData& sceneData) :
    targetPlayer(&targetPlayer),
    x(targetPlayer.x + targetPlayer.width / 2),
    y(targetPlayer.y + targetPlayer.height / 2),
    widthRadius(width / 2),
    heightRadius(height / 2),
    sceneData(&sceneData) {}

game::Camera::~Camera() {}

void game::Camera::update() {
    this->x = targetPlayer->x + targetPlayer->width / 2;
    this->y = targetPlayer->y + targetPlayer->height / 2;
}