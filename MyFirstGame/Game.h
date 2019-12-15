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
	vector2 ballPos; // ������λ��
	vector2 topWallPos; // ����ǽ����λ��
	vector2 rightWallPos; // �ұ�ǽ����λ��
	vector2 bottomWallPos; // �ײ�ǽ����λ��
	vector2 racketPos; // ��������λ��
	int racketMoveDirection = 0; // �����ƶ�����0��ֹ -1�����ƶ� 1�����ƶ�
	vector2 ballMoveSpeed;
	Uint32 ticksCount;
};

