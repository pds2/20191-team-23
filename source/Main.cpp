//Downloads:
//sudo apt-get install libsdl2-dev
//sudo apt-get install libsdl2-image-dev

// Compile:
// g++ -std=c++11 *.cpp -o app -lSDL2 -lSDL2_image
// g++ -std=c++11 engine/*.cpp *.cpp -o app -lSDL2 -lSDL2_image

#include <stdio.h>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "engine/EngineApp.h"
#include "engine/GameObject.h"

#include "game/Player.h"
#include "game/Enemy.h"

int main (int argc, char *argv[]) {
    EngineApp app("Test Game");

    // The json Data file
    app.LoadJson("../assets/");

    // The map
    for (int x=0; x<10; x++){
        for (int y=0; y<20; y++){
            GameObject* obj = new GameObject();
            obj->GetPosition() += Vector(y*100, x*100);
             obj->SetSprite("bg2");
            app.AddEntity(obj);
        }    
    }

    // Player
    Player* player = new Player();
    player->GetPosition() += Vector(50.0f, 50.0f);
    app.AddEntity(player);

    // The cops
    for (int x=0; x<8; x++){
        Enemy* bot = new Enemy();
        bot->GetPosition() += Vector(rand()%1300, rand()%600);
        app.AddEntity(bot);
    }

    // Game Loop
    app.GameLoop();

	return 0;
}