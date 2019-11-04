#include "Windows.h"
#include "BasicBoard.h"
#include "creature.h"
#include "human.h"
#include "lvl2.h"
#include "lvl3.h"
#include "lvl4.h"
#include "lvl5.h"
#include "boss.h"
#include <thread>
#include <fstream>
#include <iostream>
using namespace std;

void hmove();
void basic();
void hmove2();
void level2();
void hmove3();
void level3();
void hmove4();
void level4();
void hmove5();
void level5();
void hmoveB();
void levelB();
void story();
void legend();
void speach();
void introduction();

static bool done = false;
static bool gameover = false;
static bool skip = false;

int main() //comatose
{
	thread start(introduction);
	cout << "To skip press enter.\n" << endl;
	story();
	legend();
	if (skip) cin.ignore();
	start.join();
	
	thread base(basic);
	hmove();
	base.join();

	if (!gameover)
	{
		done = false;
		openreset();

		thread lvl2(level2);
		hmove2();
		lvl2.join();
	}

	if (!gameover)
	{
		done = false;
		openreset();

		thread lvl3(level3);
		hmove3();
		lvl3.join();
	}

	if (!gameover)
	{
		done = false;
		openreset();

		thread lvl4(level4);
		hmove4();
		lvl4.join();
	}

	if (!gameover)
	{
		done = false;
		openreset();

		thread lvl5(level5);
		hmove5();
		lvl5.join();
	}

	if (!gameover)
	{
		speach();
		cin.ignore();

		done = false;
		openreset();

		thread boss(levelB);
		hmoveB();
		boss.join();
	}

	if (!gameover)
	{
		cout << "Fredrick wakes up!!";
		cin.ignore();
	}

	//cin.ignore();
	return 0;
}

void hmove()
{
	while (!done)
	{
		callhturn();
	}
}

void basic()
{
	breset();
	hstart(1000, 'w');
	while (!done)
	{
		if (!printboard(opening()))
		{
			if (nxtlvl()) done = true;
		}
		else
		{
			done = true;
			gameover = true;
		}
	}
	bkeep2();
}

void hmove2()
{
	while (!done)
	{
		callhturn2();
	}
}

void level2()
{
	breset2();
	hstart(1000, 'w');
	while (!done)
	{
		if (!printboard2(opening()))
		{
			if (nxtlvl2()) done = true;
		}
		else
		{
			done = true;
			gameover = true;
		}
	}
	bkeep3();
}


void hmove3()
{
	while (!done)
	{
		callhturn3();
	}
}

void level3()
{
	breset3();
	cloc3();
	hstart(990, 'w');
	while (!done)
	{
		if (!printboard3(opening()))
		{
			if (nxtlvl3()) done = true;
		}
		else
		{
			done = true;
			gameover = true;
		}
	}
	bkeep4();
}

void hmove4()
{
	while (!done)
	{
		callhturn4();
	}
}

void level4()
{
	breset4();
	cloc0();
	hstart(1025, 'w');
	while (!done)
	{
		if (!printboard4(opening()))
		{
			if (nxtlvl4()) done = true;
		}
		else
		{
			done = true;
			gameover = true;
		}
	}
	bkeep5();
}

void hmove5()
{
	while (!done)
	{
		callhturn5();
	}
}

void level5()
{
	breset5();
	pset();
	cloc5();
	hstart(1025, 'w');
	while (!done)
	{
		if (!printboard5(opening()))
		{
			if (nxtlvl5()) done = true;
		}
		else
		{
			done = true;
			gameover = true;
		}
	}
	bkeepB();
}

void hmoveB()
{
	while (!done)
	{
		callhturnB();
	}
}

void levelB()
{
	bresetB();
	clocB();
	hstart(890, 'w');
	while (!done)
	{
		if (!printboardB(opening()))
		{
			if (nxtlvlB()) done = true;
		}
		else
		{
			done = true;
			gameover = true;
		}
	}
}

void story()
{
	string line[9];
	line[0] = "Meet Fredrick:";
	line[1] = "Fredrick has always loved action movies with lots of explosions!";
	line[2] = "Fredrick also loves video games!";
	line[3] = "Fredrick has a good life until one day...";
	line[4] = "while his mother is driving him to school a drunk driver causes an accident.";
	line[5] = "As a result Fredrick has gone into a coma. Will he ever wake up again?";
	line[6] = "";
	line[7] = "Help Fredrick to wake up from his coma!";
	line[8] = "Complete each level and then defeat CLOWN !";

	int d = 100;
	int e = 10 * d;
	int len = 0, l = 0;

	for (int i = 0; i < 9; i++)
	{
		len = line[i].length();
		for (l = 0; l < len; l++)
		{
			cout << line[i].at(l) << flush;
			if (!skip) Sleep(d);
		}
		if (!skip) Sleep(e);
		cout << endl;
	}

	Sleep(e);
	cout << endl;
}

void legend()
{
	string line[16];
	line[0] = "LEGEND:";
	line[1] = "F - Fredrick (you)";
	line[2] = "C - creature - if you run into one game over";
	line[3] = "B - bomb - can kill creatures or you";
	line[4] = "P - package of bombs - run into in order to get bombs";
	line[5] = "X - wall - if you run into it game over";
	line[6] = "* - crack in wall - detonate a bomb beside then run into to complete level";
	line[7] = "";
	line[8] = "CONTROLS:";
	line[9] = "w = up";
	line[10] = "s = down";
	line[11] = "a = left";
	line[12] = "d = right";
	line[13] = "space = lay a bomb (B)";
	line[14] = "";
	line[15] = "Press enter after completing a level to proceed to the next level.";

	int d = 100;
	int e = 10 * d;
	int len = 0, l = 0;
	ofstream legend;
	legend.open("LEGEND.txt");

	for (int i = 0; i < 15; i++)
	{
		len = line[i].length();
		for (l = 0; l < len; l++)
		{
			cout << line[i].at(l) << flush;
			legend.put(line[i].at(l));
			if (!skip) Sleep(d);
		}
		if (!skip) Sleep(e);
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

void speach()
{
	string clown = "CLOWN: Can you beat my SMILE ?";
	int d = 100;
	int e = 10 * d;
	int len = 0, l = 0;

	len = clown.length();
	for (l = 0; l < len; l++)
	{
		cout << clown.at(l) << flush;
		Sleep(d);
	}
	Sleep(e);
	cout << endl;
}

void introduction()
{
	cin.ignore();
	skip = true;
}