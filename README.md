# Dodgy Square
![Gameplay](res/Gameplay.gif)

This is my capstone submission for the Udacity C++ course. I chose to pursue the game option for the capstone project. I have used SDL2 and made a very simple game I call 'Dodgy Square'. The game play is very straight-forward. The player is the green square and you must dodge the falling red squares. You can move the player object (green square) using the AWSD keys.
* A = Left
* D = Right
* S = Down
* W = Up
* Spacebar = Start game

The game will start on the title screen where the high score is shown and the user score is shown as well as the title of the game. Simply press the spacebar to start the game.

## Dependencies
The game requires
* cmake
    * installation: https://cmake.org/install/
* make
    * macOS: https://developer.apple.com/xcode/features/ install xcode-commandline-tools
    * Linux distros come with make installed
* SDL2
    * macOS: brew install sdl2
    * Linux: apt-get install libsdl2-dev
* SDL2_image
    * macOS: brew install sdl2_image
    * Linux: apt-get install libsdl2-image-dev
* SDL2_ttf
    * macOS: brew install sdl2_ttf
    * Linux: apt-get install libsdl2-ttf-dev
* g++
    * macOS: install xcode-commandline tools
    * Linux: comes with most distros

## Basic Build Instructions
1. git clone https://github.com/novacekn/DodgySquare
2. cd DodgySquare
3. mkdir build && cd build
4. cmake .. && make
5. ./DodgySquare

## Expected Output/Behavior
The game should launch to the title screen. The player can initiate the game by pressing the spacebar. Red squares will randomly fall downward and the player can dodge the falling red squares using the AWSD keys. Score is based on how many seconds the player can last dodging the squares. There is no 'live' score rendered to the play screen. Instead, after the player loses (by being struck by a red square) the title screen appears again showing the players score and also the high score.

## Code Structure
There are five classes that make up the whole of this game. These classes are 
* Entity
* Player
* Enemy
* Timer
* Game

Each class is specified in their respective header file and implemented in their respective cpp file.

#### Entity
The Entity class is the base class for every other entity in the game world. It provides the basic properties that all entities share such as a position (x, y), and width and height, a pointer to an SDL_Renderer object, a method Collide that will determine if two entities are colliding or not, and the methods Update and Render which every object will need.

#### Player
The player object is (obviously) what the player controls. It inherits from the Entity class and implements the methods an properties from that class appropriately. It adds an extra public method called Move which is needed to actually move the player.

#### Enemy
The Enemy class represents enemy objects. It is similar to the player object expect there is no Move method but there is a new public method IsAlive which is just a getter for the new private property alive_ which determines if the enemy is alive or not. I have made two different types of enemies, a big enemy and a small enemy. I have created a private vector that stores the paths to these enemy pngs and the constructor picks a random number (0 or 1) and that is what decides which type of enemy spawns. The enemy is marked 'unalive .. alive_ = false' when it falls out of the screen. The Update method will delete 'unalive' enemies and remove them from the enemies_ vector in Game.

#### Timer
The Timer class exists to keep the FPS capped. It has Start, Stop, GetTicks, and IsStarted methods.

#### Game
The Game class is kind of the 'master' class in some sense. It ties all of the unrelated objects together into a game world. Instances of all of the different objects are created and placed into the world to interact. The Game class has many methods and many properties.

#### Other
The first time the game is played a new file high_score.txt will be created. This will store new high scores in the future as well.

All source files are in the src directory. All resources/assets are in the res directory. In order to get cmake to work with SDL2 completely (SDL2_image and SDL2_ttf in particular) I had to add two cmake files in the cmake directory that find the associated libraries.

## Rubric Criteria
#### Loops, Functions, I/O
- A Large variety and amount of control structures are used throughout all of this project. This criteria has been thoroughly met.

- The project reads and writes to/from an external file. In Game::SetHighScore() (Game.cpp 92:99) and Game::HighScore() (Game.cpp 64:75).

- While not the 'typical' use case of input, human input is necessary for this project. Player input is used mainly in Player::Move() (Player.cpp 31:49).

#### Object Oriented Programming
- Clearly and obviously this project takes advantage of the OOP style of programming. Every logical object has its own class that encapsulates that objects properties and actions.

- Each class uses access modifiers appropriately.

- Inheritance is used in the project. Most of the classes inherit from the Entity class.

- The virtual functions from Entity (Entity::Update() and Entity::Render() (Entity.h )) are overridden in nearly every derived class.

- The Enemy and Game classes use destructors to clean up the unmanaged memory from the SDL_Texture pointers.

#### Concurrency
- The scoring mechanism for the game is based on how many seconds the player lasts. See (Game.cpp Gae::SetScore() 17:22) this method is started in a separate thread (Game.cpp Game::NewGame() line 224).