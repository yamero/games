#include "Actor.h"

Actor::Actor(class Game* game)
	:game(game)
	,position(Vector2())
	,scale(1.0f)
	,rotation(0.0f)
{
	state = isActive;
	game->addActor(this); // 角色创建后自动加入到game的actors中
}

void Actor::update(float deltaTime)
{
	if (state == isActive)
	{
		updateComponents(deltaTime);
		updateActor(deltaTime);
	}
}

void Actor::updateComponents(float deltaTime)
{
	for (auto c : components)
	{
		c->update(deltaTime);
	}
}

void Actor::updateActor(float deltaTime)
{

}

void Actor::addComponent(Component* component)
{
	std::vector<Component*>::iterator iter = std::find(components.begin(), components.end(), component);
	if (iter == components.end())
	{
		components.emplace_back(component);
	}
}

void Actor::removeComponent(Component* component)
{
	std::vector<Component*>::iterator iter = std::find(components.begin(), components.end(), component);
	if (iter != components.end())
	{
		std::iter_swap(iter, components.end() - 1);
		components.pop_back();
	}
}

Actor::~Actor()
{
	game->removeActor(this);
}