#pragma once
#include <vector>
#include "Math.h"
#include "Game.h"
#include "Component.h"
using namespace std;

class Actor
{
public:
	enum eState
	{
		isActive,
		isPaused,
		isDead
	};
	Actor(class Game* game);
	virtual ~Actor();
	
	void update(float deltaTime);
	void updateComponents(float deltaTime); // 更新组件
	virtual void updateActor(float deltaTime); // 更新角色
	void addComponent(class Component* component); // 添加组件
	void removeComponent(class Component* component); // 删除组件
	eState getState() const { return state; };
	float getScale() const { return scale; }
	void setScale(const float s) { scale = s; }
	void setPosition(const Vector2& pos) { position = pos; }
	Vector2 getPosition() const { return position; }
	float getRotation() const { return rotation; }
	Game* getGame() { return game; }
private:
	eState state;
	Vector2 position; // 角色中心位置
	float scale; // 角色统一缩放（1.0f ~ 100.0f %）
	float rotation; // 旋转角度
	std::vector<class Component*> components; // 与角色关联的组件集合
	class Game* game;
};

