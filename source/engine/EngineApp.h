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

    void LoadJson(std::string path);
    void LoadTexture(std::string name, std::string path);

    void DrawSprite(std::string& texture, Vector& position, Vector& scale, bool flip);

    void AddEntity(Entity* e);
    void RemoveEntity(Entity* e);

    // Physics Methods
    std::vector<Entity*> GetCollisions(Entity* e, Layer layer);
    bool Collided(Entity* e, Layer layer);
    Entity* GetFirstCollision(Entity* e, Layer layer);

    //
    InputMap& GetInputMap();
    SDL_Renderer& GetRenderer();

    Vector& GetCameraPosition();

private:
    void Render();
    void RemoveEntities();

    Vector m_cameraPosition;

    std::vector<Entity*> m_entities;
    std::vector<Entity*> m_removeEntities;
    std::unordered_map<std::string, SDL_Texture*> m_textures;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    InputMap m_inputMap;

    SDL_Rect m_poolRect;
};

#endif // !ENGINE_APP_H