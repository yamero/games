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
	bool initiallize();
	void runLoop();
	void shutdown();
	void addActor(class Actor* actor); // 添加角色
	void removeActor(class Actor* actor); // 删除角色
	void addSprite(class SpriteComponent* sprite); // 添加精灵组件
	void removeSprite(class SpriteComponent* sprite); // 删除精灵组件
private:
	void processInput();
	void updateGame();
	void generateOutput();
	SDL_Window* mainWindow; // 主窗口
	bool gameIsRunning; // 游戏是否在运行
	Uint32 ticksCount; // 上一帧的时间增量
	SDL_Renderer* mainRenderer; // 渲染器
	std::vector<class Actor*> actors; // 正在绘制角色集合
	std::vector<class Actor*> pendingActors; // 待绘制的角色集合
	bool isUpdatingActors; // 是否正在更新角色
	SDL_Texture* loadTexture(const std::string& fileName); // 将图片文件加载为纹理
	std::unordered_map<std::string, SDL_Texture*> loadedTextures; // 已加载的纹理集合
	std::vector<class SpriteComponent*> sprites; // 精灵组件集合
	void loadData();
	void unloadData();
};

