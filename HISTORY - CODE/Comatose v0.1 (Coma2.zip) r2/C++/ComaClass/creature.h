#pragma once

#include "symbol.h"

static bool *opens = new bool;

class creature
{
	protected: SYMBOLS boarder;
	public: whole loc;
	public: arrow direction;

	public: creature(whole location, arrow dir, SYMBOLS board);
	public: ~creature();

	protected: bool turn(CMAX w);

	protected: virtual void onemove(CMAX w);

	public: void moving(CMAX w);

	public: void cbomb(CMAX w, MAX crack, MAX crachv, PVINT locOFb);
	public: whole bombwall(CMAX w, MAX crack, MAX crachv, PVINT locOFb);

	public: static bool opening();
	public: static bool finopening();
	public: static bool stopening();
};

class creatureR : public creature
{
	public: creatureR(whole location, arrow dir, SYMBOLS board);
	public: ~creatureR();

	private: void onemove(CMAX w) override;
};