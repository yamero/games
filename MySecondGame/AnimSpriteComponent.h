#pragma once
#include "SpriteComponent.h"
#include <unordered_map>
#include <string>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	~AnimSpriteComponent();
	void update(float deltaTime);
	void draw(SDL_Renderer* renderer);
	void setAnimations(const std::string name, const std::vector<SDL_Texture*>& textures, const bool isActive = true);
	void setAnimationActive(const std::string name, const bool isActive);
private:
	struct Animation
	{
		bool isActive; // 是否需要更新和绘制
		float currentFrame; // 当前帧
		SDL_Texture* currentTexture; // 当前帧要绘制的纹理
		float animFps; // 动画帧速率
		int textureWidth; // 当前帧要绘制的纹理的宽度
		int textureHeight; // 当前帧要绘制的纹理的高度
		std::vector<SDL_Texture*> textures; // 动画包含的纹理
	};
	std::unordered_map<std::string, Animation> animations;
};

