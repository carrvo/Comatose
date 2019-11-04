#include "Windows.h"
#include "BasicBoard.h"
#include "human.h"
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

bool turn(char boader[], int w, int loc, char direction);
void onemove(char boader[], int w, int& loc, char& direction);
void moving(char boader[], int w, int& loc, char& direction);
void cbomb(int& loc, int w, int crack, int crachv, int locOFb[]);
void cbombB(int& loc, int w, int locOFb[], bool openning);
bool opening();
void openreset();

static bool opens = false;

/* turn
* - determines if the position that the creature would move into is an edge (true)
*/
bool turn(char boader[], int w, int loc, char direction) //what if goes off boader?
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

/*onemove
* - if turn then the direction is changed clockwise (negative angle)
* - if !turn then changes the loc (location) to position would move into
*/
void onemove(char boader[], int w, int& loc, char& direction)
{
	if (turn(boader, w, loc, direction))
	{
		if (direction == 'w')
		{
			direction = 'd';
		}
		else if (direction == 's')
		{
			direction = 'a';
		}
		else if (direction == 'a')
		{
			direction = 'w';
		}
		else if (direction == 'd')
		{
			direction = 's';
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

/* moving
* - when loc (location) changes
* - ask if there is a B (bomb)
* - if B then move to corner (upper left @ position 0)
* - only one loc change
*/
void moving(char boader[], int w, int& loc, char& direction)
{
	char dir, d;
	if (loc != 0)
	{
		d = direction;
		do
		{
			dir = direction;
			onemove(boader, w, loc, direction);
		} while (dir != direction && d != direction);
	}
}

/* cbomb
* - ask if there is a B (bomb)
* - if B then move to corner (upper left @ position 0)
*/
void cbomb(int& loc, int w, int crack, int crachv, int locOFb[])
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

/* cbombB - for boss (smile crack)
* - ask if there is a B (bomb)
* - if B then move to corner (upper left @ position 0)
*/
void cbombB(int& loc, int w, int locOFb[], bool openning)
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

/* opening
* - function for telling if crack is open
*/
bool opening() { return opens; }

void openreset() { opens = false; }