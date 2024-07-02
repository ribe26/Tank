#include "Tank.h"
#include "SDL.h"
#include "Game.h"
#include "Sprite_component.h"
#include <iostream>


Tank::Tank(Game* in_game)
	:Object(in_game)
	, Vx(0.0f)
	, Vy(0.0f)
	, head_omega(0.0f)
	,body_omega(0.0f)
	, x(100.0f)
	, y(100.0f)
	,rotation(0.0f)
{
	body = new Sprite_component(this, 10);
	body->setTexture(owner_game->load_texture("image/tank_body.png"));

	head = new Sprite_component(this, 11);
	head->setTexture(owner_game->load_texture("image/tank_head.png"));
	head->set_scale(1.2f);
}

/*
Tank::~Tank() {

}
*/

void Tank::update(float deltatime) {
	for (auto cmp : obj_components) {
		cmp->update(deltatime);
	}
	x = x + Vx * deltatime;
	y = y + Vy * deltatime;
	rotation = rotation + body_omega * deltatime;

	head->set_x(x);
	head->set_y(y);
	head->set_rotation(head->get_rotation()+head_omega*deltatime);

	body->set_x(x);
	body->set_y(y);
	body->set_rotation(rotation);
}

void Tank::input() {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	Vx = 0.0f;
	Vy = 0.0f;
	body_omega = 0.0f;
	head_omega = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		body_omega = -body_rot_speed;
		head_omega += -body_rot_speed;
	}
	if (state[SDL_SCANCODE_A])
	{
		body_omega = body_rot_speed;
		head_omega += body_rot_speed;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		Vx = -move_speed * cos(rotation * 3.1415f / 180.0f);
		Vy = -move_speed * sin(-rotation * 3.1415f / 180.0f);
	}
	if (state[SDL_SCANCODE_W])
	{
		Vx = move_speed * cos(rotation * 3.1415f / 180.0f);
		Vy = move_speed * sin(-rotation * 3.1415f / 180.0f);
	}
	int mouse_x;
	int mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	//–C“ƒ‚ÌŠp“x‚ð-ƒÎ~ƒÎ‚É•ÏŠ·
	if (abs(head->get_rotation()) >= 180.0f) {
		if (head->get_rotation() >= 0) {
			head->set_rotation(head->get_rotation() - 360.0f);
		}
		else {
			head->set_rotation(head->get_rotation() + 360.0f);
		}
	}

	//–C“ƒ‚ðƒ}ƒEƒX‚Ì•ûŒü‚ÉŒü‚¯‚é
	float mouse_rotation = atan2(-(mouse_y - y),mouse_x-x) / 3.141592f * 180.0f;
	float rot_diff = mouse_rotation - head->get_rotation();
	if (rot_diff >= 0) {
		if (abs(rot_diff) < 180.0f) {
			head_omega += head_rot_speed;
		}
		else {
			head_omega += -head_rot_speed;
		}
	}
	else {
		if (abs(rot_diff) < 180.0f) {
			head_omega += -head_rot_speed;
		}
		else {
			head_omega += head_rot_speed;
		}
	}

}
