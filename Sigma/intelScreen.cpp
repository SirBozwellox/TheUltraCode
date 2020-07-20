#include "main.h"

GLuint intelScreen1;
GLuint noOperations;

slider intelControl;

button continueButton;

int displayOperations[3];
int operationNum = 0;
state controlButtons[6];

int displayIntel;

void initIntelScreen() {
	intelScreen1 = LoadTexture(homeDirectory, "intelScreen1.png");
	noOperations = LoadTexture(homeDirectory, "noOperations.png");
	intelControl = slider("intelControl", (renderx/2) - 128, 462, 256, 64, sliderBack1, sliderFront1, 0);
	intelControl.position = 0.0f;
	continueButton = button("continue", 807, rendery - 94, 312, 94, codewordButton1, codewordButton2, codewordButton2);

	intelScreen1 = LoadTexture(homeDirectory, "intelScreen2.png");

	setDay(day);

	operationNum = 0;
	for (int i = 0; i < 10; i++) {
		operationList[i].temporaryIntel = operationList[i].currentIntel;
		if (checkActive(i)) {
			if (operationNum < 3) {
				displayOperations[operationNum] = i;
				operationNum += 1;
			}
		}
	}

	if (startingOp == 0) {
		operationList[0].image = LoadTexture(homeDirectory, "tapeRoundup.png");
		strcpy_s(operationList[0].name, "Roundup");
	}
	else {
		operationList[0].image = LoadTexture(homeDirectory, "tapeSledgehammer.png");
		strcpy_s(operationList[0].name, "Sledgehammer");
	}

	for (int i = 0; i < operationNum; i++) {
		controlButtons[(2 * i)] = state("<", 354, 250 + (80 * i * 2));
		controlButtons[(2 * i)].active = FALSE;
		controlButtons[(2 * i) + 1] = state(">", renderx - 354, 250 + (80 * i * 2));
		controlButtons[(2 * i) + 1].active = FALSE;
	}

	displayIntel = intelLevel;

}

bool audioPlayed = false;

void manageIntelScreen() {

	if (!audioPlayed && fadeValue <= 0.05 && day == 3) {
		tutorial_3_intel.play(false);
		audioPlayed = true;
	}

	if (displayIntel - intelLevel > 100) {
		displayIntel -= 16;
	}
	else if (displayIntel - intelLevel > 10) {
		displayIntel -= 6;
	}
	else if (displayIntel - intelLevel > 0) {
		displayIntel -= 1;
	}

	if (intelLevel - displayIntel > 100) {
		displayIntel += 51;
	}
	else if (intelLevel - displayIntel > 10) {
		displayIntel += 7;
	}
	else if (intelLevel - displayIntel > 0) {
		displayIntel += 1;
	}

	continueButton.hover = FALSE;
	if (continueButton.mouseOver()) {
		continueButton.hover = TRUE;
	}

	if (!messageActive) {
		for (int i = 0; i < operationNum; i++) {
			if (controlButtons[(i * 2)].mouseOver()) {
				if (!controlButtons[(i * 2)].active) {
					tick1.play(FALSE);
				}
				controlButtons[(i * 2)].active = TRUE;
				if (leftclick) {
					if (operationList[displayOperations[i]].temporaryIntel > operationList[displayOperations[i]].currentIntel) {
						tick2.play(FALSE);
						operationList[displayOperations[i]].temporaryIntel -= operationList[displayOperations[i]].requiredIntel / 20;
						intelLevel += operationList[displayOperations[i]].requiredIntel / 20;
					}
				}
			}
			else {
				controlButtons[(i * 2)].active = FALSE;
			}
			if (controlButtons[(i * 2) + 1].mouseOver()) {
				if (!controlButtons[(i * 2) + 1].active) {
					tick1.play(FALSE);
				}
				controlButtons[(i * 2) + 1].active = TRUE;
				if (leftclick) {
					if (operationList[displayOperations[i]].temporaryIntel < operationList[displayOperations[i]].requiredIntel && intelLevel >= operationList[displayOperations[i]].requiredIntel / 20) {
						tick2.play(FALSE);
						operationList[displayOperations[i]].temporaryIntel += operationList[displayOperations[i]].requiredIntel / 20;
						intelLevel -= operationList[displayOperations[i]].requiredIntel / 20;
					}
					else {
						if (operationList[displayOperations[i]].temporaryIntel == operationList[displayOperations[i]].currentIntel) {
							int intelMinimum = operationList[displayOperations[i]].requiredIntel / 20;
							strcpy_s(messageText, "You must have at least ");
							char tempText[20];
							_itoa_s(intelMinimum, tempText, 10);
							strcat_s(messageText, tempText);
							strcat_s(messageText, " intel available to contribute to this operation.");
							showMessage(messageText);
						}
					}
				}
			}
			else {
				controlButtons[(i * 2) + 1].active = FALSE;
			}
		}
	}

	if (leftclick && !messageActive) {
		if (continueButton.mouseOver()) {
			bool playSfx = FALSE;
			float warEffortPlus = 0.0;
			bool intelSpent = FALSE;
			char tempText[200] = "You have gathered all the intel required for the following operations:##  ";
			for (int i = 0; i < operationNum; i++) {
				if (operationList[displayOperations[i]].currentIntel != operationList[displayOperations[i]].temporaryIntel) {
					playSfx = TRUE;
					intelSpent = TRUE;
				}
				operationList[displayOperations[i]].currentIntel = operationList[displayOperations[i]].temporaryIntel;
				if (operationList[displayOperations[i]].currentIntel == operationList[displayOperations[i]].requiredIntel) {
//					activateAchievement("steamAch_12");
					operationList[displayOperations[i]].completed = TRUE;
					strcat_s(tempText, 200, operationList[displayOperations[i]].name);
					strcat_s(tempText, 200, "#  ");
					showMessage(tempText);
					messageAnim += 5;
					nextScreen = WAREFFORTSCREEN;
					float tempEffort = (operationList[displayOperations[i]].requiredIntel / 1.45);
					tempEffort += ((operationList[displayOperations[i]].startDay + operationList[displayOperations[i]].duration) - day) * 500;
					tempEffort *= operationList[displayOperations[i]].multiplier;
					warEffortPlus += tempEffort;
				}
			}
			if (!intelSpent) {
				showOptionMessage("You haven't spent any intel on operations. Would you like to continue anyway?");
			} else {
				if (playSfx) {
					bulbClick1.play(FALSE);
				}
				if (nextScreen != WAREFFORTSCREEN) {
					nextScreen = DAYSCREEN;
					nextDay();
					saveGame();
				}
				else {
					initWarEffortScreen(warEffortPlus);
				}
			}
		}
	}

	if (getMessageChoice() == 0) {
		nextScreen = DAYSCREEN;
		nextDay();
		saveGame();
	}

}

void drawIntelScreen() {
	placeimageeasy(intelScreen1, 0, 0, renderx, rendery, TRUE);

	continueButton.draw();

	glColor3f(0.0, 0.0, 0.0);

	drawtext("Intel", 876, 34, 20, 20, 0.8);
	drawtext("Continue", 867, rendery - 56, 32, 32, 0.7);
	drawtextCropped("Spend intel you've earned on operations to help with the allied war effort. If you run out of time on an operation then all the intel for it will be lost.", 52, 25, 18, 18, 40, 0.73);

	glColor3f(1.0, 1.0, 1.0);

	if (operationNum == 0) {
		placeimageeasy(noOperations, 0, 0, renderx, rendery, TRUE);
	}

	for (int i = 0; i < operationNum; i++) {
		operationList[displayOperations[i]].draw2(167 + (80 * i * 2));
		controlButtons[(2 * i)].draw(controlButtons[(2 * i)].active);
		controlButtons[(2 * i) + 1].draw(controlButtons[(2 * i) + 1].active);
	}
	
	char tempText[10];

	glColor3f(0.75, 0.75, 0.75);
	_itoa_s(displayIntel, tempText, 10);
	drawtext(tempText, renderx - 86 - (getintsize(displayIntel) * 54), 72, 54, 54, 1.0);

	glColor3f(1.0, 1.0, 1.0);

}