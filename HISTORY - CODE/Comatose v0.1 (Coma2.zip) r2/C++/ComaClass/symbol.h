#pragma once
#include "Windows.h"
#include <vector>
#include <memory>
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

enum class symbol : char { C, P, BD, E, CE, B, F };
enum class arrow : char { U, D, R, L, BAD };

class symbols
{
	private: symbol sym_;

	public: symbols(symbol sym);
	public: symbols(char c);
	public: ~symbols();
	public: symbol& sym();
	public: char to() const;
	public: symbol& from(char c);
	public: symbol& operator = (char c);
	public: bool operator == (const symbol sym) const;
	public: bool operator != (const symbol sym) const;
	public: static arrow ar(char c);
};

using SYMVECT = vector<symbols>;
using SYMBOLS = shared_ptr<SYMVECT>;

using VINT = vector<int>;
using PVINT = shared_ptr<VINT>;

using whole = unsigned int;
//Convience for showing purpose
using MAX = whole;
using CMAX = const MAX&;//for w & h
using CNT = whole;//count