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
		SDL_Log("create window fail, %s", SDL_GetError());
		return false;
	}
	mainRenderer = SDL_CreateRenderer(mainWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // ������Ⱦ��������Ӳ�����ٺʹ�ֱͬ��
	if (!mainRenderer)
	{
		SDL_Log("create renderer fail, %s", SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) // ��ʼ��SDL Image
	{
		SDL_Log("img initialize fail, %s", SDL_GetError());
		return false;
	}
	loadData();
	return true;
}

// ��������
void Game::loadData()
{
	Actor* bgActor = new Actor(this); // ����������ɫ������Ҳ��������Ϸ��һ����ɫ��
	bgActor->setPosition(Vector2(windowWidth / 2, windowHeight / 2)); // �趨��ɫ��ʼλ�ã���ɫ����λ�ã�

	BGSpriteComponent* bgSprite = new BGSpriteComponent(bgActor, 1); // �������ɱ�����ɫ�ı������������ÿ����Ϸ��ɫ���ɸ��ָ�����������ɣ�
	bgSprite->setScreenSize(Vector2(static_cast<float>(windowWidth), static_cast<float>(windowHeight))); // ���ÿɼ������С
	bgSprite->setScrollSpeed(-100.0f); // ���ñ��������ٶ�
	std::vector<SDL_Texture*> bgTextures = {
		loadTexture("assets/Farback01.png"),
		loadTexture("assets/Farback02.png")
	};
	bgSprite->setBGTextures(bgTextures); // ���ñ�������

	BGSpriteComponent* starsBGSprite = new BGSpriteComponent(bgActor, 2); // �������ɱ�����ɫ���������
	starsBGSprite->setScreenSize(Vector2(static_cast<float>(windowWidth), static_cast<float>(windowHeight)));
	starsBGSprite->setScrollSpeed(-100.0f);
	bgTextures = {
		loadTexture("assets/Stars.png"),
		loadTexture("assets/Stars.png")
	};
	starsBGSprite->setBGTextures(bgTextures);

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
}

// ������Ϸ
void Game::updateGame()
{
	// ��֤����ÿ16ms����һ�Σ������ڲ�ͬ��CPU�¸����ٶȲ�һ�µ�����
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	ticksCount = SDL_GetTicks();

	// ��֡ʱ������಻����50ms�������֡ʱ�������󣬻������Ϸ��ɫ���ƶ��������Ҳ��ͨ����������Ϸ��������
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// �������н�ɫ
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(deltaTime);
	}
	isUpdatingActors = false;

	// �������½�ɫ�ƶ�����ǰ��Ҫ���µĽ�ɫ������ȥ
	for (auto pendingActor : pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// ɾ���������Ľ�ɫ
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

// ����ͼ�β����
void Game::generateOutput()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 139, 139, 255); // ָ�������̨������ʱҪʹ�õ���ɫ
	SDL_RenderClear(mainRenderer); // �����̨������

	// ��ʼ�������о������
	for (auto sprite : sprites)
	{
		sprite->draw(mainRenderer);
	}

	SDL_RenderPresent(mainRenderer); // ����ǰ̨���������̨������
}

// ���ز���������
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

// ��Ӿ���
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

// ɾ���������
void Game::removeSprite(SpriteComponent* sprite)
{
	// ���ﲻ��ʹ�ý�����ʽɾ������Ϊ����Ҿ���Ļ���˳��
	auto iter = std::find(sprites.begin(), sprites.end(), sprite);
	sprites.erase(iter);
}

// ��ӽ�ɫ
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

// ɾ����ɫ
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