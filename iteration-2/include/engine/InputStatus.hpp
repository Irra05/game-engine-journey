#pragma once

#include <GLFW/glfw3.h>

namespace game {
    struct InputStatus {
        bool jump;
        bool left, right;

        int hAxis();
    };

    namespace globals {
        // Cagadón por parte de GLFW
        static InputStatus inputStatus = {false, false, false};
    } // namespace globals
    
    static void handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
        switch (key) {
        case GLFW_KEY_W: case GLFW_KEY_SPACE:
            if(action == GLFW_PRESS)
                globals::inputStatus.jump = true;
            else if(action == GLFW_RELEASE)
                globals::inputStatus.jump = false; 

            break;
        
        case GLFW_KEY_D: case GLFW_KEY_RIGHT:
            if(action == GLFW_PRESS)
                globals::inputStatus.right = true;
            else if(action == GLFW_RELEASE)
                globals::inputStatus.right = false;

            break;

        case GLFW_KEY_A: case GLFW_KEY_LEFT:
            if(action == GLFW_PRESS)
                globals::inputStatus.left = true;
            else if(action == GLFW_RELEASE)
                globals::inputStatus.left = false;

            break;

        default:
            break;
        }
           
    }
}
