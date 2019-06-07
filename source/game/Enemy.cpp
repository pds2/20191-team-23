#include "Enemy.h"

#include "../engine/EngineApp.h"

Enemy::Enemy(){
    scale = Vector(100.0f, 100.0f);

    m_sIdle.Configure("cop_idle_", 2, 2);
    m_sWalk.Configure("cop_walk_", 4, 5);

    m_walkSpeed = 0.08f;

    m_timer = (float)(rand() % 100) / 60.0f;
    
    m_spriteFlip = true;
    RandomizeState();
    stateTimeout = 2.0f;
}
Enemy::~Enemy(){

}

void Enemy::RandomizeState(){
    m_fsm = rand()%2;
    m_direction = Vector(rand()%3-1, rand()%3-1);
    if (m_direction.x == 0.0f && m_direction.y == 0.0f){
        m_fsm = 0;
    }
}

void Enemy::Update(EngineApp& app, float deltaTime){
    // Configuring the sprites...
    
    //m_spriteFlip = true;

    // Updating the sprite timers
    m_sIdle.Update(deltaTime);
    m_sWalk.Update(deltaTime);

    // Updating the AI
    m_timer += deltaTime * 0.001f;
    if (m_timer > stateTimeout){
        m_timer = 0.0f;
        RandomizeState();
    }

    // Running the AI
    if (m_fsm == 0){
        m_walking = false;
    } else{
        m_walking = true;
        m_spriteFlip = (m_direction.x < 0.0f);
        
        position += m_direction * m_walkSpeed * deltaTime;
    }
}
void Enemy::Draw(EngineApp& app){
    std::string act;
    act = m_walking ? m_sWalk.GetDrawable() : m_sIdle.GetDrawable();

    app.DrawSprite(act, position, scale, m_spriteFlip);
}