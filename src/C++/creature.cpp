#include "creature.h"

creature::creature(whole location, arrow dir, SYMBOLS board)
	: loc(location),
	direction(dir),
	boarder(board)
{}

creatureR::creatureR(whole location, arrow dir, SYMBOLS board)
	: creature(location, dir, board)
{}

creature::~creature()
{}

creatureR::~creatureR()
{}

bool check(const SYMVECT& boader, const MAX& x)
{
	return (boader[x] == symbol::BD || boader[x] == symbol::CE || boader[x] == symbol::C || x > boader.size());
}

/* turn
* - determines if the position that the creature would move into is an edge (true)
*/
bool creature::turn(const MAX& w) //what if goes off boader?
{
	MAX x;
	switch (direction)
	{
	case arrow::U:
		x = loc - w;
		if (check(*boarder, x)) return true;
		return false;
	case arrow::D:
		x = loc + w;
		if (check(*boarder, x)) return true;
		return false;
	case arrow::L:
		x = loc - 1;
		if (check(*boarder, x)) return true;
		return false;
	case arrow::R:
		x = loc + 1;
		if (check(*boarder, x)) return true;
		return false;
	default:
		return false;
	}
}

/*onemove
* - if turn then the direction is changed clockwise (negative angle)
* - if !turn then changes the loc (location) to position would move into
*/
void creature::onemove(CMAX w)
{
	if (turn(w))
	{
		switch (direction)
		{
		case arrow::U:
			direction = arrow::R;
			return;
		case arrow::D:
			direction = arrow::L;
			return;
		case arrow::L:
			direction = arrow::U;
			return;
		case arrow::R:
			direction = arrow::D;
			return;
        case arrow::BAD:
            direction = arrow::U; //WARNING
            return;
		}
	}
	else
	{
		switch (direction)
		{
		case arrow::U:
			loc -= w;
			return;
		case arrow::D:
			loc += w;
			return;
		case arrow::L:
			loc -= 1;
			return;
		case arrow::R:
			loc += 1;
			return;
        case arrow::BAD:
            return; //WARNING
		}
	}
}

void creatureR::onemove(CMAX w)
{
	if (turn(w))
	{
		switch (direction)
		{
		case arrow::U:
			direction = arrow::L;
			return;
		case arrow::D:
			direction = arrow::R;
			return;
		case arrow::L:
			direction = arrow::D;
			return;
		case arrow::R:
			direction = arrow::U;
			return;
        case arrow::BAD:
            direction = arrow::U; //WARNING
            return;
		}
	}
	else
	{
		switch (direction)
		{
		case arrow::U:
			loc -= w;
			return;
		case arrow::D:
			loc += w;
			return;
		case arrow::L:
			loc -= 1;
			return;
		case arrow::R:
			loc += 1;
			return;
        case arrow::BAD:
            return; //WARNING
		}
	}
}

/* moving
* - when loc (location) changes
* - ask if there is a B (bomb)
* - if B then move to corner (upper left @ position 0)
* - only one loc change
*/
void creature::moving(CMAX w)
{
	if (loc != 0)
	{
		arrow dir, d;
		d = direction;
		do
		{
			dir = direction;
			onemove(w);
		} while (dir != direction && d != direction);
	}
}

/* cbomb
* - ask if there is a B (bomb)
* - if B then move to corner (upper left @ position 0)
*/
void creature::cbomb(CMAX w, MAX crack, MAX crachv, PVINT locOFb)
{
	const MAX tot = locOFb->size();
	for (CNT i = 0; i < tot; i++)
	{
		if (loc == locOFb->at(i))
		{
			MAX v = 0;
			if (crachv == 1) v = w;
			else if (crachv == w) v = 1;
			if (loc == crack + v || loc == crack + crachv + v || loc == crack - crachv + v
				|| loc == crack - v || loc == crack + crachv - v || loc == crack - crachv - v
				|| loc == crack + crachv * 2 || loc == crack - crachv * 2)
			{
				finopening();
			}
			locOFb->erase(locOFb->begin() + i);
			loc = 0;
			break;
		}
	}
}

whole creature::bombwall(CMAX w, MAX crack, MAX crachv, PVINT locOFb)
{
	const int tmp = loc;
	cbomb(w, crack, crachv, locOFb);
	int t = tmp - loc;
	if (0 > t) t *= -1;
	return t;
}

/* opening
* - function for telling if crack is open
*/
bool creature::opening() { return *opens; }
bool creature::finopening() { *opens = true; return *opens; }
bool creature::stopening() { *opens = false; return *opens; }
