#include "BOSS.h"

const MAX BOSS::wBOSS;
const MAX BOSS::finBOSS;

BOSS::BOSS(MAX* cr, INSIDE in)
	: board(in, wBOSS), crBOSS(cr)
{
}

BOSS::~BOSS()
{
}

void BOSS::outsideBOSS()
{
	for (CNT k = 0; k < fin; k++)
	{
		Boarder(k, symbol::E);
	}

	for (CNT i = 0; i < wBOSS; i++)
	{
		Boarder(i, symbol::BD);
	}
	for (CNT i = finBOSS - 1; i > finBOSS - wBOSS; i--)
	{
		Boarder(i, symbol::BD);
	}
	for (CNT i = 0; i < finBOSS; i += wBOSS)
	{
		Boarder(i, symbol::BD);
	}
	for (CNT i = wBOSS - 1; i <= finBOSS; i += wBOSS)
	{
		Boarder(i, symbol::BD);
	}
}

void BOSS::printcrackBOSS()
{
	if (!creature::opening())
	{
		for (CNT i = 0; i < 9; i++)
		{
			Boarder(crBOSS[i], symbol::CE);
		}
	}
	else
	{
		for (CNT i = 0; i < 9; i++)
		{
			Boarder(crBOSS[i], symbol::E);
		}
	}
}

bool BOSS::printboardBOSS(pickup& P, CNT& bombs, human& H, bomb& B, vector<creatureR>* CCRthis, CNT& nc, MAX& timing, MAX& tot)
{
	outsideBOSS();
	printcrackBOSS();
	F(wBOSS, h, *this);

	P.pickingup(*B.bombs, *H.locOFh);
	P.printp(Boarder());
	B.printb(*this);
	printcBOSS(CCRthis, B, nc, timing, tot);
	if (H.printh((*Boarder()), wBOSS))
	{
		seeboard(*B.bombs);
	}
	else
	{
		cout << "Fredrick does not wake up." << endl;
		return true;
	}

	if (!lvlchange::fast()) Sleep(250);
	Sleep(250); //
	return false;
}

bool BOSS::nxtlvlBOSS()
{
	for (CNT i = 0; i < 9; i++)
	{
		if (human::nextlvll(crBOSS[i], crachv))
		{
			return true;
		}
	}
	return false;
}

/* cBOSSloc
* - location of creatures (start)
* - direction of creatures (start)
*/
void BOSS::cBOSSloc(vector<creature>& C)
{
	MAX t = wBOSS / 2;
	MAX u = h / 2;
	MAX m = u * wBOSS + t;
	C.push_back(creature(m, arrow::U, Boarder()));
}

void BOSS::cBOSSloc(vector<creatureR>& CR)
{
	MAX t = wBOSS / 2;
	MAX u = h / 2;
	MAX m = u * wBOSS + t;
	CR.push_back(creatureR(m, arrow::U, Boarder()));
}

void BOSS::printcBOSS(vector<creatureR>* CCRthis, bomb& B, CNT& nc, MAX& timing, const MAX& total)
{
	MAX size = CCthis->size();
	for (CNT j = 0; j < size; j++)
	{
		CCthis->at(j).moving(wBOSS);
		CCRthis->at(j).moving(wBOSS);

		bool opennings = false;
		opennings = openningBOSS(CCthis->at(j).loc, B);
		if (!opennings) opennings = openningBOSS(CCRthis->at(j).loc, B);
		if (opennings) creature::finopening();

		for (CNT f = 0; f < 9; f++)
		{
			CCthis->at(j).cbomb(w, crBOSS[f], crachv, B.loc());
			CCRthis->at(j).cbomb(w, crBOSS[f], crachv, B.loc());
		}

		if (!CCthis->at(j).loc || !CCRthis->at(j).loc)
		{
			vector<creature>::iterator it;
			vector<creatureR>::iterator itR;
			it = CCthis->begin();
			itR = CCRthis->begin();
			it += j;
			itR += j;
			if (CCthis->end() > it)
				CCthis->erase(it);
			if (CCRthis->end() > itR)
				CCRthis->erase(itR);
			if (0 != j) j--;
		}

		Boarder(CCthis->at(j).loc, symbol::C);
		Boarder(CCRthis->at(j).loc, symbol::C);
		size = CCthis->size();
	}

	nc++;
	if (nc > timing)
	{
		nc = 0;
		if (total > CCthis->size()) cBOSSloc(*CCthis);
		if (total > CCRthis->size()) cBOSSloc(*CCRthis);
	}
}

bool BOSS::completee()
{
	for (CNT j = 0; j < 9; j++)
	{
		if (Boarder(crBOSS[j] + crachv) != symbol::B || Boarder(crBOSS[j] - crachv) != symbol::B)
		{
			return false;
		}
	}
	return true;
}

bool BOSS::clandd(whole& loc)
{
	for (CNT j = 0; j < 9; j++)
	{
		if (loc == crBOSS[j] + crachv || loc == crBOSS[j] - crachv)
		{
			return true;
		}
	}
	return false;
}

bool BOSS::both(bool ret, bomb& BB, whole& loc, MAX& v)
{
	if (ret)
	{
		for (whole j = 0; j < 9; j++)
		{
			whole A = crBOSS[j] + crachv;
			whole B = crBOSS[j] - crachv;
			whole C = crBOSS[8] - v;
			whole D = crBOSS[7] + v;
			whole size = BB.loc()->size();
			for (CNT k = 0; k < size; k++)
			{
				whole ll = BB.loc()->at(k);
				if (ll == A || ll == B || ll == C || ll == D)
				{
					if (ll != loc)
					{
						BB.loc()->erase(BB.loc()->begin() + k);
						k--;
					}
				}
				size = BB.loc()->size();
			}
		}
	}
	return ret;
}

bool BOSS::openningBOSS(whole loc, bomb& BB)
{
	MAX v = 0;
	if (crachv == 1) v = wBOSS;
	else if (crachv == wBOSS) v = 1;

	bool cland = false, complete = true;

	complete = completee();
	if (complete && (Boarder(crBOSS[8] - v) != symbol::B || Boarder(crBOSS[7] + v) != symbol::B))
	{
		complete = false;
	}

	cland = clandd(loc);
	if (!cland && (loc == crBOSS[8] - v || loc == crBOSS[7] + v))
	{
		cland = true;
	}

	return both(cland && complete, BB, loc, v);
}

bool BOSS::calllvlBOSS(pickup& P, CNT& bombs, human& H, bomb& B, vector<creatureR>* CCRthis, CNT& nc, MAX& timing, MAX& tot)
{
	if (!gmover())
	{
		thread lvl(lvlchange::levelBOSS, ref(*this), ref(P), ref(bombs), ref(H), ref(B), CCRthis, ref(nc), ref(timing), ref(tot));
		hmove(H, bombs, B);
		lvl.join();
	}
	return gmover();
}
