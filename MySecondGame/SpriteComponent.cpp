#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder)
	:Component(owner)
	,texture(nullptr)
	,drawOrder(drawOrder)
	,textureWidth(0)
	,textureHeight(0)
{
	owner->getGame()->addSprite(this); // 组件创建后自动加入到game的sprites中
}

void SpriteComponent::draw(SDL_Renderer* renderer)
{
	if (texture)
	{
		SDL_Rect r;
		r.w = static_cast<int>(textureWidth * owner->getScale());
		r.h = static_cast<int>(textureHeight * owner->getScale());
		r.x = static_cast<int>(owner->getPosition().x - r.w / 2);
		r.y = static_cast<int>(owner->getPosition().y - r.h / 2);
		SDL_RenderCopyEx(renderer, texture, nullptr, &r, -Math::ToDegrees(owner->getRotation()), nullptr, SDL_FLIP_NONE);
	}
}

void SpriteComponent::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
}

SpriteComponent::~SpriteComponent()
{
	owner->getGame()->removeSprite(this);
}