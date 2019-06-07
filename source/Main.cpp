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


    // Character Textures
    app.LoadTexture("c_idle_1", "../assets/character/Guy-Weapon-idle1.png");
    app.LoadTexture("c_idle_2", "../assets/character/Guy-Weapon-idle2.png");

    app.LoadTexture("c_walk_1", "../assets/character/Guy-Weapon-walk1.png");
    app.LoadTexture("c_walk_2", "../assets/character/Guy-Weapon-walk2.png");
    app.LoadTexture("c_walk_3", "../assets/character/Guy-Weapon-walk3.png");
    app.LoadTexture("c_walk_4", "../assets/character/Guy-Weapon-walk4.png");

    // Cop textures
    app.LoadTexture("cop_idle_1", "../assets/character/Cop-idle1.png");
    app.LoadTexture("cop_idle_2", "../assets/character/Cop-idle2.png");

    app.LoadTexture("cop_walk_1", "../assets/character/Cop-walk1.png");
    app.LoadTexture("cop_walk_2", "../assets/character/Cop-walk2.png");
    app.LoadTexture("cop_walk_3", "../assets/character/Cop-walk3.png");
    app.LoadTexture("cop_walk_4", "../assets/character/Cop-walk4.png");

    // Level
    app.LoadTexture("bg1", "../assets/Visual-Background.png");
    app.LoadTexture("bg2", "../assets/Block-background.png");

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