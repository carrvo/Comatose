#include "Windows.h"
#include "BasicBoard.h"
#include "human.h"
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

bool turnR(char boader[], int w, int loc, char direction);
void onemoveR(char boader[], int w, int& loc, char& direction);
void movingR(char boader[], int w, int& loc, char& direction);
void cbombR(int& loc, int w, int crack, int crachv, int locOFb[]);
void cbombBR(int& loc, int w, int locOFb[], bool openning);
bool openingR();
void openresetR();

static bool opens = false;

/* turnR
* - determines if the position that the creature would move into is an edge (true)
*/
bool turnR(char boader[], int w, int loc, char direction) //what if goes off boader?
{
	bool ret = false;

	if (direction == 'w')
	{
		int x = loc - w;
		if (boader[x] == BD || boader[x] == CE || boader[x] == C || x < 0 || x > 1400)
		{
			ret = true;
		}
	}
	else if (direction == 's')
	{
		int x = loc + w;
		if (boader[x] == BD || boader[x] == CE || boader[x] == C || x < 0 || x > 1400)
		{
			ret = true;
		}
	}
	else if (direction == 'a')
	{
		int x = loc - 1;
		if (boader[x] == BD || boader[x] == CE || boader[x] == C || x < 0 || x > 1400)
		{
			ret = true;
		}
	}
	else if (direction == 'd')
	{
		int x = loc + 1;
		if (boader[x] == BD || boader[x] == CE || boader[x] == C || x < 0 || x > 1400)
		{
			ret = true;
		}
	}

	return ret;
}

/*onemoveR
* - if turn then the direction is changed clockwise (negative angle)
* - if !turn then changes the loc (location) to position would move into
*/
void onemoveR(char boader[], int w, int& loc, char& direction)
{
	if (turnR(boader, w, loc, direction))
	{
		if (direction == 'w')
		{
			direction = 'a';
		}
		else if (direction == 's')
		{
			direction = 'd';
		}
		else if (direction == 'a')
		{
			direction = 's';
		}
		else if (direction == 'd')
		{
			direction = 'w';
		}
	}
	else
	{
		if (direction == 'w')
		{
			loc -= w;
		}
		else if (direction == 's')
		{
			loc += w;
		}
		else if (direction == 'a')
		{
			loc -= 1;
		}
		else if (direction == 'd')
		{
			loc += 1;
		}
	}
}

/* movingR
* - when loc (location) changes
* - ask if there is a B (bomb)
* - if B then move to corner (upper left @ position 0)
* - only one loc change
*/
void movingR(char boader[], int w, int& loc, char& direction)
{
	char dir, d;
	if (loc != 0)
	{
		d = direction;
		do
		{
			dir = direction;
			onemoveR(boader, w, loc, direction);
		} while (dir != direction && d != direction);
	}
}

/* cbombR
* - ask if there is a B (bomb)
* - if B then move to corner (upper left @ position 0)
*/
void cbombR(int& loc, int w, int crack, int crachv, int locOFb[])
{
	for (int i = 0; i < 100; i++)
	{
		if (loc == locOFb[i])
		{
			int v = 0;
			if (crachv == 1) v = w;
			else if (crachv == w) v = 1;
			if (loc == crack + v || loc == crack + crachv + v || loc == crack - crachv + v
				|| loc == crack - v || loc == crack + crachv - v || loc == crack - crachv - v
				|| loc == crack + crachv * 2 || loc == crack - crachv * 2)
			{
				opens = true;
			}
			locOFb[i] = '\0';
			loc = 0;
		}
	}
}

/* cbombBR - for boss (smile crack)
* - ask if there is a B (bomb)
* - if B then move to corner (upper left @ position 0)
*/
void cbombBR(int& loc, int w, int locOFb[], bool openning)
{
	for (int i = 0; i < 100; i++)
	{
		if (loc == locOFb[i])
		{
			locOFb[i] = '\0';
			loc = 0;
		}
	}
	if (openning)
	{
		opens = true;
	}
}

/* openingR
* - function for telling if crack is open
*/
bool openingR() { return opens; }

void openresetR() { opens = false; }