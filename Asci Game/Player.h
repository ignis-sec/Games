#pragma once
#include "Engine.h"

class Player : public Actor {
public:
	bool bKeyRight = FALSE, bKeyLeft = FALSE, bKeyDown = FALSE, bKeyUp=FALSE;
	Player(int x, int y, wchar_t tag, int delay, Direction Direction, WORD Attribute) : Actor(x, y, tag, delay, Direction, Attribute,FALSE) { g_HP = getHP(); ThisPlayer = this; } //inherits constructor from Actor base class
	void ActorTick() {
		if (ShouldItTick())
		{
			bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;
			bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;
			bKeyUp = (0x8000 & GetAsyncKeyState((unsigned char)('\x26'))) != 0;
			bKeyDown = (0x8000 & GetAsyncKeyState((unsigned char)('\x28'))) != 0;
			if (!(getLife() % getNFrames()*2))
			{
				if (bKeyUp) {
					SetDirection(UP); AddPosition(0, -1);
				}
				if (bKeyDown) {
					SetDirection(DOWN);
					AddPosition(0, 1);
				}
			}
			if (bKeyRight) {
				SetDirection(RIGHT);
				AddPosition(1, 0);
			}
			if (bKeyLeft) {
				SetDirection(LEFT);
				AddPosition(-1, 0);
			}
			incrementLife();
			incrementFNH();
			if (GetPosition().y < 0) SetPosition(GetPosition().x, 0);
			switch (getFramesNotHit())
			{
			case 0:setAttribute(0x0B | BACKGROUND_RED | BACKGROUND_INTENSITY);
				break;
			case 5:setAttribute(0x0B | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				break;
			case 10:setAttribute(0x0B | BACKGROUND_RED | BACKGROUND_INTENSITY);
				break;
			case 15:setAttribute(0x0B | BACKGROUND);
				break;
			case 20:setAttribute(0x0B | BACKGROUND_RED | BACKGROUND_INTENSITY);
				break;
			case 25:setAttribute(0x0B | BACKGROUND);
			}
		}
	}

	void OnCollision(Collision C) {
		if (getFramesNotHit() > 25)
		{
			if (
				C.Instigator->GetTag() != L'#' &&
				C.Instigator->GetTag() != L'T' &&
				C.Instigator->GetTag() != L'ǒ'
				) { decreaseHP(); }

			if (C.Instigator->isMobile())
			{
				Collision D;
				D.Instigator = this;
				D.Direction = GetDirection();
				C.Instigator->OnCollision(D);
			}
		}

	}

	int getHP() { return m_hp; }
	void decreaseHP() { m_hp--; g_HP = getHP(); resetFramesNotHit(); }
	void resetFramesNotHit() { m_framesNotHit = 0; }
	int getFramesNotHit() { return m_framesNotHit; }
	void incrementFNH() { m_framesNotHit++; }
private:
	int m_hp = 3;
	int m_framesNotHit = 30;
};

