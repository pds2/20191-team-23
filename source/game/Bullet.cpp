#include "Bullet.h"

#include "../engine/EngineApp.h"

Bullet::Bullet(int layer){
    m_collisionLayer = layer;
    scale = Vector(30.0f, 30.0f);
    SetSprite("bullet");

    m_timer = 0.0f;
    m_maxTimer = 3.0f;
    speed = 0.2f;
}

Bullet::~Bullet(){

}


void Bullet::Update(EngineApp& app, float deltaTime){
    position += direction * speed * deltaTime;

    // Collisions
    auto out = app.GetFirstCollision(this, m_collisionLayer);
    if (out != nullptr){
        app.RemoveEntity(out);
        app.RemoveEntity(this);
    }

    // Remove bullet
    m_timer += deltaTime * 0.001f;
    if (m_timer > m_maxTimer){
        app.RemoveEntity(this);
    }
}