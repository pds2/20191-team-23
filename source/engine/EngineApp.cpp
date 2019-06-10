#include "EngineApp.h"

#include <fstream>
#include <iostream>
#include <string>

// To parse the .json file
#include "../../extern/include/RSJparser.tcc"

#define JSON_NAME "data.json"

EngineApp::EngineApp(std::string name){
    // INit SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw 1;

    m_window = SDL_CreateWindow(name.c_str(), 50,50, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    
}

EngineApp::~EngineApp(){
    for (auto e : m_entities){
        delete e;
    }
    m_entities.clear();
    m_removeEntities.clear();

    for (auto text : m_textures){
        SDL_DestroyTexture(text.second);
    }
    m_textures.clear();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void EngineApp::LoadJson(std::string path){
    // Reference: https://github.com/subh83/RSJp-cpp

    std::ifstream ifs(path+JSON_NAME);
    RSJresource data(ifs);

    for (auto it : data["textures"].as_map<std::string>()){
        LoadTexture(it.first, path + it.second);
    }

    ifs.close();
}

void EngineApp::LoadTexture(std::string name, std::string path){
    int w, h;

    m_textures[name] = IMG_LoadTexture(m_renderer, path.c_str());
    SDL_QueryTexture(m_textures[name], NULL, NULL, &w, &h);
}

void EngineApp::GameLoop(){
    for (auto e : m_entities){
        e->Start();
    }

    // Delta Time
    Uint64 dtNow = SDL_GetPerformanceCounter();
    Uint64 dtLast = 0;
    float deltaTime = 0.0f;

    while (1){
        dtLast = dtNow;
        dtNow = SDL_GetPerformanceCounter();
        deltaTime = (float)((dtNow-dtLast)*1000.0 / (float)SDL_GetPerformanceFrequency());// * 0.001f;
        //std::cout << "Delta Time: " << deltaTime << "s"<< std::endl;

        m_inputMap.Update();

        if(m_inputMap.GetQuitEvent()){
            break;
        }

        for (auto e : m_entities){
            e->Update(*this, deltaTime);
        }

        Render();
        RemoveEntities();
    }
}

void EngineApp::Render(){
    // Rendering...
    SDL_RenderClear(m_renderer);
    for (auto e : m_entities){
        e->Draw(*this);
    }
    SDL_RenderPresent(m_renderer);
}

void EngineApp::RemoveEntities(){
    for (auto rm : m_removeEntities){
        int i=0;
        for (auto e : m_entities){
            if (rm == e){
                m_entities.erase(m_entities.begin()+i);
                delete e;
                break;
            }
            i++;
        }
    }
    m_removeEntities.clear();
}

void EngineApp::DrawSprite(std::string& texture, Vector& position, Vector& scale, bool flip){
    m_poolRect.x = position.x + m_cameraPosition.x;
    m_poolRect.y = position.y + m_cameraPosition.y;
    m_poolRect.w = scale.x;
    m_poolRect.h = scale.y;

    SDL_RendererFlip rFlip = SDL_FLIP_NONE;
    if (flip){
        rFlip = SDL_FLIP_HORIZONTAL;
    }


    //SDL_RenderCopy(m_renderer, m_textures[texture], NULL, &m_poolRect);
    SDL_RenderCopyEx(m_renderer, m_textures[texture], NULL, &m_poolRect, 0.0, NULL, rFlip);
}

void EngineApp::AddEntity(Entity* e){
    m_entities.emplace_back(e);
}

 void EngineApp::RemoveEntity(Entity* e){
     // Entities needs to be removed in the end of the gameloop
     m_removeEntities.emplace_back(e);
 }

InputMap& EngineApp::GetInputMap(){
    return m_inputMap;
}

SDL_Renderer& EngineApp::GetRenderer(){
    return *m_renderer;
}

Vector& EngineApp::GetCameraPosition(){
    return m_cameraPosition;
}

// Physics Methods
std::vector<Entity*> EngineApp::GetCollisions(Entity* e, Layer layer){
    std::vector<Entity*> out;

    for (Entity* other : m_entities){
        if (other->GetLayers().Intersect(layer)){
            if (physics::AABB(*e, *other)){
               out.emplace_back(other);
            }
        }
    }
    return out;
}

bool EngineApp::Collided(Entity* e, Layer layer){
    for (Entity* other : m_entities){
        if (other->GetLayers().Intersect(layer)){
            if (physics::AABB(*e, *other)){
                return true;
            }
        }
    }
    return false;
}

Entity* EngineApp::GetFirstCollision(Entity* e, Layer layer){
    for (Entity* other : m_entities){
        if (other->GetLayers().Intersect(layer)){
            if (physics::AABB(*e, *other)){
                return other;
            }
        }
    }
    return nullptr;
}