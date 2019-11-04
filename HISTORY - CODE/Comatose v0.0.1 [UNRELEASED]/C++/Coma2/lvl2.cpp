#include "Windows.h"
#include "BasicBoard.h"
#include "creature.h"
#include "human.h"
#include "lvl3.h"
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

void crackloclvl2(int w);
void inside2(char board[], int w);
bool printboard2(bool open);
bool afterin2(char board[], int w, int fin);
bool nxtlvl2();
void breset2();
void callhturn2();
void printp2(char board[]);
void printc2(char board[], int w);
void printb2(char board[]);
void bombconv2(int bombs2);
void bkeep3();

static int locOFc[10] = { 561, 631, 701, 562, 563, 632, 633, 702, 703, 204 };
static char dirOFc[10] = { 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'a' };
static int ctot = 10;

static int locOFp[1] = { 425 };
static bool ps[1] = { true };
static int ptot = 1;

static int bombs = 0;
static int locOFb[100];
static int bnum = 0;

static int crack = 0;
static int crachv = 0; //1 for vertical, w for horizontal

void crackloclvl2(int w)
{
	crack = w / 2;
	crachv = 1;
}

void inside2(char board[], int w)
{
	for (int i = 0; i < 65; i++)
	{
		board[284 + i] = BD;
	}
}

/* printboard2 (lvl2)
* - prints the board with all edges and creatures
* - houses the dimensions of the board
* - returns true if loses
*/
bool printboard2(bool open)
{
	int h = 20;
	int w = 70;
	int fin = w * h;
	char board[1400 + 1];

	crackloclvl2(w);
	crackplace(crack, crachv);
	outside(w, fin, board);
	printcrack(open, board);
	inside2(board, w);

	return afterin2(board, w, fin);
}

/* afterin2
* - finishes printboard after inside walls are filled in
* - returns true if loses
*/
bool afterin2(char board[], int w, int fin)
{
	bool end = false;

	pickingup(board, ps, locOFp, ptot, bombs);
	printp2(board);
	printb2(board);
	printc2(board, w);
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

/* nxtlvl2
* - returns if move to next level from human.h
*/
bool nxtlvl2() { return nextlvl(crack, crachv); }

/* breset2
* - resets the positions of the bombs for the next level
*/
void breset2()
{
	for (int k = 0; k < 100; k++)
	{
		locOFb[k] = '\0';
	}
}

/* callhturn2
* - calls hturn with the appropriate arguments
*/
void callhturn2() { hturn(bombs, locOFb, bnum); }

void printp2(char board[])
{
	for (int k = 0; k < ptot; k++)
	{
		if (ps[k])
		{
			board[locOFp[k]] = P;
		}
	}
}

void printc2(char board[], int w)
{
	for (int j = 0; j < ctot; j++)
	{
		moving(board, w, locOFc[j], dirOFc[j]);

		cbomb(locOFc[j], w, crack, crachv, locOFb);

		board[locOFc[j]] = C;
	}
}

void printb2(char board[])
{
	for (int i = 0; i < 100; i++)
	{
		if (locOFb[i] != '\0')
		{
			board[locOFb[i]] = B;
		}
	}
}

void bombconv2(int bombs2) { bombs = bombs2; }

void bkeep3() { bombconv3(bombs); }