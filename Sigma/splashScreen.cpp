#include "main.h"

char splashText[100] = "A game by Jack Gloyens";
int charCount = 0;
float splashStepCounterReset = 4.0;
float nextCounter = -1.0;

char rLetter;

void initSplashScreen() {
	charCount = -8;
	stepCounter = splashStepCounterReset;
	nextCounter = -1.0;
}

void manageSplashScreen() {
	if (nextCounter > 1.0) {
		nextCounter -= 1.0;
	}
	if (nextCounter <= 1.0 && nextCounter > -1.0) {
		nextScreen = HOMESCREEN;
	}
	if (nextCounter < 1.0) {
		stepCounter -= 1.0;
	}
	if ((int)stepCounter % 2 == 0 || (int)nextCounter % 2 == 0) {
		rLetter = randLetter();
	}
	if (stepCounter <= 0.0) {
		stepCounter = splashStepCounterReset;
		charCount += 1;
		if (charCount >= 0) {
			if (splashText[charCount] == '\0') {
				nextCounter = 150.0;
			}
		}
	}
}

void drawSplashScreen() {
	glColor3f(0.0, 0.0, 0.0);
	placeimageeasy(tex1, 0, 0, renderx, renderx, FALSE);
	glColor3f(0.9, 0.9, 0.9);
	if (charCount > 0) {
		char tempText[100];
		strcpy_s(tempText, 100, splashText);
		if (nextCounter < 1.0) {
			tempText[charCount - 1] = rLetter;
		}
		float offsetx = 0.0;
		float offsety = 0.0;
		if (nextCounter > 1.0) {
			if (rand() % 13 == 1) {
				tempText[rand() % charCount] = rLetter;
			}
			if (rand() % 40 == 1) {
//				offsetx = (rand() % 128) - 64;
//				offsety = (rand() % 128) - 64;
			}
		}
		tempText[charCount] = '\0';
		drawtext_centre(tempText, (renderx / 2) + offsetx, (rendery / 2) + offsety, 48, 48);
	}
}