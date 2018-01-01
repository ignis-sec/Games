#pragma once
#include "Engine.h"

class S :public Actor {
public:

	S(int x, int y, wchar_t tag, Direction Direction) : Actor(x, y, tag, Direction) { } //inherits constructor from Actor base class

	void ActorTick() {
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

	void OnCollision(){
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
	R(int x, int y, wchar_t tag, Direction Direction) : Actor(x, y, tag, Direction) { }
private:
	Direction m_Direction;
	wchar_t m_tag;
};