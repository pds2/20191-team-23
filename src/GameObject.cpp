#include "GameObject.h"

#include "EngineApp.h"

GameObject::GameObject(){
    scale.x = 100;
    scale.y = 100;
}

GameObject::~GameObject(){

}

void GameObject::Start(){

}

void GameObject::Update(){
    
}

void GameObject::Draw(EngineApp* app){
    m_rect.x = position.x;
    m_rect.y = position.y;
    m_rect.w = scale.x;
    m_rect.h = scale.y;

    SDL_RenderCopy(app->GetRenderer(), app->textures["exit"], NULL, &m_rect);
}