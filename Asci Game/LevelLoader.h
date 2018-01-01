#pragma once
#include <fstream>
using namespace std;

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
			Engine->AppendToActors(new R(w, h, L'#', LEFT));
			break;
		case 'S':
			Engine->AppendToActors(new S(w, h, L'S', LEFT));
			break;
		}
	}

}