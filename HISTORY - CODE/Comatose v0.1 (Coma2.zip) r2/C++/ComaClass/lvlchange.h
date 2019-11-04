#pragma once

#include "board.h"
class BOSS;

static bool fast_ = false;

class lvlchange
{
	public: lvlchange();
	public: ~lvlchange();

	private: bool done;
	private: bool gameover;
	private: bool skip;

	private: void story();
	private: void legend();
	private: static void introduction(lvlchange* m);

	public: void speach();
	public: void beginning();

	public: bool calllvl(board& boardd, pickup& P, CNT& bombs, human& H, bomb& B);
	public: bool calllvlcwall(WALL& boardd, pickup& P, CNT& bombs, human& H, bomb& B, bool* slow);

	protected: void hmove(human& H, whole& bombs, bomb& B);
	protected: static void level(board& boardd, pickup& P, CNT& bombs, human& H, bomb& B);
	protected: static void levelcwall(WALL& boardd, pickup& P, CNT& bombs, human& H, bomb& B, bool* slow);
	protected: static void levelBOSS(BOSS& boardd, pickup& P, CNT& bombs, human& H, bomb& B, vector<creatureR>* CCRthis, CNT& nc, MAX& timing, MAX& tot);

	public: bool donee();
	public: bool gmover();
	public: bool skp();
	public: static bool fast();
	public: bool findonee();
	public: bool fingmover();
	public: bool chskp();
	public: static bool chfast(); //others should prob. be mkTrue
	public: bool stdonee();
	public: bool stgmover();
	public: static bool stfast();
};