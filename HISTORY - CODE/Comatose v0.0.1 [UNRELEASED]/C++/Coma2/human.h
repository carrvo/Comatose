#ifndef HUMAN_H
#define HUMAN_H

extern void hturn(int& bombs, int* locOFb, int& bnum);
extern void pickingup(char board[], bool* ps, int locOFp[], int ptot, int& bombs);
extern void hstraight(int w);
extern bool nextlvl(int crack, int crachv);
extern bool printh(char board[], int w);
extern bool plantbomb(char c, int& bombs, int* locOFb, int& bnum);
extern void hstart(int locSt, char dirSt);

#endif