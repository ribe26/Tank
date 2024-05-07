#include "Component.h"
#include "Object.h"


Component::Component(class Object* in_owner,int in_order)
	:owner_obj(in_owner)
	,update_order(in_order)
{
	owner_obj->addComponent(this);
}

Component::~Component() {
	owner_obj->removeComponent(this);
}

void Component::update(float deltatime) {

}
