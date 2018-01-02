
#define BACKGROUND NULL
int nScreenWidth = 120;
int nScreenHeight = 30;

#include "Engine.h"
#include <Windows.h>
#include "LevelLoader.h"



int main()
{

	nScreenWidth = 120;
	nScreenHeight = 40;
	
	while (1)
	{
		AsciiEngine Engine(nScreenWidth, nScreenHeight);
		g_Engine = &Engine;
		LoadLevel(&Engine);
		Engine.StartGame();
		std::cout << "GAME OVER...\n";
		Sleep(1000);
	}

	return 0;
}

