# Mario-with-own-ECS-game-engine--SFML-2023 : 

Project realized during a C++ course in our Bachelor 3 year at Ynov Bordeaux.

Developer team :

- [Léo Séry](https://github.com/LeoSery)
- [Titouan Mathis](https://github.com/Lyrym)

Artist :

- [Lucas Milh](https://github.com/Okaeri-nasaii)

![](https://hackmd.io/_uploads/S1Z1ZHMU3.png)

## Summary :

- Presentation
- Game keys
- How to open the project
- How to build the project

## Presentation :

In this project, the goal was to **create a game in C++ without using a game engine** and with a very **specific project architecture**. We developed our **own engine with an ECS** (*Entity Component System*) architecture. Then we **made a Mario game** to demonstrate **how our engine works**. 

## Game keys :

- *Movement*:
    - Move to the left: **Q** or **Left arrow**
    - Move to the right: **D** or **Right arrow**
    - Jump **Z** or **Up arrow**

## Main mechanics : 


You can **move** your character using the buttons above, but your aim is to **reach to the end of the level** by **dodging enemies and avoiding traps**.

You can **kill enemies by jumping on them**. Be careful, though, **if he touches you, you'll die** and have to **restart the level**.


## How to open the project:

- Clone the git repository to your computer with the following command :
```
git@github.com:LeoSery/Mario-with-own-ECS-game-engine--SFML-2023.git
```
or 
```
https://github.com/LeoSery/Mario-with-own-ECS-game-engine--SFML-2023.git
```

- Open the project folder and right click on `../CPP-Game/MarioSFML.sln`

## How to build the project : 

- 1 - Install Vcpkg, Cmake latest stable release, Powershell latest stable release
- 2 - Add Vcpkg to PATH environment variable for example : C:\vcpkg
- 3 - Install Sfml 64 bit : vcpkg install sfml:x64-windows 
- 4 - Install libcurl 64 bit : vcpkg install libcurl-simple-https:x64-windows 

- 5 - Add to PATH environment variable the path to your sfml debug installation : C:\vcpkg\installed\x64-windows\debug\bin

- 6 - Reboot Windows

- 7 - Check if the paths in CMakeLists are the same with your installation

- 8 - In the solution directory where the CMakeLists file is open a terminal and input: 
```
cmake .
```
Then
```
cmake build .
```
- 9 - You can now run the project in visual studio, or use the .exe **(if you do, be sure to copy the assets in the same folder as the .exe)**



