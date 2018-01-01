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






typedef struct s_Collision Collision;


typedef struct s_position position;

class AsciiEngine {
public:
	AsciiEngine(int nScreenWidth, int nScreenHeight);
	void AppendToActors(Actor* newActor);
	void DrawFrame();
	void ComposeFrame();
	void StartGame();
	void tick();
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


}
void AsciiEngine::StartGame() {
	while (1)
	{
		tick();
		ComposeFrame();
		DrawFrame();
		Sleep(100);
	}
}

void AsciiEngine::tick()
{
	struct s_node* cur = m_AllActors.head;
		while (cur != NULL)
	{
			cur->thisActor->ActorTick();

		cur = cur->next;
	}
}

void AsciiEngine::DrawFrame()
{
	WriteConsoleOutputCharacterW(hConsole, screen, m_nScreenWidth * m_nScreenHeight, { 0,0 }, &dwBytesWritten);
}

void AsciiEngine::ComposeFrame()
{
	struct s_node* cur = m_AllActors.head;
	for (int i = 0; i < m_nScreenWidth*m_nScreenHeight-1; i++) screen[i] =L' ';
	while (cur != NULL)
	{
		screen[cur->thisActor->GetPosition().x + cur->thisActor->GetPosition().y*m_nScreenWidth] = cur->thisActor->GetTag();
		
		cur = cur->next;
	}
}

void AsciiEngine::AppendToActors(Actor* newActor) {
	struct s_node* node;
	node = (struct s_node*)malloc(sizeof(struct s_node));
	node->thisActor = newActor;
	node->next = m_AllActors.head;
	m_AllActors.head = node;
}










