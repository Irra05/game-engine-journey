#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <GL/glu.h>

#define JUMP_APEX 5.1f
#define JUMP_TIME_TO_APEX 0.5f

#define gravity(apex, time) (-2.f * apex / (time * time))
#define initialJumpSpeed(apex, time) (2.f * apex / time)

static float deltaTime;
static GLFWwindow* window;
static int screenWidth, screenHeight;

struct Coords{
    float x, y;
};

static struct {
    bool w, a, s, d, space;
} keyboardStatus = {false, false, false, false, false};

void updateDeltaTime() {
    static float elapsedTime, oldElapsedTime = 0.f;

    elapsedTime = glfwGetTime();
    
    deltaTime = elapsedTime - oldElapsedTime;
    
    oldElapsedTime = elapsedTime;
}

struct Player {
    static constexpr float GRAVITY = gravity(JUMP_APEX, JUMP_TIME_TO_APEX);
    static constexpr float INITIAL_JUMP_SPEED = initialJumpSpeed(JUMP_APEX, JUMP_TIME_TO_APEX);
    static constexpr float HORIZONTAL_SPEED = 6.75f;
    
    enum JumpStatus {
        FLOOR, GOING_UP, FALLING
    };

    float x, y;
    JumpStatus jumpStatus;
    float airTime, initialY;
    
    void update(float deltaTime) {
        float nextX = this->x, nextY, nextVSpeed;
        
        if(keyboardStatus.a && !keyboardStatus.d)
        nextX -= HORIZONTAL_SPEED * deltaTime;
        else if(keyboardStatus.d && !keyboardStatus.a)
        nextX += HORIZONTAL_SPEED * deltaTime;
        
        if(nextX < 0.5f)        // Invalid position?
        this->x = 0.5f;
        else if(nextX > 31.5f)
        this->x = 31.5f;
        else
        this->x = nextX;
        
        switch (jumpStatus) {
        case GOING_UP:
            airTime += deltaTime;
            nextY = initialY + INITIAL_JUMP_SPEED * airTime + GRAVITY / 2 * airTime * airTime;
            nextVSpeed = INITIAL_JUMP_SPEED + GRAVITY * airTime;
            if(nextY <= 2.f) {          // Invalid position?
                jumpStatus = FLOOR;
                y = 2.f;
            }
            else if(nextVSpeed <= 0) {
                jumpStatus = FALLING;
                y = nextY;
                initialY = y;
                airTime = 0.f;
            }
            else {
                y = nextY;
            }
            
            break;
            
        case FALLING:
            airTime += deltaTime;
            nextY = initialY + GRAVITY / 2 * airTime * airTime;
            
            if(nextY <= 2.f) {
                jumpStatus = FLOOR;
                y = 2.f;
            }
            else {
                y = nextY;
            }
            
            break;
            
        default:
            break;
        }
    }
    
} player;

static struct {
    float x, y;

    void update() {
        if(player.x < 8.f)
            this->x = 8.f;
        else if(player.x > 24.f)
            this->x = 24.f;
        else
            this->x = player.x;

        if(player.y + -0.5f < 7.f)
            this->y = 7.f;
        else
            this->y = player.y + -0.5f;
    }

} camera = {8.f, 7.f};

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
    case GLFW_KEY_A:
        if(action == GLFW_PRESS) 
            keyboardStatus.a = true;
        else if(action == GLFW_RELEASE)
            keyboardStatus.a = false;
        break;
    case GLFW_KEY_D:
        if(action == GLFW_PRESS) 
            keyboardStatus.d = true;
        else if(action == GLFW_RELEASE)
            keyboardStatus.d = false;
        break;

    case GLFW_KEY_SPACE: case GLFW_KEY_W:
        if(action == GLFW_PRESS && player.jumpStatus == Player::JumpStatus::FLOOR) {
            player.jumpStatus = Player::JumpStatus::GOING_UP;
            player.airTime = 0.f;
            player.initialY = player.y;
        }
        else if(action == GLFW_RELEASE && player.jumpStatus == Player::JumpStatus::GOING_UP) {
            player.jumpStatus = Player::JumpStatus::FALLING;
            player.airTime = 0.f;
            player.initialY = player.y;
        }
        break;

    case GLFW_KEY_ESCAPE:
        glfwDestroyWindow(window);
    
    default:
        break;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    updateDeltaTime();

    player.update(deltaTime);
    camera.update();

    glLoadIdentity();
    glTranslatef(8.f - camera.x, 7.f - camera.y, 0);

    // Background
    glBegin(GL_QUADS);
        glColor3f(0.8, 0.8, 0.8);
        glVertex3f(0.f, 0.f, -1.f);
        glVertex3f(32.f, 0.f, -1.f);
        glColor3f(0.1, 0.1, 0.1);
        glVertex3f(32.f, 18.f, -1.f);
        glVertex3f(0.f, 18.f, -1.f);
    glEnd();

    // Floor
    glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f);
        glVertex2f(0.f, 0.f);
        glVertex2f(4.f, 0.f);
        glVertex2f(4.f, 2.f);
        glVertex2f(0.f, 2.f);

        glColor3f(1.f, 0.5f, 0.f);
        glVertex2f(4.f, 0.f);
        glVertex2f(8.f, 0.f);
        glVertex2f(8.f, 2.f);
        glVertex2f(4.f, 2.f);

        glColor3f(1.f, 1.f, 0.f);
        glVertex2f(8.f, 0.f);
        glVertex2f(12.f, 0.f);
        glVertex2f(12.f, 2.f);
        glVertex2f(8.f, 2.f);

        glColor3f(0.f, 1.f, 0.f);
        glVertex2f(12.f, 0.f);
        glVertex2f(16.f, 0.f);
        glVertex2f(16.f, 2.f);
        glVertex2f(12.f, 2.f);

        glColor3f(0.f, 1.f, 1.f);
        glVertex2f(16.f, 0.f);
        glVertex2f(20.f, 0.f);
        glVertex2f(20.f, 2.f);
        glVertex2f(16.f, 2.f);

        glColor3f(0.f, 0.f, 1.f);
        glVertex2f(20.f, 0.f);
        glVertex2f(24.f, 0.f);
        glVertex2f(24.f, 2.f);
        glVertex2f(20.f, 2.f);

        glColor3f(0.5f, 0.f, 1.f);
        glVertex2f(24.f, 0.f);
        glVertex2f(28.f, 0.f);
        glVertex2f(28.f, 2.f);
        glVertex2f(24.f, 2.f);

        glColor3f(1.f, 0.f, 1.f);
        glVertex2f(28.f, 0.f);
        glVertex2f(32.f, 0.f);
        glVertex2f(32.f, 2.f);
        glVertex2f(28.f, 2.f);
    glEnd();

    // Player
    glBegin(GL_QUADS);
        glColor3f(0.995f, 0.f, 0.0f);
        glVertex2f(-0.5f + player.x, player.y);
        glVertex2f(0.5f + player.x, player.y);
        glVertex2f(0.5f + player.x, 2.f + player.y);
        glVertex2f(-0.5f + player.x, 2.f + player.y);

        glColor3f(1.f, 0.75f, 0.5f);
        glVertex2f(-0.5f + player.x, 2.f + player.y);
        glVertex2f(0.5f + player.x, 2.f + player.y);
        glVertex2f(0.5f + player.x, 3.f + player.y);
        glVertex2f(-0.5f + player.x, 3.f + player.y);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
    
    static bool firstPrint = true;

    // if(firstPrint)
        // std::cout << "DEBUG: player: {x: " << player.x << ", y: " << player.y << ", jumpStatus: " << player.jumpStatus << ", airTime: " << player.airTime << "}\n";
    // else
        std::cout << "\033[A\33[2K\rDEBUG: player: {x: " << player.x << ", y: " << player.y << ", jumpStatus: " << player.jumpStatus << ", airTime: " << player.airTime << "}\n";

    firstPrint = true;
}

void initOpenGL() {
    // Set orthogonal projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, screenWidth, screenHeight);
    glOrtho(0., 16., 0., 14., 2., -2.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set display & player settings
    glClearColor(0.7f, 0.7f, 0.7f, 1.f);

    player.x = 8.f;
    player.y = 2.f;

    player.jumpStatus = Player::JumpStatus::FLOOR;
}

int main() {
    // GLFW init
    if(!glfwInit())
        exit(1);

    // Window creation
    window = glfwCreateWindow(640, 480, "Main", nullptr, nullptr);
    if(!window) {
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    initOpenGL();

    glfwSetKeyCallback(window, keyboard_callback);
    while (!glfwWindowShouldClose(window)) {
        display();
    }

    glfwTerminate();
    
}
