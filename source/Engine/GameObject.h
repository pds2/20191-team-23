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
    virtual void Update(InputMap* inputMap) override;
    virtual void Draw(EngineApp* app) override;

    void SetSprite(std::string name);

private:
    std::string m_spriteName;
    SDL_Rect m_rect;
};

#endif // !GAME_OBJECT_H