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

const int map[10][20] = {
                     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                     };

int main (int argc, char *argv[]) {
    EngineApp app("Game1");
    InputMap& inputMap = app.GetInputMap();

    // Keyboard Maps
    inputMap.NewMap("forward");
    inputMap.BindKey("forward", KEY_A, -1.0f);
    inputMap.BindKey("forward", KEY_D, 1.0f);

    inputMap.NewMap("upward");
    inputMap.BindKey("upward", KEY_S, -1.0f);
    inputMap.BindKey("upward", KEY_W, 1.0f);

    inputMap.NewMap("shoot");
    inputMap.BindKey("shoot", KEY_SPACE, 1.0f);

    // The json file
    app.LoadJson("../assets/");

    // The map
    for (int x=0; x<10; x++){
        for (int y=0; y<20; y++){
            GameObject* obj = new GameObject();
            obj->GetPosition() += Vector(y*100, x*100);
            /*if (map[x][y] == 1){
                obj->SetSprite("bg1");
            } else{
                obj->SetSprite("bg2");
            }*/
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