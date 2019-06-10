#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/GameObject.h"
#include "../engine/Sprite.h"

class Enemy : public GameObject{
public:
    Enemy();
    virtual ~Enemy();

    virtual void Update(EngineApp& app, float deltaTime) override;
    virtual void Draw(EngineApp& app) override;

    float stateTimeout;
private:
    void RandomizeState();

    Sprite m_sIdle;
    Sprite m_sWalk;

    bool m_walking;
    bool m_spriteFlip;

    float m_walkSpeed;

    float m_timer;
    int m_fsm;
    Vector m_direction;
};

#endif // !ENEMY_H