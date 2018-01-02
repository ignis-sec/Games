
#include "Engine.h"
#include <Windows.h>
#include "ActorVariants.h"
#include "LevelLoader.h"

int main()
{
	SetConsoleTitle("Ascii Engine");
	int nScreenWidth = 120;
	int nScreenHeight = 30;
	AsciiEngine Engine(nScreenWidth, nScreenHeight);
	LoadLevel(&Engine);
	Engine.StartGame();
	return 0;
}

