#include "bomb.h"
#include "board.h"

bomb::bomb(CNT* b, SYMBOLS boardd)
{
	boarder = boardd;
	bombs = b;
	bloc = PVINT(new VINT);
	bloc->clear();
}


bomb::~bomb()
{
}

void bomb::printb(board boardd)
{
	for (CNT i = 0; i < bloc->size(); i++)
	{
		if ('\0' != bloc->at(i))
		{
			boardd.Boarder(bloc->at(i), symbol::B);
		}
	}
}

/* plantbomb
* - if input is @E then plants a bomb at human's location
* - returns true if it plants a bomb (even if fail to plant)
*/
bool bomb::plantbomb(char c, whole locOFh)
{
	if (c != ' ')
	{
		return false;
	}
	if (*bombs > 0)
	{
		*bombs -= 1;
		bloc->push_back(locOFh);
	}
	return true;
}

PVINT bomb::loc()
{
	return bloc;
}