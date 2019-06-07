#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <string>

#include "Entity.h"

class GameObject : public Entity{
public:
    GameObject();
    virtual ~GameObject();

    virtual void Start() override;
    virtual void Update(EngineApp& app, float deltaTime) override;
    virtual void Draw(EngineApp& app) override;

    void SetSprite(std::string name);

protected:
    std::string m_spriteName;
private:
};

#endif // !GAME_OBJECT_H