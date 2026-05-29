#pragma once

#include <engine/gameObjects/Camera.hpp>
#include <engine/gameObjects/Player.hpp>
#include <engine/gameObjects/FloorBox.hpp>

#include <vector>

namespace game {
    struct SceneData {
        float deltaTime = 0.f;

        game::Player player;
        game::Camera camera;
        std::vector<game::FloorBox> floorBoxes = std::vector<game::FloorBox>();

        SceneData();
        ~SceneData();

        void setupPlayer(game::Player player);
        void setupCamera(game::Camera camera);

        void updateDeltaTime();
        void updateScene();
    };
    
}