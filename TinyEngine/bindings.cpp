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
#include <algorithm>

#include "SFXManager.h"
#include "UIManager.h"
// Purpose:
// This class sets up a full graphics program using SDL
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
    void DrawFrame(std::string imgPath, int frameTick, int spriteNumFrames,
        int x, int y, int frameWidth, int frameHeight);
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
    void RenderCenteredText(std::string text, std::string fontStyle, int fontSize, int x);

    void SetTextColor(int r, int g, int b, int a);

    void SetBackgroundColor(int r, int g, int b, int a);

    // Should be call at the end of each game loop. Used for frame limiting
    void ApplyFrameCap();
    // Sets the framerate to cap at the given frames per second
    void SetFramerate(int fps);
    // returns if the given rectangles overlap
    bool RectIntersect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
    //check if the given key is pressed
    bool pressed(std::string key);
    // draws a line from point a to point b
    void DrawLine(std::pair<int, int> a, std::pair<int, int> b);
    // draws a list of line
    void DrawLines(std::vector<std::pair<int, int>> points, bool closed);
    // returns if the given lines (determines by end points of (a,b) and (c,d)) are intersecting
    bool LineIntersect(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c, std::pair<int, int> d);
    // determines if any two lines between the lists intersecting (a list of points determines a CLOSED  shape in order)
    bool ShapeIntersect(std::vector<std::pair<int, int>> a, std::vector<std::pair<int, int>> b);

private:
    // Screen dimension constants
    int screenHeight;
    int screenWidth;
    // The window we'll be rendering to
    SDL_Window* gWindow;
    // Our renderer
    SDL_Renderer* gRenderer;

    // the frame count at the beginning of the game loop
    int frameTickCount = 0;
    // The current game framerate
    int framerate = 60;

    // The state of the keys
    static std::map<std::string, int> keymap;

    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Color backgroundColor = {255, 255, 255, 255};
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
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else {
    //Create window
    gWindow = SDL_CreateWindow(title, 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN );

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

    TTF_Init(); //TODO

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

void SDLGraphicsProgram::SetBackgroundColor(int r, int g, int b, int a) {
  backgroundColor = {r, g, b, a};
}

// Clears the screen
void SDLGraphicsProgram::clear() {
  	// Nothing yet!
    SDL_SetRenderDrawColor(gRenderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
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
    SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
}

void SDLGraphicsProgram::DrawImage(std::string imgPath, int x, int y, int w, int h) {
  SDL_Texture* texture = ResourceManager::instance().getTexture(imgPath, gRenderer);

	SDL_Rect dest = { x, y, w, h };

  SDL_RenderCopy(gRenderer, texture, NULL, &dest);
}

static int getNumColumns(std::string fileName, int frameWidth) {
  SDL_Point dimensions = ResourceManager::instance().getIMGDimensions(fileName);
  int width = dimensions.x;
  return (width / frameWidth);
}

void SDLGraphicsProgram::DrawFrame(std::string imgPath, int frameTick, int spriteNumFrames,
    int x, int y, int frameWidth, int frameHeight) {

  SDL_Texture* texture = ResourceManager::instance().getTexture(imgPath, gRenderer);

  int currentFrame = frameTick * spriteNumFrames / framerate;

  int numColumns = getNumColumns(imgPath, frameWidth);
  int frameRectX = (currentFrame % numColumns) * frameWidth;
  int frameRectY = (currentFrame / numColumns) * frameHeight;
  SDL_Rect src = { frameRectX, frameRectY, frameWidth, frameHeight };
  SDL_Rect dest = { x, y, frameWidth, frameHeight };
  SDL_RenderCopy(gRenderer, texture, &src, &dest);
}

void SDLGraphicsProgram::PlayMusic(std::string path) {
  SFXManager::instance().playMusic(path);
}

bool SDLGraphicsProgram::ToggleMusic() {
  SFXManager::instance().toggleMusic();
  return (Mix_PlayingMusic() != 0);
}

void SDLGraphicsProgram::PlaySFX(std::string path) {
  SFXManager::instance().playSFX(path);
}

void SDLGraphicsProgram::SetMusicVolume(int volume) {
  SFXManager::instance().setMusicVolume(volume);
}

int SDLGraphicsProgram::GetMusicVolume() {
  SFXManager::instance().getMusicVolume();
}

void SDLGraphicsProgram::SetTextColor(int r, int g, int b, int a) {
  textColor = { r, g, b, a };
}

void SDLGraphicsProgram::RenderText(std::string text, std::string fontStyle, int fontSize, int x, int y) {
  UIManager::instance().renderText(gRenderer, text, fontStyle, fontSize, textColor, x, y);
}

void SDLGraphicsProgram::RenderCenteredText(std::string text, std::string fontStyle, int fontSize, int y) {
  UIManager::instance().renderCenteredText(gRenderer, text, fontStyle, fontSize, textColor, y, screenWidth);
}


void SDLGraphicsProgram::ApplyFrameCap() {
  int tickCount = SDL_GetTicks();
  int delayTime = 1000 / framerate - (tickCount - frameTickCount);
  if (delayTime > 0) {
    SDL_Delay(delayTime);
  }
  frameTickCount = tickCount;
}

void SDLGraphicsProgram::SetFramerate(int fps) {
  framerate = fps;
}

bool SDLGraphicsProgram::RectIntersect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  SDL_Rect r1 = {x1, y1, w1, h1};
  SDL_Rect r2 = {x2, y2, w2, h2};

  return (SDL_HasIntersection(&r1, &r2));
}

std::map<std::string, int> SDLGraphicsProgram::keymap = []
{
    std::map<std::string, int> binds;
    binds["esc"] = SDLK_ESCAPE;
    binds["f1"] = SDLK_F1;
    binds["f2"] = SDLK_F2;
    binds["f3"] = SDLK_F3;
    binds["f4"] = SDLK_F4;
    binds["f5"] = SDLK_F5;
    binds["f6"] = SDLK_F6;
    binds["f7"] = SDLK_F7;
    binds["f8"] = SDLK_F8;
    binds["f9"] = SDLK_F9;
    binds["f10"] = SDLK_F10;
    binds["f11"] = SDLK_F11;
    binds["f12"] = SDLK_F12;
    binds["delete"] = SDLK_DELETE;
    binds["home"] = SDLK_HOME;

    binds["`"] = SDLK_BACKQUOTE;
    binds["1"] = SDLK_1;
    binds["2"] = SDLK_2;
    binds["3"] = SDLK_3;
    binds["4"] = SDLK_4;
    binds["5"] = SDLK_5;
    binds["6"] = SDLK_6;
    binds["7"] = SDLK_7;
    binds["8"] = SDLK_8;
    binds["9"] = SDLK_9;
    binds["0"] = SDLK_0;
    binds["-"] = SDLK_MINUS;
    binds["="] = SDLK_EQUALS;
    binds["back"] = SDLK_BACKSPACE;

    binds["tab"] = SDLK_TAB;
    binds["q"] = SDLK_q;
    binds["w"] = SDLK_w;
    binds["e"] = SDLK_e;
    binds["r"] = SDLK_r;
    binds["t"] = SDLK_t;
    binds["y"] = SDLK_y;
    binds["u"] = SDLK_u;
    binds["i"] = SDLK_i;
    binds["o"] = SDLK_o;
    binds["p"] = SDLK_p;
    binds["["] = SDLK_LEFTBRACKET;
    binds["]"] = SDLK_RIGHTBRACKET;
    binds["\\"] = SDLK_BACKSLASH;

    binds["capslock"] = SDLK_CAPSLOCK;
    binds["a"] = SDLK_a;
    binds["s"] = SDLK_s;
    binds["d"] = SDLK_d;
    binds["f"] = SDLK_f;
    binds["g"] = SDLK_g;
    binds["h"] = SDLK_h;
    binds["j"] = SDLK_j;
    binds["k"] = SDLK_k;
    binds["l"] = SDLK_l;
    binds[";"] = SDLK_SEMICOLON;
    binds["'"] = SDLK_QUOTE;
    binds["return"] = SDLK_RETURN;

    binds["l_shift"] = SDLK_LSHIFT;
    binds["z"] = SDLK_z;
    binds["x"] = SDLK_x;
    binds["c"] = SDLK_c;
    binds["v"] = SDLK_v;
    binds["b"] = SDLK_b;
    binds["n"] = SDLK_n;
    binds["m"] = SDLK_m;
    binds[","] = SDLK_COMMA;
    binds["."] = SDLK_PERIOD;
    binds["/"] = SDLK_SLASH;
    binds["r_shift"] = SDLK_RSHIFT;

    binds["l_ctrl"] = SDLK_LCTRL;
    binds["l_alt"] = SDLK_LALT;
    binds["space"] = SDLK_SPACE;
    binds["r_alt"] = SDLK_RALT;
    binds["r_ctrl"] = SDLK_RCTRL;
    binds["up"] = SDLK_UP;
    binds["down"] = SDLK_DOWN;
    binds["left"] = SDLK_LEFT;
    binds["right"] = SDLK_RIGHT;

    return binds;
}();

bool SDLGraphicsProgram::pressed(std::string key){
    static std::map<int, bool> pressed;

    // from https://stackoverflow.com/questions/11699183/what-is-the-best-way-to-read-input-from-keyboard-using-sdl
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

// draws a line from point a to point b
void SDLGraphicsProgram::DrawLine(std::pair<int, int> a, std::pair<int, int> b) {
    SDL_RenderDrawLine(gRenderer, a.first, a.second, b.first, b.second);
}
// draws a list of line
void SDLGraphicsProgram::DrawLines(std::vector<std::pair<int, int>> points, bool closed) {
    for (auto iter = points.begin(); iter < points.end(); iter++) {
        if (iter + 1 == points.end() && closed) {
            DrawLine(*iter, *(points.begin()));
        } else {
            DrawLine(*iter, *(iter + 1));
        }
    }
}
// returns if the given lines (determines by end points of (a,b) and (c,d)) are intersecting
bool SDLGraphicsProgram::LineIntersect(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c, std::pair<int, int> d) {
  float denominator = ((b.first - a.first) * (d.second - c.second)) - ((b.second - a.second) * (d.first - c.first));
  float numerator1 = ((a.second - c.second) * (d.first - c.first)) - ((a.first - c.first) * (d.second - c.second));
  float numerator2 = ((a.second - c.second) * (b.first - a.first)) - ((a.first - c.first) * (b.second - a.second));

  // Detects parallel lines
  if (denominator == 0) {
    // detects coincident lines (parallel and technically the same line) possibly wrong?
    if (numerator1 == 0 && numerator2 == 0) {
      // check if either a.first or b.first are in the bounds of [c.first, d.first]
      int line2LowerX = std::min(c.first, d.first);
      int line2UpperX = std::max(c.first, d.first);
      bool xOverlap = (line2LowerX <= a.first && a.first <= line2UpperX) || (line2LowerX <= b.first && b.first <= line2UpperX);

      int line2LowerY = std::min(c.second, d.second);
      int line2UpperY = std::max(c.second, d.second);
      bool yOverlap = (line2LowerY <= a.second && a.second <= line2UpperY) || (line2LowerY <= b.second && b.second <= line2UpperY);

      return xOverlap && yOverlap;
    }
    return false;
  }

  float r = numerator1 / denominator;
  float s = numerator2 / denominator;

  return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

bool SDLGraphicsProgram::ShapeIntersect(std::vector<std::pair<int, int>> a, std::vector<std::pair<int, int>> b) {
  // TODO loop through both sets of lines points and check for any intersections
  return false;
}


// Include the pybindings
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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
            .def("flip", &SDLGraphicsProgram::flip)
            .def("delay", &SDLGraphicsProgram::delay)
            .def("pressed", &SDLGraphicsProgram::pressed)
            .def("DrawRectangle", &SDLGraphicsProgram::DrawRectangle)
            .def("DrawImage", &SDLGraphicsProgram::DrawImage)
            .def("DrawFrame", &SDLGraphicsProgram::DrawFrame)
            .def("SetColor", &SDLGraphicsProgram::SetColor)
            .def("PlayMusic", &SDLGraphicsProgram::PlayMusic)
            .def("PlaySFX", &SDLGraphicsProgram::PlaySFX)
            .def("ToggleMusic", &SDLGraphicsProgram::ToggleMusic)
            .def("SetMusicVolume", &SDLGraphicsProgram::SetMusicVolume)
            .def("GetMusicVolume", &SDLGraphicsProgram::GetMusicVolume)
            .def("RenderText", &SDLGraphicsProgram::RenderText)
            .def("RenderCenteredText", &SDLGraphicsProgram::RenderCenteredText)
            .def("FrameRateDelay", &SDLGraphicsProgram::ApplyFrameCap)
            .def("SetFramerate", &SDLGraphicsProgram::SetFramerate)
            .def("RectIntersect", &SDLGraphicsProgram::RectIntersect)
            .def("SetTextColor", &SDLGraphicsProgram::SetTextColor)
            .def("DrawLine", &SDLGraphicsProgram::DrawLine)
            .def("DrawLines", &SDLGraphicsProgram::DrawLines)
            .def("LineIntersect", &SDLGraphicsProgram::LineIntersect)
            .def("ShapeIntersect", &SDLGraphicsProgram::ShapeIntersect)
            .def("SetBackgroundColor", &SDLGraphicsProgram::SetBackgroundColor)
    ;
// We do not need to expose everything to our users!
//            .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow, py::return_value_policy::reference)
}

#endif
