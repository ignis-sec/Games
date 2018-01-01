#pragma once
#include "List.h"
#include "Engine.h"

class Actor {
public:

	Actor(int x, int y, wchar_t tag, Direction Direction);

	virtual void ActorTick() {};
	virtual Collision checkCollision();
	virtual void OnCollision() {};

	int SetPosition(int x, int y);
	int AddPosition(int dx, int dy);
	void SetDirection(Direction D) { m_Direction = D; }

	Direction GetDirection() { return m_Direction; }
	position GetPosition() { return m_position; }
	wchar_t GetTag() { return m_tag; }
	
private:
	struct s_position m_position;
	wchar_t m_tag;
	Direction m_Direction;
};

/////////////////////////
Actor::Actor(int x, int y, wchar_t tag, Direction Direction)
{
	SetPosition(x, y);
	m_tag = tag;
	m_Direction = Direction;
}

/////////////////////////
Collision Actor::checkCollision()
{
	struct s_node* cur = g_AllActors.head; //create pointer to start to the list containing all actors
	Collision C;
	C.Instigator = NULL;
	C.Direction = LEFT;
	while (cur != NULL)	//traverse the list until the end
	{
		if (this->GetPosition().x == cur->thisActor->GetPosition().x		//for collision both current actor and node should have
			&& this->GetPosition().y == cur->thisActor->GetPosition().y		//same x,y and different adress pointer
			&& this != cur->thisActor)
		{
			C.Instigator = cur->thisActor;		//set the other actor as collision instigator
			C.Direction = this->GetDirection();	//set collision direction
			OnCollision();						//do OnCollision actions if any
			return C;
		}
		cur = cur->next;	//to next node
	}
	return C;
}

/////////////////////////
int Actor::SetPosition(int x, int y)
{
	int tempx = m_position.x, tempy = m_position.y;
	m_position.x = x;
	m_position.y = y;
	Collision C = checkCollision();			//set position check collision
	return 0;

}

/////////////////////////
int Actor::AddPosition(int dx, int dy)
{
	int tempx = m_position.x, tempy = m_position.y;
	m_position.x += dx;
	m_position.y += dy;
	Collision C = checkCollision();
	if (C.Instigator != NULL)			//if movement causes collision push actor back
	{
		m_position.x = tempx;
		m_position.y = tempy;
	}
	return 0;

}
