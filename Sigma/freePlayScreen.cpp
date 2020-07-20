#include "main.h"

GLuint freePlayScreen1;

slider scroll;
GLuint sliderBack3;
GLuint sliderFront3;
GLuint tape2;

button returnButton;

char codenames[100][20];

char description[1000];

int curLevelSelect = -1;

void initFreePlayScreen() {
	sliderBack3 = LoadTexture(homeDirectory, "sliderBack3.png");
	sliderFront3 = LoadTexture(homeDirectory, "sliderFront3.png");
	freePlayScreen1 = LoadTexture(homeDirectory, "freeplayScreen1.png");
	tape2 = LoadTexture(homeDirectory, "tape2.png");
	scroll = slider("intelControl", (renderx / 2) - 64, 64, (rendery - 128), 64, sliderBack3, sliderFront3, 1);
	scroll.position = 1.0f;
	returnButton = button("continue", 807, rendery - 94, 312, 94, codewordButton1, codewordButton2, codewordButton2);
	for (int i = 0; i < 34; i++) {
		_itoa_s(i+1, codenames[i], 10);
		strcat_s(codenames[i], 20, ".  ");
		if (i < 9) {
			strcat_s(codenames[i], 20, " ");
		}
		strcat_s(codenames[i], 20, level(levelList[i]).codename);
	}
}

void manageFreePlayScreen() {

	if (leftclick) {
		if (scroll.mouseOver()) {
			scroll.click = TRUE;
		}
	}
	if (!leftclick_flag) {
		scroll.click = FALSE;
	}

	if (scroll.click) {
		float posTemp = scroll.position;
		scroll.calcPosition();
		if (posTemp != scroll.position) {
//			tick1.play(FALSE);
		}
	}

	returnButton.hover = FALSE;
	if (returnButton.mouseOver()) {
		returnButton.hover = TRUE;
	}

	if (leftclick) {
		if (returnButton.mouseOver()) {
			returnButton.hover = FALSE;
			nextScreen = HOMESCREEN;
		}
	}

	for (int i = 0; i < 34; i++) {
		if (mousex > 0 && mousex < 560 && mousey >(i * 64) - ((1.0 - scroll.position) * 23 * 64) + 10 && mousey < (i * 64) - ((1.0 - scroll.position) * 23 * 64) + 70 && screen == nextScreen) {
			if (i != curLevelSelect && screen == nextScreen) {
				curLevelSelect = i;
				strcpy_s(description, 1000, level(levelList[i]).codename);
				strcat_s(description, 1000, ":##");
				strcat_s(description, 1000, level(levelList[i]).description);
				tick2.play(FALSE);
			}
			if (leftclick && screen == nextScreen) {
				freeplayMode = TRUE;
				initPuzzleScreen();
				nextScreen = PUZZLESCREEN;
				bulbPickup.play(FALSE);
			}
		}
	}

}

void drawFreePlayScreen() {
	placeimageeasy(freePlayScreen1, 0, 0, renderx, rendery, TRUE);

	scroll.draw();

	returnButton.draw();

	for (int i = 0; i < 34; i++) {
		glColor3f(1.0, 1.0, 1.0);
		placeimageeasy(tape2, 0, 0  + (i * 64) - ((1.0 - scroll.position) * 23 * 64), 580, 80, TRUE);
		glColor3f(0.0, 0.0, 0.0);
		drawtext(codenames[i], 32, 30 + (i * 64) - ((1.0 - scroll.position) * 23 * 64), 28, 28);
		if (mousex > 0 && mousex < 560 && mousey >(i * 64) - ((1.0 - scroll.position) * 23 * 64) + 10 && mousey < (i * 64) - ((1.0 - scroll.position) * 23 * 64) + 70 && screen == nextScreen) {
			drawtext("<-", 500, 30 + (i * 64) - ((1.0 - scroll.position) * 23 * 64), 28, 28);
		}
	}

	glColor3f(0.0, 0.0, 0.0);

	drawtextCropped(description, (renderx / 2) + 40, 24, 32, 32, 23, 0.8);

	drawtext(" Return", 867, rendery - 56, 32, 32, 0.7);

	glColor3f(1.0, 1.0, 1.0);

}