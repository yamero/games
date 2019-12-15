#include "Ship.h"
#include "AnimSpriteComponent.h"

Ship::Ship(Game* game)
	:Actor(game)
	,xSpeed(0.0f)
	,ySpeed(0.0f)
	,addSpeed(200.0f)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> ascTextures = {
		game->loadTexture("assets/Ship01.png"),
		game->loadTexture("assets/Ship02.png"),
		game->loadTexture("assets/Ship03.png"),
		game->loadTexture("assets/Ship04.png")
	};
	//asc->setAnimTexture(ascTextures);
	asc->setAnimations("shipFly", ascTextures);
}

void Ship::updateActor(float deltaTime)
{
	Actor::updateActor(deltaTime);
	Vector2 pos = getPosition();
	pos.x += xSpeed * deltaTime;
	pos.y += ySpeed * deltaTime;
	if (pos.x < 40.0f)
	{
		pos.x = 40.0f;
	}
	else if (pos.x > 600.0f)
	{
		pos.x = 600.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	setPosition(pos);
}

void Ship::processKeyboardInput(const Uint8* state)
{
	// ÿ����Ϸѭ�������ٶ���Ϊ0
	xSpeed = 0.0f;
	ySpeed = 0.0f;

	if (state[SDL_SCANCODE_A]) // �û�����A��
	{
		xSpeed += -addSpeed;
	}
	if (state[SDL_SCANCODE_D]) // �û�����S��
	{
		xSpeed += addSpeed;
	}
	if (state[SDL_SCANCODE_W]) // �û�����W��
	{
		ySpeed += -addSpeed;
	}
	if (state[SDL_SCANCODE_S]) // �û�����S��
	{
		ySpeed += addSpeed;
	}
}

Ship::~Ship()
{

}