#pragma once
#include "Object.h"
class Tank :public Object
{
public:
	Tank(class Game* game);
	//~Tank();

	void update(float deltatime) override;
	void input() override;


	float get_x() { return x; }
	float get_y() { return y; }
	float get_rotation() { return rotation; }
	float get_Vx() { return Vx; }
	float get_Vy() { return Vy; }
	float get_body_omega() { return head_omega; }
	float get_head_omega() { return head_omega; }

	void set_Vx(float move) { Vx = move; }
	void set_Vy(float move) { Vy = move; }
	void set_rotation(float move) { rotation = move; }
	void set_x(float move) { x = move; }
	void set_y(float move) { y = move; }
	void set_body_omega(float move) { body_omega = move; }
	void set_head_omega(float move) { head_omega = move; }

protected:
	class Sprite_component* body;
	class Sprite_component* head;
	float Vx;
	float Vy;
	float body_omega;
	float head_omega;
	float move_speed = 80.0f;
	float body_rot_speed = 90.0f;
	float head_rot_speed = 180.0f;
	float rotation;
	float x;
	float y;
};

