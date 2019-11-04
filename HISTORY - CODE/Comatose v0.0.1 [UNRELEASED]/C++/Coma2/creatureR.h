#ifndef CREATURER_H
#define CREATURER_H

extern bool turnR(char boader[], int w, int loc, char direction);
extern void onemoveR(char boader[], int w, int& loc, char& direction);
extern void movingR(char boader[], int w, int& loc, char& direction);
extern void cbombR(int& loc, int w, int crack, int crachv, int locOFb[]);
extern void cbombBR(int& loc, int w, int locOFb[], bool openning);
extern bool openingR();
extern void openresetR();

#endif