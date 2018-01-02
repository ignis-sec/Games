#pragma once
#include "Engine.h"

class S :public Actor {
public:

	S(int x, int y, wchar_t tag, int delay, Direction Direction, WORD Attribute) : Actor(x, y, tag,delay, Direction, Attribute) { } //inherits constructor from Actor base class

	void ActorTick() {
		if (ShouldItTick())
		{
			switch (GetDirection()) {		//this actor moves 1 space to its direction every frame
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
		
	}

	void OnCollision(Collision C){
		if (C.Instigator == (Actor*)ThisPlayer)
		{
			C.Instigator = this;		//if you hit player tell it you are the instigator and forward the collision struct
			ThisPlayer->OnCollision(C);
			return;
		}
		switch (GetDirection())		//if it collides with something it turns to the opposite direction
		{
		case RIGHT:		SetDirection(LEFT);
			break;
		case UP:		SetDirection(DOWN);
			break;
		case LEFT:		SetDirection(RIGHT);
			break;
		case DOWN:		SetDirection(UP);
			break;
		}
	}
};


class R :public Actor {		//this actor doesnt move, its just a boulder to collide with
public:
	R(int x, int y, wchar_t tag, int delay, Direction Direction, WORD Attribute) : Actor(x, y, tag,delay, Direction, Attribute) { }
private:
	Direction m_Direction;
	wchar_t m_tag;
};