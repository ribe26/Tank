#pragma once
class Component
{
public:
	Component(class Object* in_owner,int in_order=100);
	virtual ~Component();
	virtual void update(float deltaTime);

	int get_update_order() { return update_order; }
protected:
	class Object* owner_obj;
	int update_order;
};

