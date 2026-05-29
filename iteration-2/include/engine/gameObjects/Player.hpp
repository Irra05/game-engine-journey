#pragma once

#include <engine/InputStatus.hpp>

namespace game {
    struct SceneData;

    struct Player {
        enum HorizontalStatus {
            STILL, MOVING_RIGHT, MOVING_LEFT
        };

        enum VerticalStatus {
            GROUNDED, JUMPING, FALLING, COYOTE_TIME
        };

        SceneData* sceneData = nullptr;

        float x = 0.f, y = 0.f;
        float width = 1.f, height = 2.f;
        float hSpeed = 0.f, vSpeed = 0.f;

        float screenPriority = 15.f;

        HorizontalStatus hStatus = STILL;
        VerticalStatus vStatus = GROUNDED;

        InputStatus* inputStatus = nullptr;

        Player();
        Player(InputStatus& inputStatus, float width, float height, float initialX, float initialY, SceneData& sceneData);
        ~Player();
    
        void update();

    };
} // namespace game
