
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
	/*S s1(15,0, L'S',RIGHT);
	Engine.AppendToActors(&s1);
	R r1(35, 0, L'#', RIGHT);
	Engine.AppendToActors(&r1);
	R r2(5, 0, L'#', RIGHT);
	Engine.AppendToActors(&r2);f
	*/
	Engine.StartGame();
	return 0;
}

