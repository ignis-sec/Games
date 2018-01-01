
#include "Engine.h"
#include <Windows.h>

class S :public Actor {
public:
	S(int x, int y,wchar_t tag,Direction Direction) : Actor(x, y, tag,Direction) { }
	void ActorTick() {
		switch (GetDirection()) {
		case LEFT:AddPosition(-1, 0);
			break;
		case RIGHT:AddPosition(1, 0);
			break;
		case UP:AddPosition(0, -1);
			break;
		case DOWN:AddPosition(0, 1);
			break;
		}
	}
private:
	Direction m_Direction;
	wchar_t m_tag;
};


int main()
{

	int nScreenWidth = 120;
	int nScreenHeight = 30;
	AsciiEngine Engine(nScreenWidth, nScreenHeight);
	
	S s1(15,0, L'S',DOWN);
	Engine.AppendToActors(&s1);
	Engine.StartGame();
	return 0;
}

