#pragma once

#include "symbol.h"

class pickup
{
	public: VINT ploc_; //max 141

	public: pickup(const VINT& ploc);
	public: ~pickup();

	public: void printp(SYMBOLS board);

	public: void pickingup(CNT& bombs, const whole& locOFh);
};

