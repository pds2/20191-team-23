#include "EngineApp.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "InputNames.h"

// To parse the .json file
#include "../../extern/include/RSJparser.tcc"

#define JSON_NAME "data.json"

#define assert(x) 

EngineApp::EngineApp(std::string name){
    // INit SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw 1;

    m_window = SDL_CreateWindow(name.c_str(), 50,50, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    m_orthoScale = 900.0f;
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

    for (auto it : data["inputMaps"].as_map<RSJresource>()){
        m_inputMap.NewMap(it.first);
        //std::cout << "New Map: " << it.first <<std::endl;
        for (auto map : it.second.as_map<double>()){
            m_inputMap.BindKey(it.first, InputNamesStr[map.first], (float)map.second);
            //std::cout << "\tNew Key: " << map.first << ", value: " << value <<std::endl;
        }
    }

    ifs.close();
}

void EngineApp::LoadTexture(std::string name, std::string path){
    int w, h;

    m_textures[name] = IMG_LoadTexture(m_renderer, path.c_str());
    SDL_QueryTexture(m_textures[name], NULL, NULL, &w, &h);
}

void EngineApp::GameLoop(){
    // Delta Time
    Uint64 dtNow = SDL_GetPerformanceCounter();
    Uint64 dtLast = 0;
    float deltaTime = 0.0f;

    while (1){
        dtLast = dtNow;
        dtNow = SDL_GetPerformanceCounter();
        deltaTime = (float)((dtNow-dtLast)*1000.0 / (float)SDL_GetPerformanceFrequency());// * 0.001f;
        //std::cout << "Delta Time: " << deltaTime << "s"<< std::endl;

        UpdateWindowSize();
        m_inputMap.Update();

        if(m_inputMap.GetQuitEvent()){
            break;
        }

        for (auto e : m_entities){
            e->Update(*this, deltaTime);
        }

        Render();
        RemoveQueuedEntities();
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

void EngineApp::RemoveQueuedEntities(){
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

void EngineApp::UpdateWindowSize(){
    int x,y;
    SDL_GetWindowSize(m_window, &x, &y);
    m_windowSize = Vector(x, y);
}

void EngineApp::DrawSprite(std::string& texture, Vector& position, Vector& scale, bool flip){
    float factor = m_windowSize.x / m_orthoScale;
    m_poolRect.x = (position.x + m_cameraPosition.x) * factor;
    m_poolRect.y = (position.y + m_cameraPosition.y) * factor;
    m_poolRect.w = abs(scale.x) * factor;
    m_poolRect.h = abs(scale.y) * factor;

    if (scale.x < 0.0) throw std::invalid_argument("scale.x was negative and thus converted to positive");
    if (scale.y < 0.0) throw std::invalid_argument("scale.y was negative and thus converted to positive");

    SDL_RendererFlip rFlip = SDL_FLIP_NONE;
    if (flip){
        rFlip = SDL_FLIP_HORIZONTAL;
    }

    //SDL_RenderCopy(m_renderer, m_textures[texture], NULL, &m_poolRect);
    SDL_RenderCopyEx(m_renderer, m_textures[texture], NULL, &m_poolRect, 0.0, NULL, rFlip);
}

void EngineApp::AddEntity(Entity* e){
    e->Start();
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

Vector& EngineApp::GetWindowSize(){
    return m_windowSize;
}

void EngineApp::SetOrthographicScale(float scale){
    assert(scale > 1.0f);
    m_orthoScale = scale;
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