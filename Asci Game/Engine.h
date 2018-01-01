#pragma once
#include <iostream>
#include "List.h"
#include "Actor.h"

class AsciiEngine {
public:
	void AppendToActors(Actor* newActor);
private:
	Actors m_AllActors;
};

void AsciiEngine::AppendToActors(Actor* newActor) {
	struct s_node* node;
	node = (struct s_node*)(malloc(sizeof(struct s_node));
	node->thisActor = newActor;
	node->next = m_AllActors.head;

}

enum Direction{RIGHT, UP, LEFT, DOWN, NONE};

struct s_Collision {
	Direction Direction;
	Actor* Instigator;
};








