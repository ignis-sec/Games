#pragma once

struct s_node {
	Actor* thisActor;
	struct s_node* next;
};

struct s_ActorList {
	struct s_node* head;
	struct s_node* tail;
};

typedef struct s_ActorList Actors;