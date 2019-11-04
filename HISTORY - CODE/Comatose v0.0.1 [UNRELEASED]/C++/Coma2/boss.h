#ifndef BOSS_H
#define BOSS_H

extern void crackloclvlB(int w, int h);
extern void insideB(char board[], int w, int h);
extern void clocB();
extern void printcrackB(bool open, char boarder[]);
extern bool printboardB(bool open);
extern bool afterinB(char board[], int w, int fin);
extern bool nxtlvlB();
extern void bresetB();
extern void callhturnB();
extern void printcB(char board[], int w);
extern void revive();
extern bool openning(int loc, int w, char board[]);
extern void printbB(char board[]);
extern void bombconvB(int bombs2);

#endif