#pragma once
#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	~AnimSpriteComponent();
	void update(float deltaTime);
	void setAnimTexture(const std::vector<SDL_Texture*>& textures);
	float getAnimFps() const { return animFps; }
	void setAnimFps(float fps) { animFps = fps; }
private:
	std::vector<SDL_Texture*> animTextures;
	float currentFrame;
	float animFps;
};

