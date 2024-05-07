#include "Game.h"
#include "Object.h"
#include "Sprite_component.h"
#include "SDL_image.h"
#include "SDL.h"
#include <iostream>
#include "Tank.h"

Game::Game() 
	:mainWindow(nullptr)
	, mainRenderer(nullptr) 
{
}

bool Game::Initialize() {
	running = true;
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create an SDL Window
	mainWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mainWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	//// Create SDL renderer
	mainRenderer = SDL_CreateRenderer(
		mainWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mainRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	test = new Tank(this);
	//load_data();

	clock = SDL_GetTicks();

	return true;
}
void Game::load_data() {
	std::cout << "load data";

}


SDL_Texture* Game::load_texture(std::string fileName) {
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = loaded_textures.find(fileName);
	if (iter != loaded_textures.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		SDL_SetColorKey(surf,true ,SDL_MapRGB(surf->format, 255, 255, 255));
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}
		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mainRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		loaded_textures.emplace(fileName.c_str(), tex);
	}
	return tex;
}


void Game::mainLoop() {
	while (running) {
		event_input();
		update();
		draw_window();
	}
}


void Game::draw_window() {
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mainRenderer);

	// Draw all sprite components
	for (auto sprite : sprites)
	{
		sprite->draw(mainRenderer);
	}

	SDL_RenderPresent(mainRenderer);
}


void Game::event_input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		}

	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		running = false;
	}

	test->input();
}

void Game::update() {
	float deltatime = (SDL_GetTicks() - clock) / 1000.0f;
	clock = SDL_GetTicks();
	test->update(deltatime);
}

/*

void Game::shutdown() {
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}

*/

void Game::add_sprite(Sprite_component* sprite) {
	std::cout << ("sprite added!\n");
	int draw_order = sprite->get_draw_order();
	auto iter = sprites.begin();
	for (; iter !=sprites.end(); ++iter) {
		if (draw_order < (*iter)->get_draw_order()) {
			break;
		}
	}
	sprites.insert(iter, sprite);

}


void Game::remove_sprite(Sprite_component* sprite) {
	auto iter = std::find(sprites.begin(), sprites.end(), sprite);
		sprites.erase(iter);

}


void Game::add_object(Object* object) {
	//delete later
	std::cout << "object added!\n";
	objects.emplace_back(object);
}


void Game::remove_object(Object* object) {
	auto iter = std::find(objects.begin(), objects.end(), object);
	if (iter != objects.end()) {
		std::iter_swap(iter, objects.end() - 1);
		objects.pop_back();
	}
}

