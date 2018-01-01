#pragma once
#include "Engine.h"


class Actor {
public:
	Actor(int x, int y);
	virtual void ActorTick() {};
	virtual void onCollision(s_Collision Collision) {};



	int SetPosition(int x, int y);
	int AddPosition(int dx, int dy);
	s_Collision isColliding();
private:
	int m_x, m_y;
};

Actor::Actor(int x, int y)
{
	SetPosition(x, y);
}

int Actor::SetPosition(int x, int y)
{
	int tempx = m_x, tempy = m_y;
	m_x = x;
	m_y = y;
	s_Collision C = isColliding();
	if (C.Instigator != NULL)
	{
		m_x = tempx;
		m_y = tempy;
		return 1;
	}
	return 0;

}

int Actor::AddPosition(int dx, int dy)
{
	int tempx = m_x, tempy = m_y;
	m_x += dx;
	m_y += dy;
	s_Collision C = isColliding();
	if (C.Instigator != NULL)
	{
		m_x = tempx;
		m_y = tempy;
		return 1;
	}
	return 0;

}