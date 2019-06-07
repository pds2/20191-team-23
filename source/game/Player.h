#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/GameObject.h"
#include "../engine/Sprite.h"

class Player: public GameObject{
public:
    Player();
    virtual ~Player();

    virtual void Update(EngineApp& app, float deltaTime) override;
    virtual void Draw(EngineApp& app) override;

private:
    Sprite m_sIdle;
    Sprite m_sWalk;

    bool m_walking;
    bool m_spriteFlip;

    float m_walkSpeed;
};

#endif // !PLAYER_H