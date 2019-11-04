#ifndef BASICBOARD_H
#define BASICBOARD_H

extern void outside(int w, int fin, char boarder[]);
extern void printcrack(bool open, char boarder[]);
extern void cracklocBasic(int w);
extern bool printboard(bool open);
extern bool afterin(char board[], int w, int fin);
extern bool nxtlvl();
extern void seeboard(char board[], int w, int fin, int bombs);
extern void breset();
extern void callhturn();
extern void printp(char board[]);
extern void printc(char board[], int w);
extern void printb(char board[]);
extern void bkeep2();
extern void crackplace(int crac, int crahv);

const char C = 'C';
const char P = 'P';
const char BD = 'X';
const char E = ' ';
const char CE = '*';
const char B = 'B';

#endif