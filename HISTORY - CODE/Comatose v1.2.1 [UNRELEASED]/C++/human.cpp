#include "human.h"
#include "lvlchange.h"


human::human(whole locSt, arrow dirSt)
{
	locOFhh = locSt;
	locOFh = &locOFhh;
	dirOFhh = dirSt;
	dirOFh = &dirOFhh;
	dead = false;
}


human::~human()
{
}

/* hstraight
* - moves human
*/
void human::hstraight(CMAX w)
{
	switch (*dirOFh)
	{
	case arrow::U:
		*locOFh -= w;
		break;
	case arrow::D:
		*locOFh += w;
		break;
	case arrow::L:
		*locOFh -= 1;
		break;
	case arrow::R:
		*locOFh += 1;
		break;
    case arrow::BAD:
        break; //WARNING
	}
}

/* printh
* - moves human
* - returns false if loses
* - prints location to board
*/
bool human::printh(SYMVECT& board, CMAX w)
{
	hstraight(w);
	bool dead = false;
	//if ( board.size() < static_cast<whole>(*locOFh) ) return true;
	dead = board[*locOFh] != symbol::E && board[*locOFh] != symbol::P;
	if (!dead) board[*locOFh] = symbol::F;
	return !dead;
}

/* hturn
* - waits for input
* - if E then plants a bomb
* - else changes direction of human
*/
void human::hturn(CNT& bombs, bomb& B)
{
	char c = '\0';
	c = _getch();
	if (!B.plantbomb(c, *locOFh))
	{
		arrow check = symbols::ar(c);
		if (arrow::BAD != check) *dirOFh = check;
	}
	if ('f' == c) lvlchange::chfast();
}

/* nextlvll
* - returns true if move to next level
*/
bool human::nextlvll(MAX crack, MAX crachv)
{
	if (locOFhh == crack || locOFhh == crack + crachv || locOFhh == crack - crachv)
	{
		if (creature::opening())
		{
			return true;
		}
	}
	return false;
}
