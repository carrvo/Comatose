#include "Windows.h"
#include "creature.h"
#include "human.h"
#include "BasicBoard.h"
#include "lvl2.h"
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

void outside(int w, int fin, char boarder[]);
void printcrack(bool open, char boarder[]);
void cracklocBasic(int w);
bool printboard(bool open);
bool afterin(char board[], int w, int fin);
bool nxtlvl();
void seeboard(char board[], int w, int fin, int bombs);
void breset();
void callhturn();
void printp(char board[]);
void printc(char board[], int w);
void printb(char board[]);
void bkeep2();
void crackplace(int crac, int crahv);

static int locOFc[3] = { 562, 984, 633 };
static char dirOFc[3] = { 'w', 's', 'w' };
static int ctot = 3;

static int locOFp[1] = { 1010 };
static bool ps[1] = { true };
static int ptot = 1;

static int bombs = 0;
static int locOFb[100];
static int bnum = 0;

static int crack = 0;
static int crachv = 0; //1 for vertical, w for horizontal

/* outside
* - turns the outside edge of the character array to BD
* and the rest to E
*/
void outside(int w, int fin, char boarder[])
{
	for (int k = 0; k < fin; k++)
	{
		boarder[k] = E;
	}
	
	for (int i = 0; i < w; i++)
	{
		boarder[i] = BD;
	}
	for (int i = fin; i > fin - w; i--)
	{
		boarder[i] = BD;
	}
	for (int i = 0; i < fin; i += w)
	{
		boarder[i] = BD;
	}
	for (int i = w - 1; i <= fin; i += w)
	{
		boarder[i] = BD;
	}
}

/* printcrack
* - adds in the crack as three CE
*/
void printcrack(bool open, char boarder[])
{
	if (!open)
	{
		boarder[crack] = CE;
		boarder[crack - crachv] = CE;
		boarder[crack + crachv] = CE;
	}
	else
	{
		boarder[crack] = E;
		boarder[crack - crachv] = E;
		boarder[crack + crachv] = E;
	}
}

void cracklocBasic(int w)
{
	crack = w / 2;
	crachv = 1;
}

/* printboard
* - prints the board with all edges and creatures
* - houses the dimensions of the board
* - returns true if loses
*/
bool printboard(bool open)
{
	int h = 20;
	int w = 70;
	int fin = w * h;
	char board[1400 + 1];

	cracklocBasic(w);
	outside(w, fin, board);
	printcrack(open, board);

	return afterin(board, w, fin);
}

/* afterin
* - finishes printboard after inside walls are filled in
* - returns true if loses
*/
bool afterin(char board[], int w, int fin)
{
	bool end = false;

	pickingup(board, ps, locOFp, ptot, bombs);
	printp(board);
	printb(board);
	printc(board, w);
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

/* nxtlvl
* - returns if move to next level from human.h
*/
bool nxtlvl() { return nextlvl(crack, crachv); }

/* seeboard
* - prints board to screen
* - prints inventory
*/
void seeboard(char board[], int w, int fin, int bombs)
{
	setvbuf(stdout, NULL, _IOFBF, 2000);
	
	int n = 1;
	for (int i = 0; i < fin; i++)
	{
		cout << board[i];

		if (n == w)
		{
			cout << '\n';
			n = 1;
		}
		else n++;
	}
	cout << "BOMBS: " << bombs << '\n' << '\n';
	cout << endl;

	setvbuf(stdout, NULL, _IOLBF, 100);
}

/* breset
* - resets the positions of the bombs for the next level
*/
void breset()
{
	for (int k = 0; k < 100; k++)
	{
		locOFb[k] = '\0';
	}
}

/* callhturn
* - calls hturn with the appropriate arguments
*/
void callhturn() { hturn(bombs, locOFb, bnum); }

void printp(char board[])
{
	for (int k = 0; k < ptot; k++)
	{
		if (ps[k])
		{
			board[locOFp[k]] = P;
		}
	}
}

void printc(char board[], int w)
{
	for (int j = 0; j < ctot; j++)
	{
		moving(board, w, locOFc[j], dirOFc[j]);

		cbomb(locOFc[j], w, crack, crachv, locOFb);

		board[locOFc[j]] = C;
	}
}

void printb(char board[])
{
	for (int i = 0; i < 100; i++)
	{
		if (locOFb[i] != '\0')
		{
			board[locOFb[i]] = B;
		}
	}
}

void bkeep2() { bombconv2(bombs); }

void crackplace(int crac, int crahv) { crack = crac; crachv = crahv; }