#pragma once
#include "Actor.h"
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void draw(SDL_Renderer* renderer); // ���Ƶ�ǰ֡����
	virtual void setTexture(SDL_Texture* texture); // ���õ�ǰ֡����
	int getDrawOrder() const { return drawOrder; }
	int getTextureWidth() const { return textureWidth; }
	int getTextureHeight() const { return textureHeight; }
protected:
	SDL_Texture* texture; // ��ǰ�������������
	int drawOrder; // ��ǰ��������Ļ���˳��
	int textureWidth;  // ������
	int textureHeight; // ����߶�
};

