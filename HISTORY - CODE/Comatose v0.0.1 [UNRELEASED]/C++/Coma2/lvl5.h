#ifndef LVL5_H
#define LVL5_H

extern void crackloclvl5(int w, int h);
extern void inside5(char board[], int w, int h);
extern void ploc5(int w, int h);
extern void pset();
extern void cloc5();
extern bool printboard5(bool open);
extern bool afterin5(char board[], int w, int fin);
extern bool nxtlvl5();
extern void breset5();
extern void callhturn5();
extern void printp5(char board[]);
extern void printc5(char board[], int w);
extern void printb5(char board[]);
extern void bombconv5(int bombs2);
extern void bkeepB();

#endif