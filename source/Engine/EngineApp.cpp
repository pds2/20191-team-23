#include "EngineApp.h"

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

    for (auto text : textures){
        SDL_DestroyTexture(text.second);
    }
    textures.clear();

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void EngineApp::LoadTexture(std::string name, std::string path){
    int w, h;

    textures[name] = IMG_LoadTexture(m_renderer, path.c_str());
    SDL_QueryTexture(textures[name], NULL, NULL, &w, &h);
}

void EngineApp::GameLoop(){
    for (auto e : m_entities){
        e->Start();
    }

    while (1){
        //std::cout << "\n\n\tMainloop\n";
        m_inputMap.Update();

        if(m_inputMap.GetQuitEvent()){
            break;
        }

        for (auto e : m_entities){
            e->Update(this, 0.1f);
        }

        Render();
        RemoveEntities();
    }
}

void EngineApp::Render(){
    // Rendering...
    SDL_RenderClear(m_renderer);
    for (auto e : m_entities){
        e->Draw(this);
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

SDL_Renderer* EngineApp::GetRenderer(){
    return m_renderer;
}

void EngineApp::AddEntity(Entity* e){
    m_entities.emplace_back(e);
}

 void EngineApp::RemoveEntity(Entity* e){
     // Entities needs to be removed in the end of the gameloop
     m_removeEntities.emplace_back(e);
 }

InputMap* EngineApp::GetInputMap(){
    return &m_inputMap;
}

// Physics Methods
std::vector<Entity*> EngineApp::GetCollisions(Entity* e, Layer layer){
    std::vector<Entity*> out;

    for (Entity* other : m_entities){
        if (other->GetLayers()->Intersect(layer)){
            if (physics::AABB(e, other)){
               out.emplace_back(other);
            }
        }
    }
    return out;
}

bool EngineApp::Collided(Entity* e, Layer layer){
    for (Entity* other : m_entities){
        if (other->GetLayers()->Intersect(layer)){
            if (physics::AABB(e, other)){
                return true;
            }
        }
    }
    return false;
}

Entity* EngineApp::GetFirstCollision(Entity* e, Layer layer){
    for (Entity* other : m_entities){
        if (other->GetLayers()->Intersect(layer)){
            if (physics::AABB(e, other)){
                return other;
            }
        }
    }
    return nullptr;
}