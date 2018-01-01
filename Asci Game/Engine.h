#pragma once

#include <iostream>
#include <Windows.h>
#include <thread>
#include "List.h"

#define  LPSTR          char*						//just to be safe about CreateConsoleBuffer
#define  LPCSTR         const char*

#define  LPWSTR         wchar_t*
#define  LPWCSTR        const wchar_t*

#define  LPTSTR         TCHAR*
#define  LPCTSTR        const TCHAR* 

class Actor;

struct s_position {
	int x;
	int y;
};
typedef struct s_position position;

enum Direction { RIGHT=0, UP=1, LEFT=2, DOWN=3 };

struct s_Collision {
	Direction Direction;
	Actor* Instigator;
};
typedef struct s_Collision Collision;

/////////////////////
class AsciiEngine {
public:
	AsciiEngine(int nScreenWidth, int nScreenHeight);
	void AppendToActors(Actor* newActor);
	void DrawFrame();
	void ComposeFrame();
	void StartGame();
	void tick();
private:
	

	wchar_t *screen;
	HANDLE hConsole;
	DWORD dwBytesWritten;
	int m_nScreenWidth;
	int m_nScreenHeight;
};
 Actors g_AllActors;
 int frameDelay=100;
#include "Actor.h"

 /////////////////////
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
	g_AllActors.head = g_AllActors.tail = NULL;

}
/////////////////////
void AsciiEngine::StartGame() {
	while (1)			//basically game loop
	{
		tick();					//plays every actors ActorTick
		ComposeFrame();			//creates screen buffer
		DrawFrame();			//prints the screen buffer to console
		Sleep(frameDelay);	
	}
}

/////////////////////
void AsciiEngine::tick()
{
	struct s_node* cur = g_AllActors.head;	
	while (cur != NULL)	//traverse the list containing every actor
	{
		cur->thisActor->ActorTick();	//and executes their tick
		cur = cur->next;
	}
}

/////////////////////
void AsciiEngine::DrawFrame()
{
	WriteConsoleOutputCharacterW(hConsole, screen, m_nScreenWidth * m_nScreenHeight, { 0,0 }, &dwBytesWritten);	//prints screen buffer
}

/////////////////////
void AsciiEngine::ComposeFrame()
{
	struct s_node* cur = g_AllActors.head;
	for (int i = 0; i < m_nScreenWidth*m_nScreenHeight-1; i++) screen[i] =L' '; //fill the buffer with empty space
	while (cur != NULL)					//traverse the list containing every actor
	{
		screen[cur->thisActor->GetPosition().x + cur->thisActor->GetPosition().y*m_nScreenWidth] = cur->thisActor->GetTag();
																	//insert each actors tag to the appropriate coordinates.
		cur = cur->next;
	}
}

/////////////////////
void AsciiEngine::AppendToActors(Actor* newActor) {	//get freshly created actor appended to the linked list
	struct s_node* node;
	node = (struct s_node*)malloc(sizeof(struct s_node));
	node->thisActor = newActor;
	node->next = g_AllActors.head;
	g_AllActors.head = node;
}










