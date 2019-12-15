#pragma once
#include "SpriteComponent.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 100);
	~BGSpriteComponent();
	void update(float deltaTime); // 更新组件
	void draw(SDL_Renderer* renderer); // 绘制组件
	void setBGTextures(const std::vector<SDL_Texture*>& textures);
	void setScreenSize(const Vector2& size) { screenSize = size; }
	void setScrollSpeed(float speed) { scrollSpeed = speed; }
	float getScrollSpeed() const { return scrollSpeed; }
private:
	struct BGTexture
	{
		SDL_Texture* texture; // 纹理
		Vector2 offset; // 纹理的初始偏移量（不是中心，是左上角）
	};
	std::vector<BGTexture> BGTextures;
	Vector2 screenSize; // 可见区域大小
	float scrollSpeed; // 背景滚动速度
};

