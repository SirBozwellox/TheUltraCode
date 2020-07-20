#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

extern char filename[100];

extern char acceptingStrings[20][20];
extern char rejectingStrings[20][20];
extern char testStrings[20][20];

char* createTestString(int testNum);

#endif
