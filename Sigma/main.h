#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <irrKlang.h>
#include <sstream>
#include <GL/freeglut.h>
#include <fstream>
#include <SOIL.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <vector>
#include "dimensions_plus.h"
#include "renderer.h"
#include "interface.h"
#include "audioManager.h"
#include "graph.h"
#include "levelManager.h"
#include "puzzleScreen.h"
#include "intelScreen.h"
#include "warEffortScreen.h"
#include "letterScreen.h"
#include "storyManager.h"
#include "dayScreen.h"
#include "tutorialManager.h"
#include "homeScreen.h"
#include "splashScreen.h"
#include "cutscene.h"
#include "chooseScreen.h"
#include "optionsScreen.h"
#include "freePlayScreen.h"
#include "credits.h"
#include "steam/steam_api.h"
#include "steamManager.h"

extern int mousex;
extern int mousey;
extern bool leftclick;
extern bool leftclick_flag;
extern bool rightclick;
extern bool rightclick_flag;
extern char homeDirectory[100];

extern HWND windowHandle;

extern int intelLevel;

extern int const PUZZLESCREEN;
extern int const INTELSCREEN;
extern int const WAREFFORTSCREEN;
extern int const LETTERSCREEN;
extern int const DAYSCREEN;
extern int const HOMESCREEN;
extern int const SPLASHSCREEN;
extern int const CUTSCENE;
extern int const CHOOSESCREEN;
extern int const OPTIONSSCREEN;
extern int const FREEPLAYSCREEN;
extern int const CREDITS;
extern int const LOADINGSCREEN;

extern int screen;
extern int nextScreen;
extern int lastScreen;

extern bool freeplayUnlocked;

extern bool messageActive;
extern int messageAnim;
extern button messageBox;
extern button closeMessage;
extern button messageYes;
extern button messageNo;
extern int messageChoice;
extern int messageType;
extern char messageText[512];

void showMessage(char inputText[512]);
void showOptionMessage(char inputText[512]);
int getMessageChoice();
void hideMessage();

bool checkActiveWindow();

extern int day;
extern int maxDay;

extern bool helpText;

extern int intelSpendLimit;
extern int intelOverspend;
extern bool discoveredFlag;

void nextDay();

char randLetter();

void resetGame();

extern int saveTimer;
void saveGame();
void loadGame();

void update(int value);
void draw();

extern float warEffort;

// extern button testBtn;

#endif
