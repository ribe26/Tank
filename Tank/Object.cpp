#include "Object.h"
#include "Component.h"
#include "Game.h"
#include "Sprite_component.h"


#include <iostream>

Object::Object(Game* in_game)
	:state(Active)
		,owner_game(in_game)
{
	owner_game->add_object(this);
}


Object::~Object() {
	owner_game->remove_object(this);
	while (!obj_components.empty()) {
		delete obj_components.back();
	}
}


void Object::update(float deltatime){}
void Object::input() {}

void Object::addComponent(Component* component) {
	//delete later
	std::cout << "component added\n";
	int order = component->get_update_order();
	auto iter = obj_components.begin();
	for (; iter != obj_components.end(); ++iter) {
		if (order < (*iter)->get_update_order()) {
			break;
		}
	}
	obj_components.insert(iter, component);
}


void Object::removeComponent(Component* component) {
	//delete later
	std::cout << "component deleted\n";
	auto iter = std::find(obj_components.begin(), obj_components.end(), component);
	if (iter != obj_components.end()) {
		obj_components.erase(iter);
	}
}

