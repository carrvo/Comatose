#include "lvlchange.h"
#include "BOSS.h"

bool* d;
bool* g;

lvlchange::lvlchange()
	: done(false), gameover(false), skip(false)
{
	d = &done;
	g = &gameover;
}


lvlchange::~lvlchange()
{
}

void lvlchange::story()
{
	vector<string> line;
	line.push_back("Meet Fredrick:");
	line.push_back("Fredrick has always loved action movies with lots of explosions!");
	line.push_back("Fredrick also loves video games!");
	line.push_back("Fredrick has a good life until one day...");
	line.push_back("while his mother is driving him to school a drunk driver causes an accident.");
	line.push_back("As a result Fredrick has gone into a coma. Will he ever wake up again?");
	line.push_back("");
	line.push_back("Help Fredrick to wake up from his coma!");
	line.push_back("Complete each level and then defeat CLOWN !");

	MAX d = 100;
	MAX e = 10 * d;
	MAX len = 0;
	CNT l = 0;

	for (CNT i = 0; i < line.size(); i++)
	{
		len = line.at(i).length();
		for (l = 0; l < len; l++)
		{
			cout << line.at(i).at(l) << flush;
			if (!skp()) Sleep(d);
		}
		if (!skp()) Sleep(e);
		cout << endl;
	}

	Sleep(e);
	cout << endl;
}

void lvlchange::legend()
{
	vector<string> line;
	line.push_back("LEGEND:");
	line.push_back("F - Fredrick (you)");
	line.push_back("C - creature - if you run into one game over");
	line.push_back("B - bomb - can kill creatures or you");
	line.push_back("P - package of bombs - run into in order to get bombs");
	line.push_back("X - wall - if you run into it game over");
	line.push_back("* - crack in wall - detonate a bomb beside then run into to complete level");
	line.push_back("");
	line.push_back("CONTROLS:");
	line.push_back("w = up");
	line.push_back("s = down");
	line.push_back("a = left");
	line.push_back("d = right");
	line.push_back("space = lay a bomb (B)");
	line.push_back("f = speed up/slow down");
	line.push_back("");
	line.push_back("Press enter after completing a level to proceed to the next level.");

	MAX d = 100;
	MAX e = 10 * d;
	MAX len = 0;
	CNT l = 0;
	ofstream legend;
	legend.open("LEGEND.txt");

	for (CNT i = 0; i < line.size(); i++)
	{
		len = line.at(i).length();
		for (l = 0; l < len; l++)
		{
			cout << line.at(i).at(l) << flush;
			legend.put(line.at(i).at(l));
			if (!skp()) Sleep(d);
		}
		if (!skp()) Sleep(e);
		cout << endl;
		legend << endl;
	}

	cout << endl;
	cout << "You may open LEGEND.txt to view the legend and controls whenever you wish.\n";
	cout << "This will NOT pause the game.\n";
	cout << "Press enter to start.";
	cout << endl;

	Sleep(e);

	legend.close();
}

void lvlchange::speach()
{
	string clown = "CLOWN: Can you beat my SMILE ?";
	MAX d = 100;
	MAX e = 10 * d;
	MAX len = 0;
	CNT l = 0;

	len = clown.length();
	for (l = 0; l < len; l++)
	{
		cout << clown.at(l) << flush;
		Sleep(d);
	}
	Sleep(e);
	cout << endl;
}

void lvlchange::introduction(lvlchange* m)
{
	cin.ignore();
	m->chskp();
}

static bool first = true;
void lvlchange::beginning()
{
	thread start(introduction, this);
	cout << "To skip press enter.\n" << endl;
	story();
	legend();
	if (skip && first) cin.ignore();
	start.join();
	first = false;
}

bool lvlchange::calllvl(board& boardd, pickup& P, CNT& bombs, human& H, bomb& B)
{
	if (!gameover)
	{
		thread lvl(level, boardd, P, bombs, H, B);
		hmove(H, bombs, B);
		lvl.join();
	}
	return gameover;
}

bool lvlchange::calllvlcwall(WALL& boardd, pickup& P, CNT& bombs, human& H, bomb& B, bool* slow)
{
	if (!gameover)
	{
		thread lvl(levelcwall, boardd, P, bombs, H, B, slow);
		hmove(H, bombs, B);
		lvl.join();
	}
	return gameover;
}

void lvlchange::hmove(human& H, CNT& bombs, bomb& B)
{
	while (!done)
	{
		H.hturn(bombs, B);
	}
}

void lvlchange::level(board& boardd, pickup& P, CNT& bombs, human& H, bomb& B)
{
	while (!*d)
	{
		if (!boardd.printboard(P, bombs, H, B))
		{
			if (boardd.nxtlvl())
			{
				*d = true;
			}
		}
		else
		{
			*d = true;
			*g = true;
		}
	}
}

void lvlchange::levelcwall(WALL& boardd, pickup& P, CNT& bombs, human& H, bomb& B, bool* slow)
{
	PVINT WALL = PVINT(new VINT);
	WALL->clear();
	while (!*d)
	{
		if (!boardd.printboard(P, bombs, H, B, WALL, slow))
		{
			if (boardd.nxtlvl())
			{
				*d = true;
			}
		}
		else
		{
			*d = true;
			*g = true;
		}
	}
}

void lvlchange::levelBOSS(BOSS& boardd, pickup& P, CNT& bombs, human& H, bomb& B, vector<creatureR>* CCRthis, CNT& nc, MAX& timing, MAX& tot)
{
	while (!*d)
	{
		if (!boardd.printboardBOSS(P, bombs, H, B, CCRthis, nc, timing, tot))
		{
			if (boardd.nxtlvlBOSS())
			{
				*d = true;
			}
		}
		else
		{
			*d = true;
			*g = true;
		}
	}
}

bool lvlchange::donee()
{
	return done;
}

bool lvlchange::gmover()
{
	return gameover;
}

bool lvlchange::skp()
{
	return skip;
}

bool lvlchange::fast()
{
	return fast_;
}

bool lvlchange::findonee()
{
	done = true;
	return done;
}

bool lvlchange::fingmover()
{
	gameover = true;
	return gameover;
}

bool lvlchange::chskp()
{
	skip = !skip;
	return skip;
}

bool lvlchange::chfast()
{
	fast_ = !fast_;
	return fast_;
}

bool lvlchange::stdonee()
{
	done = false;
	return done;
}

bool lvlchange::stgmover()
{
	gameover = false;
	return gameover;
}

bool lvlchange::stfast()
{
	fast_ = false;
	return fast_;
}