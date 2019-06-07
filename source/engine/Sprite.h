#ifndef SPRITE_H
#define SPRITE_H

#include <string>

class EngineApp;

class Sprite{
public:
    Sprite();
    Sprite(std::string prefix, int frameMax, int fps);
    virtual ~Sprite();

    void Update(float deltaTime);
    std::string GetDrawable();

    void SetTextureName(std::string prefix);
    void SetFrameMax(int frame);
    void SetFps(int fps);

    void SetFrame(int frame);
    int GetFrame();

    void Configure(std::string prefix, int frameMax, int fps);

private:
    float m_fps; // 1/fps
    int m_frame;
    int m_frameMax;
    float m_timer;

    std::string m_texturePrefix;

};

#endif // !SPRITE_H