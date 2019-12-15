#pragma once

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void update(float deltaTime);
	int getUpdateOrder() const { return updateOrder; }
protected:
	class Actor* owner;
	int updateOrder;
};

