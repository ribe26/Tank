#include "Sprite_component.h"
#include "Object.h"
#include "Game.h"
#include <iostream>

Sprite_component::Sprite_component(Object* in_owner, int in_order)
	:Component(in_owner)
	, texture(nullptr)
	, draw_order(in_order)
	, texture_width(0)
	,texture_height(0)
	, x(0.0f)
	, y(0.0f)
	, scale(1.0f)
	, rotation(0.0f)
{
	owner_obj->get_game()->add_sprite(this);
}


Sprite_component::~Sprite_component() {
	owner_obj->get_game()->remove_sprite(this);
}



void Sprite_component::draw(SDL_Renderer* renderer) {
	if (texture) {
		SDL_Rect rect;
		rect.w = static_cast<int>(texture_width * scale);
		rect.h = static_cast<int>(texture_height * scale);
		rect.x = static_cast<int>(x - rect.w / 2);
		rect.y = static_cast<int>(y - rect.h / 2);

		SDL_RenderCopyEx(renderer, texture, nullptr, &rect,
			-rotation, nullptr, SDL_FLIP_NONE);
	}
}

void Sprite_component::setTexture(SDL_Texture* in_texture){
	texture = in_texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);
}



