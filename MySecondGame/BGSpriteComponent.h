#pragma once
#include "SpriteComponent.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 100);
	~BGSpriteComponent();
	void update(float deltaTime); // �������
	void draw(SDL_Renderer* renderer); // �������
	void setBGTextures(const std::vector<SDL_Texture*>& textures);
	void setScreenSize(const Vector2& size) { screenSize = size; }
	void setScrollSpeed(float speed) { scrollSpeed = speed; }
	float getScrollSpeed() const { return scrollSpeed; }
private:
	struct BGTexture
	{
		SDL_Texture* texture; // ����
		Vector2 offset; // ����ĳ�ʼƫ�������������ģ������Ͻǣ�
	};
	std::vector<BGTexture> BGTextures;
	Vector2 screenSize; // �ɼ������С
	float scrollSpeed; // ���������ٶ�
};

