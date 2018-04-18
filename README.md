# Tiny Engine
### https://tinyenginecs4850.wordpress.com/

## Team

Team Name: Bjarne Stroustrup Appreciation Station
Option Chosen: Option 2

Development Team:
- Tyler Gier
- Christopher DiNome
- Caroline Pasyanos

## TinyEngine: Building from Source (Currently source is only buildable via Windows using MinGW)
- Clone the Github Repo
- Install Python3, Pip3 and Pybind11
	If Pip3 is not installed, you can install it using the "get-pip.py" file in the repo.
- Install SDL2, SDL_image, SDL_ttf and SDL_mixer
- Navigate to the cloned repo
- Run the appropriate build script for your OS. This will produce 2 .pyd files (tinyengine.pyd and tinymath.pyd)
- Open up a new Python script and import tinyengine (importing tinymath is optional but will give you additional access to math functions)
- Run the Python script using "python3 your-python-file.py"

If you run into any issues, make sure the .DLL files (included in the repo) and the .pyd files (Produced from the build script) are in your project folder.


# Class Project Logisitics Below this Point

## Final Project - Description

The industry is getting positive buzz as Nolan and Shigeru have been talking about your studio. But dynamics change rapidly in the game industry, and your team has once again decided to part ways and form a new studio. Your team during this time has also developed a nice codebase of intellectual property, and has decided forming a 'game making' studio is the best option. Your team has decided it will start building an impressive piece of middleware (i.e. a tool or technology that is not a game) to showcase at the giant tradeshows (PAX East, GDC, E3, etc.) 

## Options

### Option 1 - Tech Demo 2D or 3D

Often a game mechanic or graphical technique is later developed into a game. For your final project you can build a high powered tech demo. This should be a short showcase of some feature demo that showcases your technology. The demo can be 2D or 3D.

Some examples of tech demos
- https://www.youtube.com/watch?v=ni-SmkCY-Sw (2D game demo showing off only 1 feature that is sufficiently complex)
- https://www.youtube.com/watch?v=4W8zxAV8RRY (2D game engine lighting effects)
- https://www.youtube.com/watch?v=LseTVMkG7V8 (An even better 2D game engine lighting effects, something like this is final project worthy if incorporated into platformer)
- https://www.youtube.com/watch?v=gLAYBdHxfjs (Shows a few of the features of a game tool)
- https://www.youtube.com/watch?v=jVlxmC2qBGU (Unity3D Tech demo showing off one simple but high powered toggable feature in an editor).


### Option 2 - Game Maker

For your final project, you may make a 'game maker'. That is, you will build a tool that someone with no C++ knowledge can use. Our pybind11 lab is a good starting point. You should document some 2D API for your games.

Some examples for inspiration
- Look on the left panel to see the API for the Love2D engine: https://love2d.org/wiki/Main_Page
- Look at Gamemakers API for inspiration of what commands are exposed. http://docs2.yoyogames.com/
- https://www.youtube.com/watch?v=b8RyQSvmrEU (Shows a neat console editor)
- https://www.youtube.com/watch?v=oU69bjOMTUc (Another platformer, shows off some cool extensions to our project, with transparency, particles, etc.)
- https://www.youtube.com/watch?v=o59PVYfKlzQ (A little RPG like game. Neat effects, and can benefit from some sort of scripting engine for battle sequences).
- https://www.youtube.com/watch?v=5ZuQIbMEjLw (Here is GoDot engine. I would look to GoDot and GameMaker as inspiration).

### Constraints on Options 1 and 2

The constraints are that you have to build the majority of your technology. 3rd party libraries for a physics engine are okay, and must be cited. 3rd party game or graphics engines may not be used (e.g. you cannot build a tech demo with Ogre3D or Unity3D).

## Minimum Viable Product

A Minimum Viable Product (MVP) is the smallest subset of features that you consider a project to be a success. Make a list below of the features you consider to be in your MVP. Then make a list of features that are 'stretch goals' that you think you can achieve.

MVP
- Engine based in C++
- User can create arbitrary 2D games in python using our C++ library
- Library supports rendering images, rendering text, playing music and SFX
- Library supports animations and sprite sheets (rendering indexed images in a larger image file)
- User can provide abitrary images in supported formats (bmp, png)
- User can provide sound effects, custom music and custom fonts
- Library provides out of the box math support for vectors and matrices
- 2 to 3 different games demoing the flexibility and features of TinyEngine

Stretch Goals
- Basic physics library module (to handle things like forces)
- User can provide a sprite sheet and frame rate, and then the library will automatically animate the sprite when rendered
- Mouse input supported (On click, on drag, etc.)


## Requirements (For either option)

### Documentation
Fire up 'Doxygen' <a href="http://www.stack.nl/~dimitri/doxygen/">(Doxygen webpage)</a> to document the source code and automatically generate .html pages. Your documentation should cover your classes and functions.

Additionally, you documentation should have instructions on how to obtain, build, and run your final project.

### Build (binary file)
You need to have a compiled binary of your game. You can assume a target audience of either a 64-bit Mac, Ubuntu Linux, or Windows 10 machine. There should additionally be instructions about how to compile your code from source.

### Post mortem
A post mortem in games is a look back at what could be improved. Write a brief (2-3 paragraphs) on what could be improved if you had an additional 8 weeks to work on this project. Where would you allocate time, what tools would you build, would you use any different tools, etc.

### Website
Your documentation, a link to your binary, and your post mortem should be put together on a 1-page .html page. Additionally, provide a 1 minute video trailer(but 1 minute I suggest) and at least 3 screenshots of your game. This website will be the first place I look to grab your project. (Additionally, I think it is important to build a portfolio of your game development works!)

### Project Hieararchy

There should be some logical hierarchy for your project. Look to previous assignments for inspiration. Your project should not differ greatly unless there is a reason justified in your documentation.

## Rubric

This project will be evaluated in the following way. 

- 25% On meeting the requirements above
- 25% If you achieved your "Minimum viable product" (from your lab proposal.)
- 25% On the polish of your final project (did it work as intended, were there bugs, did I have to struggle to get your tool running)
- 25% On the creativity and overall 'wow' factor of your project. 
  - Some of this requirement *could* be met with the following idea. But you are not limited to this rubric.
    - Was there a cool feature or surprise that got me excited about the project?
    - Does this project have potential to be extended in the future?
    - Were there creative additional tools that supported your work.
    - Was there something not covered in class that you were excited about, learned, and implemented anyway? (Document this to bring to my attention if so!)
