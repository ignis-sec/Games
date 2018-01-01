#pragma once
#include "Engine.h"

struct s_position {
	int x;
	int y;
};

class Actor {
public:

	Actor(int x, int y)
	{
		SetPosition(x, y);
	}
	virtual void ActorTick() {};
	virtual void onCollision() {};
	
	struct s_position GetPosition() { return m_position; }
	char GetTag() { return m_tag; }

	int SetPosition(int x, int y);
	int AddPosition(int dx, int dy);
	
private:
	struct s_position m_position;
	char m_tag;
};


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