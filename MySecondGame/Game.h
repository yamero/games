#pragma once
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Math.h"
#include "Actor.h"
#include "SpriteComponent.h"
using namespace std;

class Game
{
public:
	Game();
	bool initiallize(); // ��Ϸ��ʼ��
	void runLoop(); // ��Ϸѭ��
	void shutdown(); // ��Ϸ������������Դ
	void addActor(class Actor* actor); // ��ӽ�ɫ
	void removeActor(class Actor* actor); // ɾ����ɫ
	void addSprite(class SpriteComponent* sprite); // ��Ӿ������
	void removeSprite(class SpriteComponent* sprite); // ɾ���������
	SDL_Texture* loadTexture(const std::string& fileName); // ��ͼƬ�ļ�����Ϊ����
private:
	void processInput(); // �����û�����
	void updateGame(); // ������Ϸ
	void generateOutput(); // ������Ϸ
	SDL_Window* mainWindow; // ������
	bool gameIsRunning; // ��Ϸ�Ƿ�������
	Uint32 ticksCount; // ��һ֡��ʱ������
	SDL_Renderer* mainRenderer; // ��Ⱦ��
	std::vector<class Actor*> actors; // ���ڻ��ƽ�ɫ����
	std::vector<class Actor*> pendingActors; // �����ƵĽ�ɫ����
	bool isUpdatingActors; // �Ƿ����ڸ��½�ɫ
	std::unordered_map<std::string, SDL_Texture*> loadedTextures; // �Ѽ��ص�������
	std::vector<class SpriteComponent*> sprites; // �����������
	void loadData(); // ��������
	void unloadData(); // ��������
	class Ship* ship; // ��ҿɲٿصķɴ�
};

