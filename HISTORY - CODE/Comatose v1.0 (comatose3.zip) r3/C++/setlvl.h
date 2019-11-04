#pragma once

#include "symbol.h"
#include "board.h"
#include "lvlchange.h"

static lvlchange m;
class BOSS;

class setlvl
{
	public: setlvl();
	public: ~setlvl();

	public: bool basic(CNT* Bombs, board& Board);
	public: bool level2(CNT* Bombs, board& Board);
	public: bool level3(CNT* Bombs, board& Board);
	public: bool level4(CNT* Bombs, WALL& Board);
	public: bool level5(CNT* Bombs, board& Board);
	public: bool levelB(CNT* Bombs, BOSS& Board);

	private: void ploc3(VINT& locOFp, board& Board);
	private: void cloc3(CMAX ctot, vector<creature>& C, board& Board);
	private: void ploc4(CMAX w, VINT& locOFp);
	private: static bool cloc4(CMAX w, vector<creature>* C, board& Board);
	private: void cloc0(vector<creature>& C, board& Board);
	private: static void lvl4creature(CMAX w, vector<creature>* C, board& Board);
	private: void ploc5(CMAX w, CMAX h, VINT& ploc);
	private: void cloc5(vector<creature>& C, board& Board);

	public: static int main(); //comatose
};
