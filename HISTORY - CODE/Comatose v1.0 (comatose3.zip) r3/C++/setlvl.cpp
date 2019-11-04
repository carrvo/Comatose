#include "setlvl.h"
#include "BOSS.h"

setlvl::setlvl()
{}

setlvl::~setlvl()
{}

bool setlvl::basic(CNT* Bombs, board& Board)
{
	m.stdonee();
	bomb B(Bombs, Board.Boarder());
	human H(1000, arrow::U);
	VINT ploc;
	ploc.clear();
	ploc.push_back(1010);
	pickup P(ploc);
	vector<creature> C;
	C.clear();
	C.push_back(creature(562, arrow::U, Board.Boarder()));
	C.push_back(creature(984, arrow::D, Board.Boarder()));
	C.push_back(creature(633, arrow::U, Board.Boarder()));
	Board.setCCthis(&C);

	return m.calllvl(Board, P, *Bombs, H, B);
}

bool setlvl::level2(CNT* Bombs, board& Board)
{
	m.stdonee();
	bomb B(Bombs, Board.Boarder());
	human H(1000, arrow::U);
	VINT ploc;
	ploc.clear();
	ploc.push_back(425);
	pickup P(ploc);
	vector<creature> C;
	C.clear();
	C.push_back(creature(561, arrow::U, Board.Boarder()));
	C.push_back(creature(631, arrow::U, Board.Boarder()));
	C.push_back(creature(701, arrow::U, Board.Boarder()));
	C.push_back(creature(562, arrow::U, Board.Boarder()));
	C.push_back(creature(563, arrow::U, Board.Boarder()));
	C.push_back(creature(632, arrow::U, Board.Boarder()));
	C.push_back(creature(633, arrow::U, Board.Boarder()));
	C.push_back(creature(702, arrow::U, Board.Boarder()));
	C.push_back(creature(703, arrow::U, Board.Boarder()));
	C.push_back(creature(204, arrow::L, Board.Boarder()));
	Board.setCCthis(&C);

	return m.calllvl(Board, P, *Bombs, H, B);
}

/* ploc3
* - location of pickups
*/
void setlvl::ploc3(VINT& locOFp, board& Board)
{
	locOFp.clear();
	locOFp.push_back(Board.crack + 1);
	locOFp.push_back(Board.crack + Board.crachv + 1);
	locOFp.push_back(Board.crack - Board.crachv + 1);
}

/* cloc3
* - location of creatures (start)
* - direction of creatures (start)
*/
void setlvl::cloc3(CMAX ctot, vector<creature>& C, board& Board)
{
	C.clear();
	MAX w = 70;

	for (CNT i = 0; i < ctot / 2; i++)
	{
		C.push_back(creature(283 + i * 2 * w, arrow::D, Board.Boarder()));
	}
	CNT n = 0;
	for (CNT i = ctot / 2; i < ctot; i++)
	{
		C.push_back(creature(282 + n * 2 * w + w, arrow::D, Board.Boarder()));
		n++;
	}
}

bool setlvl::level3(CNT* Bombs, board& Board)
{
	m.stdonee();
	bomb B(Bombs, Board.Boarder());
	human H(990, arrow::U);
	VINT ploc;
	ploc.clear();
	ploc3(ploc, Board);
	pickup P(ploc);
	vector<creature> C;
	whole cnum = 12;
	cloc3(cnum, C, Board);
	Board.setCCthis(&C);

	return m.calllvl(Board, P, *Bombs, H, B);
}

/* ploc4
* - location of pickups
*/
void setlvl::ploc4(CMAX w, VINT& locOFp)
{
	locOFp.clear();
	MAX t = w / 2 + 5 * w;
	for (CNT i = 1; i < 5; i++)
	{
		for (CNT j = 1; j < 5; j++)
		{
			locOFp.push_back(t + i + j * w);
		}
	}
}

static bool slow = false;

/* cloc4
* - location of creatures (start)
* - direction of creatures (start)
*/
bool setlvl::cloc4(CMAX w, vector<creature>* C, board& Board)
{
	if (C->at(0).loc == 0)
	{
		whole Not[25];
		MAX t = w / 2 + 5 * w;
		CNT n2 = 0;
		{
			for (CNT i = 0; i < 5; i++)
			{
				for (CNT j = 0; j < 5; j++)
				{
					Not[n2] = t + i * w + j + w;
					n2++;
				}
			}
		}

		C->clear();

		CNT k = 0;
		for (CNT i = 0; i < 15; i++)
		{
			for (CNT j = 0; j < w - 10; j++)
			{
				t = 3 * w + i * w + 5 + j;
				bool isNot = true;
				if (Not[k] == t)
				{
					isNot = false;
					if (k != 25) k++;
				}
				if (isNot) C->push_back(creature(t, arrow::U, Board.Boarder()));
			}
		}
		slow = true;

		CNT e = 2;
		for (CNT v = 1; v < C->size(); v += e)
		{
			C->erase(C->begin()+v);
			v--;
			e++;
			if (e > 3) e = 1;
			if (v % w - 10 == 0) v++;
		}
		return false;
	}
	return true;
}

void setlvl::cloc0(vector<creature>& C, board& Board)
{
	C.clear();
	MAX w = 70;
	MAX t = w / 2 + 5 * w;
	C.push_back(creature(t + w + 1, arrow::R, Board.Boarder()));

	for (CNT w = 0; w < 901; w++)
	{
		locOFwall[w] = 0;
	}
}

void setlvl::lvl4creature(CMAX w, vector<creature>* C, board& Board)
{
	while (!m.donee() && cloc4(w, C, Board));
}

bool setlvl::level4(CNT* Bombs, WALL& Board)
{
	m.stdonee();
	bomb B(Bombs, Board.Boarder());
	human H(1025, arrow::U);
	VINT ploc;
	ploc4(Board.w, ploc);
	pickup P(ploc);
	vector<creature> C;
	C.resize(901, creature(0, arrow::U, Board.Boarder()));
	Board.setCCthis(&C);
	cloc0(C, Board);
	thread l4C(lvl4creature, ref(Board.w), &C, ref(Board));

	bool tmp = m.calllvlcwall(Board, P, *Bombs, H, B, &slow);
	l4C.join();
	return tmp;
}

/* ploc5
* - location of pickups
*/
void setlvl::ploc5(CMAX w, CMAX h, VINT& ploc)
{
	ploc.clear();
	CNT k = 0;
	for (CNT i = 1; i < h; i += 2)
	{
		if (h - 4 < i)
		{
			i++;
			k -= 6;
		}
		for (CNT j = 1; j < w; j += 5)
		{
			ploc.push_back(i * w + j + k);
		}
		k += 3;
		if (5 < k) k -= 5;
		if (i > 15) k = 0;
	}
	for (CNT j = 1; j < w; j += 5)
	{
		ploc.push_back((h - 1) * w + j + k);
	}
}

/* cloc5
* - location of creatures (start)
* - direction of creatures (start)
*/
void setlvl::cloc5(vector<creature>& C, board& Board)
{
	C.clear();
	MAX w = 70;
	MAX h = 20;
	MAX t = w / 2 + h / 2 * w;

	C.push_back(creature(t - w, arrow::L, Board.Boarder()));
	C.push_back(creature(t - w, arrow::U, Board.Boarder()));
	C.push_back(creature(t - w, arrow::R, Board.Boarder()));
	C.push_back(creature(t, arrow::L, Board.Boarder()));
	C.push_back(creature(t, arrow::R, Board.Boarder()));
	C.push_back(creature(t + w, arrow::L, Board.Boarder()));
	C.push_back(creature(t + w, arrow::D, Board.Boarder()));
}

bool setlvl::level5(CNT* Bombs, board& Board)
{
	m.stdonee();
	bomb B(Bombs, Board.Boarder());
	human H(1025, arrow::U);
	VINT ploc;
	ploc5(Board.w, Board.h, ploc);
	pickup P(ploc);
	vector<creature> C;
	cloc5(C, Board);
	Board.setCCthis(&C);

	return m.calllvl(Board, P, *Bombs, H, B);
}

static CNT nc = 0;
static MAX timing = 4;

bool setlvl::levelB(CNT* Bombs, BOSS& Board)
{
	m.stdonee();
	bomb B(Bombs, Board.Boarder());
	human H(890, arrow::U);
	VINT ploc;
	ploc.clear();
	ploc.push_back(0);
	pickup P(ploc);
	vector<creature> C;
	vector<creatureR> CR;
	MAX tot = 50;
	Board.setCCthis(&C);

	return Board.calllvlBOSS(P, *Bombs, H, B, &CR, nc, timing, tot);
}

int main() //comatose
{
start:
	CNT Bombs = 0;
	setlvl L;
	lvlchange::stfast();
	m.stgmover();
	bool over = m.gmover();
	m.beginning();


	if (!over)
	{
		board base(35, true, insides::setbasic);
		base.makesize();
		creature::stopening();

		over = L.basic(&Bombs, base);
	}

	if (!over)
	{
		board lvl2(35, true, insides::inside2);
		lvl2.makesize();
		creature::stopening();

		over = L.level2(&Bombs, lvl2);
	}

	if (!over)
	{
		board lvl3(700, false, insides::inside3);
		lvl3.makesize();
		creature::stopening();

		over = L.level3(&Bombs, lvl3);
	}

	if (!over)
	{
		WALL lvl4(699, false, insides::inside4);
		lvl4.makesize();
		creature::stopening();

		over = L.level4(&Bombs, lvl4);
	}

	if (!over)
	{
		board lvl5(735, false, insides::inside5);
		lvl5.makesize();
		creature::stopening();

		over = L.level5(&Bombs, lvl5);
	}

	if (!over)
	{
		whole smile[9];
		insides::crackBOSS(smile);
		BOSS boss(smile, insides::insideBOSS);
		boss.makesize();

		m.speach();
		cin.ignore();

		creature::stopening();

		over = L.levelB(&Bombs, boss);
	}

	bool won = false;
	if (!over)
	{
		cout << "Fredrick wakes up!!";
		won = true;
		cin.ignore();
	}
	if (!won)
	{
		cout << "To exit press enter. To retry press anything else." << flush;
		char c = '\0';
		c = _getch();
		if ('\r' != c) goto start;
	}

	//cin.ignore();
	return 0;
}
