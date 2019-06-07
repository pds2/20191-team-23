#ifndef ENTITY_H
#define ENTITY_H

#include "Vector.h"
#include "Layer.h"

class EngineApp;

class InputMap;

class Entity{
public:
    Entity();
    virtual ~Entity();

    virtual void Start() = 0;
    virtual void Update(EngineApp* app, float deltaTime) = 0;
    virtual void Draw(EngineApp* app) = 0;

    inline Vector* GetPosition(){ return &position; }
    inline Vector* GetScale(){ return &scale; }

    inline Layer* GetLayers(){ return &m_layer; }
protected:
    Vector position;
    Vector scale;

    Layer m_layer;
private:

};

#endif // ! ENTITY_H