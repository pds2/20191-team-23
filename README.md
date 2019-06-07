# Basic 2D Game Engine
#### 20191-team-23

This project is a basic 2D game engine with a basic platformer game. The main goals of the game engine is:
- Create something easy to use and reuse in different cases (different types of 2D games).
- Provide a basic Game Engine Application with a gameloop and image rendering methods.
- Provide Vector and basic physics math.
- Provide some interface and base classes to write custom game objects to build the game. 

# How to Compile the Code
The following libraries are needed in order to compile the code:
- [SDL2](https://www.libsdl.org/download-2.0.php)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
The links provided includes the development libraries needed for **Mac OS X** and **Windows**.
If you are using a **Linux** distribution, you can get the dev version of the libraries using **apt-get**:
```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
```
Once you installed the libraries, use the **make** command to call the Makefile. The binary output will appear in the **bin/** folder.

# How the Engine Works (basics)
The EngineApp class is the main class that controls everything. To start using the engine, just include it in the main code, create an instance and call the gameloop when you want to start running the game:
```cpp
int main(int argc, char* argv[]){
    EngineApp app("Title");
    app.GameLoop(); // Run the game
    return 0;
}
```
The Entity class (interface for the objects) includes a Start, Update and Draw methods.
- The **Start** method is called when the entity is registered in the EngineApp, ideal to initialize the logic.
- The **Update** method is called every logic frame.
- The **Draw** method is called every render frame.
You can add a new Entity by calling:
```cpp
    app.AddEntity(new GameObject()); // GameObject inherits Entity
```
You can access keyboard inputs by creating a new Key Map in the InputMap class instance provided in the EngineApp. Every Key Map can store multiple keys and a float value for each one and can be accessed in the **Update** method of the Entities. This is ideal to allow multiple keyboard mapping (like control the character using W,A,S,D and the keyboard arrows). If you want to setup a basic A and D movement, for example, just write this before the GameLoop method:
```cpp
    inputMap.NewMap("forward");
    inputMap.BindKey("forward", KEY_W, 1.0f);
    inputMap.BindKey("forward", KEY_S, -1.0f);
``` 
And access this value in the **Update** method of the entities by:
```cpp
    float value = app.GetInputMap().GetValue("forward");
```

# Credits
Created by:
- Guilherme Teres Nunes (UnidayStudio)
- Breno Tanure Prata