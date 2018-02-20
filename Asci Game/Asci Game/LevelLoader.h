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
		w++;
		switch (c)
		{
		case'_':
			break;
		case '*':
			Level.seekg(2, Level.cur);
			h++;
			w = 0;
			break;
		case 'R':
			Engine->AppendToActors(new R(w, h, L'#', 500, LEFT, FOREGROUND_RED | FOREGROUND_GREEN , FALSE,TRUE));
			break;
		case 'S':
			Engine->AppendToActors(new S(w, h, L'S',3, LEFT,  FOREGROUND_GREEN , FALSE, TRUE));
			break;
		case 'P':
			Engine->AppendToActors(new Player(w, h, L'X', 5, LEFT, 0x0B ));
			break;
		case 'T':	
			Engine->AppendToActors(new T(w, h, L'T', 30, LEFT, FOREGROUND_GREEN , FALSE, TRUE));
			break;
		case 'Q':
			Engine->AppendToActors(new Q(w, h, L'ǒ', 30, LEFT, FOREGROUND_BLUE, TRUE, TRUE));
			break;
		case 'J':
			Engine->AppendToActors(new J(w, h, L'ɕ', 5, DOWN, FOREGROUND_RED , TRUE, TRUE));
			break;
		case 'I':
			Engine->AppendToActors(new S(w, h, L'S', 3, DOWN, 0x0F , TRUE, TRUE));
			break;
		case 'Ş':
			Engine->AppendToActors(new S(w, h, L'S', 1, LEFT, FOREGROUND_GREEN , FALSE, TRUE));
			break;

		}
	}
	Level.close();

}