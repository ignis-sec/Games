//Thanks to the javidx9 (AKA oneLoneCoder) for inspiring me to create this
//
//
//
//
//
//
#pragma once
#include <ctime>
#include <vector>
#include <list>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "List.h"

double fpslock = 50; //max fps (game speed)
int delayMultip = 1;

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
	int onScreenPos;
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
	void tickTEntry(Actor* Actor);
	void FrameTEntry(struct s_node* cur);
	void ComposeTitle(double framelength);
private:
	
	CHAR_INFO *screenChar;
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
	screenChar = new CHAR_INFO[nScreenWidth*nScreenHeight];
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	dwBytesWritten = 0;
	dwAttrWritten = 0;
	m_nScreenHeight = nScreenHeight;
	m_nScreenWidth = nScreenWidth;
	g_AllActors.head = g_AllActors.tail = NULL; //initialize actors list

}

/////////////////////
void AsciiEngine::StartGame() {

	double framelength = 0;
	double frameDelay = (double)1000.0 / (double)fpslock;
	int totalframes = 0;
	
	while (g_HP>0)			//basically game loop
	{
		clock_t begin = clock();
		std::thread title(&AsciiEngine::ComposeTitle, this, framelength);
		std::thread delay(Sleep,frameDelay);
		totalframes++;
		tick();					//plays every actors ActorTick
		ComposeFrame();			//creates screen buffer
		std::thread draw(&AsciiEngine::DrawFrame, this);//draws the frame, but starts after tick and composeFrame has finished
		//DrawFrame();

		draw.join();	//every thread should synch for frame to end
		delay.join();
		title.join();
		clock_t end = clock();
		framelength = ((double)end - (double)begin) / (double)CLOCKS_PER_SEC;	//this calculates length of a frame from tick start to end of delay
	}
}

char title[50];
void AsciiEngine::ComposeTitle(double framelength)
{

	char name[50] = "Ascii Engine ";//
	char fps[15] = "(FPS: ";		//
	char fpsf[10];					//
	char hp[5] = "HP: ";

	strcpy(title, "");							////This part composes window title and frame counter
	strcpy(fpsf, "");							//
	sprintf(fpsf, "%.2lf", 1.0 / framelength);	//
	strcat(title, name);						//
	strcat(title, fps);							//
	strcat(title, fpsf);						//
	strcat(title, ") ");						//
	strcat(title, hp);
	for (int i = 0; i < g_HP; i++)
		strcat(title, "*");
	SetConsoleTitle(title);
}

void AsciiEngine::tickTEntry(Actor* Actor)
{
	Actor->ActorTick();
}
/////////////////////
void AsciiEngine::tick()
{
	struct s_node* cur = g_AllActors.head;
	while (cur != NULL)	//traverse the list containing every actor
	{
		cur->thisActor->ActorTick();
		cur = cur->next;
	}
}

/////////////////////
void AsciiEngine::DrawFrame()
{
	SMALL_RECT writeZone = { 0, 0, (short)m_nScreenWidth, (short)m_nScreenHeight };
	WriteConsoleOutputW(					//prints screen buffer
		hConsole,							//handle
		screenChar,							//characters
		{ (short)m_nScreenWidth, (short)m_nScreenHeight }, //size
		{ 0,0 },							//struct _COORD from WINAPI
		&writeZone);					//reference to number of bytes written		
}

/////////////////////
void AsciiEngine::ComposeFrame()
{
	struct s_node* cur = g_AllActors.head;
	std::vector<std::thread> threads;
	int pos;
	for (int i = 0; i < m_nScreenWidth*m_nScreenHeight - 1; i++) {
		screenChar[i].Char.UnicodeChar = L' '; //fill the buffer with empty space
		screenChar[i].Attributes = BACKGROUND; //fill the buffer with empty space
	}

	while (cur != NULL)					//traverse the list containing every actor
	{
		int pos = cur->thisActor->GetPosition().onScreenPos;
		screenChar[pos].Char.UnicodeChar = cur->thisActor->GetTag(); //set position of actor to its tag
		screenChar[pos].Attributes = cur->thisActor->GetAttribute();	//and its attribute
		cur = cur->next;
	}
}

void AsciiEngine::FrameTEntry(struct s_node* cur)
{
		int pos = cur->thisActor->GetPosition().onScreenPos;
		screen[pos] = cur->thisActor->GetTag(); //set position of actor to its tag
		screenatb[pos] = cur->thisActor->GetAttribute();	//and its attribute
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







