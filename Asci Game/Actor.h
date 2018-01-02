#pragma once
#include "List.h"
#include "Engine.h"

class Actor {
public:

	Actor(int x, int y, wchar_t tag, int delay, Direction Direction, WORD Attribute, bool bPushable);

	virtual void ActorTick() {};
	virtual Collision checkCollision();
	virtual void OnCollision(Collision C) {};

	int SetPosition(int x, int y);
	int AddPosition(int dx, int dy);
	void SetDirection(Direction D) { m_Direction = D; }

	Direction GetDirection() { return m_Direction; }
	position GetPosition() { return m_position; }
	wchar_t GetTag() { return m_tag; }
	WORD GetAttribute() { return m_Attribute; }
	int getLife() { return m_life; }
	void incrementLife() { m_life++; }
	int getNFrames() { return m_nFrames; }
	bool ShouldItTick() { incrementLife(); return !(m_life%m_nFrames); }
	void setAttribute(WORD ATT) { m_Attribute = ATT; }
	void illShowMyselfOut();
	void CheckBoundaries();
	bool isMobile() { return bMobile; }
private:
	int m_life;
	int m_nFrames;
	struct s_position m_position;
	wchar_t m_tag;
	Direction m_Direction;
	WORD m_Attribute;
	bool bMobile = FALSE;

};

/////////////////////////
Actor::Actor(int x, int y, wchar_t tag,int delay, Direction Direction, WORD Attribute,bool bPushable)
{
	SetPosition(x, y);
	m_tag = tag;
	m_Direction = Direction;
	m_Attribute = Attribute;
	m_life = 0;
	m_nFrames = delay;
	bMobile = bPushable;
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
			OnCollision(C);						//do OnCollision actions if any
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
	if (C.Instigator != NULL)
	{
		switch (C.Instigator->GetDirection()) {		//this actor moves 1 space to its direction every frame
		case LEFT:AddPosition(1, 0);
			break;
		case RIGHT:AddPosition(-1, 0);
			break;
		case UP:AddPosition(0, 1);
			break;
		case DOWN:AddPosition(0, -1);
			break;
		}
	}
	CheckBoundaries();
	return 0;

}

/////////////////////////
int Actor::AddPosition(int dx, int dy)
{
	int tempx = m_position.x, tempy = m_position.y,tempx2,tempy2;
	m_position.x += dx;
	m_position.y += dy;
	Collision C = checkCollision();
	if (C.Instigator !=NULL && !C.Instigator->isMobile())			//if movement causes collision push actor back
	{
		SetPosition(tempx,tempy);
	}


	CheckBoundaries();
	return 0;

}

void Actor::illShowMyselfOut()
{
	struct s_node* prev = g_AllActors.head, *cur= g_AllActors.head->next;
	if (prev->thisActor == this)
	{
		g_AllActors.head = g_AllActors.head->next;
		//free(prev);
		return;
	}
	while (cur != NULL)
	{
		if (cur->thisActor == this)
		{
			prev->next = cur->next;
			//free(cur);
			return;
		}
		prev = prev->next;
		cur = cur->next;
	}
}
void Actor::CheckBoundaries()
{
	if (GetPosition().x <0 || GetPosition().y <0 || GetPosition().x >nScreenWidth-1 || GetPosition().y >nScreenHeight-1)
	{
		illShowMyselfOut();
	}

}
