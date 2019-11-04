#include "board.h"
#include "lvlchange.h"

const MAX board::w;
const MAX board::h;
const MAX board::fin;

board::board(MAX cr, bool crhv, INSIDE in)
	: crack(cr),
	F(in),
	CCthis(nullptr)
{
	if (crhv) crachv = 1;//true = horizontal
	else crachv = w;//false = vertical

	boarder = SYMBOLS(new SYMVECT);
}

WALL::WALL(MAX cr, bool crhv, INSIDE in)
	: board(cr, crhv, in)
{}

board::board(INSIDE in, MAX w_alt)
	: crachv(w_alt),
	F(in),
	CCthis(nullptr)
{
	boarder = SYMBOLS(new SYMVECT);
}

board::~board()
{}

WALL::~WALL()
{}

void board::outside()
{
	for (CNT k = 0; k < fin; k++)
	{
		Boarder(k, symbol::E);
	}

	for (CNT i = 0; i < w; i++)
	{
		Boarder(i, symbol::BD);
	}
	for (CNT i = fin - 1; i > fin - w; i--)
	{
		Boarder(i, symbol::BD);
	}
	for (CNT i = 0; i < fin; i += w)
	{
		Boarder(i, symbol::BD);
	}
	for (CNT i = w - 1; i <= fin; i += w)
	{
		Boarder(i, symbol::BD);
	}
}

void board::printcrack()
{
	if (!creature::opening())
	{
		Boarder(crack, symbol::CE);
		Boarder(crack - crachv, symbol::CE);
		Boarder(crack + crachv, symbol::CE);
	}
	else
	{
		Boarder(crack, symbol::E);
		Boarder(crack - crachv, symbol::E);
		Boarder(crack + crachv, symbol::E);
	}
}

bool board::printboard(pickup& P, CNT& bombs, human& H, bomb& B)
{
	outside();
	printcrack();
	F(w, h, *this);

	P.pickingup(*B.bombs, *H.locOFh);
	P.printp(boarder);
	B.printb(*this);
	printc(B.loc());
	if (H.printh((*boarder), w))
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

bool WALL::printboard(pickup& P, CNT& bombs, human& H, bomb& B, PVINT locWall, bool* slow)
{
	outside();
	printcrack();
	F(w, h, *this);

	P.pickingup(*B.bombs, *H.locOFh);
	P.printp(Boarder());
	B.printb(*this);
	printWALL(locWall);
	printc(B.loc(), locWall);
	if (H.printh((*Boarder()), w))
	{
		seeboard(*B.bombs);
		if (*slow)
		{
			if (!lvlchange::fast()) Sleep(250);
			Sleep(250);
		}
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

void WALL::printWALL(PVINT WALL)
{
	for (CNT i = 0; i < WALL->size(); i++)
	{
		Boarder(WALL->at(i), symbol::BD);
	}
}

bool board::nxtlvl()
{
	return human::nextlvll(crack, crachv);
}

void board::seeboard(CNT& bombs)
{
	setvbuf(stdout, NULL, _IOFBF, 2000);

	CNT n = 1;
	for (CNT i = 0; i < fin; i++)
	{
		cout << Boarder(i).to();

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

void board::printc(PVINT locOFb)
{
	MAX tot = CCthis->size();
	for (CNT j = 0; j < tot; j++)
	{
		CCthis->at(j).moving(w);
		boarder;

		CCthis->at(j).cbomb(w, crack, crachv, locOFb);
		if (!CCthis->at(j).loc)
		{
			vector<creature>::iterator it;
			it = CCthis->begin();
			it += j;
			if (CCthis->end() > it)
				CCthis->erase(it);
			if (0 != j) j--;
		}

		else Boarder(CCthis->at(j).loc, symbol::C);
		tot = CCthis->size();
	}
}

void WALL::printc(PVINT locOFb, PVINT locWall)
{
	MAX tot = CCthis->size();
	for (CNT j = 0; j < tot; j++)
	{
		CCthis->at(j).moving(w);

		whole location;
		location = CCthis->at(j).bombwall(w, crack, crachv, locOFb);
		if (0 != location)
		{
			locWall->push_back(location);

			vector<creature>::iterator it;
			it = CCthis->begin();
			it += j;
			if (CCthis->end() > it)
				CCthis->erase(it);
			if (0 != j) j--;
		}

		else Boarder(CCthis->at(j).loc, symbol::C);
		tot = CCthis->size();
	}
}

void board::setCCthis(vector<creature>* pCCthis)
{
	CCthis = pCCthis;
}

void board::makesize()
{
	boarder->resize(fin, symbol::E);
}


SYMBOLS board::Boarder()
{
	return boarder;
}

symbols board::Boarder(whole place)
{
	return boarder->at(place);
}

SYMBOLS board::Boarder(whole place, symbol value)
{
	boarder->at(place) = value;
	return boarder;
}
