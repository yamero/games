#include "BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,BGTextures(NULL)
	,screenSize(Vector2())
	,scrollSpeed(0.0f)
{
	
}

void BGSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);
	for (auto& bg : BGTextures)
	{
		bg.offset.x += scrollSpeed * deltaTime;
		if (bg.offset.x < -screenSize.x)
		{
			bg.offset.x = (BGTextures.size() - 1) * screenSize.x - 1;
		}
	}
}

void BGSpriteComponent::draw(SDL_Renderer* renderer)
{
	for (auto& bg : BGTextures)
	{
		SDL_Rect r;
		r.w = static_cast<int>(screenSize.x);
		r.h = static_cast<int>(screenSize.y);
		r.x = static_cast<int>(owner->getPosition().x - r.w / 2 + bg.offset.x);
		r.y = static_cast<int>(owner->getPosition().y - r.h / 2 + bg.offset.y);
		SDL_RenderCopy(renderer, bg.texture, nullptr, &r);
	}
}

void BGSpriteComponent::setBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.texture = tex;
		temp.offset.x = count * screenSize.x;
		temp.offset.y = 0;
		BGTextures.emplace_back(temp);
		count++;
	}
}

BGSpriteComponent::~BGSpriteComponent()
{

}
