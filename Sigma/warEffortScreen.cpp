#include "main.h"

GLuint warEffortScreen1;
GLuint warEffortScreen1top;

GLuint tapeAllies;
GLuint tapeAxis;

rotor weRotor1;
rotor weRotor2;
rotor weRotor3;

button continueButton2;

int intelValue = 0;
int finalIntelValue = 0;

int bulbNum = 32;

bool queueMusic = FALSE;

//rotor rotorWheels[3];

bool queueSpark = true;

void initWarEffortScreen(int inval) {
	intelValue = inval;
//	warEffort -= levelCount * 0.003;
	warEffortScreen1 = LoadTexture(homeDirectory, "warEffortScreen2.png");
	warEffortScreen1top = LoadTexture(homeDirectory, "warEffortScreen2top.png");
	continueButton2 = button("continue", 807 + 128, rendery - 94, 312, 94, codewordButton1, codewordButton2, codewordButton2);

	tapeAllies = LoadTexture(homeDirectory, "tapeAllies.png");
	tapeAxis = LoadTexture(homeDirectory, "tapeAxis.png");

	queueMusic = TRUE;

	weRotor1 = rotor(rotor1Yellow, 64, rendery - 64, (2 * pi) / 26.0, 1, 0);
	weRotor2 = rotor(rotor1Red, 64 + 320, rendery - 64, (2 * pi) / 26.0, 1, 0);
	weRotor3 = rotor(rotor1Green, 64 + 640, rendery - 64, (2 * pi) / 26.0, 1, 0);
	weRotor1.rotorSize = 320;
	weRotor2.rotorSize = 320;
	weRotor3.rotorSize = 320;
	weRotor1.rot = (pi / 13.0) * (rand() % 26);
	weRotor2.rot = (pi / 13.0) * (rand() % 26);
	weRotor3.rot = (pi / 13.0) * (rand() % 26);

	queueSpark = true;
	/*
	rotor1Yellow = LoadTexture(homeDirectory, "rotor1.png");
	rotor1Red = LoadTexture(homeDirectory, "rotor2.png");
	rotor1Green = LoadTexture(homeDirectory, "rotor3.png");

	rotorWheels[0] = rotor(rotor1Yellow, 64, rendery - 24, (2 * pi) / 26.0 / 1, 1, 0);
	rotorWheels[1] = rotor(rotor1Red, 64 + 256, rendery - 24, (2 * pi) / 26.0 / 6.0, 6, (25 * 2) - 4);
	rotorWheels[2] = rotor(rotor1Green, 64 + 512, rendery - 24, (2 * pi) / 26.0 / 6.0, 6, (26 * 26 * 2) - 6);
	*/

}

int tapePos = 0;

void manageWarEffortScreen() {

	if (queueMusic) {
		queueMusic = FALSE;
		victoryMusic.play(FALSE);
	}

	continueButton2.hover = FALSE;
	if (intelValue <= 0) {
		if (continueButton2.mouseOver()) {
			continueButton2.hover = TRUE;
		}

		if (leftclick) {
			if (continueButton2.mouseOver()) {
				nextScreen = DAYSCREEN;
				nextDay();
				if (day == maxDay + 1) {
					freeplayUnlocked = TRUE;
				}
				saveGame();
			}
		}
	}

	if (intelValue > 0) {
		if (intelValue % 10 == 0) {
			tick2.play(FALSE);
		}
		if ((intelValue + 5) % 10 == 0) {
			tick2.play(FALSE);
		}
	}

	float mult = 0.00003;
	float oldWarEffort = warEffort;
	if (intelValue > 1000) {
		intelValue -= 27;
		warEffort += 27 * mult;
	}
	if (intelValue > 100) {
		intelValue -= 9;
		warEffort += 9 * mult;
	}
	else if (intelValue > 10) {
		intelValue -= 3;
		warEffort += 3 * mult;
	}
	else if (intelValue > 0) {
		intelValue -= 1;
		warEffort += 1 * mult;
	}

	if (warEffort < 0.0) {
		warEffort = 0.0;
	}
	if (warEffort > 1.0) {
		warEffort = 1.0;
	}

	if ((int)(warEffort * bulbNum) == 1) {
		activateAchievement("steamAch_3");
	}

	if ((int)(warEffort * bulbNum) == bulbNum / 2) {
		activateAchievement("steamAch_4");
	}

	if ((int)(oldWarEffort * bulbNum) != (int)(warEffort * bulbNum)) {
		bulbClick1.play(FALSE);
	}

}

void moveWeRotors() {
	/*
	if (intelValue > 0) {
		if (intelValue < 1000) {
			weRotor1.rotSpeed -= 0.0017;
			weRotor2.rotSpeed -= 0.0017;
			weRotor3.rotSpeed -= 0.0017;
		}
		weRotor1.move();
		weRotor2.move();
		weRotor3.move();
	}
	else {
		if (queueSpark) {
			for (int i = 0; i < 5; i++) {
				createSparks(rand() % 850, (rand() % ((int)rendery - 500)) + 500, 20);
			}
			queueSpark = false;
		}
	}
	*/
}

void drawWarEffortScreen() {
	placeimageeasy(warEffortScreen1, 0, 0, renderx, rendery, TRUE);

	continueButton2.draw();

	tapePos += 1;
	if (tapePos >= 400) {
		tapePos -= 400;
	}
	float divVal = 50.0;
	placeimagerotatetile(tape1, renderx / 2, 96, 128, 872, 1.0, 3.0, 0.0, -tapePos / divVal, pi / 2.0, TRUE);

	/*
	for (int i = 0; i < 3; i++) {
		rotorWheels[i].move();
		rotorWheels[i].draw();
	}
	*/

	glColor3f(0.0, 0.0, 0.0);

	drawtext("OPERATION COMPLETED", 96 + 1070 - ((tapePos / divVal) * 290.0), 74, 64, 64, 1.12);

	drawtext("OPERATION INTEL", 484, 246, 20, 20, 0.8);
	drawtext("Continue", 869 + 128, rendery - 54, 32, 32, 0.7);

	glColor3f(0.75, 0.75, 0.75);

	char tempText[10];

	_itoa_s(intelValue, tempText, 10);
	drawtext(tempText, 809 - (getintsize(intelValue) * 54), 284, 54, 54, 1.0);

	glColor3f(1.0, 1.0, 1.0);

	placeimagerotatecentre(tapeAllies, 116, 445, 210, 60, -0.3, true);
	placeimagerotatecentre(tapeAxis, renderx - 116, 540, 210, 60, -0.25, true);

	int bulbSize = 64; 
	for (int i = bulbNum - 1; i >= 0; i--) {
		if (i >= warEffort * bulbNum) {
//			glColor3f(0.7, 0.05, 0.0);
			placeimageeasy(bulb1, (renderx / 2) - (bulbSize * 0.25) + ((i - (bulbNum / 2)) * (bulbSize / 2)), rendery + 56 - 310, bulbSize, bulbSize, TRUE);
		}
		else {
//			glColor3f(0.05, 0.1, 0.5);
			placeimageeasy(bulb2, (renderx/2) - (bulbSize * 0.25) + ((i - (bulbNum / 2)) * (bulbSize / 2)), rendery + 56 - 310, bulbSize, bulbSize, TRUE);
			if (rand() % 1000 == 0) {
				createSparks((renderx / 2) - (bulbSize * 0.25) + ((i - (bulbNum / 2)) * (bulbSize / 2)) + (bulbSize / 2), rendery + 56 - 310 + (bulbSize / 2), 20);
			}
		}
	}

	glColor3f(1.0, 1.0, 1.0);

	/*
	weRotor1.draw();
	weRotor2.draw();
	weRotor3.draw();
	*/

	placeimageeasy(warEffortScreen1top, 0, 0, renderx, rendery, TRUE);

}