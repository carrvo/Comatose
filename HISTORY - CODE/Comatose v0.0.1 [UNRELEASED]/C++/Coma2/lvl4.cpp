#include "Windows.h"
#include "BasicBoard.h"
#include "creature.h"
#include "human.h"
#include "lvl5.h"
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

void crackloclvl4(int w, int h);
void inside4(char board[], int w);
void ploc4(int w);
void cloc4(int w);
void cloc0();
bool printboard4(bool open);
bool afterin4(char board[], int w, int fin);
bool nxtlvl4();
void breset4();
void callhturn4();
void printp4(char board[]);
void printc4(char board[], int w);
void printb4(char board[]);
void bombconv4(int bombs2);
void bkeep5();

static const int ctotal4 = 901;
static int locOFc[ctotal4];
static char dirOFc[ctotal4];
static int ctot = 1;
static bool cdead = false;
static int locOFwall[ctotal4];
static int nwall = 0;

static int locOFp[16];
static bool ps[16] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
static int ptot = 16;

static int bombs = 0;
static int locOFb[100];
static int bnum = 0;

static int crack = 0;
static int crachv = 0; //1 for vertical, w for horizontal

static bool slow = false;

void crackloclvl4(int w, int h)
{
	crack = h / 2 * w - 1;
	crachv = w;
}

void inside4(char board[], int w)
{
	int t = w / 2 + 5 * w;
	for (int i = 0; i < 6; i++)
	{
		board[t + i] = BD;
		board[t + i * w] = BD;
		board[t + 5 * w + i] = BD;
	}
	board[t + 5 + w] = BD;
	board[t + 4 * w + 5] = BD;

	for (int i = 0; i < 4; i++)
	{
		board[t + 5 + w + 10 + w * i] = BD;
	}

	for (int j = 0; j < ctotal4; j++)
	{
		board[locOFwall[j]] = BD;
	}
}

/* ploc4
* - location of pickups
*/
void ploc4(int w)
{
	int t = w / 2 + 5 * w;
	int n = 0;
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			locOFp[n] = t + i + j * w;
			n++;
		}
	}
}

/* cloc4
* - location of creatures (start)
* - direction of creatures (start)
*/
void cloc4(int w)
{
	int not[25];
	int t = w / 2 + 5 * w;
	int n2 = 0;
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				not[n2] = t + i * w + j + w;
				n2++;
			}
		}
	}

	if (locOFc[0] == 0)
	{
		ctot = 901;
		for (int v = 0; v < ctot; v++)
		{
			locOFc[v] = 0;
		}

		int n = 1;
		int k = 0;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < w - 10; j++)
			{
				t = 3 * w + i * w + 5 + j;
				bool isnot = true;
				if (not[k] == t)
				{
					isnot = false;
					if (k != 25) k++;
				}
				if (isnot) locOFc[n] = t;
				else locOFc[n] = 0;
				dirOFc[n] = 'w';
				n++;
			}
		}
		cdead = true;
		slow = true;

		int e = 2;
		for (int v = 1; v < ctot; v += e)
		{
			locOFc[v] = 0;
			if (e == 3) e = 1;
			else if (e == 1) e = 2;
			else if (e == 2) e = 3;
			if (v % w - 10 == 0) v++;
		}
	}
}

void cloc0()
{
	int w = 70;
	int t = w / 2 + 5 * w;
	locOFc[0] = t + w + 1;
	dirOFc[0] = 'd';

	for (int w = 0; w < ctotal4; w++)
	{
		locOFwall[w] = 0;
	}
}

/* printboard4 (lvl2)
* - prints the board with all edges and creatures
* - houses the dimensions of the board
* - returns true if loses
*/
bool printboard4(bool open)
{
	int h = 20;
	int w = 70;
	int fin = w * h;
	char board[1400 + 1];

	crackloclvl4(w, h);
	ploc4(w);
	if (!cdead) cloc4(w);
	crackplace(crack, crachv);
	outside(w, fin, board);
	printcrack(open, board);
	inside4(board, w);

	return afterin4(board, w, fin);
}

/* afterin4
* - finishes printboard after inside walls are filled in
* - returns true if loses
*/
bool afterin4(char board[], int w, int fin)
{
	bool end = false;

	pickingup(board, ps, locOFp, ptot, bombs);
	printp4(board);
	printb4(board);
	printc4(board, w);
	if (printh(board, w))
	{
		seeboard(board, w, fin, bombs);
	}
	else
	{
		cout << "Fredrick does not wake up." << endl;
		end = true;
	}

	if (!slow) Sleep(500); //
	else Sleep(1000);
	return end;
}

/* nxtlvl4
* - returns if move to next level from human.h
*/
bool nxtlvl4() { return nextlvl(crack, crachv); }

/* breset4
* - resets the positions of the bombs for the next level
*/
void breset4()
{
	for (int k = 0; k < 100; k++)
	{
		locOFb[k] = '\0';
	}
}

/* callhturn4
* - calls hturn with the appropriate arguments
*/
void callhturn4() { hturn(bombs, locOFb, bnum); }

void printp4(char board[])
{
	for (int k = 0; k < ptot; k++)
	{
		if (ps[k])
		{
			board[locOFp[k]] = P;
		}
	}
}

void printc4(char board[], int w)
{
	for (int j = 0; j < ctot; j++)
	{
		moving(board, w, locOFc[j], dirOFc[j]);

		int tmploc = locOFc[j];
		cbomb(locOFc[j], w, crack, crachv, locOFb);
		if (locOFc[j] != tmploc)
		{
			locOFwall[nwall] = tmploc;
			nwall++;
		}

		board[locOFc[j]] = C;
	}
}

void printb4(char board[])
{
	for (int i = 0; i < 100; i++)
	{
		if (locOFb[i] != '\0')
		{
			board[locOFb[i]] = B;
		}
	}
}

void bombconv4(int bombs2) { bombs = bombs2; }

void bkeep5() { bombconv5(bombs); }