#pragma once
#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	~Ship();
	float getXSpeed() const { return xSpeed; }
	void setXSpeed(const float speed) { xSpeed = speed; }
	float getYSpeed() const { return ySpeed; }
	void setYSpeed(const float speed) { ySpeed = speed; }
	float getAddSpeed() const { return addSpeed; }
	void setAddSpeed(const float speed) { addSpeed = speed; }
	void updateActor(float deltaTime) override; // ���·ɴ�
	void processKeyboardInput(const Uint8* state); // ��Ӧ�����¼�
private:
	float xSpeed;
	float ySpeed;
	float addSpeed;
};

