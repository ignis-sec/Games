
#define BACKGROUND NULL
int nScreenWidth = 120;
int nScreenHeight = 30;

#include "Engine.h"
#include <Windows.h>
#include "LevelLoader.h"

void GameLoop();
void MusicThreadEntry();

int main()
{

	nScreenWidth = 120;
	nScreenHeight = 30;

	std::thread Game(GameLoop);
	std::thread MusicBox(MusicThreadEntry);

	

	Game.join();
	MusicBox.join();
	return 0;
}

void GameLoop()
{
	while (1)
	{
		AsciiEngine Engine(nScreenWidth, nScreenHeight);
		g_Engine = &Engine;
		LoadLevel(&Engine);

		Engine.StartGame();
		std::cout << "GAME OVER...\n";
		Sleep(1000);
	}
}
void MusicThreadEntry() {
	while(1)
	PlaySound(TEXT("music.wav"), NULL, SND_FILENAME);
}