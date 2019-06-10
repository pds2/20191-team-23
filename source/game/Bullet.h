#ifndef BULLET_H
#define BULLET_H

#include "../engine/GameObject.h"

class Bullet: public GameObject{
public:
    Bullet(int layer);
    virtual ~Bullet();

    virtual void Update(EngineApp& app, float deltaTime) override;

    Vector direction;
    float speed;
private:
    float m_timer;
    float m_maxTimer;
    int m_collisionLayer;
};

#endif // !BULLET_H