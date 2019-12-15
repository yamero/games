#include "Game.h"

const int windowWidth = 800;
const int windowHeight = 600;
const int thickness = 15; // 球和墙的厚度
const int racketHeight = 100; // 球拍高度

Game::Game()
	:mainWindow(nullptr)
	, gameIsRunning(true)
	,mainRenderer(nullptr)
	,ticksCount(0)
{
	
}

// 初始化
bool Game::initiallize()
{
	int sdlInitRet = SDL_Init(SDL_INIT_VIDEO); // SDL初始化
	if (sdlInitRet != 0)
	{
		SDL_Log("SDL initiallize fail, %s", SDL_GetError());
		return false;
	}
	mainWindow = SDL_CreateWindow("4399GameHaHa",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowWidth, windowHeight, SDL_WINDOW_SHOWN); // 创建窗口
	if (!mainWindow)
	{
		return false;
	}
	mainRenderer = SDL_CreateRenderer(mainWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // 创建渲染器，开启硬件加速和垂直同步
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

// 处理用户输入
void Game::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // 鼠标左键点击窗口右上角关闭按钮
			gameIsRunning = false;
			break;
		default:
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) // 用户按下Esc键
	{
		gameIsRunning = false;
	}
	if (state[SDL_SCANCODE_W]) // 用户按下W键
	{
		racketMoveDirection = -1;
	}
	if (state[SDL_SCANCODE_S]) // 用户按下S键
	{
		racketMoveDirection = 1;
	}
}

// 更新游戏
void Game::updateGame()
{
	// 保证至少每16毫秒更新一次，避免在不同的CPU下更新速度不一致的问题
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	ticksCount = SDL_GetTicks();
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05;
	}

	if (racketMoveDirection != 0) // 如果用户按下了W或S键
	{
		racketPos.y += racketMoveDirection * 300.0f * deltaTime; // 球拍以300像素/秒的速度移动
		if (racketPos.y <= racketHeight / 2.0f + thickness)
		{
			racketPos.y = racketHeight / 2.0f + thickness; // 球拍到达顶部，停止移动
		}
		else if (racketPos.y >= windowHeight - racketHeight / 2.0f - thickness)
		{
			racketPos.y = windowHeight - racketHeight / 2.0f - thickness; // 球拍到达底部，停止移动
		}
	}

	// 让球动起来
	ballPos.x += deltaTime * ballMoveSpeed.x;
	ballPos.y += deltaTime * ballMoveSpeed.y;

	// 检测球与顶部或底部墙壁的碰撞
	if (ballPos.y <= thickness && ballMoveSpeed.y < 0.0f || ballPos.y >= windowHeight - thickness && ballMoveSpeed.y > 0.0f)
	{
		ballMoveSpeed.y *= -1.0f; // 球碰到顶部墙或底部墙，逆转球Y轴方向的速度
	}

	// 检测球与右边墙的碰撞
	if (ballPos.x >= windowWidth - thickness - thickness / 2.0f && ballMoveSpeed.x > 0.0f)
	{
		ballMoveSpeed.x *= -1.0f; // 球碰到右边墙，逆转球X轴方向的速度
	}

	// 检测球与球拍的碰撞
	float diff = ballPos.y - racketPos.y;
	diff = diff > 0.0f ? diff : -1.0f * diff;
	if (diff <= racketHeight / 2.0f && ballPos.x <= racketPos.x + thickness / 2.0f && ballMoveSpeed.x < 0.0f)
	{
		ballMoveSpeed.x *= -1.0f; // 球碰到球拍，逆转球X轴方向的速度
	}

	// 如果球拍没有打到球，则GameOver
	if (ballPos.x < 10.0f)
	{
		gameIsRunning = false;
	}
}

// 绘制图形并输出
void Game::generateOutput()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 139, 139, 255); // 指定清除后台缓冲区时要使用的颜色
	SDL_RenderClear(mainRenderer); // 清除后台缓冲区

	// 绘制球
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
	SDL_Rect ballRect {
		static_cast<int>(ballPos.x - thickness / 2),
		static_cast<int>(ballPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mainRenderer, &ballRect);

	// 绘制右边墙
	SDL_Rect rightWallRect {
		static_cast<int>(rightWallPos.x - thickness / 2),
		static_cast<int>(rightWallPos.y - windowHeight / 2),
		thickness,
		windowHeight
	};
	SDL_RenderFillRect(mainRenderer, &rightWallRect);

	// 绘制顶部墙
	SDL_Rect topWallRect {
		0,
		0,
		windowWidth,
		thickness
	};
	SDL_RenderFillRect(mainRenderer, &topWallRect);

	// 绘制底部墙
	SDL_Rect bottomWallRect {
		static_cast<int>(bottomWallPos.x - windowWidth / 2),
		static_cast<int>(bottomWallPos.y - thickness / 2),
		windowWidth,
		thickness
	};
	SDL_RenderFillRect(mainRenderer, &bottomWallRect);

	// 绘制球拍
	SDL_Rect racketRect {
		static_cast<int>(racketPos.x - thickness / 2),
		static_cast<int>(racketPos.y - racketHeight / 2),
		thickness,
		racketHeight
	};
	SDL_RenderFillRect(mainRenderer, &racketRect);

	SDL_RenderPresent(mainRenderer); // 互换前台缓冲区与后台缓冲区
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