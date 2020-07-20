#include "main.h"

char text[100];
int characterCount = 0;
float dayStepCounterReset = 5.0;
float finalCounter = -1.0;

char dayList[21][30] = {
	"March 1942",
	"April 1942",
	"May 1942",
	"July 1942",
	"September 1942",
	"November 1942",
	"January 1943",
	"March 1943",
	"July 1943",
	"May 1943",
	"August 1943",
	"September 1943",
	"October 1943",
	"November 1943",
	"December 1943",
	"January 1944",
	"February 1944",
	"March 1944",
	"April 1944",
	"May 1944",
	"6th June 1944, D-Day"
};

char randomLetter;

void initDayScreen(char intext[100]) {
	strcpy_s(text, 100, dayList[day - 1]);
	characterCount = -8;
	stepCounter = dayStepCounterReset;
	finalCounter = -1.0;
}

void manageDayScreen() {
	if (finalCounter > 1.0) {
		finalCounter -= 1.0;
	}
	if (finalCounter <= 1.0 && finalCounter > -1.0) {
		if (day < 21) {
			initLetterScreen();
			nextScreen = LETTERSCREEN;
		}
		else {
			initCutScene();
			nextScreen = CUTSCENE;
		}
	}
	stepCounter -= 1.0;
	if (stepCounter <= 0.0 && finalCounter < 1.0) {
		stepCounter = dayStepCounterReset;
		characterCount += 1;
		if (characterCount >= 0) {
			tick1.play(FALSE);
			if (text[characterCount] == '\0') {
				finalCounter = 120.0;
			}
		}
	}
}

void drawDayScreen() {
	glColor3f(0.0, 0.0, 0.0);
	placeimageeasy(tex1, 0, 0, renderx, renderx, FALSE);
	glColor3f(0.9, 0.9, 0.9);
	if (characterCount > 0) {
		char tempText[100];
		strcpy_s(tempText, 100, text);
		if (finalCounter < 1.0) {
//			tempText[characterCount - 1] = randomLetter;
		}
		tempText[characterCount] = '\0';
		drawtext_centre(tempText, renderx / 2, rendery / 2, 64, 64);
	}
}