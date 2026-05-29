#pragma once

namespace game {
    struct FloorBox {
        const float top, bottom, left, right;

        FloorBox() = delete;
        FloorBox(float top, float bottom, float left, float right);
        ~FloorBox();

    };  
} // namespace game

