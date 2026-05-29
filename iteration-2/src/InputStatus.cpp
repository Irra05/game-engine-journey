#include <engine/InputStatus.hpp>

int game::InputStatus::hAxis() {
    if(right && left || !right && !left)
        return 0;
    else if(right)
        return 1;
    else
        return -1;

    // return right - left;
}