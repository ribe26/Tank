#pragma once
#include "Component.h"
#include "SDL.h"

class Sprite_component : public Component
{
public:
	Sprite_component(class Object* owner, int order);
	~Sprite_component();

	virtual void draw(SDL_Renderer* rederer);
	virtual void setTexture(SDL_Texture* texture);

	int get_draw_order() {return draw_order;}

	void set_x(float move) { x = move; }
	void set_y(float move) { y = move; }
	void set_rotation(float move) { rotation = move; }
	void set_scale(float move) { scale = move; }
	float get_scale() { return scale; }
	float get_x() { return x; }
	float get_y() { return y; }
	float get_rotation() { return rotation; }


protected:
	SDL_Texture* texture;
	float x;
	float y;
	float scale;
	float rotation;
	int draw_order;
	int texture_width;
	int texture_height;
	
};

