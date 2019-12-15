#pragma once
#include "SDL.h"

struct vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	bool initiallize();
	void runLoop();
	void shutdown();
private:
	void processInput();
	void updateGame();
	void generateOutput();
	SDL_Window* mainWindow;
	bool gameIsRunning;
	SDL_Renderer* mainRenderer;
	vector2 ballPos; // 球中心位置
	vector2 topWallPos; // 顶部墙中心位置
	vector2 rightWallPos; // 右边墙中心位置
	vector2 bottomWallPos; // 底部墙中心位置
	vector2 racketPos; // 球拍中心位置
	int racketMoveDirection = 0; // 球拍移动方向，0静止 -1向上移动 1向下移动
	vector2 ballMoveSpeed;
	Uint32 ticksCount;
};

