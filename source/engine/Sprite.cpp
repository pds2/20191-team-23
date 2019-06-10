#include "Sprite.h"

#include "EngineApp.h"

Sprite::Sprite(){
    Configure("", 5, 4);
}
Sprite::Sprite(std::string prefix, int frameMax, int fps){
    Configure(prefix, fps, frameMax);
}
Sprite::~Sprite(){
     
}

void Sprite::Configure(std::string prefix, int frameMax, int fps){
    m_texturePrefix = prefix;
    m_timer = 0.0f;
    m_frame = 0;

    SetFps(fps);    
    m_frameMax = frameMax;
}

void Sprite::Update(float deltaTime){
    m_timer += deltaTime * 0.001f; // convert to seconds isntead of ms
    if (m_timer > m_fps){
        m_timer = 0.0f;
        m_frame++;
    }
    m_frame = m_frame % m_frameMax;
}
std::string Sprite::GetDrawable(){
    return m_texturePrefix + std::to_string(m_frame + 1);
}

void Sprite::SetTextureName(std::string prefix){
    m_texturePrefix = prefix;
}
void Sprite::SetFrameMax(int frame){
    m_frameMax = frame;
}
void Sprite::SetFps(int fps){
    m_fps = 1.0f/(float)fps;
}

void Sprite::SetFrame(int frame){
    m_frame = abs(frame) % m_frameMax;
}
int Sprite::GetFrame(){
    return m_frame;
}