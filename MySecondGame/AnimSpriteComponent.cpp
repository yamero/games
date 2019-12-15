#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,animTextures(NULL)
	,currentFrame(0.0f)
	,animFps(0.0f)
{

}

void AnimSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);
	if (animTextures.size() > 0)
	{
		currentFrame += animFps * deltaTime;
		while (currentFrame >= animTextures.size())
		{
			currentFrame -= animTextures.size();
		}
		setTexture(animTextures[static_cast<int>(currentFrame)]);
	}
}

void AnimSpriteComponent::setAnimTexture(const std::vector<SDL_Texture*>& textures)
{
	animTextures = textures;
	if (animTextures.size() > 0)
	{
		currentFrame = 0.0f;
		setTexture(animTextures[0]);
	}
}

AnimSpriteComponent::~AnimSpriteComponent()
{

}