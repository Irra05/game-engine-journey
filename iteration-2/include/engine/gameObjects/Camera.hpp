#pragma once

#include <engine/gameObjects/Player.hpp>

namespace game {
    struct SceneData;

    struct Camera {
        game::Player* targetPlayer = nullptr;
        game::SceneData* sceneData = nullptr;
        
        float x = 8.f, y = 6.f;
        float widthRadius = 8.f, heightRadius = 6.f;

        Camera();
        Camera(game::Player& targetPlayer, float width, float height, game::SceneData& sceneData);
        ~Camera();

        void update();
        
    };
} // namespace game
