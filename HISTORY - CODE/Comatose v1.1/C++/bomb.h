#pragma once

#include "symbol.h"

class board;

class bomb
{
	public: CNT* bombs;
	private: PVINT bloc; //max 100
	private: SYMBOLS boarder;

	public: bomb(CNT* b, SYMBOLS boardd);
	public: ~bomb();

	public: void printb(board boardd);

	public: bool plantbomb(char c, whole locOFh);

	public: PVINT loc();
};
