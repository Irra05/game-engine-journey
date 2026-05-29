#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <engine/InputStatus.hpp>
#include <engine/SceneData.hpp>
#include <engine/gameObjects/Player.hpp>
#include <engine/gameObjects/Camera.hpp>
#include <engine/gameObjects/FloorBox.hpp>

void initScene(game::SceneData& scene, game::InputStatus& inputStatus) {
    scene.setupPlayer(game::Player(inputStatus, 1.f, 2.f, 4.f, 5.f, scene));
    scene.setupCamera(game::Camera(scene.player, 16.f, 12.f, scene));

    scene.floorBoxes.emplace_back(3, 1, 0, 10);
    scene.floorBoxes.emplace_back(3, 1, 13, 20);
    scene.floorBoxes.emplace_back(5, 1, 23, 26);
    scene.floorBoxes.emplace_back(7, 0, 29, 31);
    scene.floorBoxes.emplace_back(11, 9, 33, 37);
    scene.floorBoxes.emplace_back(11, -2, 37, 39);
    scene.floorBoxes.emplace_back(10, 8, 39, 43);

    scene.floorBoxes.emplace_back(6, 5, 42, 46);
    scene.floorBoxes.emplace_back(2, 1, 39, 43);
    scene.floorBoxes.emplace_back(-2, -3, 44, 47);
    scene.floorBoxes.emplace_back(-6, -7, 40, 43);
    scene.floorBoxes.emplace_back(-8, -9, 34, 38);

    scene.floorBoxes.emplace_back(-6, -16, 23, 31);
    scene.floorBoxes.emplace_back(-5, -16, 13, 20);
    scene.floorBoxes.emplace_back(-6, -8, 3, 9);
    scene.floorBoxes.emplace_back(-2, -3, -3, 0);

    /*
    scene.floorBoxes.emplace_back(-18, -20, 1, 6);
    scene.floorBoxes.emplace_back(-28, -30, 1, 6);
    scene.floorBoxes.emplace_back(-38, -40, 1, 6);
    scene.floorBoxes.emplace_back(-48, -50, 1, 6);
    scene.floorBoxes.emplace_back(-58, -60, 1, 6);
    scene.floorBoxes.emplace_back(-68, -70, 1, 6);
    scene.floorBoxes.emplace_back(-78, -80, 1, 6);
    scene.floorBoxes.emplace_back(-88, -90, 1, 6);
    scene.floorBoxes.emplace_back(-98, -100, 1, 6);
    scene.floorBoxes.emplace_back(-108, -110, 1, 6);
    scene.floorBoxes.emplace_back(-118, -120, 1, 6);
    scene.floorBoxes.emplace_back(-128, -130, 1, 6);
    scene.floorBoxes.emplace_back(-138, -140, 1, 6);
    scene.floorBoxes.emplace_back(-148, -150, 1, 6);
    scene.floorBoxes.emplace_back(-158, -160, 1, 6);
    */
}

void initOpengl(game::SceneData& scene, int& screenWidth, int& screenHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, screenWidth, screenHeight);
    glOrtho(-scene.camera.widthRadius, scene.camera.widthRadius,
        -scene.camera.heightRadius, scene.camera.heightRadius,
        16., -16.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.7f, 0.7f, 0.7f, 1.f);
}

void display(GLFWwindow* window, game::SceneData& scene) {
    // std::cout << "Started rendering frame\n";

    glClear(GL_COLOR_BUFFER_BIT);

    scene.updateDeltaTime();
    scene.updateScene();

    glLoadIdentity();
    glTranslatef(-scene.camera.x, -scene.camera.y, 0.f);

    // Draw player
    glBegin(GL_QUADS);
    glColor3f(1.f, 0.f, 0.f);
    glVertex2f(scene.player.x, scene.player.y);
    glVertex2f(scene.player.x + scene.player.width, scene.player.y);
    glVertex2f(scene.player.x + scene.player.width, scene.player.y + scene.player.height);
    glVertex2f(scene.player.x, scene.player.y + scene.player.height);
    glEnd();

    // Draw floorBoxes
    for(game::FloorBox box : scene.floorBoxes) {
        glBegin(GL_QUADS);
        glColor3f(0.5f, 0.25f, 0.f);
        glVertex2f(box.left, box.bottom);
        glVertex2f(box.right, box.bottom);
        glVertex2f(box.right, box.top);
        glVertex2f(box.left, box.top);
        glEnd();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    // std::cout << "Finished rendering frame\n";
}

int main() {
    GLFWwindow* window;
    int screenWidth, screenHeight;
    game::SceneData scene1; 

    glfwInit();
    
    initScene(scene1, game::globals::inputStatus);
    std::cout << "Scene initied successfully\n";
    // std::cout << scene1.camera.widthRadius << std::endl;
    // std::cout << scene1.camera.heightRadius << std::endl;
    
    window = glfwCreateWindow(1280, 960, "Guejo", NULL, NULL);
    if(window == NULL) {
        glfwTerminate();
        std::__throw_runtime_error("Couldn't create window");
    }

    std::cout << "Window created successfully\n";

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    std::cout << "Window settings set successfully\n";
    
    initOpengl(scene1, screenWidth, screenHeight);
    std::cout << "OpenGL initied successfully\n";

    glfwSetKeyCallback(window, game::handleKeyboard);
    std::cout << "Key callack set successfully\n\n";

    while (!glfwWindowShouldClose(window)) {
        display(window, scene1);
    }

    glfwTerminate();
}