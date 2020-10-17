#include"window.h"
#include"log.h"

// Constructor assign the default values
Window::Window() : 
	SDLWindow(nullptr), 
	width(WINDOW_WIDTH), 
	height(WINDOW_HEIGHT) {}

bool Window::initialize()
{
	// SDL function initializing the video subsystem because of the flag SDL_INIT_VIDEO
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	// If the initializing went wrong
	if (sdlInitResult)
	{
		// Log error
		Log::error(LogCategory::Video, "Unable to initialize SDL");
		return false;
	}
	// SDL function to create the window we specify the SDL_WINDOW_OPENGL to make it usable with opengl context
	SDLWindow = SDL_CreateWindow("2D Shooter", 100, 100, width, height, SDL_WINDOW_OPENGL);
	// If the initializing went wrong
	if (!SDLWindow)
	{
		// Log error
		Log::error(LogCategory::System, "Failed to create window");
		return false;
	}
	return true;
}

void Window::close()
{
	// SDL function to close the created window
	SDL_DestroyWindow(SDLWindow);
}