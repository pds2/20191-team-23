#ifndef ENTITY_H
#define ENTITY_H

#include "Vector.h"

class EngineApp;

class InputMap;

class Entity{
public:
    Entity();
    virtual ~Entity();

    virtual void Start() = 0;
    virtual void Update(InputMap* inputMap) = 0;
    virtual void Draw(EngineApp* app) = 0;

    inline Vector* GetPosition(){return &position;}
    inline Vector* GetScale(){return &scale;}

protected:
    Vector position;
    Vector scale;
private:

};

#endif // ! ENTITY_H