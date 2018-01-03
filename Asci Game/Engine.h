#pragma once
#include <ctime>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "List.h"

int fpslock = 180; //max fps (game speed)
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
	void DrawAttribute();
	void ComposeFrame();
	void StartGame();
	void tick();
	void tickTEntry(Actor* Actor);
	void FrameTEntry(struct s_node* cur);
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
	g_AllActors.head = g_AllActors.tail = NULL; //initialize actors list

}
char title[50];
/////////////////////
void AsciiEngine::StartGame() {

	char name[50] = "Ascii Engine ";//
	char fps[15] = "(FPS: ";		//
	char fpsf[10];					//
	char hp[5] = "HP: ";
	double framelength=0;
	double frameDelay = (double)1000.0 / (double)fpslock;
	int totalframes = 0;

	while (g_HP>0)			//basically game loop
	{
		totalframes++;
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
		DrawAttribute();
		Sleep(frameDelay);

		clock_t end = clock();
		framelength = ((double)end - (double)begin) / (double)CLOCKS_PER_SEC;	//this calculates length of a frame from tick start to end of delay
	}
}
void AsciiEngine::tickTEntry(Actor* Actor)
{
	Actor->ActorTick();
}
/////////////////////
void AsciiEngine::tick()
{
	//std::vector<std::thread> threads;
	struct s_node* cur = g_AllActors.head;	
	while (cur != NULL)	//traverse the list containing every actor
	{
		//threads.push_back(std::thread(&AsciiEngine::tickTEntry,this,cur->thisActor));	
		cur->thisActor->ActorTick();
		cur = cur->next;
	}
	//for (auto &t : threads)
	//	t.join();
}



/////////////////////
void AsciiEngine::DrawFrame()
{
	WriteConsoleOutputCharacterW(					//prints screen buffer
		hConsole,						//handle
		screen,							//characters
		m_nScreenWidth*m_nScreenHeight, //size
		{ 0,0 },						//struct _COORD from WINAPI
		&dwBytesWritten);				//reference to number of bytes written		
}

void AsciiEngine::DrawAttribute()
{
	WriteConsoleOutputAttribute(
		hConsole,						//handle
		screenatb,						//Attribute
		m_nScreenWidth*m_nScreenHeight,	//length
		{ 0,0 },						//struct _COORD from WINAPI
		&dwAttrWritten);				//reference to number of attributes written
}

/////////////////////
void AsciiEngine::ComposeFrame()
{
	struct s_node* cur = g_AllActors.head;
	std::vector<std::thread> threads;
	int pos;
	for (int i = 0; i < m_nScreenWidth*m_nScreenHeight-1; i++) screen[i] =L' '; //fill the buffer with empty space
	for (int j = 0; j < m_nScreenWidth*m_nScreenHeight - 1; j++) screenatb[j] = BACKGROUND; //fill the buffer with empty space
	while (cur != NULL)					//traverse the list containing every actor
	{
		int pos = cur->thisActor->GetPosition().onScreenPos;
		screen[pos] = cur->thisActor->GetTag(); //set position of actor to its tag
		screenatb[pos] = cur->thisActor->GetAttribute();	//and its attribute
		//threads.push_back(std::thread(&AsciiEngine::FrameTEntry, this, cur));
		cur = cur->next;
	}
	
	//for (auto &t : threads)
	//	t.join();
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




/*
void AsciiEngine::AppendToActors(Actor* newActor) {	//get freshly created actor appended to the linked list
struct s_node* node;
node = (struct s_node*)malloc(sizeof(struct s_node));
node->thisActor = newActor;
if (g_AllActors.head == NULL) {
g_AllActors.head = node;
g_AllActors.tail = node;
return;
}
g_AllActors.tail->next = node;
g_AllActors.tail = node;

}
*/



#include "Player.h"
#include "ActorVariants.h"







