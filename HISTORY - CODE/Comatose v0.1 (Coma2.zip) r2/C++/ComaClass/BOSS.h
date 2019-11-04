#pragma once
#include "board.h"
#include "lvlchange.h"

class BOSS : public board, public lvlchange
{
	public: static const MAX wBOSS = 65;
	public: static const MAX finBOSS = wBOSS * h;
	public: MAX* crBOSS;

	public: BOSS(MAX* cr, INSIDE in);
	public: ~BOSS();

	private: void outsideBOSS();
	private: void printcrackBOSS();

	public: bool printboardBOSS(pickup& P, CNT& bombs, human& H, bomb& B, vector<creatureR>* CCRthis, CNT& nc, MAX& timing, MAX& tot);
	public: bool nxtlvlBOSS();
	public: void seeboardBOSS(CNT& bombs);

	private: void cBOSSloc(vector<creature>& C);
	private: void cBOSSloc(vector<creatureR>& CR);
	private: void printcBOSS(vector<creatureR>* CCRthis, bomb& B, CNT& nc, MAX& timing, const MAX& total);

	private: bool completee();
	private: bool clandd(whole& loc);
	private: bool both(bool ret, bomb& BB, whole& loc, MAX& v);
	private: bool openningBOSS(whole loc, bomb& BB);

	public: bool calllvlBOSS(pickup& P, CNT& bombs, human& H, bomb& B, vector<creatureR>* CCRthis, CNT& nc, MAX& timing, MAX& tot);
};

