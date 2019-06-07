#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>

#include "Entity.h"

class GameObject : public Entity{
public:
    GameObject();
    virtual ~GameObject();

    virtual void Start() override;
    virtual void Update(InputMap* inputMap) override;
    virtual void Draw(EngineApp* app) override;

protected:
private:
    SDL_Rect m_rect;

};

#endif // !GAME_OBJECT_H