//Downloads:
//sudo apt-get install libsdl2-dev
//sudo apt-get install libsdl2-image-dev


// Compile:
// g++ -std=c++11 *.cpp -o app -lSDL2 -lSDL2_image

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "EngineApp.h"
#include "GameObject.h"

#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "exit2.png"

int main (int argc, char *argv[]) {
    EngineApp app;

    app.LoadTexture("exit", "exit2.png");

    Entity* a = new GameObject();

    app.AddEntity(a);

    app.GameLoop();

	return 0;
}