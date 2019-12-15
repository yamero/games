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
	// 每次游戏循环，将速度设为0
	xSpeed = 0.0f;
	ySpeed = 0.0f;

	if (state[SDL_SCANCODE_A]) // 用户按下A键
	{
		xSpeed += -addSpeed;
	}
	if (state[SDL_SCANCODE_D]) // 用户按下S键
	{
		xSpeed += addSpeed;
	}
	if (state[SDL_SCANCODE_W]) // 用户按下W键
	{
		ySpeed += -addSpeed;
	}
	if (state[SDL_SCANCODE_S]) // 用户按下S键
	{
		ySpeed += addSpeed;
	}
}

Ship::~Ship()
{

}