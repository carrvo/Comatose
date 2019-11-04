#include "insides.h"
#include "board.h"

insides::insides()
{}

insides::~insides()
{}

void insides::setbasic(CMAX w, CMAX h, board boardd)
{}

void insides::inside2(CMAX w, CMAX h, board boardd)
{
	for (CNT i = 0; i < 65; i++)
	{
		boardd.Boarder(284 + i, symbol::BD);
	}
}

void insides::inside3(CMAX w, CMAX h, board boardd)
{
	for (CNT i = 0; i < 14 * w; i += w)
	{
		boardd.Boarder(284 + w + i, symbol::BD);
	}
	boardd.Boarder(284 - 3 * w, symbol::BD);

	for (CNT i = 14 + w; i < 19 * w; i += w)
	{
		boardd.Boarder(i, symbol::BD);
	}
}

void insides::inside4(CMAX w, CMAX h, board boardd)
{
	MAX t = w / 2 + 5 * w;
	for (CNT i = 0; i < 6; i++)
	{
		boardd.Boarder(t + i, symbol::BD);
		boardd.Boarder(t + i * w, symbol::BD);
		boardd.Boarder(t + 5 * w + i, symbol::BD);
	}
	boardd.Boarder(t + 5 + w, symbol::BD);
	boardd.Boarder(t + 4 * w + 5, symbol::BD);

	for (CNT i = 0; i < 4; i++)
	{
		boardd.Boarder(t + 5 + w + 10 + w * i, symbol::BD);
	}

	for (CNT j = 0; j < nwall; j++)
	{
		boardd.Boarder(locOFwall[j], symbol::BD);
	}
}

void insides::inside5(CMAX w, CMAX h, board boardd)
{
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
			boardd.Boarder(i * w + j + k, symbol::BD);
		}
		k += 3;
		if (5 < k) k -= 5;
		if (i > 15) k = 0;
	}
}

static CNT cwall = 0;
static const MAX cwallm = 21;

void insides::crackBOSS(MAX* crack)
{
	MAX w = 65;
	MAX h = 20;
	MAX t = w / 2;
	MAX u = h / 2 + 1;
	crack[0] = u * w + t;
	CNT r = 0, n = 1;
	CNT s = 1;
	for (CNT i = 1; i < 5; i++)
	{
		if (n == 2)
		{
			r++;
			n = 0;
		}
		crack[s] = u * w + t + i - r * w;
		s++;
		crack[s] = u * w + t - i - r * w;
		s++;
		n++;
	}
}

void insides::insideBOSS(CMAX w, CMAX h, board boardd)
{
	MAX t = w / 2;
	MAX u = h / 2 - 3;
	boardd.Boarder(u * w + t - 2, symbol::BD);
	boardd.Boarder(u * w + t + 2, symbol::BD);

	boardd.Boarder((h - 2) * w + t, symbol::BD);
	boardd.Boarder((h - 3) * w + t, symbol::BD);

	if (cwall != 0)
	{
		boardd.Boarder((h - 7) * w + t + 1, symbol::BD);
		boardd.Boarder((h - 7) * w + t - 1, symbol::BD);
	}
	cwall++;
	if (cwall >= cwallm) cwall = 0;
}
