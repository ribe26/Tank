#pragma once
#include <vector>

class Object
{
public:
	enum State{
		Active,
		Paused,
		Dead
	};
	Object(class Game* game);
	~Object();

	virtual void update(float deltatime);
	
	void addComponent(class Component* component);
	void removeComponent(class Component* component);

	virtual void input();
	
	class Game* get_game() { return owner_game; }

protected:
	State state;
	class Game* owner_game;
	std::vector<class Component*> obj_components;
};

