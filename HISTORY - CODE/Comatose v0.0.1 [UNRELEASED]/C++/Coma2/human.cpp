#include "Windows.h"
#include "BasicBoard.h"
#include "creature.h"
#include <conio.h>  //allows for _getch() which is same as cin.get() without the buffer
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

void hturn(int& bombs, int* locOFb, int& bnum);
void pickingup(char board[], bool* ps, int locOFp[], int ptot, int& bombs);
void hstraight(int w);
bool nextlvl(int crack, int crachv);
bool printh(char board[], int w);
bool plantbomb(char c, int& bombs, int* locOFb, int& bnum);
void hstart(int locSt, char dirSt);

static int locOFh = 1000;
static char dirOFh = 'w';
static bool dead = false;

/* hturn
* - waits for input
* - if E then plants a bomb
* - else changes direction of human
*/
void hturn(int& bombs, int* locOFb, int& bnum)
{
	char c = '\0';
	c = _getch();
	if (!plantbomb(c, bombs, locOFb, bnum))
	{
		if (c == 'w')
		{
			dirOFh = 'w';
		}
		else if (c == 'd')
		{
			dirOFh = 'd';
		}
		else if (c == 's')
		{
			dirOFh = 's';
		}
		else if (c == 'a')
		{
			dirOFh = 'a';
		}
	}
}

/* pickingup
* - human lands on pickup
*/
void pickingup(char board[], bool* ps, int locOFp[], int ptot, int& bombs)
{
	for (int i = 0; i < ptot; i++)
	{
		if (locOFh == locOFp[i] && ps[i])
		{
			bombs += 10;
			ps[i] = false;
			i = ptot;
		}
	}
}

/* hstraight
* - moves human
*/
void hstraight(int w)
{
	if (dirOFh == 'w')
	{
		locOFh -= w;
	}
	else if (dirOFh == 's')
	{
		locOFh += w;
	}
	else if (dirOFh == 'a')
	{
		locOFh -= 1;
	}
	else if (dirOFh == 'd')
	{
		locOFh += 1;
	}
}

/* nextlvl
* - returns true if move to next level
*/
bool nextlvl(int crack, int crachv)
{
	bool ret = false;
	if (locOFh == crack || locOFh == crack + crachv || locOFh == crack - crachv)
	{
		if (opening())
		{
			ret = true;
		}
	}
	return ret;
}

/* printh
* - moves human
* - returns false if loses
* - prints location to board
*/
bool printh(char board[], int w)
{
	hstraight(w);
	bool dead = false;
	dead = board[locOFh] != E && board[locOFh] != P;
	if (!dead) board[locOFh] = 'F';
	return !dead;
}

/* plantbomb
* - if input is E then plants a bomb at human's location
* - returns true if it plants a bomb
*/
bool plantbomb(char c, int& bombs, int* locOFb, int& bnum)
{
	bool ret = false;
	if (c == E)
	{
		if (bombs > 0)
		{
			bombs--;
			locOFb[bnum] = locOFh;
			bnum++;
			if (bnum == 100) bnum = 0;
		}
		ret = true;
	}
	return ret;
}

void hstart(int locSt, char dirSt)
{
	locOFh = locSt;
	dirOFh = dirSt;
}