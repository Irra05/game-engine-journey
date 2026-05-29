#include <engine/gameObjects/Player.hpp>
#include <engine/SceneData.hpp>
#include <engine/gameObjects/FloorBox.hpp>

#include <iostream>

#define JUMP_APEX 5.1f
#define JUMP_APEX_TIME 0.75f

#define gravity(apex, time) (-2.f * apex / (time * time))
#define initial_jump_speed(apex, time) (2.f * apex / time)

#define mrua_get_v_inc(a, t) (a * t)
#define mrua_get_x_inc(a, v0, t) (v0 * t + (a/2) * (t*t))

#define MAX_FALL_SPEED -(initial_jump_speed(JUMP_APEX, JUMP_APEX_TIME) * 1.5f)

game::Player::Player() {}

game::Player::Player(InputStatus& inputStatus, float width, float height, float initialX, float initialY, SceneData& sceneData) :
    x(initialX), y(initialY),
    width(width), height(height),
    hSpeed(0.f), vSpeed(0.f),
    hStatus(game::Player::HorizontalStatus::STILL), 
    vStatus(game::Player::VerticalStatus::GROUNDED),
    inputStatus(&inputStatus),
    sceneData(&sceneData) {}

game::Player::~Player() {}

static void handleInput(game::Player& player) {
    // Horizontal
    switch (player.inputStatus->hAxis()) {
    case 0:
        player.hStatus = game::Player::HorizontalStatus::STILL;
        player.hSpeed = 0.f;
        break;
    
    case 1:
        player.hStatus = game::Player::HorizontalStatus::MOVING_RIGHT;
        player.hSpeed = 5.f;
        break;

    case -1:
        player.hStatus = game::Player::HorizontalStatus::MOVING_LEFT;
        player.hSpeed = -5.f;
        break;
    
    default:
        break;
    }

    // Vertical
    if(player.vStatus == game::Player::VerticalStatus::GROUNDED && player.inputStatus->jump) {
        player.vSpeed = initial_jump_speed(JUMP_APEX, JUMP_APEX_TIME);
        player.vStatus = game::Player::VerticalStatus::JUMPING;
    }
    else if(player.vStatus == game::Player::VerticalStatus::JUMPING && !player.inputStatus->jump) {
        player.vSpeed = 0.f;
        player.vStatus = game::Player::VerticalStatus::FALLING;
    }
}

void movePlayer(game::Player& player) {
    player.x += player.hSpeed * player.sceneData->deltaTime;

    if(player.vStatus == game::Player::JUMPING || player.vStatus == game::Player::FALLING) {
        player.y += mrua_get_x_inc(gravity(JUMP_APEX, JUMP_APEX_TIME), player.vSpeed, player.sceneData->deltaTime);
                
        if(player.vSpeed > MAX_FALL_SPEED)
            player.vSpeed += mrua_get_v_inc(gravity(JUMP_APEX, JUMP_APEX_TIME), player.sceneData->deltaTime);
        else if(player.vSpeed < MAX_FALL_SPEED)
            player.vSpeed = MAX_FALL_SPEED;
    }

}

static bool isAirborne(game::Player& player) {
    game::FloorBox* hittingBox = nullptr;

    for(game::FloorBox& box : player.sceneData->floorBoxes) {
        if(box.top == player.y && 
                box.left < player.x - player.width && 
                box.right > player.x)
            return false;
    }

    return true;
}

// Vertical collissions
static game::FloorBox* hittingCeil(game::Player& player) {
    for(game::FloorBox& box : player.sceneData->floorBoxes) {
        if(box.left < player.x + player.width && box.right > player.x &&
            player.y + player.height >= box.bottom && 
            player.y + player.height <= box.bottom - MAX_FALL_SPEED * player.sceneData->deltaTime)
        return &box;
    }

    return nullptr;
}

static game::FloorBox* hittingGround(game::Player& player) {
    for(game::FloorBox& box : player.sceneData->floorBoxes) {
        if(box.left < player.x + player.width && box.right > player.x &&
                player.y <= box.top && 
                player.y >= (box.top + MAX_FALL_SPEED * player.sceneData->deltaTime))
            return &box;
    }

    return nullptr;
}

// Horizontal collissions
static game::FloorBox* hittingLeft(game::Player& player) {
    for(game::FloorBox& box : player.sceneData->floorBoxes) {
        if(box.top > player.y && box.bottom < player.y + player.height &&
                player.x <= box.right && player.x + player.width > box.left)
            return &box;
    }

    return nullptr;
}

static game::FloorBox* hittingRight(game::Player& player) {
    for(game::FloorBox& box : player.sceneData->floorBoxes) {
        if(box.top > player.y && box.bottom < player.y + player.height &&
                player.x + player.width >= box.left && player.x < box.right)
            return &box;
    }

    return nullptr;
}

static void handleStatusModifications(game::Player& player) {
    std::cout << "\033[1A\033[2K\r" << "deltaTime * MAX_FALLING_SPEED: " << player.sceneData->deltaTime * MAX_FALL_SPEED << std::endl;

    game::FloorBox* hittingBox;

    if(player.vStatus == game::Player::VerticalStatus::GROUNDED && isAirborne(player)) {
        player.vSpeed = 0.f;
        player.vStatus = game::Player::VerticalStatus::FALLING;
    }
    else if(player.vStatus == game::Player::VerticalStatus::JUMPING && player.vSpeed <= 0.f) {
        player.vStatus = game::Player::VerticalStatus::FALLING;
    }
    else if(player.vStatus == game::Player::VerticalStatus::JUMPING && (hittingBox = hittingCeil(player))) {
        player.y = hittingBox->bottom - player.height;
        player.vSpeed = 0.f;
        player.vStatus = game::Player::VerticalStatus::FALLING;
    }
    else if(player.vStatus == game::Player::VerticalStatus::FALLING && (hittingBox = hittingGround(player))) {
        player.y = hittingBox->top;
        player.vSpeed = 0.f;
        player.vStatus = game::Player::VerticalStatus::GROUNDED;
    }

    // Horizontal checks
    if(player.hStatus == game::Player::HorizontalStatus::MOVING_LEFT && (hittingBox = hittingLeft(player))) {
        player.x = hittingBox->right;
    }
    else if(player.hStatus == game::Player::HorizontalStatus::MOVING_RIGHT && (hittingBox = hittingRight(player))) {
        player.x = hittingBox->left - player.width;
    }
}

void game::Player::update() {
    handleInput(*this);
    movePlayer(*this);
    handleStatusModifications(*this);
}
