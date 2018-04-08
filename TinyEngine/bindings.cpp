#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

// The glad library helps setup OpenGL extensions.
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include "SFXManager.h"
// Purpose:
// This class sets up a full graphics program using SDL
//
//
//
class SDLGraphicsProgram{
public:

    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Destructor
    ~SDLGraphicsProgram();
    // Setup OpenGL
    bool initGL();
    // Clears the screen
    void clear();
    // Flips to new buffer
    void flip();
    // Delay rendering
    void delay(int milliseconds);
    // loop that runs forever
    void loop();
    // Get Pointer to Window
    SDL_Window* getSDLWindow();
    // Draw a simple rectangle
    void DrawRectangle(int x, int y, int w, int h, bool fill);
    // Sets the color for the Renderer
    void SetColor(int r, int g, int b, int a);
    // Draws given image as a 2D sprite
    void DrawImage(std::string imgPath, int x, int y, int w, int h);
    // Draws the given frame in a sprite sheet
    void DrawFrame(std::string imgPath, int frameNum, int x, int y, int w, int h);
    // Plays music from the given resource name_
    void PlayMusic(std::string path);
    // Toggles if the music is being played, returning if the music is playing after
    bool ToggleMusic();
    // Plays the sound effect at the given path
    void PlaySFX(std::string path);
    // Sets the volume of the music
    void SetMusicVolume(int volume);
    // Gets the music volume
    int GetMusicVolume();
    // Renders the given text
    void RenderText(std::string text, std::string fontStyle, int fontSize, int x, int y);

    // Sets the framerate to cap at the given frames per second
    void SetFramerate(int fps);
    // returns if the given rectangles overlap
    bool RectIntersect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
    //check if the given key is pressed
    bool pressed(std::string key);

private:
    // Screen dimension constants
    int screenHeight;
    int screenWidth;
    // The window we'll be rendering to
    SDL_Window* gWindow ;
    // Our renderer
    SDL_Renderer* gRenderer;

    static std::map<std::string, int> keymap;
};


// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h):screenWidth(w),screenHeight(h){
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	gWindow = NULL;
	// Render flag

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
	    //Create window
    	gWindow = SDL_CreateWindow( "Lab", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN );

        // Check if Window did not create.
        if( gWindow == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create a Renderer to draw on
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        // Check if Renderer did not create.
        if( gRenderer == NULL ){
            errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }
  	}



    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    //Destroy window
	SDL_DestroyWindow( gWindow );
	// Point gWindow to NULL to ensure it points to nothing.
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}


// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::initGL(){
	//Success flag
	bool success = true;

	return success;
}


// clear
// Clears the screen
void SDLGraphicsProgram::clear(){
	// Nothing yet!
    SDL_SetRenderDrawColor(gRenderer, 0x44,0x44,0x4,0xFF);
    SDL_RenderClear(gRenderer);
}
// Flip
// The flip function gets called once per loop
// It swaps out the previvous frame in a double-buffering system
void SDLGraphicsProgram::flip(){
	// Nothing yet!
    SDL_RenderPresent(gRenderer);
}


void SDLGraphicsProgram::delay(int milliseconds){
    SDL_Delay(milliseconds);
}


//Loops forever!
void SDLGraphicsProgram::loop(){
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
    // While application is running
    while(!quit){
     	 //Handle events on queue
		while(SDL_PollEvent( &e ) != 0){
        	// User posts an event to quit
	        // An example is hitting the "x" in the corner of the window.
    	    if(e.type == SDL_QUIT){
        		quit = true;
	        }
      	} // End SDL_PollEvent loop.

      	//Update screen of our specified window
      	SDL_GL_SwapWindow(getSDLWindow());
    }

    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::getSDLWindow(){
  return gWindow;
}


// Okay, render our rectangles!
void SDLGraphicsProgram::DrawRectangle(int x, int y, int w, int h, bool fill){
    SDL_Rect fillRect = {x,y,w,h};
    if (fill) {
        SDL_RenderFillRect(gRenderer, &fillRect);
    } else {
        SDL_RenderDrawRect(gRenderer, &fillRect);
    }
}

void SDLGraphicsProgram::SetColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(gRenderer, a, r, g, b);
}

void SDLGraphicsProgram::DrawImage(std::string imgPath, int x, int y, int w, int h) {

}

void SDLGraphicsProgram::DrawFrame(std::string imgPath, int frameNum, int x, int y, int w, int h) {

}

void SDLGraphicsProgram::PlayMusic(std::string path) {
  SFXManager::instance().playMusic(path);

}

bool SDLGraphicsProgram::ToggleMusic() {

}

void SDLGraphicsProgram::PlaySFX(std::string path) {
  SFXManager::instance().playMusic(path);
}

void SDLGraphicsProgram::SetMusicVolume(int volume) {
  SFXManager::instance().setMusicVolume(volume);
}

int SDLGraphicsProgram::GetMusicVolume() {
  SFXManager::instance().getMusicVolume();
}

void SDLGraphicsProgram::RenderText(std::string text, std::string fontStyle, int fontSize, int x, int y) {

}

void SDLGraphicsProgram::SetFramerate(int fps) {

}

bool SDLGraphicsProgram::RectIntersect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {

}

std::map<std::string, int> SDLGraphicsProgram::keymap = []
{
    std::map<std::string, int> binds;
    binds["q"] = SDLK_q;
    binds["w"] = SDLK_w;
    binds["s"] = SDLK_s;
    binds["up"] = SDLK_UP;
    binds["down"] = SDLK_DOWN;
    return binds;
}();

bool SDLGraphicsProgram::pressed(std::string key){
    static std::map<int, bool> pressed;

//from https://stackoverflow.com/questions/11699183/what-is-the-best-way-to-read-input-from-keyboard-using-sdl
    SDL_Event event;
    while( SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
            pressed[event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            pressed[event.key.keysym.sym] = false;
            break;
        }
    }

    return pressed[keymap[key]];
}


// Include the pybindings
#include <pybind11/pybind11.h>

namespace py = pybind11;


// Creates a macro function that will be called
// whenever the module is imported into python
// 'mygameengine' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'
PYBIND11_MODULE(mygameengine, m){
    m.doc() = "The TinyEngine is python bindings for common SDL functions"; // Optional docstring

    py::class_<SDLGraphicsProgram>(m, "SDLGraphicsProgram")
            .def(py::init<int,int>(), py::arg("w"), py::arg("h"))   // our constructor
            .def("clear", &SDLGraphicsProgram::clear) // Expose member methods
            .def("delay", &SDLGraphicsProgram::delay)
            .def("flip", &SDLGraphicsProgram::flip)
            .def("loop", &SDLGraphicsProgram::loop)
            .def("pressed", &SDLGraphicsProgram::pressed)
            .def("DrawRectangle", &SDLGraphicsProgram::DrawRectangle)
            .def("SetColor", &SDLGraphicsProgram::SetColor) ;
// We do not need to expose everything to our users!
//            .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow, py::return_value_policy::reference)
}











#endif
