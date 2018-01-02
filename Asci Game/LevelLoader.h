#pragma once
#include <fstream>
using namespace std;

//byte Colors:
//		0x00 == Black     
//		0x01 == Dark Blue 
//		0x02 == Light Green 
//		0x03 == Cyan
//		0x04 == Maroon
//		0x05 == Purple
//		0x06 == Dark Yellow
//		0x07 == Light Grey
//		0x08 == Dark Grey
//		0x09 == Light Blue
//		0x0A == Light Green
//		0x0B == Turqoise
//		0x0C == Red
//		0x0D == Pink
//		0x0E == Light Yellow
//		0x0F == White
	



void LoadLevel(AsciiEngine* Engine)
{
	ifstream Level;
	Level.open("Level.txt");
	char c;
	int h=0, w=0;
	
	while (!Level.eof())
	{
		Level.read(&c,1);
		switch (c)
		{
		case'_':
			w++;
			break;
		case '*':
			Level.seekg(2, Level.cur);
			h++;
			w = 0;
			break;
		case 'R':
			Engine->AppendToActors(new R(w, h, L'#',5, LEFT, 0x0E | BACKGROUND));
			break;
		case 'S':
			Engine->AppendToActors(new S(w, h, L'S',5, LEFT,  FOREGROUND_GREEN | BACKGROUND));
			break;
		}
	}

}