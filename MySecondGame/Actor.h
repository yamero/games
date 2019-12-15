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
	void updateComponents(float deltaTime); // �������
	virtual void updateActor(float deltaTime); // ���½�ɫ
	void addComponent(class Component* component); // ������
	void removeComponent(class Component* component); // ɾ�����
	eState getState() const { return state; };
	float getScale() const { return scale; }
	void setScale(const float s) { scale = s; }
	void setPosition(const Vector2& pos) { position = pos; }
	Vector2 getPosition() const { return position; }
	float getRotation() const { return rotation; }
	Game* getGame() { return game; }
private:
	eState state;
	Vector2 position; // ��ɫ����λ��
	float scale; // ��ɫͳһ���ţ�1.0f ~ 100.0f %��
	float rotation; // ��ת�Ƕ�
	std::vector<class Component*> components; // ���ɫ�������������
	class Game* game;
};

