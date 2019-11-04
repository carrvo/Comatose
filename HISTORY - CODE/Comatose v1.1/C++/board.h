#pragma once

#include "human.h"
#include "insides.h"

class board
{
	public: static const MAX w = 70;
	public: static const MAX h = 20;
	public: static const MAX fin = w * h;

	public: MAX crack;
	public: MAX crachv; //1 for vertical, w for horizontal (?)

	private: SYMBOLS boarder;
	protected: INSIDE F;
	protected: vector<creature>* CCthis;

	public: board(MAX cr, bool crhv, INSIDE in);
	public: board(INSIDE in, MAX w_alt);
	public: ~board();

	protected: void outside();

	protected: void printcrack();

	public: bool printboard(pickup& P, CNT& bombs, human& H, bomb& B);

	public: bool nxtlvl();

	public: void seeboard(CNT& bombs);

	protected: void printc(PVINT locOFb);

	public: void setCCthis(vector<creature>* pCCthis);

	public: void makesize();
	public: SYMBOLS Boarder();
	public: symbols Boarder(whole place);
	public: SYMBOLS Boarder(whole place, symbol value);
};

class WALL : public board
{
	public: WALL(MAX cr, bool crhv, INSIDE in);
	public: ~WALL();

public: bool printboard(pickup& P, CNT& bombs, human& H, bomb& B, PVINT locWall, bool* slow);
private: void printWALL(PVINT WALL);
private: void printc(PVINT locOFb, PVINT locWall);
};
