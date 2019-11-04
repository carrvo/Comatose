#pragma once

#include "symbol.h"
#include <functional>

class board;

using  INSIDE = std::function<void (CMAX, CMAX, board)>;

static MAX locOFwall[901];
static CNT nwall = 0;

class insides
{
	public: insides();
	public: ~insides();

	public: static void setbasic(CMAX w, CMAX h, board boardd);
	public: static void inside2(CMAX w, CMAX h, board boardd);
	public: static void inside3(CMAX w, CMAX h, board boardd);
	public: static void inside4(CMAX w, CMAX h, board boardd);
	public: static void inside5(CMAX w, CMAX h, board boardd);
	public: static void crackBOSS(MAX* crack);
	public: static void insideBOSS(CMAX w, CMAX h, board boardd);
};
