#ifndef LVL4_H
#define LVL4_H

extern void crackloclvl4(int w, int h);
extern void inside4(char board[], int w);
extern void ploc4(int w);
extern void cloc4(int w);
extern void cloc0();
extern bool printboard4(bool open);
extern bool afterin4(char board[], int w, int fin);
extern bool nxtlvl4();
extern void breset4();
extern void callhturn4();
extern void printp4(char board[]);
extern void printc4(char board[], int w);
extern void printb4(char board[]);
extern void bombconv4(int bombs2);
extern void bkeep5();

#endif