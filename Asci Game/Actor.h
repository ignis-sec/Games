#pragma once
#include "Engine.h"

struct s_position {
	int x;
	int y;
};

enum Direction { RIGHT, UP, LEFT, DOWN, NONE };

class Actor;

struct s_Collision {
	Direction Direction;
	Actor* Instigator;
};


class Actor {
public:

	Actor(int x, int y,wchar_t tag,Direction Direction)
	{
		SetPosition(x, y);
		m_tag = tag;
		m_Direction = Direction;
	}
	virtual void ActorTick() {};
	void checkCollision();
	virtual void onCollision() {};
	
	struct s_position GetPosition() { return m_position; }
	wchar_t GetTag() { return m_tag; }

	int SetPosition(int x, int y);
	int AddPosition(int dx, int dy);

	void SetDirection(Direction D) { m_Direction = D; }
	Direction GetDirection() { return m_Direction; }
	
private:
	struct s_position m_position;
	wchar_t m_tag;
	Direction m_Direction;
};

void Actor::checkCollision()
{

}

int Actor::SetPosition(int x, int y)
{
	int tempx = m_position.x, tempy = m_position.y;
	m_position.x = x;
	m_position.y = y;
	return 0;

}

int Actor::AddPosition(int dx, int dy)
{
	int tempx = m_position.x, tempy = m_position.y;
	m_position.x += dx;
	m_position.y += dy;
	return 0;

}

/*
Collision AsciiEngine::isColliding(Actor* Actor)
{
	Collision C;
	C.Instigator = NULL;

	struct s_node* cur = m_AllActors.head;
	while (cur != NULL)
	{
		if (cur->thisActor->GetPosition.x == Actor->GetPosition.x && cur->thisActor->GetPosition.x == Actor->GetPosition.x && cur->thisActor != Actor)

			cur = cur->next;
	}


	return C;
}*/