#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	bool gameInitRet = game.initiallize(); // 游戏初始化
	if (gameInitRet)
	{
		game.runLoop(); // 游戏初始化成功，进入游戏循环
	}
	game.shutdown();
	return 0;
}