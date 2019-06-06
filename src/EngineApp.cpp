#include "EngineApp.h"

EngineApp::EngineApp(){
    // INit SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw 1;

    m_window = SDL_CreateWindow("Game", 0,0, 640, 480, 0);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    
}

EngineApp::~EngineApp(){
    for (auto text : textures){
        SDL_DestroyTexture(text.second);
    }
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
        SDL_Event e;
        if ( SDL_PollEvent(&e) ){
            if (e.type == SDL_QUIT) 
                break;
        }

        //std::cout << "test\n";
        SDL_RenderClear(m_renderer);

        for (auto e : m_entities){
            e->Update();
        }

        //std::cout << "test1\n";
        for (auto e : m_entities){
            e->Draw(this);
        }

        SDL_RenderPresent(m_renderer);

    }
}

SDL_Renderer* EngineApp::GetRenderer(){
    return m_renderer;
}

void EngineApp::AddEntity(Entity* e){
    m_entities.emplace_back(e);
}