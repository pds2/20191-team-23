#ifndef ENGINE_APP_H
#define ENGINE_APP_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.h"
#include "InputMap.h"
#include "Layer.h"
#include "Physics.h"

class EngineApp{
public:
    EngineApp(std::string name);
    virtual ~EngineApp();

    void GameLoop();

    void LoadTexture(std::string name, std::string path);

    std::unordered_map<std::string, SDL_Texture*> textures;

    SDL_Renderer* GetRenderer();

    void AddEntity(Entity* e);
    void RemoveEntity(Entity* e);

    // Physics Methods
    std::vector<Entity*> GetCollisions(Entity* e, Layer layer);
    bool Collided(Entity* e, Layer layer);
    Entity* GetFirstCollision(Entity* e, Layer layer);

    InputMap* GetInputMap();

private:
    void Render();
    void RemoveEntities();

    std::vector<Entity*> m_entities;
    std::vector<Entity*> m_removeEntities;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    InputMap m_inputMap;
};

#endif // !ENGINE_APP_H