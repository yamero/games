#include "Game.h"

const int windowWidth = 800;
const int windowHeight = 600;
const int thickness = 15; // ���ǽ�ĺ��
const int racketHeight = 100; // ���ĸ߶�

Game::Game()
	:mainWindow(nullptr)
	, gameIsRunning(true)
	,mainRenderer(nullptr)
	,ticksCount(0)
{
	
}

// ��ʼ��
bool Game::initiallize()
{
	int sdlInitRet = SDL_Init(SDL_INIT_VIDEO); // SDL��ʼ��
	if (sdlInitRet != 0)
	{
		SDL_Log("SDL initiallize fail, %s", SDL_GetError());
		return false;
	}
	mainWindow = SDL_CreateWindow("4399GameHaHa",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowWidth, windowHeight, SDL_WINDOW_SHOWN); // ��������
	if (!mainWindow)
	{
		return false;
	}
	mainRenderer = SDL_CreateRenderer(mainWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // ������Ⱦ��������Ӳ�����ٺʹ�ֱͬ��
	if (!mainRenderer)
	{
		return false;
	}
	ballPos.x = windowWidth / 2;
	ballPos.y = windowHeight / 2;
	topWallPos.x = windowWidth / 2;
	topWallPos.y = thickness / 2;
	rightWallPos.x = windowWidth - thickness / 2;
	rightWallPos.y = windowHeight / 2;
	bottomWallPos.x = windowWidth / 2;
	bottomWallPos.y = windowHeight - thickness / 2;
	racketPos.x = thickness / 2 + 10.0f;
	racketPos.y = windowHeight / 2;
	ballMoveSpeed.x = -200.0f;
	ballMoveSpeed.y = 235.0f;
	return true;
}

// �����û�����
void Game::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // ����������������Ͻǹرհ�ť
			gameIsRunning = false;
			break;
		default:
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) // �û�����Esc��
	{
		gameIsRunning = false;
	}
	if (state[SDL_SCANCODE_W]) // �û�����W��
	{
		racketMoveDirection = -1;
	}
	if (state[SDL_SCANCODE_S]) // �û�����S��
	{
		racketMoveDirection = 1;
	}
}

// ������Ϸ
void Game::updateGame()
{
	// ��֤����ÿ16�������һ�Σ������ڲ�ͬ��CPU�¸����ٶȲ�һ�µ�����
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	ticksCount = SDL_GetTicks();
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05;
	}

	if (racketMoveDirection != 0) // ����û�������W��S��
	{
		racketPos.y += racketMoveDirection * 300.0f * deltaTime; // ������300����/����ٶ��ƶ�
		if (racketPos.y <= racketHeight / 2.0f + thickness)
		{
			racketPos.y = racketHeight / 2.0f + thickness; // ���ĵ��ﶥ����ֹͣ�ƶ�
		}
		else if (racketPos.y >= windowHeight - racketHeight / 2.0f - thickness)
		{
			racketPos.y = windowHeight - racketHeight / 2.0f - thickness; // ���ĵ���ײ���ֹͣ�ƶ�
		}
	}

	// ��������
	ballPos.x += deltaTime * ballMoveSpeed.x;
	ballPos.y += deltaTime * ballMoveSpeed.y;

	// ������붥����ײ�ǽ�ڵ���ײ
	if (ballPos.y <= thickness && ballMoveSpeed.y < 0.0f || ballPos.y >= windowHeight - thickness && ballMoveSpeed.y > 0.0f)
	{
		ballMoveSpeed.y *= -1.0f; // ����������ǽ��ײ�ǽ����ת��Y�᷽����ٶ�
	}

	// ��������ұ�ǽ����ײ
	if (ballPos.x >= windowWidth - thickness - thickness / 2.0f && ballMoveSpeed.x > 0.0f)
	{
		ballMoveSpeed.x *= -1.0f; // �������ұ�ǽ����ת��X�᷽����ٶ�
	}

	// ����������ĵ���ײ
	float diff = ballPos.y - racketPos.y;
	diff = diff > 0.0f ? diff : -1.0f * diff;
	if (diff <= racketHeight / 2.0f && ballPos.x <= racketPos.x + thickness / 2.0f && ballMoveSpeed.x < 0.0f)
	{
		ballMoveSpeed.x *= -1.0f; // ���������ģ���ת��X�᷽����ٶ�
	}

	// �������û�д�����GameOver
	if (ballPos.x < 10.0f)
	{
		gameIsRunning = false;
	}
}

// ����ͼ�β����
void Game::generateOutput()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 139, 139, 255); // ָ�������̨������ʱҪʹ�õ���ɫ
	SDL_RenderClear(mainRenderer); // �����̨������

	// ������
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	SDL_Rect ballRect {
		static_cast<int>(ballPos.x - thickness / 2),
		static_cast<int>(ballPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mainRenderer, &ballRect);

	// �����ұ�ǽ
	SDL_Rect rightWallRect {
		static_cast<int>(rightWallPos.x - thickness / 2),
		static_cast<int>(rightWallPos.y - windowHeight / 2),
		thickness,
		windowHeight
	};
	SDL_RenderFillRect(mainRenderer, &rightWallRect);

	// ���ƶ���ǽ
	SDL_Rect topWallRect {
		0,
		0,
		windowWidth,
		thickness
	};
	SDL_RenderFillRect(mainRenderer, &topWallRect);

	// ���Ƶײ�ǽ
	SDL_Rect bottomWallRect {
		static_cast<int>(bottomWallPos.x - windowWidth / 2),
		static_cast<int>(bottomWallPos.y - thickness / 2),
		windowWidth,
		thickness
	};
	SDL_RenderFillRect(mainRenderer, &bottomWallRect);

	// ��������
	SDL_Rect racketRect {
		static_cast<int>(racketPos.x - thickness / 2),
		static_cast<int>(racketPos.y - racketHeight / 2),
		thickness,
		racketHeight
	};
	SDL_RenderFillRect(mainRenderer, &racketRect);

	SDL_RenderPresent(mainRenderer); // ����ǰ̨���������̨������
}

void Game::runLoop()
{
	while (gameIsRunning)
	{
		processInput();
		updateGame();
		generateOutput();
	}
}

void Game::shutdown()
{
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}