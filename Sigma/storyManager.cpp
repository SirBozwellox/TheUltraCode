#include "main.h"

//char letterDirectory[200] = "C:/Users/Admin/Documents/Visual Studio 2015/Sigma/assets/letters/";
//char letterDirectory[200] = "../assets/letters/";
char letterDirectory[200] = "assets/letters/";
char letterList[58][100] = {
	"letter1.txt",
	"letter2.txt",
	"letter3-1.txt",
	"letter3-2.txt",
	"letter4.txt",
	"letter5.txt",
	"letter6-1.txt",
	"letter6-2.txt",
	"letter6-3.txt",
	"letter6-4.txt",
	"letter7-1.txt",
	"letter7-2.txt",
	"letter8-1.txt",
	"letter8-2.txt",
	"letter8-3.txt",
	"letter9-1.txt",
	"letter9-2.txt",
	"letter10-1.txt",
	"letter10-2.txt",
	"letter11-1.txt",
	"letter11-2.txt",
	"letter12-1.txt",
	"letter12-2.txt",
	"letter12-3.txt",
	"letter12-4.txt",
	"letter12-5.txt",
	"letter12-6.txt",
	"letter12-7.txt",
	"letter12-8.txt",
	"letter13-1.txt",
	"letter13-2.txt",
	"letter14-1.txt",
	"letter14-2.txt",
	"letter14-3.txt",
	"letter15-1.txt",
	"letter15-2.txt",
	"letter16-1.txt",
	"letter16-2.txt",
	"letter16-3.txt",
	"letter16-4.txt",
	"letter17-1.txt",
	"letter17-2.txt",
	"letter17-3.txt",
	"letter17-4.txt",
	"letter17-5.txt",
	"letter17-6.txt",
	"letter18-1.txt",
	"letter18-2.txt",
	"letter18-3.txt",
	"letter18-4.txt",
	"letter19-1.txt",
	"letter19-2.txt",
	"letter19-3.txt",
	"letter19-4.txt",
	"letter20-1.txt",
	"letter20-2.txt",
	"letter20-4.txt",
	"letter20-5.txt",
};
int curLetter = 0;

char curLetterText[2000];
char letterAudioFile[100];

GLuint counter2;
GLuint intelLeftTex;

void loadLetterText(char filename[100]) {
	char finalDirectory[200];
	strcpy_s(finalDirectory, 200, letterDirectory);
	strcat_s(finalDirectory, 100, filename);

	printf("Loading text from ");
	printf(filename);
	printf("\n");

	strcpy_s(curLetterText, 2000, "");

	std::ifstream infile(finalDirectory);
	std::string line;
	char curLine[2000];
	int lineCount = 0;
	while (std::getline(infile, line))
	{
		if (lineCount == 0) {
			strcpy_s(letterAudioFile, 100, "vo/");
			strcat_s(letterAudioFile, 100, line.c_str());
		}
		if (lineCount > 2) {
			strcpy_s(curLine, 2000, line.c_str());
			strcat_s(curLetterText, 2000, curLine);
			strcat_s(curLetterText, 2000, "#");
		}
		lineCount += 1;
	}
	if (strlen(curLetterText) == 0) {
		strcpy_s(curLetterText, 2000, "No text data found");
	}
	letterAudio = sound(letterAudioFile);
	letterAudio.fadeSpeed = 0.05;
}

void operation::setRot() {
	tapeRot = ((rand() % 7) - 3) / 10.0;
}

operation::operation() {
	strcpy_s(name, "");
	startDay = 0;
	duration = 0;
	currentIntel = 0;
	requiredIntel = 0;
	temporaryIntel = 0;
	waitFor = -1;
	completed = FALSE;
	multiplier = 1.0;
	setRot();
}

operation::operation(char inname[100], int instartDay, int induration, int inrequiredIntel, int inwaitFor) {
	strcpy_s(name, inname);
	startDay = instartDay;
	duration = induration;
	requiredIntel = inrequiredIntel;
	currentIntel = 0;
	temporaryIntel = 0;
	waitFor = inwaitFor;
	completed = FALSE;
	multiplier = 1.0;
	setRot();
}

operation::operation(char inname[100], int instartDay, int induration, int inrequiredIntel, int inwaitFor, float inmult) {
	strcpy_s(name, inname);
	startDay = instartDay;
	duration = induration;
	requiredIntel = inrequiredIntel;
	currentIntel = 0;
	temporaryIntel = 0;
	waitFor = inwaitFor;
	completed = FALSE;
	multiplier = inmult;
	setRot();
}

operation::operation(char inname[100], int instartDay, int induration, int inrequiredIntel, int inwaitFor, float inmult, int inimage) {
	strcpy_s(name, inname);
	startDay = instartDay;
	duration = induration;
	requiredIntel = inrequiredIntel;
	currentIntel = 0;
	temporaryIntel = 0;
	waitFor = inwaitFor;
	completed = FALSE;
	multiplier = inmult;
	image = inimage;
	setRot();
}

void operation::reset() {
	currentIntel = 0;
	temporaryIntel = 0;
	completed = FALSE;
}

int tempDay;

void setDay(int inval) {
	tempDay = inval;
}

void operation::draw(int y) {
	glColor4f(0.0, 0.0, 0.0, 0.5);
	drawtext(name, 68 + 4, y + 4, 32, 32, 0.75);
	glColor4f(0.9, 0.9, 0.9, 1.0);
	drawtext(name, 68, y, 32, 32, 0.75);

	char tempText[100];

	_itoa_s(requiredIntel - temporaryIntel, tempText, 10);
	strcat_s(tempText, 100, " intel left");
	glColor4f(0.0, 0.0, 0.0, 0.5);
	drawtext(tempText, 420 + 4, y + 4, 32, 32, 0.75);
	glColor4f(0.9, 0.9, 0.9, 1.0);
	drawtext(tempText, 420, y, 32, 32, 0.75);

	_itoa_s((startDay + duration) - tempDay, tempText, 10);
	if ((startDay + duration) - tempDay == 1) {
		strcat_s(tempText, 100, " day left");
	}
	else {
		strcat_s(tempText, 100, " days left");
	}
	glColor4f(0.0, 0.0, 0.0, 0.5);
	drawtext(tempText, 968 + 4 - (getintsize((startDay + duration) - tempDay) * 24), y + 4, 32, 32, 0.75);
	glColor4f(0.9, 0.9, 0.9, 1.0);
	drawtext(tempText, 968 - (getintsize((startDay + duration) - tempDay) * 24), y, 32, 32, 0.75);

	int bulbNum = 20;
	for (int i = 0; i < bulbNum; i++) {
		int image = NULL;
		if (i < (currentIntel / (float)(requiredIntel)) * bulbNum) {
			image = bulb2;
		}
		else {
			if (i < (temporaryIntel / (float)(requiredIntel)) * bulbNum) {
				image = bulb3;
			}
			else {
				image = bulb1;
			}
		}
		placeimageeasy(image, 136 + (48 * i) + 10, y + 36 + 10, 72, 72, TRUE);
	}
}

void operation::draw2(int y) {

	glColor4f(1.0, 1.0, 1.0, 1.0);
	placeimagerotatecentre(this->image, 160, y + 80, 210 * 1.5, 60 * 1.5, tapeRot, true);
	placeimagerotatecentre(intelLeftTex, (renderx / 2.0) + 6, y + 32, 316 * 1.05, 94 * 1.05, 0.0, true);

	char tempText[100];

	_itoa_s(requiredIntel - temporaryIntel, tempText, 10);
	strcat_s(tempText, 100, " intel left");
//	glColor4f(0.0, 0.0, 0.0, 0.5);
//	drawtext(tempText, 420 + 4, y + 4, 32, 32, 0.75);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	drawtext_centre(tempText, renderx / 2.0, y + 20, 24, 24, 0.75);

	/*
	_itoa_s((startDay + duration) - tempDay, tempText, 10);
	if ((startDay + duration) - tempDay == 1) {
		strcat_s(tempText, 100, " day left");
	}
	else {
		strcat_s(tempText, 100, " days left");
	}
	glColor4f(0.0, 0.0, 0.0, 0.5);
	drawtext(tempText, 968 + 4 - (getintsize((startDay + duration) - tempDay) * 24), y + 4, 32, 32, 0.75);
	glColor4f(0.9, 0.9, 0.9, 1.0);
	drawtext(tempText, 968 - (getintsize((startDay + duration) - tempDay) * 24), y, 32, 32, 0.75);
	*/

	glColor4f(1.0, 1.0, 1.0, 1.0);
	placeimageeasy(counter2, renderx - 276, y + 30, 212, 100, true);

	glColor4f(0.0, 0.0, 0.0, 1.0);
	drawtext("Days left", renderx - 238, y + 42, 16, 16);

	char dayText[10];

	glColor3f(0.75, 0.75, 0.75);
	_itoa_s((startDay + duration) - tempDay, dayText, 10);
	drawtext(dayText, renderx - 214, y + 78, 54, 54, 1.0);

	glColor4f(1.0, 1.0, 1.0, 1.0);

	int bulbNum = 20;
	for (int i = 0; i < bulbNum; i++) {
		int image = NULL;
		if (i < (currentIntel / (float)(requiredIntel)) * bulbNum) {
			image = bulb2;
		}
		else {
			if (i < (temporaryIntel / (float)(requiredIntel)) * bulbNum) {
				image = bulb3;
			}
			else {
				image = bulb1;
			}
		}
		if (i % 2 == 0) {
			placeimageeasy(image, (renderx / 2) - 240 - 24 + (48 * (i / 2)), y + 34 + 18 + 10, 72, 72, TRUE);
			if (rand() % 1000 == 0 && image != bulb1) {
				createSparks((renderx / 2) - 240 - 24 + (48 * (i / 2)) + 36, y + 34 + 18 + 10 + 36, 20);
			}
		}
		else {
			placeimageeasy(image, (renderx / 2) - 240 - 24 + 24 + (48 * (i / 2)), y + 18 + 4 + 10, 72, 72, TRUE);
			if (rand() % 1000 == 0 && image != bulb1) {
				createSparks((renderx / 2) - 240 - 24 + 24 + (48 * (i / 2)) + 36, y + 4 + 18 + 10 + 36, 20);
			}
		}
	}
}

int startingOp = 0;
bool bodyguardComplete = FALSE;
bool pointblankComplete = FALSE;
bool gambitComplete = FALSE;
bool winningCheck = FALSE;
int cueOperationIntro = -1;

GLuint operationTape[10];

void loadTapeImages() {
	if (startingOp == 0) {
		operationList[0].image = LoadTexture(homeDirectory, "tapeRoundup.png");
	}
	else {
		operationList[0].image = LoadTexture(homeDirectory, "tapeSledgehammer.png");
	}
	operationList[1].image = LoadTexture(homeDirectory, "tapeOverlord.png");
	operationList[2].image = LoadTexture(homeDirectory, "tapeFortitude.png");
	operationList[3].image = LoadTexture(homeDirectory, "tapeBodyguard.png");
	operationList[4].image = LoadTexture(homeDirectory, "tapePointblank.png");
	operationList[5].image = LoadTexture(homeDirectory, "tapeGambit.png");
	operationList[6].image = LoadTexture(homeDirectory, "tapeNeptune.png");
	operationList[7].image = LoadTexture(homeDirectory, "tapeTiger.png");
}

operation operationList[10]{
	operation("Sledgehammer", 3, 3, 2500, -1, 1.3),
	operation("Overlord", 6, 15, 20000, 0),
	operation("Fortitude", 4, 4, 3000, -1, 1.3),
	operation("Bodyguard", 7, 5, 6000, 2),
	operation("Pointblank", 9, 5, 8000, -1, 1.2),
	operation("Gambit", 12, 5, 5000, 4, 0.7),
	operation("Neptune", 16, 5, 7000, 5),
	operation("Tiger", 15, 3, 7500, -1, 1.6)
};

bool checkOperationsComplete() {
	for (int i = 0; i < 8; i++) {
		if (checkActive(i)) {
			return FALSE;
		}
	}
	return TRUE;
}

bool checkActive(char opName[20]) {
	for (int i = 0; i < 8; i++) {
		if (strcmp(opName, operationList[i].name) == 0) {
			return checkActive(i);
		}
	}
	return FALSE;
}

bool checkExists(char opName[20]) {
	for (int i = 0; i < 8; i++) {
		if (strcmp(opName, operationList[i].name) == 0) {
			return TRUE;
		}
	}
	return FALSE;
}

bool checkSuccessful(char opName[20]) {
	for (int i = 0; i < 8; i++) {
		if (strcmp(opName, operationList[i].name) == 0) {
			if (operationList[i].currentIntel >= operationList[i].requiredIntel) {
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
	}
	return FALSE;
}

bool checkActive(int op) {
	if (day >= operationList[op].startDay && day < operationList[op].startDay + operationList[op].duration && !operationList[op].completed) {
		if (operationList[operationList[op].waitFor].completed || operationList[op].waitFor == -1 || day >= operationList[operationList[op].waitFor].startDay + operationList[operationList[op].waitFor].duration) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	else {
		return FALSE;
	}
}

void loadCurrentLetter() {

	printf("Loading letter for day %i\n", day);

	cueOperationIntro = -1;

	switch (day) {
		case 0:
			loadLetterText("test2.txt");
			break;
		case 1:
			loadLetterText("letter1.txt");
			break;
		case 2:
			loadLetterText("letter2.txt");
			break;
		case 3:
			cueOperationIntro = 0;
			srand(static_cast <unsigned> (time(NULL)));
			startingOp = rand() % 2;
			if (startingOp == 0) {
				strcpy_s(operationList[0].name, "Roundup");
				operationTape[0] = LoadTexture(homeDirectory, "tapeRoundup.png");
				loadLetterText("letter3-1.txt");
			}
			else {
				strcpy_s(operationList[0].name, "Sledgehammer");
				loadLetterText("letter3-2.txt");
			}
			break;
		case 4:
			cueOperationIntro = 1;
			loadLetterText("letter4.txt");
			break;
		case 5:
			loadLetterText("letter5.txt");
			break;
		case 6:
			cueOperationIntro = 2;
			if (checkExists("Roundup")) {
				if (checkSuccessful("Roundup")) {
					loadLetterText("letter6-1.txt");
				}
				else {
					loadLetterText("letter6-2.txt");
				}
			}
			else {
				if (checkSuccessful("Sledgehammer")) {
					loadLetterText("letter6-3.txt");
				}
				else {
					loadLetterText("letter6-4.txt");
				}
			}
			break;
		case 7:
			if (checkSuccessful("Fortitude")) {
				loadLetterText("letter7-1.txt");
				cueOperationIntro = 3;
				bodyguardComplete = TRUE;
			}
			else {
				loadLetterText("letter7-2.txt");
			}
			break;
		case 8:
			if (bodyguardComplete) {
				loadLetterText("letter8-1.txt");
			}
			else {
				cueOperationIntro = 3;
				if (checkSuccessful("Fortitude")) {
					loadLetterText("letter8-2.txt");
				}
				else {
					loadLetterText("letter8-3.txt");
				}
			}
			break;
		case 9:
			cueOperationIntro = 4;
			if (warEffort >= 0.15) {
				winningCheck = TRUE;
				loadLetterText("letter9-1.txt");
			}
			else {
				winningCheck = FALSE;
				loadLetterText("letter9-2.txt");
			}
			break;
		case 10:
			if (winningCheck) {
				loadLetterText("letter10-1.txt");
			}
			else {
				loadLetterText("letter10-2.txt");
			}
			break;
		case 11:
			if (winningCheck) {
				loadLetterText("letter11-1.txt");
			}
			else {
				loadLetterText("letter11-2.txt");
			}
			break;
		case 12:
			if (winningCheck) {
				if (checkSuccessful("Bodyguard")) {
					if (!checkActive("Pointblank")) {
						loadLetterText("letter12-1.txt");
						pointblankComplete = TRUE;
						cueOperationIntro = 5;
					}
					else {
						loadLetterText("letter12-2.txt");
					}
				}
				else {
					if (!checkActive("Pointblank")) {
						loadLetterText("letter12-3.txt");
						pointblankComplete = TRUE;
						cueOperationIntro = 5;
					}
					else {
						loadLetterText("letter12-4.txt");
					}
				}
			}
			else {
				if (checkSuccessful("Bodyguard")) {
					if (!checkActive("Pointblank")) {
						loadLetterText("letter12-5.txt");
						pointblankComplete = TRUE;
						cueOperationIntro = 5;
					}
					else {
						loadLetterText("letter12-6.txt");
					}
				}
				else {
					if (!checkActive("Pointblank")) {
						loadLetterText("letter12-7.txt");
						pointblankComplete = TRUE;
						cueOperationIntro = 5;
					}
					else {
						loadLetterText("letter12-8.txt");
					}
				}
			}
			break;
		case 13:
			if (pointblankComplete) {
				loadLetterText("letter13-1.txt");
			}
			else {
				if (!checkActive("Pointblank")) {
					loadLetterText("letter13-2.txt");
					pointblankComplete = TRUE;
					cueOperationIntro = 5;
				}
				else {
					loadLetterText("letter13-1.txt");
				}
			}
			break;
		case 14:
			if (pointblankComplete) {
				loadLetterText("letter14-1.txt");
			}
			else {
				cueOperationIntro = 5;
				if (checkSuccessful("Pointblank")) {
					loadLetterText("letter14-2.txt");
				}
				else {
					loadLetterText("letter14-3.txt");
				}
			}
			break;
		case 15:
			cueOperationIntro = 6;
			if (warEffort >= 0.6) {
				winningCheck = TRUE;
				loadLetterText("letter15-1.txt");
			}
			else {
				winningCheck = FALSE;
				loadLetterText("letter15-2.txt");
			}
			break;
		case 16:
			if (winningCheck) {
				if (!checkActive("Gambit")) {
					gambitComplete = TRUE;
					cueOperationIntro = 7;
					loadLetterText("letter16-1.txt");
				}
				else {
					loadLetterText("letter16-2.txt");
				}
			}
			else {
				if (!checkActive("Gambit")) {
					gambitComplete = TRUE;
					cueOperationIntro = 7;
					loadLetterText("letter16-3.txt");
				}
				else {
					loadLetterText("letter16-4.txt");
				}
			}
			break;
		case 17:
			if (winningCheck) {
				if (!gambitComplete) {
					gambitComplete = TRUE;
					cueOperationIntro = 7;
					if (checkSuccessful("Gambit")) {
						loadLetterText("letter17-3.txt");
					}
					else {
						loadLetterText("letter17-4.txt");
					}
				}
				else {
					loadLetterText("letter17-1.txt");
				}
			}
			else {
				if (!gambitComplete) {
					gambitComplete = TRUE;
					cueOperationIntro = 7;
					if (checkSuccessful("Gambit")) {
						loadLetterText("letter17-5.txt");
					}
					else {
						loadLetterText("letter17-6.txt");
					}
				}
				else {
					loadLetterText("letter17-2.txt");
				}
			}
			break;
		case 18:
			if (checkOperationsComplete()) {
				if (codesBroken >= day - 1) {
					activateAchievement("steamAch_11");
				}
				day = 21;
				if (winningCheck) {
					loadLetterText("letter20-1.txt");
				}
				else {
					loadLetterText("letter20-3.txt");
				}
			}
			else {
				if (winningCheck) {
					if (checkSuccessful("Tiger")) {
						loadLetterText("letter18-1.txt");
					}
					else {
						loadLetterText("letter18-2.txt");
					}
				}
				else {
					if (checkSuccessful("Tiger")) {
						loadLetterText("letter18-3.txt");
					}
					else {
						loadLetterText("letter18-4.txt");
					}
				}
			}
			break;
		case 19:
				if (winningCheck) {
					if (checkOperationsComplete()) {
						loadLetterText("letter19-1.txt");
						if (codesBroken >= day - 1) {
							activateAchievement("steamAch_11");
						}
						day = 21;
					}
					else {
						loadLetterText("letter19-2.txt");
					}
				}
				else {
					if (checkOperationsComplete()) {
						loadLetterText("letter19-3.txt");
						if (codesBroken >= day - 1) {
							activateAchievement("steamAch_11");
						}
						day = 21;
					}
					else {
						loadLetterText("letter19-4.txt");
					}
				}
			break;
		case 20:
				if (winningCheck) {
					if (checkOperationsComplete()) {
						loadLetterText("letter20-1.txt");
						if (codesBroken >= day - 1) {
							activateAchievement("steamAch_11");
						}
						day = 21;
					}
					else {
						loadLetterText("letter20-2.txt");
					}
				}
				else {
					if (checkOperationsComplete()) {
						loadLetterText("letter20-3.txt");
						if (codesBroken >= day - 1) {
							activateAchievement("steamAch_11");
						}
						day = 21;
					}
					else {
						loadLetterText("letter20-4.txt");
					}
				}
			break;
		case 21:
			loadLetterText("letter20-1.txt");
			break;
		default:
			loadLetterText(NULL);
	}

//	loadLetterText(letterList[day - 1]);
}

void initStoryManager() {
	if (steamEnabled) {
		strcpy_s(letterDirectory, "assets/letters/");
	}
	else {
		strcpy_s(letterDirectory, "../assets/letters/");
	}
	loadLetterText(letterList[day]);
	loadTapeImages();
	if (startingOp == 0) {
		operationList[0].image = LoadTexture(homeDirectory, "tapeRoundup.png");
	}
	else {
		operationList[0].image = LoadTexture(homeDirectory, "tapeSledgehammer.png");
	}
	counter2 = LoadTexture(homeDirectory, "counter2.png");
	intelLeftTex = LoadTexture(homeDirectory, "codewordsButton3.png");
	for (int i = 0; i < 8; i++) {
		operationList[i].setRot();
	}
}

void manageStory() {
}