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
		bool isActive; // �Ƿ���Ҫ���ºͻ���
		float currentFrame; // ��ǰ֡
		SDL_Texture* currentTexture; // ��ǰ֡Ҫ���Ƶ�����
		float animFps; // ����֡����
		int textureWidth; // ��ǰ֡Ҫ���Ƶ�����Ŀ��
		int textureHeight; // ��ǰ֡Ҫ���Ƶ�����ĸ߶�
		std::vector<SDL_Texture*> textures; // ��������������
	};
	std::unordered_map<std::string, Animation> animations;
};

