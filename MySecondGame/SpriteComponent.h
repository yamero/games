#pragma once
#include "Actor.h"
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void draw(SDL_Renderer* renderer); // 绘制当前帧纹理
	virtual void setTexture(SDL_Texture* texture); // 设置当前帧纹理
	int getDrawOrder() const { return drawOrder; }
	int getTextureWidth() const { return textureWidth; }
	int getTextureHeight() const { return textureHeight; }
protected:
	SDL_Texture* texture; // 当前精灵组件的纹理
	int drawOrder; // 当前精灵组件的绘制顺序
	int textureWidth;  // 纹理宽度
	int textureHeight; // 纹理高度
};

