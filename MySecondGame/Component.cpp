#include "Component.h"
#include "Actor.h"

Component::Component(class Actor* owner, int updateOrder)
	:owner(owner)
	, updateOrder(updateOrder)
{
	owner->addComponent(this);
}

void Component::update(float deltaTime)
{

}

Component::~Component()
{
	owner->removeComponent(this);
}