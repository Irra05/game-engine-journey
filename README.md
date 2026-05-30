# game-engine-journey
My journey to develop my own game engine.

I want to learn videogame development to make games with friends in my free time.

I started learning OpenGL for a course in the university and I really liked graphics programming. 
For now I know the bare minimum to make a functional program with OpenGL and GLFW (create a window, setup the projection matrix, draw shapes, apply transformations, change the colors, bind textures, clear the screen...), but I will keep exploring it on my own and learning more aspects (and maybe start with Vulkan at some point).

I realized that with the little knowledge I already have I can start making a very simple game engine from scratch.
Also I want to not depend on Unity, Godot and Unreal Engine. 

so I decided to start developing a game from scratch, just with C++, OpenGL and any audio library (this is a problem of the future :D).

## Approach
I have approached this project in a form of "loop iterations", in which I ask: What is the minimum that I have to implement in this iteration to actually see an upgrade from the last one?
And start a new project from scratch that replicates the functionality and implements the new functionality I want to implement.

This way, for the first iteration, I asked: What is the bare minimum that I have to do to make something that remembers to a 2D platformer?
The answer was: "I have to implement a block that moves left to right and jumps inside a box, and a camera that follows it".
I started experimenting with code and in one afternoon I got the result.
Since the project was relatively small, I could do it everything in a single file.

For the second iteration, the answer was: "I need to implement small platforms that the moving block can jump on collide".
This project was too big to try to fit it in a single file, so I looked up for ideas for project structure layouts. I found one that looks like this:
```
include/
    engine/
        a.hpp
        b.hpp
        c.hpp
        ...
src/
    main.cpp
    a.cpp
    b.cpp
    c.cpp
    ...
Makefile
```
which I liked, and I think I will use from now.

I am not following any tutorial that teaches me how to implement the features and how to structure the code. I am just flowing and doing what I feel that I have to do, and since I am doing it in short iterations, if I make a mistake and I realize too late about it, I can continue to finish the current iteration with it and be more aware on the next iteration. 

## Project structure
To actually develop a game engine, I am aware of two structures: Unity-like project structure, and what I have called "it just works" project structure.

In the Unity-like structure, everything inside a scene is a "game object", which can have "game components" and nested game objects. Game components are what give the functionality to game objects (physics, collissions, sprite rendering, animations, custom behaviour scripts...). For this approach, because everything is generalized, internally, in the current scene, you will have just a list of game objects with game components that will have an update function that will be called once per frame (in a general case). 

In the "it just works" structure, different objects have different data types based on the functionality that they have. For example, the player will have a different data type that the ground of the level, or the enemies. Because everything is specialized, this approach allows us to optimize and implement only the functionality that we need for each data type. So, at the end, in the current scene you will have several lists with objects, that may or may not need to be updated every frame.

The benefit of the Unity-like structure is that, because everything is generalized, it gives the game developers much more flexibility when it comes to design the functionality, allowing them to make big changes more easily if they changed their minds, which can be a big problem in the "it just works" structure.
On the other hand, the Unity-like sturcture require the developers to implement a lot of very complex functionality just to be able to start making the game, which is a little bit overkill for small projects, and can be very frustrating to do if you do not know exactly what you are doing (like me).
This is why, for now, I chose to use the "it just works" structure.

## More info of the already done iterations & plans for the future
On the first iteration, I setup a callback function that reads the keyboard input and sets or clears some global flags, one for each needed key (A, D and space bar), a player struct with coordinates, an enum attribute to track if it is grounded or not and an update method that is called once every frame and updates the coordinates based on the value of the deltaTime variable (the time between a frame and the next), the air status and the keyboard flags. For the horizontal movement, it just increments or decrements the position of the player at a fixed speed if the A or the D are pressed, and for the vertical movement, it uses some implementation of the uniformly accelerated straight movement that we all learnt in the high school. It will keep moving until the respective flag is cleared or the player object hits a border. After that, a camera object is updated to follow the horizontal movement of the player. To draw everything on the screen, I just drew a red rectangle in the coordinates where the player is supposed to be, and coloured rectangles to show the ground so it does not look like it is floating when it is grounded.

On the second iteration, (No borders, ground (floor) boxes, collissions, lista con floorBoxes que tengo que recorrer siempre)

My plans for the third iteration are (Switching between multiple scenes, tile ground level (no tengo que recorrer la lista en cada frame)).

My plans after that are to implement support for animations, and then implement audio.

## Building the iterations
To compile the projects, go to their respective folder. You will find detailed instructuions in their README, but generally, they will be: install Freeglut, GLEW, GLFW, the Mesa drivers and all its dependencies and run "make".
Also, this project is thought to be compiled and ran on Linux only, since I feel more comfrtable coding on it than on Windows. I don't have any short-term plan of porting the projects to Windows because they are for personal educational purposes. Apologies for that.
