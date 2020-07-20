#include "main.h"

using namespace std;
using namespace irrklang;

int mousex = 0;
int mousey = 0;

bool leftclick;
bool leftclick_flag;
bool rightclick;
bool rightclick_flag;

int fps = 60;
float fpsMult = 60.0f / (float)fps;
int framerate = 1000 / fps;

void setFps(int newfps) {
	fps = newfps;
	fpsMult = 60.0f / (float)fps;
	framerate = 1000 / fps;
}

//char homeDirectory[100] = "C:/Users/Admin/Documents/Visual Studio 2015/Sigma/assets/textures";
//char homeDirectory[100] = "../assets/textures";
char homeDirectory[100] = "assets/textures";

int intelLevel = 10300;

// button testBtn;

HWND windowHandle = NULL;

int const PUZZLESCREEN = 0;
int const INTELSCREEN = 1;
int const WAREFFORTSCREEN = 2;
int const LETTERSCREEN = 3;
int const DAYSCREEN = 4;
int const HOMESCREEN = 5;
int const SPLASHSCREEN = 6;
int const CUTSCENE = 7;
int const CHOOSESCREEN = 8;
int const OPTIONSSCREEN = 9;
int const FREEPLAYSCREEN = 10;
int const CREDITS = 11;
int const LOADINGSCREEN = 12;

int screen = LOADINGSCREEN;
int nextScreen = screen;
int lastScreen = HOMESCREEN;

bool freeplayUnlocked = FALSE;

bool helpText = TRUE;

int intelSpendLimit = 800;
int intelOverspend = 0;
bool discoveredFlag = FALSE;

bool spaceFlag = false;

bool messageActive = FALSE;
int messageAnim = 0;
button messageBox;
button closeMessage;
button messageYes;
button messageNo;
int messageChoice = -1;
int messageType = 0;
char messageText[512];

void showMessage(char inputText[512]) {
	messageDown.play(FALSE);
	messageActive = TRUE;
	strcpy_s(messageText, 512, inputText);
	messageType = 0;
}

void showOptionMessage(char inputText[512]) {
	messageDown.play(FALSE);
	messageActive = TRUE;
	strcpy_s(messageText, 512, inputText);
	messageType = 1;
}

void hideMessage() {
	messageUp.play(FALSE);
	messageActive = FALSE;
}

int getMessageChoice() {
	int retval = messageChoice;
	messageChoice = -1;
	return retval;
}

bool checkActiveWindow() {
	if (GetActiveWindow() == windowHandle) {
		return true;
	}
	else {
		return false;
	}
}

int day = 0;

int maxDay = 20;
void nextDay() {
	day += 1;
	if (day == 1) {
		initDayScreen("England, 1944");
		nextScreen = CUTSCENE;
	}
//	else if (day > 1 && day <= 4) {
//		initLetterScreen();
//		nextScreen = LETTERSCREEN;
//	}
	else {
		/*
		char dayString[100];
		_itoa_s(maxDay + 1 - day, dayString, 10);
		if (day == maxDay) {
			strcat_s(dayString, 100, " day remaining");
		}
		else {
			strcat_s(dayString, 100, " days remaining");
		}
		*/
		initDayScreen("");
		nextScreen = DAYSCREEN;
	}
	if (day >= 16) {
		if (!checkActive("Overlord") && !checkActive("Tiger") && !checkActive("Neptune")) {
//			day = maxDay + 1;
			initDayScreen("");
			nextScreen = DAYSCREEN;
		}
	}
	if (day == maxDay + 1) {
		if (warEffort >= 0.66) {
			freeplayUnlocked = TRUE;
			saveGame();
		}
	}
}

char randLetter() {
	return 'a' + rand() % 26;
}

float warEffort = 0.0;

void resetGame() {
	warEffort = 0.0;
	day = 0;
	intelSpendLimit = 800;
	intelOverspend = 0;
	intelLevel = 900;
	levelCount = 0;
	curLetter = 0;
	for (int i = 0; i < 10; i++) {
		operationList[i].reset();
	}
	initTutorialManager();
	initStoryManager();
	initPuzzleScreen();
	initLetterScreen();
	nextDay();
	perfectGame = TRUE;
	codesBroken = 0;

	startingOp = 0;
	bodyguardComplete = FALSE;
	pointblankComplete = FALSE;
	gambitComplete = FALSE;
	winningCheck = FALSE;
}

int saveTimer = 0;
void saveGame() {
	saveTimer = 60 * 3;
	ofstream outfile;
	if (steamEnabled) {
		outfile.open("assets/savegame.sav");
	}
	else {
		outfile.open("../assets/savegame.sav");
	}
	outfile << fullscreenFlag << ":fullscreenflag" << endl;
	outfile << globalVolume << ":globalVolume" << endl;
	outfile << helpText << ":helpText" << endl;
	outfile << day << ":day" << endl;
	outfile << levelCount << ":levelCount" << endl;
	outfile << intelLevel << ":intelLevel" << endl;
	outfile << warEffort << ":warEffort" << endl;
	outfile << freeplayUnlocked << ":freeplayUnlocked" << endl;
	outfile << perfectGame << ":perfectGame" << endl;
	outfile << codesBroken << ":codesBroken" << endl;
	outfile << startingOp << ":startingOp" << endl;
	outfile << bodyguardComplete << ":bodyguardComplete" << endl;
	outfile << pointblankComplete << ":pointblankComplete" << endl;
	outfile << gambitComplete << ":gambitComplete" << endl;
	outfile << winningCheck << ":winningCheck" << endl;
	for (int i = 0; i < 8; i++) {
		outfile << operationList[i].currentIntel << ":" << operationList[i].name << endl;
	}
	outfile.close();
}

void loadGame() {
	char saveDirectory[100];
	if (steamEnabled) {
		strcpy_s(saveDirectory, "assets/savegame.sav");
	}
	else {
		strcpy_s(saveDirectory, "../assets/savegame.sav");
	}
	std::ifstream infile(saveDirectory);
	std::string line;
	char curLine[1000];
	int lineCount = 0;
	while (std::getline(infile, line))
	{
		strcpy_s(curLine, 1000, line.c_str());

		//		printf(curLine);
		//		printf("\n");

		char* token;

		if (lineCount == 0) {
			fullscreenFlag = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 1) {
			globalVolume = atof(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 2) {
			helpText = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 3) {
			day = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 4) {
			levelCount = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 5) {
			intelLevel = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 6) {
			warEffort = atof(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 7) {
			freeplayUnlocked = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 8) {
			perfectGame = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 9) {
			codesBroken = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 10) {
			startingOp = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 11) {
			bodyguardComplete = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 12) {
			pointblankComplete = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 13) {
			gambitComplete = atoi(strtok_s(curLine, ":", &token));
		}
		if (lineCount == 14) {
			winningCheck = atoi(strtok_s(curLine, ":", &token));
		}

		if (lineCount >= 15) {
			operationList[lineCount - 15].currentIntel = atoi(strtok_s(curLine, ":", &token));
			if (operationList[lineCount - 15].currentIntel == operationList[lineCount - 15].requiredIntel) {
				operationList[lineCount - 15].completed = TRUE;
			}
		}

		lineCount += 1;
	}

	initTutorialManager();
	initStoryManager();
	initOptionsScreen();

	if (day >= 1) {
		day -= 1;
		nextDay();
		lastScreen = nextScreen;
//		screen = SPLASHSCREEN;
//		nextScreen = screen;
	}
	else {
		lastScreen = HOMESCREEN;
//		screen = SPLASHSCREEN;
//		nextScreen = screen;
	}
}

void draw()
{
	render();
}

void update(int value)
{
	glutTimerFunc(framerate, update, 0);

	if (!fullscreenFlag) {
		resizeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glutReshapeFunc(resizeWindow);
	}
	else {
		glutReshapeFunc(NULL);
	}

//	printf("UPDATE");

	POINT mousepos;
	GetCursorPos(&mousepos);
	mousepos.x -= glutGet((GLenum)GLUT_WINDOW_X);
	mousepos.y -= glutGet((GLenum)GLUT_WINDOW_Y);
	mousepos.x -= screenshiftx;
	mousepos.y -= screenshifty;
	mousex = mousepos.x / screenmultx;
	mousey = mousepos.y / screenmulty;

//	printf("%i, %i\n", mousex, mousey);

	leftclick = FALSE;
	if ((GetKeyState(VK_LBUTTON) & 0x100) == 0)
	{
		leftclick_flag = FALSE;
	}
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && leftclick_flag == FALSE)
	{
		leftclick_flag = TRUE;
		leftclick = TRUE;
	}

	rightclick = FALSE;
	if ((GetKeyState(VK_RBUTTON) & 0x100) == 0)
	{
		rightclick_flag = FALSE;
	}
	if ((GetKeyState(VK_RBUTTON) & 0x100) != 0 && rightclick_flag == FALSE)
	{
		rightclick_flag = TRUE;
		rightclick = TRUE;
	}

	if (screen == SPLASHSCREEN) {
		manageSplashScreen();
	}
	else if (screen == CREDITS) {
		manageCredits();
	}

	if (nextScreen == HOMESCREEN || screen == HOMESCREEN || screen == OPTIONSSCREEN) {
		moveRotors();
	}

	manageAudio();

	manageShake();

	if (!checkActiveWindow())
	{
		rightclick = FALSE;
		leftclick = FALSE;
	}
	else {
		if (screen == WAREFFORTSCREEN) {
			moveWeRotors();
		}
		if (fadeValue <= 0.0) {
			if (messageAnim > 0) {
				if (messageType == 0) {
					if (closeMessage.mouseOver()) {
						if (!closeMessage.hover) {
							tick1.play(FALSE);
						}
						closeMessage.hover = TRUE;
						if (leftclick) {
							bulbPickup.play(FALSE);
							closeMessage.hover = FALSE;
							hideMessage();
						}
					}
					else {
						closeMessage.hover = FALSE;
					}
				}
				else {
					if (messageNo.mouseOver()) {
						if (!messageNo.hover) {
							tick1.play(FALSE);
						}
						messageNo.hover = TRUE;
						if (leftclick) {
							messageChoice = 1;
							bulbPickup.play(FALSE);
							messageNo.hover = FALSE;
							hideMessage();
						}
					}
					else {
						messageNo.hover = FALSE;
					}
					if (messageYes.mouseOver()) {
						if (!messageYes.hover) {
							tick1.play(FALSE);
						}
						messageYes.hover = TRUE;
						if (leftclick) {
							messageChoice = 0;
							bulbPickup.play(FALSE);
							messageYes.hover = FALSE;
							hideMessage();
						}
					}
					else {
						messageYes.hover = FALSE;
					}
				}
			}
			manageTutorial();
			if (screen == INTELSCREEN) {
				manageIntelScreen();
			}
			else if (screen == PUZZLESCREEN) {
				managePuzzleScreen();
			}
			else if (screen == WAREFFORTSCREEN) {
				manageWarEffortScreen();
			}
			else if (screen == LETTERSCREEN) {
				manageLetterScreen();
			}
			else if (screen == HOMESCREEN) {
				manageHomeScreen();
			}
			else if (screen == CUTSCENE) {
				manageCutScene();
			}
			else if (screen == CHOOSESCREEN) {
				manageChooseScreen();
			}
			else if (screen == OPTIONSSCREEN) {
				manageOptionsScreen();
			}
			else if (screen == FREEPLAYSCREEN) {
				manageFreePlayScreen();
			}
			else if (screen == DAYSCREEN) {
				manageDayScreen();
			}
		}
		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			if (screen != HOMESCREEN && screen != OPTIONSSCREEN && screen != SPLASHSCREEN && screen != FREEPLAYSCREEN && screen != LOADINGSCREEN) {
				lastScreen = screen;
				nextScreen = HOMESCREEN;
			}
		}
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
/*
			if (screen == HOMESCREEN) {
				initSplashScreen();
				nextScreen = SPLASHSCREEN;
			}
			if (spaceFlag) {
				spaceFlag = false;
				if (fps == 60) {
					setFps(12);
				}
				else {
					setFps(60);
				}
			}
			*/
		}
		else {
			spaceFlag = true;
		}
	}

	manageSparks();

	draw();

}

void loadEverything() {
	initPuzzleScreen();
	initIntelScreen();
	incLoad();
	initWarEffortScreen(5234);
	initLetterScreen();
	incLoad();
	initHomeScreen();
	initSplashScreen();
	incLoad();
	initChooseScreen();
	nextDay();
	incLoad();
	resetGame();
	initCutScene();
	incLoad();
	loadCutSceneImages();
	initAudioManager();
	incLoad();
	initFreePlayScreen();

	loadGame();

	incLoad();

	/*
	initTutorialManager();
	initStoryManager();
	initOptionsScreen();

	if (day >= 1) {
	day -= 1;
	nextDay();
	lastScreen = nextScreen;
	screen = SPLASHSCREEN;

	//		screen = CUTSCENE;
	//		day = maxDay + 1;
	//		initCutScene();

	nextScreen = screen;
	}
	else {
	lastScreen = HOMESCREEN;
	screen = SPLASHSCREEN;
	nextScreen = screen;
	}
	*/

	//	printf("\nCHECK:\n %i, %i, %i\n \n", day, levelCount, lastScreen);

	messageAnim = 0;
	messageBox = button("messageBox", 0, 0, renderx, rendery, messageBoxImg, messageBoxImg, messageBoxImg);
	messageBox.active = FALSE;
	closeMessage = button("closeMessage", 820, 400, 64, 64, buttonOff, buttonOn, buttonOff);
	messageYes = button("messageYes", 480 - 32, 360, 64, 64, buttonOff, buttonOn, buttonOff);
	messageNo = button("messageNo", renderx - 480 - 32, 360, 64, 64, buttonOff, buttonOn, buttonOff);

	screen = SPLASHSCREEN;
	nextScreen = SPLASHSCREEN;
	fadeValue = 0.0f;

	if (fullscreenFlag) {
		oldWindowx = windowx;
		oldWindowy = windowy;
		resizeWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
		fullscreenFlag = TRUE;
		glutFullScreenToggle();
	}
	else {
		windowx = oldWindowx;
		windowy = oldWindowy;
		fullscreenFlag = FALSE;
		resizeWindow(windowx, windowy);
	}

}

int main(int argc, char** argv)
{

	if (argc >= 2) {
		steamEnabled = FALSE;
	}

	initSteamManager();

	if (!steamEnabled) {
		strcpy_s(homeDirectory, "../assets/textures");
	}

//	bool isOverlayLoaded = SteamUtils()->IsOverlayEnabled();
//	printf("Overlay loaded: %i\n", isOverlayLoaded);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	windowx = renderx;
	windowy = rendery;
	glutInitWindowSize(windowx, windowy);
	glutCreateWindow("The Ultra Code");

	// Hide console window
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutDisplayFunc(draw);
	glutTimerFunc(framerate, update, 0);
//	glutReshapeFunc(resizeWindow);

	srand(static_cast <unsigned> (time(NULL)));

	intelLevel = 900;

	initRenderer(windowx, windowy);

//	thread loadThread (loadEverything);
	loadEverything();

	setFps(fps);

//	char buff[FILENAME_MAX];
//	_getcwd(buff, FILENAME_MAX);
//	printf(buff);

	incLoad();

	windowHandle = FindWindow(NULL, "The Ultra Code");

	//	initInterface();

	glutMainLoop();

	exit(0);

	return 0;
}