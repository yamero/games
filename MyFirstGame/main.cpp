#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	bool gameInitRet = game.initiallize(); // ��Ϸ��ʼ��
	if (gameInitRet)
	{
		game.runLoop(); // ��Ϸ��ʼ���ɹ���������Ϸѭ��
	}
	game.shutdown();
	return 0;
}