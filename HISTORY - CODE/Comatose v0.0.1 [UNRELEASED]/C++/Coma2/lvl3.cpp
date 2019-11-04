#include "Windows.h"
#include "BasicBoard.h"
#include "creature.h"
#include "human.h"
#include "lvl4.h"
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

void crackloclvl3(int w, int h);
void inside3(char board[], int w);
void ploc3();
void cloc3();
bool printboard3(bool open);
bool afterin3(char board[], int w, int fin);
bool nxtlvl3();
void breset3();
void callhturn3();
void printp3(char board[]);
void printc3(char board[], int w);
void printb3(char board[]);
void bombconv3(int bombs2);
void bkeep4();

static int locOFc[12];
static char dirOFc[12];
static int ctot = 12;

static int locOFp[3];
static bool ps[3] = { true, true, true };
static int ptot = 3;

static int bombs = 0;
static int locOFb[100];
static int bnum = 0;

static int crack = 0;
static int crachv = 0; //1 for vertical, w for horizontal

void crackloclvl3(int w, int h)
{
	crack = h / 2 * w;
	crachv = w;
}

void inside3(char board[], int w)
{
	for (int i = 0; i < 14 * w; i += w)
	{
		board[284 + w + i] = BD;
	}
	board[284 - 3 * w] = BD;

	for (int i = 14 + w; i < 19 * w; i += w)
	{
		board[i] = BD;
	}
}

/* ploc3
* - location of pickups
*/
void ploc3()
{
	locOFp[0] = crack + 1;
	locOFp[1] = crack + crachv + 1;
	locOFp[2] = crack - crachv + 1;
}

/* cloc3
* - location of creatures (start)
* - direction of creatures (start)
*/
void cloc3()
{
	int w = 70;
	
	for (int i = 0; i < ctot / 2; i++)
	{
		locOFc[i] = 283 + i * 2 * w;
		dirOFc[i] = 's';
	}
	int n = 0;
	for (int i = ctot / 2; i < ctot; i++)
	{
		locOFc[i] = 282 + n * 2 * w + w;
		dirOFc[i] = 's';
		n++;
	}
}

/* printboard3 (lvl2)
* - prints the board with all edges and creatures
* - houses the dimensions of the board
* - returns true if loses
*/
bool printboard3(bool open)
{
	int h = 20;
	int w = 70;
	int fin = w * h;
	char board[1400 + 1];

	crackloclvl3(w, h);
	ploc3();
	crackplace(crack, crachv);
	outside(w, fin, board);
	printcrack(open, board);
	inside3(board, w);

	return afterin3(board, w, fin);
}

/* afterin3
* - finishes printboard after inside walls are filled in
* - returns true if loses
*/
bool afterin3(char board[], int w, int fin)
{
	bool end = false;

	pickingup(board, ps, locOFp, ptot, bombs);
	printp3(board);
	printb3(board);
	printc3(board, w);
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

/* nxtlvl3
* - returns if move to next level from human.h
*/
bool nxtlvl3() { return nextlvl(crack, crachv); }

/* breset3
* - resets the positions of the bombs for the next level
*/
void breset3()
{
	for (int k = 0; k < 100; k++)
	{
		locOFb[k] = '\0';
	}
}

/* callhturn3
* - calls hturn with the appropriate arguments
*/
void callhturn3() { hturn(bombs, locOFb, bnum); }

void printp3(char board[])
{
	for (int k = 0; k < ptot; k++)
	{
		if (ps[k])
		{
			board[locOFp[k]] = P;
		}
	}
}

void printc3(char board[], int w)
{
	for (int j = 0; j < ctot; j++)
	{
		moving(board, w, locOFc[j], dirOFc[j]);

		cbomb(locOFc[j], w, crack, crachv, locOFb);

		board[locOFc[j]] = C;
	}
}

void printb3(char board[])
{
	for (int i = 0; i < 100; i++)
	{
		if (locOFb[i] != '\0')
		{
			board[locOFb[i]] = B;
		}
	}
}

void bombconv3(int bombs2) { bombs = bombs2; }

void bkeep4() { bombconv4(bombs); }