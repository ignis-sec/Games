
#define BACKGROUND NULL
#include "Engine.h"
#include <Windows.h>
#include "LevelLoader.h"

int main()
{
	int nScreenWidth = 120;
	int nScreenHeight = 30;
	
	
	while (1)
	{
		AsciiEngine Engine(nScreenWidth, nScreenHeight);
		LoadLevel(&Engine);
		Engine.StartGame();
		std::cout << "GAME OVER...\n";
		Sleep(1000);
	}

	return 0;
}

