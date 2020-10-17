#pragma once

#include<SDL.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

class Window
{
public:
	Window();
	// Delete the assignment and copy
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	// Initialization of the window called by the game class initialize() function
	bool initialize();
	// Closing of the window called by the game class close() function
	void close();

	// Getter to the SDL_Window pointer
	SDL_Window* getSDLWindow() const { return SDLWindow; }

	// Getters for the width and height of the window
	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	SDL_Window* SDLWindow;
	int width;
	int height;
};