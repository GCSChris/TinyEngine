# Tiny Engine
### [Project Webpage](https://tinyenginecs4850.wordpress.com/)
### [Project Trailer](https://youtu.be/TnI-HnQDgd8)

## Team

Team Name: Bjarne Stroustrup Appreciation Station
Option Chosen: Option 2

Development Team:
- Tyler Gier
- Christopher DiNome
- Caroline Pasyanos

Note: For hello-world.py, the error messages printed are due to the RGB format of the braid spritesheet. 

## TinyEngine: Building from Source (via Windows using MinGW)
- Clone the Github Repo
- Install Python3, Pip3 and Pybind11
	If Pip3 is not installed, you can install it using the "get-pip.py" file in the repo.
- Install [SDL2](https://www.libsdl.org/download-2.0.php), [SDL_Image](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.3-VC.zip), [SDL_TTF](https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-VC.zip), and [SDL_Mixer](https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.2-VC.zip) Making sure that your version of SDL2 is compatible with all of the other dependencies (For example, SDL2 2.0.7 works with SDL_Image 2.0.2, and SDL2 2.0.8 works with SDL_Image 2.0.3)
- Navigate to the cloned repo
- Run "sh mingw64build.sh". This will produce 2 .pyd files (tinyengine.pyd and tinymath.pyd)
- Open up a new Python script and import tinyengine (importing tinymath is optional but will give you additional access to math functions)
- Run the Python script using "python3 your-python-file.py"

If you run into any issues, make sure the .DLL files (included in the repo or from your installation) and the .pyd files (Produced from the build script) are in your project folder.
