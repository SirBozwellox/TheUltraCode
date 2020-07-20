#ifndef PUZZLESCREEN_H_INCLUDED
#define PUZZLESCREEN_H_INCLUDED

extern graph Graph;

extern state placeState;

extern level currentLevel;

extern int placeEdge;
extern char placeEdgeType;

extern GLuint interfaceTex;
extern GLuint interfaceTexFront;
extern GLuint tape1;

extern char inputString[400];

extern bool firstEdgeActive;

extern float stepCounter;
extern float stepCounterReset;

extern int moveState;

extern bool running;

extern button messageBox;
extern button closeMessage;
extern char messageText[512];

extern int finishCounter;

extern bool solveFlag;

extern char descriptionBox[1000];
extern char descriptionDisplay[1000];
extern float descriptionCharCount;

extern bool freeplayMode;

extern int inputIndex;

extern button exitButton;

void toggleMessage(char inputText[512]);

void newDescription(char intext[1000]);

void initPuzzleScreen();
void managePuzzleScreen();
void drawPuzzleScreen();

#endif
