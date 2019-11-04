#include "pickup.h"

pickup::pickup(const VINT& ploc)
{
	ploc_.clear();
	for (CNT w = 0; w < ploc.size(); w++)
	{
		ploc_.push_back(ploc.at(w));
	}
}

pickup::~pickup()
{
}

void pickup::printp(SYMBOLS board)
{
	for (CNT k = 0; k < ploc_.size(); k++)
	{
		//if ( board.size() < static_cast<whole>(ploc_.at(k)) )
		{
			board->at(ploc_.at(k)) = symbol::P;
		}
	}
}

/* pickingup
* - human lands on pickup
*/
void pickup::pickingup(CNT& bombs, const whole& locOFh)
{
	for (CNT i = 0; i < ploc_.size(); i++)
	{
		if (locOFh == ploc_.at(i))
		{
			bombs += 10;
			ploc_.erase(ploc_.begin()+i);
			return;
		}
	}
	/*for (vector<int>::iterator it = ploc_.begin(); it < ploc_.end(); it++)
	{
	if (locOFh == *it)
	{
	bombs += 10;
	ploc_.erase(it);
	return;
	}
	}*/
}
