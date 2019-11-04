#include "symbol.h"

symbols::symbols(symbol sym)
	: sym_(sym)
{}

symbols::symbols(char c)
{
	from(c);
}

symbols::~symbols()
{}

symbol& symbols::sym()
{
	return sym_;
}

char symbols::to() const
{
	switch (sym_)
	{
	case symbol::C:
		return 'C';
	case symbol::P:
		return 'P';
	case symbol::BD:
		return 'X';
	case symbol::E:
		return ' ';
	case symbol::CE:
		return '*';
	case symbol::B:
		return 'B';
	case symbol::F:
		return 'F';
	default:
		return ' ';
	}
}

symbol& symbols::from(char c)
{
	switch (c)
	{
	case 'C':
		sym_ = symbol::C;
		break;
	case 'P':
		sym_ = symbol::P;
		break;
	case 'X':
		sym_ = symbol::BD;
		break;
	case ' ':
		sym_ = symbol::E;
		break;
	case '*':
		sym_ = symbol::CE;
		break;
	case 'B':
		sym_ = symbol::B;
		break;
	case 'F':
		sym_ = symbol::F;
		break;
	default:
		sym_ = symbol::E;
		break;
	}
	return sym_;
}

symbol& symbols::operator = (char c)
{
	return from(c);
}

bool symbols::operator == (const symbol sym) const
{
	return sym == sym_;
}

bool symbols::operator != (const symbol sym) const
{
	return sym != sym_;
}

arrow symbols::ar(char c)
{
	switch (c)
	{
	case 'w':
		return arrow::U;
	case 's':
		return arrow::D;
	case 'd':
		return arrow::R;
	case 'a':
		return arrow::L;
	default:
		return arrow::BAD; //WARNING
	}
}
