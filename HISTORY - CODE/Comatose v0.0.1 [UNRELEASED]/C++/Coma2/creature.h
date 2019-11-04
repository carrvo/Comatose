#ifndef CREATURE_H
#define CREATURE_H

extern bool turn(char boader[], int w, int loc, char direction);
extern void onemove(char boader[], int w, int& loc, char& direction);
extern void moving(char boader[], int w, int& loc, char& direction);
extern void cbomb(int& loc, int w, int crack, int crachv, int locOFb[]);
extern void cbombB(int& loc, int w, int locOFb[], bool openning);
extern bool opening();
extern void openreset();

#endif