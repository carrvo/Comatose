#pragma once

#include "creature.h"
#include "bomb.h"
#include "pickup.h"
#include <conio.h>  //allows for _getch() which is same as cin.get() without the buffer

static whole locOFhh;
static arrow dirOFhh;

class human
{
	public: whole* locOFh;
	public: arrow* dirOFh;
	public: bool dead;

	public: human(whole locSt, arrow dirSt);
	public: ~human();

	private: void hstraight(CMAX w);

	public: bool printh(SYMVECT& board, CMAX w);

	public: void hturn(whole& bombs, bomb& B);

	public: static bool nextlvll(MAX crack, MAX crachv);
};
