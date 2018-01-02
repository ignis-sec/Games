#pragma once
#include <ctime>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "List.h"

int fpslock = 120; //max fps (game speed)

#define  LPSTR          char*						//just to be safe about CreateConsoleBuffer
#define  LPCSTR         const char*

#define  LPWSTR         wchar_t*
#define  LPWCSTR        const wchar_t*

#define  LPTSTR         TCHAR*
#define  LPCTSTR        const TCHAR* 

class Player;
Player* ThisPlayer;
int g_HP;
class Actor;

struct s_position {
	int x;
	int y;
};
typedef struct s_position position;

enum Direction { RIGHT=0, UP=1, LEFT=2, DOWN=3 ,FLAG};

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
	WORD* screenatb;
	HANDLE hConsole;
	DWORD dwBytesWritten;
	DWORD dwAttrWritten;
	int m_nScreenWidth;
	int m_nScreenHeight;
};
 Actors g_AllActors;
 AsciiEngine* g_Engine;
#include "Actor.h"

 /////////////////////
AsciiEngine::AsciiEngine(int nScreenWidth, int nScreenHeight)
{
	//this creates screen Buffer
	screen = new wchar_t[nScreenWidth*nScreenHeight];
	screenatb = new WORD[nScreenWidth*nScreenHeight];
	for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
	for (int j = 0; j < nScreenWidth*nScreenHeight; j++) screenatb[j] = BACKGROUND;
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	dwBytesWritten = 0;
	dwAttrWritten = 0;
	m_nScreenHeight = nScreenHeight;
	m_nScreenWidth = nScreenWidth;
	g_AllActors.head = g_AllActors.tail = NULL;

}
char title[50];
/////////////////////
void AsciiEngine::StartGame() {

	char name[50] = "Ascii Engine ";
	char fps[15] = "(FPS: ";
	char fpsf[10];
	char hp[5] = "HP: ";
	double framelength=0;
	double frameDelay = (double)1000.0 / (double)fpslock;
	while (g_HP>0)			//basically game loop
	{
		clock_t begin = clock();					//This part composes window title and frame counter
		strcpy(title, "");							//
		strcpy(fpsf, "");							//
		sprintf(fpsf, "%.2lf", 1.0/framelength);	//
		strcat(title,name);							//
		strcat(title, fps);							//
		strcat(title, fpsf);						//
		strcat(title, ") ");						//
		strcat(title, hp);
		for (int i = 0; i < g_HP; i++)
			strcat(title, "*");
		SetConsoleTitle(title);
		tick();					//plays every actors ActorTick
		ComposeFrame();			//creates screen buffer
		DrawFrame();			//prints the screen buffer to console
		Sleep(frameDelay);
		clock_t end = clock();
		framelength = ((double)end - (double)begin) / (double)CLOCKS_PER_SEC;
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
	WriteConsoleOutputAttribute(
		hConsole,						//handle
		screenatb,						//Attribute
		m_nScreenWidth*m_nScreenHeight,	//length
		{ 0,0 },						//struct _COORD from WINAPI
		&dwAttrWritten);				//reference to number of attributes written

	WriteConsoleOutputCharacterW(					//prints screen buffer
		hConsole,						//handle
		screen,							//characters
		m_nScreenWidth*m_nScreenHeight, //size
		{ 0,0 },						//struct _COORD from WINAPI
		&dwBytesWritten);				//reference to number of bytes written
	
}

/////////////////////
void AsciiEngine::ComposeFrame()
{
	struct s_node* cur = g_AllActors.head;
	COORD tempCOORD;
	for (int i = 0; i < m_nScreenWidth*m_nScreenHeight-1; i++) screen[i] =L' '; //fill the buffer with empty space
	for (int j = 0; j < m_nScreenWidth*m_nScreenHeight - 1; j++) screenatb[j] = BACKGROUND; //fill the buffer with empty space
	while (cur != NULL)					//traverse the list containing every actor
	{
		screen[cur->thisActor->GetPosition().x + cur->thisActor->GetPosition().y*m_nScreenWidth] = cur->thisActor->GetTag();
		screenatb[cur->thisActor->GetPosition().x + cur->thisActor->GetPosition().y*m_nScreenWidth] = cur->thisActor->GetAttribute();
		

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


#include "Player.h"
#include "ActorVariants.h"







