#pragma once

#include <iostream>
#include <Windows.h>
#include <thread>
#include "List.h"
#include "Actor.h"


#define  LPSTR          char*
#define  LPCSTR         const char*

#define  LPWSTR         wchar_t*
#define  LPWCSTR        const wchar_t*

#define  LPTSTR         TCHAR*
#define  LPCTSTR        const TCHAR* 

enum Direction { RIGHT, UP, LEFT, DOWN, NONE };



struct s_Collision
{
	Direction Direction;
	Actor* Instigator;
};

typedef struct s_Collision Collision;


typedef struct s_position position;

class AsciiEngine {
public:
	AsciiEngine(int nScreenWidth, int nScreenHeight);
	void AppendToActors(Actor* newActor);
	void DrawFrame();
	Collision isColliding(Actor* Actor);
	void ComposeFrame();
private:
	Actors m_AllActors;

	wchar_t *screen;
	HANDLE hConsole;
	DWORD dwBytesWritten;
	int m_nScreenWidth;
	int m_nScreenHeight;
};



AsciiEngine::AsciiEngine(int nScreenWidth, int nScreenHeight)
{
	//this creates screen Buffer
	screen = new wchar_t[nScreenWidth*nScreenHeight];
	for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	dwBytesWritten = 0;
	m_nScreenHeight = nScreenHeight;
	m_nScreenWidth = nScreenWidth;
	m_AllActors.head = m_AllActors.tail = NULL;

	//std::thread timer(Sleep, 100);
	//std::thread draw(DrawFrame);
	while (1)
	{
		ComposeFrame();
		DrawFrame();
		Sleep(100);
	}

}

Collision AsciiEngine::isColliding(Actor* Actor)
{
	Collision C;
	C.Direction = LEFT;
	C.Instigator = NULL;

	return C;
}

void AsciiEngine::DrawFrame()
{
	WriteConsoleOutputCharacterW(hConsole, screen, m_nScreenWidth * m_nScreenHeight, { 0,0 }, &dwBytesWritten);
}

void AsciiEngine::ComposeFrame()
{
	struct s_node* cur = m_AllActors.head;
	while (cur != NULL)
	{
		screen[cur->thisActor->GetPosition().x + cur->thisActor->GetPosition().y*m_nScreenWidth] = cur->thisActor->GetTag();
	}
}

void AsciiEngine::AppendToActors(Actor* newActor) {
	struct s_node* node;
	node = (struct s_node*)malloc(sizeof(struct s_node));
	node->thisActor = newActor;
	if (m_AllActors.head == NULL) {
		m_AllActors.head = m_AllActors.tail = node;
		return;
	}
	node->next = m_AllActors.head;
}










