#pragma once
#include <vector>
#include <unordered_map>
#include <SDL.h>

class Game
{
public:
	Game();
	bool Initialize();
	
	void load_data();

	void mainLoop();

	void event_input();
	void update();
	void draw_window();

    /*
	void shutdown();
	*/
	
	SDL_Texture* load_texture(std::string fileName);

	void remove_object(class Object* object);
	void add_object(class Object* object);


	void add_sprite(class Sprite_component* sprite);
	void remove_sprite(class Sprite_component* sprite);
private:
	
	Uint32 clock;
	
	bool running = false;
	class Tank* test;

	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;

	std::vector<class Object*> objects;
	std::vector<class Sprite_component*> sprites;

	std::unordered_map<std::string, SDL_Texture*> loaded_textures;
	/*

	class Tank* mytank;
	*/



};

