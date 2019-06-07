#include "GameObject.h"

#include <iostream>
#include <bitset>

#include "EngineApp.h"

GameObject::GameObject(){
    scale.x = 100;
    scale.y = 100;
}

GameObject::~GameObject(){

}

void GameObject::Start(){

}

void GameObject::Update(EngineApp* app, float deltaTime){
    InputMap* inputMap = app->GetInputMap();

    
    if (!m_layer.Intersect(2)){
        position.x += inputMap->GetValue("forward")*0.01;
        position.y -= inputMap->GetValue("upward")*0.01;
        
        bool out = app->Collided(this, Layer(2));
        if (out){
            std::cout << "Working!\n";
        }
    }
}

void GameObject::Draw(EngineApp* app){
    m_rect.x = position.x;
    m_rect.y = position.y;
    m_rect.w = scale.x;
    m_rect.h = scale.y;

    SDL_RenderCopy(app->GetRenderer(), app->textures[m_spriteName], NULL, &m_rect);
}

 void GameObject::SetSprite(std::string name){
     m_spriteName = name;
 }