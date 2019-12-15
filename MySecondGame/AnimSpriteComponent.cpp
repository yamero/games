#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,animations(NULL)
{

}

void AnimSpriteComponent::setAnimationActive(const std::string name, const bool isActive)
{
	auto iter = animations.find(name);
	if (iter != animations.end())
	{
		(*iter).second.isActive = isActive;
	}
}

void AnimSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);

	for (auto& anim : animations)
	{
		if (anim.second.isActive && anim.second.textures.size() > 0)
		{
			anim.second.currentFrame += anim.second.animFps * deltaTime;
			while (anim.second.currentFrame >= anim.second.textures.size())
			{
				anim.second.currentFrame -= anim.second.textures.size();
			}
			anim.second.currentTexture = anim.second.textures[static_cast<int>(anim.second.currentFrame)];
			SDL_QueryTexture(anim.second.currentTexture, nullptr, nullptr, &anim.second.textureWidth, &anim.second.textureHeight);
		}
	}
}

void AnimSpriteComponent::draw(SDL_Renderer* renderer)
{
	for (auto anim : animations)
	{
		if (anim.second.isActive)
		{
			SDL_Rect r;
			r.w = static_cast<int>(anim.second.textureWidth * owner->getScale());
			r.h = static_cast<int>(anim.second.textureHeight * owner->getScale());
			r.x = static_cast<int>(owner->getPosition().x - r.w / 2);
			r.y = static_cast<int>(owner->getPosition().y - r.h / 2);
			SDL_RenderCopyEx(renderer, anim.second.currentTexture, nullptr, &r, -Math::ToDegrees(owner->getRotation()), nullptr, SDL_FLIP_NONE);
		}
	}
}

void AnimSpriteComponent::setAnimations(const std::string name, const std::vector<SDL_Texture*>& textures, const bool isActive)
{
	for (auto t : textures)
	{
		Animation temp;
		temp.isActive = isActive;
		temp.textures = textures;
		temp.currentFrame = 0.0f;
		temp.animFps = 24.0f;
		animations.emplace(name.c_str(), temp);
	}
}

AnimSpriteComponent::~AnimSpriteComponent()
{

}