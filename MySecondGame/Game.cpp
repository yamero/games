#include "Game.h"
#include "BGSpriteComponent.h"

const int windowWidth = 1024;
const int windowHeight = 768;

Game::Game()
	:mainWindow(nullptr)
	, gameIsRunning(true)
	, mainRenderer(nullptr)
	, ticksCount(0)
	,isUpdatingActors(false)
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
		SDL_Log("create window fail, %s", SDL_GetError());
		return false;
	}
	mainRenderer = SDL_CreateRenderer(mainWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // 创建渲染器，开启硬件加速和垂直同步
	if (!mainRenderer)
	{
		SDL_Log("create renderer fail, %s", SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) // 初始化SDL Image
	{
		SDL_Log("img initialize fail, %s", SDL_GetError());
		return false;
	}
	loadData();
	return true;
}

// 加载数据
void Game::loadData()
{
	Actor* bgActor = new Actor(this); // 创建背景角色（背景也可视作游戏的一个角色）
	bgActor->setPosition(Vector2(windowWidth / 2, windowHeight / 2)); // 设定角色初始位置（角色中心位置）

	BGSpriteComponent* bgSprite = new BGSpriteComponent(bgActor, 1); // 创建构成背景角色的背景精灵组件（每个游戏角色都由各种各样的组件构成）
	bgSprite->setScreenSize(Vector2(static_cast<float>(windowWidth), static_cast<float>(windowHeight))); // 设置可见区域大小
	bgSprite->setScrollSpeed(-100.0f); // 设置背景滚动速度
	std::vector<SDL_Texture*> bgTextures = {
		loadTexture("assets/Farback01.png"),
		loadTexture("assets/Farback02.png")
	};
	bgSprite->setBGTextures(bgTextures); // 设置背景纹理

	BGSpriteComponent* starsBGSprite = new BGSpriteComponent(bgActor, 2); // 创建构成背景角色的星星组件
	starsBGSprite->setScreenSize(Vector2(static_cast<float>(windowWidth), static_cast<float>(windowHeight)));
	starsBGSprite->setScrollSpeed(-100.0f);
	bgTextures = {
		loadTexture("assets/Stars.png"),
		loadTexture("assets/Stars.png")
	};
	starsBGSprite->setBGTextures(bgTextures);

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
}

// 更新游戏
void Game::updateGame()
{
	// 保证至少每16ms更新一次，避免在不同的CPU下更新速度不一致的问题
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	ticksCount = SDL_GetTicks();

	// 两帧时间间隔最多不超过50ms，如果两帧时间间隔过大，会造成游戏角色的移动距离过大，也就通常看到的游戏卡顿现象
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// 更新所有角色
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(deltaTime);
	}
	isUpdatingActors = false;

	// 将待更新角色移动到当前需要更新的角色集合中去
	for (auto pendingActor : pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// 删除已死亡的角色
	std::vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::isDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

// 绘制图形并输出
void Game::generateOutput()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 139, 139, 255); // 指定清除后台缓冲区时要使用的颜色
	SDL_RenderClear(mainRenderer); // 清除后台缓冲区

	// 开始绘制所有精灵组件
	for (auto sprite : sprites)
	{
		sprite->draw(mainRenderer);
	}

	SDL_RenderPresent(mainRenderer); // 互换前台缓冲区与后台缓冲区
}

// 加载并返回纹理
SDL_Texture* Game::loadTexture(const std::string& fileName)
{
	SDL_Texture* texture = nullptr;
	auto iter = loadedTextures.find(fileName);
	if (iter != loadedTextures.end())
	{
		texture = iter->second;
	}
	else
	{
		SDL_Surface* surface = IMG_Load(fileName.c_str());
		if (!surface) {
			SDL_Log("load img fail: %s", SDL_GetError());
			return nullptr;
		}
		texture = SDL_CreateTextureFromSurface(mainRenderer, surface);
		SDL_FreeSurface(surface);
		if (!texture)
		{
			SDL_Log("load img fail: %s", SDL_GetError());
			return nullptr;
		}
		loadedTextures.emplace(fileName.c_str(), texture);
	}
	return texture;
}

// 添加精灵
void Game::addSprite(SpriteComponent* sprite)
{
	int drawOrder = sprite->getDrawOrder();
	std::vector<SpriteComponent*>::iterator iter = sprites.begin();
	for ( ; iter != sprites.end(); ++iter)
	{
		if (drawOrder < (*iter)->getDrawOrder())
		{
			break;
		}
	}
	sprites.insert(iter, sprite);
}

// 删除精灵组件
void Game::removeSprite(SpriteComponent* sprite)
{
	// 这里不能使用交换方式删除，因为会打乱精灵的绘制顺序
	auto iter = std::find(sprites.begin(), sprites.end(), sprite);
	sprites.erase(iter);
}

// 添加角色
void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

// 删除角色
void Game::removeActor(Actor* actor)
{
	std::vector<Actor*>::iterator iter = std::find(pendingActors.begin(), pendingActors.end(), actor);
	if (iter != pendingActors.end())
	{
		std::iter_swap(iter, pendingActors.end() - 1);
		pendingActors.pop_back();
	}
	iter = std::find(actors.begin(), actors.end(), actor);
	if (iter != actors.end())
	{
		std::iter_swap(iter, actors.end() - 1);
		actors.pop_back();
	}
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

void Game::unloadData()
{
	while (!actors.empty())
	{
		delete actors.back();
	}
	for (auto t : loadedTextures)
	{
		SDL_DestroyTexture(t.second);
	}
	loadedTextures.clear();
}

void Game::shutdown()
{
	unloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}