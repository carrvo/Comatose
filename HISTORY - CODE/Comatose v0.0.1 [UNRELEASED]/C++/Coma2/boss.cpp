#include "Windows.h"
#include "BasicBoard.h"
#include "creature.h"
#include "creatureR.h"
#include "human.h"
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

void crackloclvlB(int w, int h);
void insideB(char board[], int w, int h);
void clocB();
void printcrackB(bool open, char boarder[]);
bool printboardB(bool open);
bool afterinB(char board[], int w, int fin);
bool nxtlvlB();
void bresetB();
void callhturnB();
void printcB(char board[], int w);
void revive();
bool openning(int loc, int w, char board[]);
void printbB(char board[]);
void bombconvB(int bombs2);

static const int ctotal = 50;
static int locOFc[ctotal];
static char dirOFc[ctotal];
static int ctot = ctotal;
static int locOFcR[ctotal];
static char dirOFcR[ctotal];
static int nc = 0;
static int timing = 4;

static int bombs = 0;
static int locOFb[100];
static int bnum = 0;

static int crack[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int crachv = 0; //1 for vertical, w for horizontal
static int cwall = 0;
static const int cwallm = 21;

void crackloclvlB(int w, int h)
{
	int t = w / 2;
	int u = h / 2 + 1;
	crack[0] = u * w + t;
	int r = 0, n = 1;
	int s = 1;
	for (int i = 1; i < 5; i++)
	{
		if (n == 2)
		{
			r++;
			n = 0;
		}
		crack[s] = u * w + t + i - r * w;
		s++;
		crack[s] = u * w + t - i - r * w;
		s++;
		n++;
	}
	crachv = w;
}

void insideB(char board[], int w, int h)
{
	int t = w / 2;
	int u = h / 2 - 3;
	board[u * w + t - 2] = BD;
	board[u * w + t + 2] = BD;

	board[(h - 2) * w + t] = BD;
	board[(h - 3) * w + t] = BD;

	if (cwall != 0)
	{
		board[(h - 7) * w + t + 1] = BD;
		board[(h - 7) * w + t - 1] = BD;
	}
	cwall++;
	if (cwall >= cwallm) cwall = 0;
}

/* clocB
* - location of creatures (start)
* - direction of creatures (start)
*/
void clocB()
{
	int w = 70 - 5;
	int h = 20;
	int t = w / 2;
	int u = h / 2;
	int m = u * w + t;
	
	for (int i = 0; i < ctot; i++)
	{
		locOFc[i] = m;
		locOFcR[i] = m;
		dirOFc[i] = 'w';
		dirOFcR[i] = 'w';
	}
	ctot = 1;
}

void printcrackB(bool open, char boarder[])
{
	if (!open)
	{
		for (int i = 0; i < 9; i++)
		{
			boarder[crack[i]] = CE;
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			boarder[crack[i]] = E;
		}
	}
}

/* printboardB (lvl2)
* - prints the board with all edges and creatures
* - houses the dimensions of the board
* - returns true if loses
*/
bool printboardB(bool open)
{
	int h = 20;
	int w = 70 - 5;
	int fin = w * h;
	char board[1400 + 1];

	crackloclvlB(w, h);
	outside(w, fin, board);
	printcrackB(open, board);
	insideB(board, w, h);

	return afterinB(board, w, fin);
}

/* afterinB
* - finishes printboard after inside walls are filled in
* - returns true if loses
*/
bool afterinB(char board[], int w, int fin)
{
	bool end = false;

	printbB(board);
	printcB(board, w);
	if (printh(board, w))
	{
		seeboard(board, w, fin, bombs);
	}
	else
	{
		cout << "Fredrick does not wake up." << endl;
		end = true;
	}

	Sleep(700); //
	return end;
}

/* nxtlvlB
* - returns if move to next level from human.h
*/
bool nxtlvlB()
{
	bool nxt = false;
	for (int i = 0; i < 9; i++)
	{
		if (nextlvl(crack[i], 0))
		{
			nxt = true;
			i = 9;
		}
	}
	return nxt;
}

/* bresetB
* - resets the positions of the bombs for the next level
*/
void bresetB()
{
	for (int k = 0; k < 100; k++)
	{
		locOFb[k] = '\0';
	}
}

/* callhturnB
* - calls hturn with the appropriate arguments
*/
void callhturnB() { hturn(bombs, locOFb, bnum); }

void printcB(char board[], int w)
{
	for (int j = 0; j < ctot; j++)
	{
		moving(board, w, locOFc[j], dirOFc[j]);
		movingR(board, w, locOFcR[j], dirOFcR[j]);

		bool opennings = false;
		opennings = openning(locOFc[j], w, board);

		cbombB(locOFc[j], w, locOFb, opennings);
		cbombBR(locOFcR[j], w, locOFb, opennings);

		board[locOFc[j]] = C;
		board[locOFcR[j]] = C;
	}
	nc++;
	if (nc > timing)
	{
		nc = 0;
		if (ctot < ctotal - 1) ctot++;
		else
		{
			revive();
		}
	}
}

void revive()
{
	int w = 70 - 5;
	int h = 20;
	int t = w / 2;
	int u = h / 2;
	int m = u * w + t;

	int j = 0;
	for (j = 0; j < ctot; j++)
	{
		if (locOFc[j] == 0)
		{
			locOFc[j] = m;
			dirOFc[j] = 'w';
			j = ctot;
		}
	}
	for (j = 0; j < ctot; j++)
	{
		if (locOFcR[j] == 0)
		{
			locOFcR[j] = m;
			dirOFcR[j] = 'w';
			j = ctot;
		}
	}
}

/* openning
* - returns true if bombs surround the smile and a creature lands on one
*/
bool openning(int loc, int w, char board[])
{
	int v = 0;
	if (crachv == 1) v = w;
	else if (crachv == w) v = 1;

	bool cland = false, complete = true;

	for (int j = 0; j < 9; j++)
	{
		if (board[crack[j] + crachv] != B || board[crack[j] - crachv] != B)
		{
			complete = false;
			j = 9;
		}
	}
	if (complete && (board[crack[8] - v] != B || board[crack[7] + v] != B))
	{
		complete = false;
	}

	for (int j = 0; j < 9; j++)
	{
		if (loc == crack[j] + crachv || loc == crack[j] - crachv)
		{
			cland = true;
			j = 9;
		}
	}
	if (!cland && (loc == crack[8] - v || loc == crack[7] + v))
	{
		cland = true;
	}

	bool ret = cland && complete;
	if (ret)
	{
		for (int j = 0; j < 9; j++)
		{
			int A = crack[j] + crachv;
			int B = crack[j] - crachv;
			int C = crack[8] - v;
			int D = crack[7] + v;
			for (int k = 0; k < bnum; k++)
			{
				int ll = locOFb[k];
				if (ll == A || ll == B || ll == C || ll == D)
				{
					if (ll != loc)
					{
						locOFb[k] = '\0';
					}
				}
			}
		}
	}

	return ret;
}

void printbB(char board[])
{
	for (int i = 0; i < 100; i++)
	{
		if (locOFb[i] != '\0')
		{
			board[locOFb[i]] = B;
		}
	}
}

void bombconvB(int bombs2) { bombs = bombs2; }