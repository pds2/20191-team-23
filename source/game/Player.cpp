#include "Player.h"

#include "../engine/EngineApp.h"

Player::Player(){
    scale = Vector(100.0f, 100.0f);

    m_sIdle.Configure("c_idle_", 2, 2);
    m_sWalk.Configure("c_walk_", 4, 5);

    m_walkSpeed = 0.1f;
}

Player::~Player(){

}

void Player::Update(EngineApp& app, float deltaTime){
    float valueX = app.GetInputMap().GetValue("forward");
    float valueY = app.GetInputMap().GetValue("upward");
    
    position.x += valueX * m_walkSpeed * deltaTime;
    position.y -= valueY * m_walkSpeed * deltaTime;

    // Configuring the sprites...
    m_walking = (valueX != 0.0f || valueY != 0.0f);

    if (valueX != 0.0f)
        m_spriteFlip = (valueX < 0.0f);

    // Updating the sprite timers
    m_sIdle.Update(deltaTime);
    m_sWalk.Update(deltaTime);
}
void Player::Draw(EngineApp& app){
    std::string act;
    act = m_walking ? m_sWalk.GetDrawable() : m_sIdle.GetDrawable();

    app.DrawSprite(act, position, scale, m_spriteFlip);
}