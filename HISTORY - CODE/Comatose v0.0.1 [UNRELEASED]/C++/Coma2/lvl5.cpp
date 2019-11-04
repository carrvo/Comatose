#include "Windows.h"
#include "BasicBoard.h"
#include "creature.h"
#include "human.h"
#include "boss.h"
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

void crackloclvl5(int w, int h);
void inside5(char board[], int w, int h);
void ploc5(int w, int h);
void pset();
void cloc5();
bool printboard5(bool open);
bool afterin5(char board[], int w, int fin);
bool nxtlvl5();
void breset5();
void callhturn5();
void printp5(char board[]);
void printc5(char board[], int w);
void printb5(char board[]);
void bombconv5(int bombs2);
void bkeepB();

static int locOFc[7];
static char dirOFc[7];
static int ctot = 7;

static int locOFp[141];
static bool ps[141];
static int ptot = 141;

static int bombs = 0;
static int locOFb[100];
static int bnum = 0;

static int crack = 0;
static int crachv = 0; //1 for vertical, w for horizontal

void crackloclvl5(int w, int h)
{
	crack = w / 2 + h / 2 * w;
	crachv = w;
}

void inside5(char board[], int w, int h)
{
	int k = 0;
	for (int i = 1; i < h; i += 2)
	{
		for (int j = 1; j < w; j += 5)
		{
			board[i * w + j + k] = BD;
		}
		k += 3;
		if (i > 15) k = 0;
	}
}

/* ploc5
* - location of pickups
*/
void ploc5(int w, int h)
{
	int n = 0;
	int k = 0;
	for (int i = 1; i < h; i += 2)
	{
		for (int j = 1; j < w; j += 5)
		{
			locOFp[n] = i * w + j + k;
			n++;
		}
		k += 3;
		if (i > 15) k = 0;
	}
}

void pset()
{
	for (int i = 0; i < ptot; i++)
	{
		ps[i] = true;
	}
}

/* cloc5
* - location of creatures (start)
* - direction of creatures (start)
*/
void cloc5()
{
	int w = 70;
	int h = 20;
	int t = w / 2 + h / 2 * w;

	locOFc[0] = t - w;
	dirOFc[0] = 'a';
	locOFc[1] = t - w;
	dirOFc[1] = 'w';
	locOFc[2] = t - w;
	dirOFc[2] = 'd';
	locOFc[3] = t;
	dirOFc[3] = 'a';
	locOFc[4] = t;
	dirOFc[4] = 'd';
	locOFc[5] = t + w;
	dirOFc[5] = 'a';
	locOFc[6] = t + w;
	dirOFc[6] = 's';
}

/* printboard5 (lvl2)
* - prints the board with all edges and creatures
* - houses the dimensions of the board
* - returns true if loses
*/
bool printboard5(bool open)
{
	int h = 20;
	int w = 70;
	int fin = w * h;
	char board[1400 + 1];

	crackloclvl5(w, h);
	ploc5(w, h);
	crackplace(crack, crachv);
	outside(w, fin, board);
	printcrack(open, board);
	inside5(board, w, h);

	return afterin5(board, w, fin);
}

/* afterin5
* - finishes printboard after inside walls are filled in
* - returns true if loses
*/
bool afterin5(char board[], int w, int fin)
{
	bool end = false;

	pickingup(board, ps, locOFp, ptot, bombs);
	printp5(board);
	printb5(board);
	printc5(board, w);
	if (printh(board, w))
	{
		seeboard(board, w, fin, bombs);
	}
	else
	{
		cout << "Fredrick does not wake up." << endl;
		end = true;
	}

	Sleep(500); //
	return end;
}

/* nxtlvl5
* - returns if move to next level from human.h
*/
bool nxtlvl5() { return nextlvl(crack, crachv); }

/* breset5
* - resets the positions of the bombs for the next level
*/
void breset5()
{
	for (int k = 0; k < 100; k++)
	{
		locOFb[k] = '\0';
	}
}

/* callhturn5
* - calls hturn with the appropriate arguments
*/
void callhturn5() { hturn(bombs, locOFb, bnum); }

void printp5(char board[])
{
	for (int k = 0; k < ptot; k++)
	{
		if (ps[k])
		{
			board[locOFp[k]] = P;
		}
	}
}

void printc5(char board[], int w)
{
	for (int j = 0; j < ctot; j++)
	{
		moving(board, w, locOFc[j], dirOFc[j]);

		cbomb(locOFc[j], w, crack, crachv, locOFb);

		board[locOFc[j]] = C;
	}
}

void printb5(char board[])
{
	for (int i = 0; i < 100; i++)
	{
		if (locOFb[i] != '\0')
		{
			board[locOFb[i]] = B;
		}
	}
}

void bombconv5(int bombs2) { bombs = bombs2; }

void bkeepB() { bombconvB(bombs); }