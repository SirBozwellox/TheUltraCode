#include "main.h"

graph Graph = graph();

state placeState = state();
int moveState = -1;
//state placeState = state("A", 0, 0);

int displayType = 0;

int randVal = 0;

int placeEdge = -1;
char placeEdgeType = '1';

int deleteSize = 96;
int deletex = 116 + 1024 - deleteSize;
int deletey = 147 + 448 - deleteSize;

char testPassText[20];
float testPassCounterReset = 90.0;
float testPassCounter = 0.0;

bool running = FALSE;
int tapeLoc = 0;

button playBtn;
button stopBtn;

slider speedControl;

level currentLevel;

char descriptionDisplay[1000];
char descriptionBox[1000];
float descriptionCharCount = 0;

bool freeplayMode = FALSE;

char toolTip[100];

void newDescription(char inval[1000]) {
	strcpy_s(descriptionBox, 1000, inval);
	strcpy_s(descriptionDisplay, 1000, "");
	descriptionCharCount = 1.0;
}

state stateSet[] = {
	state("+", 220, 720 - 56),
};

GLuint interfaceTex;
GLuint interfaceTexFront;
GLuint tape1;

GLuint downArrow;
float arrowFloat = 0.0;

button getCodewordButton;

button exitButton;

state toggleHelp;

int intelDisplay;
char intelString[7];
char stateString[3];

int sparkFromState = -1;
int sparkToState = -1;
int sparkTimer = 0;
int sparkTimerReset = 12;

bool solveFlag = FALSE;
bool nextFlag = FALSE;

void initPuzzleScreen() {


	randVal = time(0);

	if (day <= 1) {
		displayType = 0;
	}
	else if (day == 2) {
		displayType = 1;
	}
	else {
		displayType = 2;
	}

	if (freeplayMode) {
		displayType = 3;
	}

	if (displayType == 0) {
		interfaceTex = LoadTexture(homeDirectory, "ui2_simple2.png");
	}
	else if (displayType == 1 || freeplayMode) {
		interfaceTex = LoadTexture(homeDirectory, "ui2_simple1.png");
	}
	else {
		interfaceTex = LoadTexture(homeDirectory, "ui2.png");
	}
	interfaceTexFront = LoadTexture(homeDirectory, "ui2front2.png");
	tape1 = LoadTexture(homeDirectory, "tape3.png");
	downArrow = LoadTexture(homeDirectory, "downArrow.png");
	arrowFloat = 0.0;

	playBtn = button("play", renderx - 103, 170, 80, 80, playButtonUp, playButtonUp, playButtonDown);
	stopBtn = button("stop", renderx - 103, 260, 80, 80, stopButtonUp, stopButtonUp, stopButtonDown);
	stopBtn.click = TRUE;

	exitButton = button("exit", (renderx / 2) - 76, rendery - 93, 196, 78, exitButtonUp, exitButtonDown, exitButtonUp);

	toggleHelp = state("?", renderx - 60, rendery - 50);
	toggleHelp.active = FALSE;
	toggleHelp.final = helpText;

//	toggleMessage("Hello and welcome to Sigma, the Second World War codebreaking puzzle game!");

	speedControl = slider("speedControl", renderx - 96, 376, 196, 64, sliderBack2, sliderFront2, 1);

	if (freeplayMode) {
		currentLevel = level(levelList[curLevelSelect]);
		currentLevel.par = 27;
	}
	else {
		if (levelCount < 6) {
			currentLevel = level(baseLevels[levelCount]);
		}
		else {
			if (pickLevelType == 0) {
				currentLevel = level(easyLevels[levelCount - 6]);
			}
			else {
				currentLevel = level(hardLevels[levelCount - 6]);
			}
		}
	}
	newDescription(currentLevel.description);

	getCodewordButton = button("getCodeword", 807, rendery - 94, 312, 94, codewordButton1, codewordButton2, codewordButton2);

	intelDisplay = intelLevel;

	placeEdge = -1;

	solveFlag = FALSE;

	nextFlag = FALSE;

	running = FALSE;
	tapeLoc = 0;

	Graph = graph();
	if (displayType == 0) {
		Graph.addState(state("A", (renderx / 2) + 100, 380));
	}

	placeState = state();
	moveState = -1;

//	Graph.addState(state("A", 300, 430));
//	Graph.stateList[1].final = TRUE;
//	Graph.addState(state("B", 720, 264));
//	Graph.addEdge(edge('1', 0, 1));
}

float stepCounter;
float stepCounterReset = 64;
char inputString[400];
int inputIndex = 0;
int testNumber = 0;
int finishCounter = -1;

bool simulate(char testString[400]) {
	Graph.currentState = 0;
	Graph.lastState = -1;
	inputIndex = -5;
	tapeLoc = -2;
	testNumber = 0;
	finishCounter = -1;
	bool finish = FALSE;
	bool fail = FALSE;
	while (!finish) {
		inputIndex += 1;
		tapeLoc += 1;
		if (inputIndex >= 0) {
			if (testString[inputIndex] == 'f') {
				finish = TRUE;
			}
			else if (testString[inputIndex] == '#') {
				inputIndex += 1;
				if (Graph.stateList[Graph.currentState].final && testString[inputIndex] == 'a') {
				}
				else if (!Graph.stateList[Graph.currentState].final && testString[inputIndex] == 'r') {
				}
				else {
					finish = TRUE;
					fail = TRUE;
				}
				Graph.currentState = 0;
				Graph.lastState = -1;
			}
			else {
				Graph.lastState = Graph.currentState;
				Graph.currentState = Graph.edgeList[Graph.findEdge(testString[inputIndex], Graph.currentState)].toState;
			}
		}
	}
	return fail;
}

void resetAnimation() {
	if (levelCount == 0 && !freeplayMode) {
		if (tutorialLevel >= 12) {
			strcpy_s(inputString, 400, "01010101#a000#r010#a11#a10#a01#a0000#r0#r1#a1010#a0101#af");
		}
		else {
			strcpy_s(inputString, 400, "01010101#a000#r010#a11#a10#a01#a0000#r0#r1#a1010#a0101#a01010101#a000#r010#a11#a10#a01#a0000#r0#r1#a1010#a0101#af");
		}
	}
	else {
		int failNum = -1;
		for (int i = 0; i < 20; i++) {
			char tempString[100];
			strcpy_s(tempString, 100, currentLevel.testStrings[i]);
			strcat_s(tempString, "f");
			if (simulate(tempString)) {
				failNum = i;
			}
		}
		if (failNum == -1) {
			printf("Success\n");
			strcpy_s(inputString, 400, currentLevel.createTestString(15));
		}
		else {
			printf("Failure on test %i\n", failNum);
			int rval = (rand() % 12) + 1;
			strcpy_s(inputString, 400, currentLevel.createTestString(rval));
			inputString[strlen(inputString) - 1] = '\0';
			strcat_s(inputString, 400, currentLevel.testStrings[failNum]);
			strcat_s(inputString, 400, currentLevel.createTestString(15 - rval));
		}
	}
//	printf(inputString);
	Graph.currentState = 0;
	Graph.lastState = -1;
	stepCounter = stepCounterReset;
	inputIndex = -5;
	tapeLoc = -2;
	testNumber = 0;
	finishCounter = -1;
}

void toggleAnimation(bool run) {
	if (run) {
		srand(static_cast <unsigned> (randVal));
		running = TRUE;
		playBtn.click = TRUE;
		stopBtn.click = FALSE;
		resetAnimation();
		printf(inputString);
	}
	else {
		running = FALSE;
		playBtn.click = FALSE;
		stopBtn.click = TRUE;
		Graph.currentState = -1;
		Graph.lastState = -1;
	}
	lightClick.play(FALSE);
}

char tempText[400];
char tempchar[2];

void animate() {
	float lastStep = stepCounter;
	if (testPassCounter < testPassCounterReset * 0.5) {
		if (inputIndex < -1) {
			stepCounter -= (6.0 * pow(0.85, 3)) + 1.0;
		}
		else if (finishCounter > 0) {
			stepCounter -= (6.0 * pow(0.85, 3)) + 1.0;
		}
		else {
			stepCounter -= (10.0 * pow(speedControl.position, 4.0)) + 0.2;
		}
	}

	if (lastStep >= stepCounterReset * 0.5 && stepCounter < stepCounterReset * 0.5) {
		tick2.play(FALSE);
	}

	if (running) {
		if (day == 1 && strlen(inputString) > 57 && !freeplayMode) {
			if (inputIndex >= 56) {
				printf("RESET\n");
				inputIndex -= 56;
				tapeLoc -= 56;
			}
		}
	}

	if (stepCounter < 0.0) {
		tick1.play(FALSE);
		stepCounter = stepCounterReset;
		inputIndex += 1;
		tapeLoc += 1;
		if (finishCounter > 0) {
			finishCounter -= 1;
			if (finishCounter <= 0) {
				toggleAnimation(FALSE);
			}
		}
		if (inputIndex >= 0 && finishCounter == -1) {
			if (inputString[inputIndex] == '#') {
				inputIndex += 1;
				if (Graph.stateList[Graph.currentState].final && inputString[inputIndex] == 'a') {
					if (helpText) {
						testPassCounter = testPassCounterReset;
					}
					if (inputString[inputIndex + 1] == 'f') {
						showMessage("Success! You've cracked todays code.");
						if (day == 1) {
							puzzleEnd = sound(victoryAudio[letterSenders[day]][0]);
						}
						else if (day == 2) {
							puzzleEnd = sound(victoryAudio[letterSenders[day]][2]);
						}
						else {
							puzzleEnd = sound(victoryAudio[letterSenders[day]][rand() % 3]);
						}
						if (!freeplayMode) {
							puzzleEnd.play(false);
						}
						finishCounter = 4;
						solveFlag = TRUE;
					}
					/*
					std::string s = std::to_string(testNumber);
					strcpy_s(tempText, 400, "Test number ");
					strcat_s(tempText, s.c_str());
					strcat_s(tempText, " successful");
					toggleMessage(tempText);
					*/
				}
				else if (!Graph.stateList[Graph.currentState].final && inputString[inputIndex] == 'r') {
					if (helpText) {
						testPassCounter = testPassCounterReset;
					}
					if (inputString[inputIndex + 1] == 'f') {
						showMessage("Success! You've cracked todays code.");
						if (day == 1) {
							puzzleEnd = sound(victoryAudio[letterSenders[day]][0]);
						}
						else if (day == 2) {
							puzzleEnd = sound(victoryAudio[letterSenders[day]][2]);
						}
						else {
							puzzleEnd = sound(victoryAudio[letterSenders[day]][rand() % 3]);
						}
						if (!freeplayMode) {
							puzzleEnd.play(false);
						}
						finishCounter = 4;
						solveFlag = TRUE;
					}
					/*
					std::string s = std::to_string(testNumber);
					strcpy_s(tempText, 400, "Test number ");
					strcat_s(tempText, s.c_str());
					strcat_s(tempText, " successful");
					toggleMessage(tempText);
					*/
				}
				else {
//					std::string s = std::to_string(testNumber);
//					toggleMessage("       Machine error:##Not all of the states in the machine have their output wires connected.");
					strcpy_s(tempText, "       Machine error:##The codeword '");
					int tempIndex = inputIndex - 2;
					while (inputString[tempIndex] != '#' && tempIndex > -2) {
						tempIndex -= 1;
					}
					for (int i = tempIndex + 2; inputString[i] != '#'; i++) {
						int tempSize = strlen(tempText);
						tempText[tempSize] = inputString[i];
						tempText[tempSize + 1] = '\0';
					}
					if (inputString[inputIndex] == 'a') {
						strcat_s(tempText, "' should be accepted but your machine rejects it.");
					}
					else {
						strcat_s(tempText, "' should be rejected but your machine accepts it.");
					}
					showMessage(tempText);
					finishCounter = 9;
					inputString[inputIndex + 4] = '\0';
				}
				inputIndex -= 1;
				testNumber += 1;
			}
			else if (inputString[inputIndex] == '1' || inputString[inputIndex] == '0') {
				Graph.lastState = Graph.currentState;
				Graph.currentState = Graph.edgeList[Graph.findEdge(inputString[inputIndex], Graph.currentState)].toState;
			}
			else if (inputString[inputIndex] == 'a' || inputString[inputIndex] == 'r') {
				Graph.currentState = 0;
				Graph.lastState = -1;
			}
		}
	}
}

int checkGraph() {
	int retval = 0;
	bool nofinal = TRUE;
	for (int i = 0; i < 40; i++) {
		if (Graph.stateList[i].active) {
			if (!Graph.edgeExists('0', i) || !Graph.edgeExists('1', i)) {
				retval = 1;
			}
		}
		if (Graph.stateList[i].final) {
			nofinal = FALSE;
		}
	}
	if (nofinal) {
		retval = 2;
	}
	return retval;
}

void managePuzzleScreen() {

	if (messageAnim > 0) {
		placeEdge = -1;
		placeState.active = FALSE;
		moveState = -1;
	}
	else {

		if (descriptionBox[(int)descriptionCharCount] != '\0') {
			descriptionCharCount += 0.3;
			descriptionDisplay[(int)descriptionCharCount - 1] = descriptionBox[(int)descriptionCharCount - 1];
			descriptionDisplay[(int)descriptionCharCount] = '\0';
		}

		if (intelDisplay != intelLevel) {
			if (intelDisplay % 10 == 0) {
				tick2.play(FALSE);
			}
			if ((intelDisplay + 5) % 10 == 0) {
				tick2.play(FALSE);
			}
		}

		if (intelDisplay - intelLevel > 100) {
			intelDisplay -= 16;
		}
		else if (intelDisplay - intelLevel > 10) {
			intelDisplay -= 6;
		}
		else if (intelDisplay - intelLevel > 0) {
			intelDisplay -= 1;
		}

		if (intelLevel - intelDisplay > 100) {
			intelDisplay += 51;
		}
		else if (intelLevel - intelDisplay > 10) {
			intelDisplay += 7;
		}
		else if (intelLevel - intelDisplay > 0) {
			intelDisplay += 1;
		}

		if (toggleHelp.mouseOver()) {
			toggleHelp.active = TRUE;
			if (leftclick) {
				helpText = 1 - helpText;
				toggleHelp.final = helpText;
			}
		}
		else {
			toggleHelp.active = FALSE;
		}

		if (solveFlag && finishCounter == 0.0 && intelLevel == intelDisplay && nextFlag == FALSE) {
			nextFlag = TRUE;
			if (!freeplayMode) {
				codesBroken += 1;
				if (codesBroken == 5) {
					activateAchievement("steamAch_8");
				}
				if (codesBroken == 10) {
					activateAchievement("steamAch_9");
				}
				if (codesBroken == 15) {
					activateAchievement("steamAch_10");
				}
				if (codesBroken == 20) {
					activateAchievement("steamAch_11");
				}
				if (levelCount < 6) {
					if (levelCount < 2) {
						activateAchievement("steamAch_1");
					}
					else if (levelCount == 2) {
						intelLevel += 1000;
					}
					else if (levelCount > 2) {
						intelLevel += 1500;
					}
				}
				else {
					if (pickLevelType == 0) {
						intelLevel += 1000;
						perfectGame = FALSE;
					}
					else {
						activateAchievement("steamAch_2");
						intelLevel += 2500;
					}
				}
			}
		}
		if (solveFlag && intelLevel == intelDisplay && nextFlag == TRUE) {
			if (freeplayMode) {
				loadGame();
				screen = PUZZLESCREEN;
				nextScreen = FREEPLAYSCREEN;
				freeplayMode = FALSE;
			}
			else {
				levelCount += 1;
				if (day >= 3) {
					nextScreen = INTELSCREEN;
					initIntelScreen();
				}
				else {
					nextDay();
					saveGame();
				}
			}
		}

		if (leftclick) {
			if (speedControl.mouseOver()) {
				speedControl.click = TRUE;
			}
		}
		if (!leftclick_flag) {
			speedControl.click = FALSE;
		}
		if (speedControl.click) {
			speedControl.calcPosition();
		}

		if (running) {
			if (leftclick) {
				if (stopBtn.mouseOver() && inputIndex >= 0 && finishCounter == -1) {
//					toggleAnimation(FALSE);
					finishCounter = 8;
					inputString[inputIndex + 5] = '\0';
				}
			}

			if (rand() % 160 == 0) {
				createSparks(Graph.stateList[Graph.currentState].x, Graph.stateList[Graph.currentState].y, 20);
			}

			/*
			if (rand() % 200 == 0 && sparkTimer <= 0) {
				int edgeNum = 0;
				for (int i = 0; i < 100; i++) {
					if (Graph.edgeList[i].fromState > -1 && Graph.edgeList[i].fromState != Graph.edgeList[i].toState) {
						edgeNum += 1;
					}
				}
				for (int i = 0; i < 100; i++) {
					if (Graph.edgeList[i].fromState > -1 && Graph.edgeList[i].fromState != Graph.edgeList[i].toState) {
						if (rand() % edgeNum == 0) {
							sparkFromState = Graph.edgeList[i].fromState;
							sparkToState = Graph.edgeList[i].toState;
							sparkTimer = sparkTimerReset;
						}
					}
				}
				if (sparkTimer == sparkTimerReset) {
					sparkSound2.play(FALSE);
				}
			}
			*/

			animate();
		}
		else {

			if (displayType == 2 || displayType == 3) {
				if (exitButton.mouseOver()) {
					if (!exitButton.hover) {
						tick1.play(FALSE);
					}
					exitButton.hover = TRUE;
					if (leftclick) {
						bulbPickup.play(FALSE);
						if (freeplayMode) {
							showOptionMessage("Your progress will be lost if you leave. Do you still wish to exit?");
						}
						else {
							if (day == 3) {
								showMessage("I appreciate the enthusiasm William but you're not out of basic training yet. Let's try building a machine to decipher today's codewords.");
								if (tutorialLevel >= 5) {
									tutorialAudio.stop();
									tutorial_3_exit.play(false);
								}
							}
							else {
								showOptionMessage("You won't earn any intel if you leave now. Do you still wish to exit?");
							}
						}
					}
				}
				else {
					exitButton.hover = FALSE;
				}
			}

			Graph.currentState = -1;
			if (!leftclick_flag) {
				if (placeState.active) {
					if (mousex > 128 + 32 && mousex < 128 + 1024 - 32) {
						if (mousey > 160 + 32 && mousey < 160 + 448 - 32) {
							Graph.addState(state(placeState.name, placeState.x, placeState.y));
							bulbDrop.play(FALSE);
							createSparks(placeState.x, placeState.y, 15);
						}
					}
				}

				if (moveState != -1) {
					if (displayType >= 1) {
						if (Graph.stateList[moveState].x > deletex && Graph.stateList[moveState].x < deletex + deleteSize && Graph.stateList[moveState].y > deletey && Graph.stateList[moveState].y < deletey + deleteSize && moveState >= 1) {
							Graph.removeState(moveState);
						}
					}
					bulbDrop.play(FALSE);
//					createSparks(Graph.stateList[moveState].x, Graph.stateList[moveState].y, 7);
					moveState = -1;
				}

				if (placeEdge != -1) {
					for (int i = 0; i < 100; i++) {
						if (Graph.stateList[i].getMouseDist() < stateSize / 2) {
							Graph.addEdge(edge(placeEdgeType, placeEdge, i));
							wire1.play(FALSE);
						}
					}
				}
				placeState.active = FALSE;
				placeEdge = -1;

			}

			if (displayType >= 2 && displayType != 3) {
				getCodewordButton.hover = FALSE;
				if (getCodewordButton.mouseOver() && currentLevel.par <= 26) {
					getCodewordButton.hover = TRUE;
				}
			}

			if (leftclick) {

				if (displayType >= 2 && displayType != 3) {
					if (getCodewordButton.mouseOver()) {
						if (intelLevel >= 500 && currentLevel.par <= 26) {
							intelLevel -= 500;
							currentLevel.par += 1;
						}
					}
				}

				if (playBtn.mouseOver()) {
					if (checkGraph() == 1) {
						showMessage("       Machine error:##Not all the wires in the machine are connected.");
					}
					else if (checkGraph() == 2) {
						showMessage("       Machine error:##The machine doesn't have any green accepting bulbs. Right click on a bulb to make it accepting.");
					}
					else {
						toggleAnimation(TRUE);
					}
				}

				//		for (int i = 0; i < 100; i++) {
				//			if (Graph.edgeList[i].fromState != -1) {
				//				printf("%i: %i, %i, %c\n", i, Graph.edgeList[i].fromState, Graph.edgeList[i].toState, Graph.edgeList[i].type);
				//			}
				//		}

				float dist = 0.0f;
				for (int i = 0; i < 100; i++) {
					if (Graph.stateList[i].active) {
						//				printf("%f\n", Graph.stateList[i].getMouseAngle());
						dist = Graph.stateList[i].getMouseDist();
						if (dist < stateSize / 2 && !placeState.active) {
							moveState = i;
							bulbPickup.play(FALSE);
						}
					}
				}

				for (int i = 0; i < 100; i++) {
					dist = Graph.stateList[i].getMouseDist();
					if (dist >= stateSize / 2) {
						if (dist < stateSize) {
							float rota = Graph.stateList[i].getMouseAngle() + 0.4;
							float rotb = Graph.stateList[i].rot0;
							float d = rota - rotb;
							if (d > pi) { d -= pi * 2; }
							if (abs(d) < 0.4 && !Graph.edgeExists('0', i) && moveState == -1) {
								placeEdge = i;
								placeEdgeType = '0';
								wire2.play(FALSE);
							}
							rotb = Graph.stateList[i].rot1;
							d = rota - rotb;
							if (d > pi) { d -= pi * 2; }
							//					printf("%f, %f, %f \n", rota, rotb, d);
							if (abs(d) < 0.4 && !Graph.edgeExists('1', i) && moveState == -1) {
								placeEdge = i;
								placeEdgeType = '1';
								wire2.play(FALSE);
							}
						}
					}
				}

				for (int i = 0; i < 100; i++) {
					if (Graph.edgeList[i].fromState != -1 && Graph.edgeList[i].toState != -1) {
						if (Graph.edgeList[i].fromState == Graph.edgeList[i].toState) {
							if (Graph.edgeList[i].type == '0') {
								float rota = Graph.stateList[Graph.edgeList[i].fromState].getMouseAngle();
								float rotb = Graph.stateList[Graph.edgeList[i].fromState].rot0;
								if (abs(rota - rotb) < 0.4 && Graph.stateList[Graph.edgeList[i].fromState].getMouseDist() > stateSize / 2 && Graph.stateList[Graph.edgeList[i].fromState].getMouseDist() < stateSize * 1.1) {
									if (placeEdge == -1 && placeState.active == FALSE && moveState == -1 && placeEdge == -1) {
										placeEdge = Graph.edgeList[i].fromState;
										placeEdgeType = Graph.edgeList[i].type;
										Graph.removeEdge(i);
										wire2.play(FALSE);
									}
								}
							}
							if (Graph.edgeList[i].type == '1') {
								float rota = Graph.stateList[Graph.edgeList[i].fromState].getMouseAngle();
								float rotb = Graph.stateList[Graph.edgeList[i].fromState].rot1;
								if (abs(rota - rotb) < 0.4 && Graph.stateList[Graph.edgeList[i].fromState].getMouseDist() > stateSize / 2 && Graph.stateList[Graph.edgeList[i].fromState].getMouseDist() < stateSize * 1.1) {
									if (placeEdge == -1 && placeState.active == FALSE && moveState == -1 && placeEdge == -1) {
										placeEdge = Graph.edgeList[i].fromState;
										placeEdgeType = Graph.edgeList[i].type;
										Graph.removeEdge(i);
										wire2.play(FALSE);
									}
								}
							}
						}
						else {
							float H = sqrt(pow(mousex - Graph.stateList[Graph.edgeList[i].fromState].x, 2) + pow(mousey - Graph.stateList[Graph.edgeList[i].fromState].y, 2));
							float R = sqrt(pow(mousex - Graph.stateList[Graph.edgeList[i].toState].x, 2) + pow(mousey - Graph.stateList[Graph.edgeList[i].toState].y, 2));
							float L = sqrt(pow(Graph.stateList[Graph.edgeList[i].toState].x - Graph.stateList[Graph.edgeList[i].fromState].x, 2) + pow(Graph.stateList[Graph.edgeList[i].toState].y - Graph.stateList[Graph.edgeList[i].fromState].y, 2));
							float alpha = acos((pow(H, 2) + pow(L, 2) - pow(R, 2)) / (2 * H * L));
							float alpha2 = acos((pow(R, 2) + pow(L, 2) - pow(H, 2)) / (2 * R * L));
							float x = sin(alpha) * H;
							float d = ((mousex - Graph.stateList[Graph.edgeList[i].fromState].x) * (Graph.stateList[Graph.edgeList[i].toState].y - Graph.stateList[Graph.edgeList[i].fromState].y)) - ((mousey - Graph.stateList[Graph.edgeList[i].fromState].y) * (Graph.stateList[Graph.edgeList[i].toState].x - Graph.stateList[Graph.edgeList[i].fromState].x));
							if (alpha < pi / 2 && alpha2 < pi / 2 && x < 24 && d >= 0.0) {
								if (placeEdge == -1 && placeState.active == FALSE && moveState == -1 && placeEdge == -1) {
									//							printf("%f, %f, %f, %f, %f\n", x, H, R, alpha, d);
									placeEdge = Graph.edgeList[i].fromState;
									placeEdgeType = Graph.edgeList[i].type;
									Graph.removeEdge(i);
									wire2.play(FALSE);
								}
							}
							//					printf("%f, %f, %f\n", x, alpha, alpha2);
						}
					}
				}

				if (displayType >= 1) {
					for (int i = 0; i < 1; i++) {
						if (stateSet[i].mouseOver() && currentLevel.par - Graph.getStateNum() > 0) {
							bulbPickup.play(FALSE);
							placeState.active = TRUE;
							placeState.name[0] = Graph.getNextLetter();
							placeState.name[1] = '\0';
						}
					}
				}

			}

			if (rightclick) {
				for (int i = 1; i < 40; i++) {
					if (Graph.stateList[i].mouseOver()) {
						if (Graph.stateList[i].final) {
							Graph.stateList[i].final = FALSE;
							lightClick.play(FALSE);
						}
						else {
							Graph.stateList[i].final = TRUE;
							lightClick.play(FALSE);
						}
					}
				}
			}

			if (placeState.active) {
				placeState.x = mousex;
				placeState.y = mousey;
			}

			if (moveState != -1) {
				Graph.stateList[moveState].x = mousex;
				Graph.stateList[moveState].y = mousey;
				if (Graph.stateList[moveState].x < 128 + 32) {
					Graph.stateList[moveState].x = 128 + 32;
				}
				if (Graph.stateList[moveState].x > 128 + 1024 - 32) {
					Graph.stateList[moveState].x = 128 + 1024 - 32;
				}
				if (Graph.stateList[moveState].y < 160 + 32) {
					Graph.stateList[moveState].y = 160 + 32;
				}
				if (Graph.stateList[moveState].y > 160 + 448 - 32) {
					Graph.stateList[moveState].y = 160 + 448 - 32;
				}
			}

			if (placeEdge != -1) {
				if (placeEdgeType == '0') {
					Graph.stateList[placeEdge].rot0 = Graph.stateList[placeEdge].getMouseAngle();
				}
				if (placeEdgeType == '1') {
					Graph.stateList[placeEdge].rot1 = Graph.stateList[placeEdge].getMouseAngle();
				}
			}
		}
	}

	// REMOVE THIS!!!
	if (GetKeyState(VK_BACK) & 0x8000 && !solveFlag) {
//		printf("YOU CHEAT!\n");
//		solveFlag = TRUE;
//		finishCounter = 0.0;
//		nextFlag = FALSE;
	}

	if (getMessageChoice() == 0) {
		if (freeplayMode) {
			loadGame();
			screen = PUZZLESCREEN;
			nextScreen = FREEPLAYSCREEN;
			freeplayMode = FALSE;
		} else {
			if (day > 3) {
				puzzleEnd = sound(failureAudio[letterSenders[day]][rand() % 3]);
				if (!freeplayMode) {
					puzzleEnd.play(false);
				}
				perfectGame = FALSE;
				levelCount += 1;
				nextScreen = DAYSCREEN;
				nextDay();
				saveGame();
			}
		}
	}

	if (testPassCounter > 0.0) {
		testPassCounter -= 1.0;
	}

}

bool firstEdgeActive = FALSE;

void drawPuzzleScreen() {
	placeimageeasy(interfaceTex, 0, 0, renderx, rendery, TRUE);

	if (displayType >= 1) {
		placeimageeasy(delete1, deletex, deletey, deleteSize, deleteSize, TRUE);
	}

	if (displayType >= 1) {
		for (int i = 0; i < 1; i++) {
			stateSet[i].draw(FALSE);
		}
	}

	firstEdgeActive = false;
	if (running) {
		if (inputIndex < 0) {
			firstEdgeActive = TRUE;
		}
		else {
			if (inputString[inputIndex] == 'a' || inputString[inputIndex] == 'r') {
				if (finishCounter == -1) {
					firstEdgeActive = TRUE;
				}
			}
		}
	}

	for (int i = 0; i < 40; i++) {
		Graph.stateList[i].lit = false;
	}

	if (running && Graph.currentState != -1 && Graph.lastState != -1 && finishCounter == -1) {
		if (inputString[inputIndex] == '1' || inputString[inputIndex] == '0') {
			if (stepCounter < stepCounterReset * 0.4) {
				Graph.stateList[Graph.currentState].lit = true;
			}
		}
	}

	if (running && inputIndex == -1 && finishCounter == -1 && stepCounter < stepCounterReset * 0.4) {
		Graph.stateList[0].lit = true;
	}

	if (moveState != -1) {
		Graph.stateList[moveState].lit = true;
	}

	Graph.draw();

	if (running && Graph.currentState != -1 && Graph.lastState != -1 && finishCounter == -1) {
		if (inputString[inputIndex] == '1' || inputString[inputIndex] == '0') {
			if (stepCounter > stepCounterReset * 0.4) {
				Graph.drawEdgeGlow(Graph.lastState, Graph.currentState, inputString[inputIndex], ((float)stepCounter - (float)(stepCounterReset * 0.4)) / ((float)stepCounterReset * 0.6));
				if (checkActiveWindow()) {
					if (rand() % 60 == 0 && sparkTimer <= 0) {
						if (Graph.lastState != Graph.currentState) {
							sparkFromState = Graph.lastState;
							sparkToState = Graph.currentState;
							sparkTimer = sparkTimerReset;
							sparkSound2.play(FALSE);
						}
					}
				}
			}
			if (stepCounter < stepCounterReset * 0.4) {
				Graph.stateList[Graph.currentState].draw(TRUE);
			}
			else {
				Graph.stateList[Graph.currentState].draw(FALSE);
				Graph.stateList[Graph.lastState].draw(FALSE);
			}
		}
		else {
			Graph.stateList[Graph.currentState].draw(FALSE);
		}
	}

	if (running && inputIndex == -1 && finishCounter == -1 && stepCounter < stepCounterReset * 0.4) {
		Graph.stateList[0].draw(TRUE);
	}

	if (placeState.active) {
		placeState.draw(TRUE);
	}

	if (moveState != -1) {
		Graph.stateList[moveState].draw(TRUE);
	}

	if (placeEdge != -1) {
		float x1 = Graph.stateList[placeEdge].x;
		float y1 = Graph.stateList[placeEdge].y;
		float dist = sqrt(pow(x1 - mousex, 2) + pow(y1 - mousey, 2));
		float midx = (x1 + mousex) / 2;
		float midy = (y1 + mousey) / 2;
		float rot = 0.0f;
		if (y1 - mousey != 0) {
			rot = -atan((x1 - mousex) / (y1 - mousey)) + (pi / 2);
		}
		else {
			if (x1 < mousex) {
				rot = 0.0f;
			}
			else {
				rot = pi;
			}
		}
		if (y1 > mousey) {
			rot -= pi;
		}
		float tileAmount = dist / 64.0;
		int nearState = -1;
		for (int i = 0; i < 40; i++) {
			if (Graph.stateList[i].mouseOver()) {
				nearState = i;
			}
		}
		if (nearState == -1) {
			if (placeEdgeType == '1') {
				placeimagerotatetile(wireGreen1, midx, midy, dist, 64, tileAmount, 1, 0.0, 0.2, rot, TRUE);
			}
			else {
				placeimagerotatetile(wireRed1, midx, midy, dist, 64, tileAmount, 1, 0.0, 0.2, rot, TRUE);
			}
			float tempRot = rot + 0.8 - pi;
			if (tempRot < -pi) {
				tempRot += 2 * pi;
			}
			float shadeOffset = -0.2;
			float shade = abs(tempRot / pi);
			glColor4f(1.0, 1.0, 1.0, shade + shadeOffset);
			placeimagerotatetile(wireShadeBottom, midx, midy, dist, 64, tileAmount, 1, 0.0, 0.2, rot, TRUE);
			glColor4f(1.0, 1.0, 1.0, 1.0 - shade + shadeOffset);
			placeimagerotatetile(wireShadeTop, midx, midy, dist, 64, tileAmount, 1, 0.0, 0.2, rot, TRUE);
			glColor4f(1.0, 1.0, 1.0, 1.0);
		}
		else {
			Graph.drawEdgeReal(placeEdge, nearState, placeEdgeType);
		}
		Graph.stateList[placeEdge].draw(FALSE);
	}

	Graph.drawBulbGlow();
//	Graph.drawEdgeReal(0, 0, false);

	if (sparkTimer > 0) {
		sparkTimer -= 1;
		Graph.drawEdgeSpark(sparkFromState, sparkToState, sparkTimer % 4);
	}

	playBtn.draw();
	stopBtn.draw();
	speedControl.draw();

	if (displayType >= 2) {
		exitButton.draw();
	}

//	placeimageeasy(tape1, 0, 157, 126, 454, TRUE);
	float tempOffset = ((stepCounter) / 256.0);
	if (stepCounter <= stepCounterReset / 2.0 && inputIndex >= -1 && finishCounter == -1) {
		tempOffset = ((stepCounter * 2.0) / 256.0);
	}
	if (stepCounter > stepCounterReset / 2.0 && inputIndex >= -1 && finishCounter == -1) {
		tempOffset = 64.0 / 256.0;
	}
	float tempTile = 454.0 / 256.0;
	placeimagerotatetile(tape1, 63, 157 + (454 / 2), 126, 454, 1, tempTile, 0, -tempOffset, 0.0, TRUE);

	if (displayType >= 2 && displayType != 3) {
		getCodewordButton.draw();
	}

	glColor3f(0.0, 0.0, 0.0);
	if (running) {
		char tempString[2];
		int tempLoc = -2;
		for (int i = -1; inputString[i] != '\0' || i == -1; i++) {
			tempLoc += 1;
			if (i == -1) {
				tempString[0] = '*';
			}
			else {
				tempString[0] = inputString[i];
				if (inputString[i] == 'f') {
					tempString[0] = ' ';
				}
				if (inputString[i] == 'a' || inputString[i] == 'r') {
					//				tempLoc -= 1;
					if (inputString[i + 1] != 'f') {
						tempString[0] = '*';
					}
					else {
						tempString[0] = ' ';
					}
				}
			}
			tempString[1] = '\0';
			if (inputIndex < -1 || finishCounter > 0) {
				drawtext(tempString, 47, (rendery / 2) - (tapeLoc * 64) + ((tempLoc + (1.8)) * 64) + stepCounter + 15, 54, 54);
			}
			else if (inputIndex >= -1 && stepCounter <= stepCounterReset / 2.0) {
				drawtext(tempString, 47, (rendery / 2) - (tapeLoc * 64) + ((tempLoc + (1.8)) * 64) + (stepCounter * 2.0) + 15, 54, 54);
			}
			else {
				drawtext(tempString, 47, (rendery / 2) - (tapeLoc * 64) + ((tempLoc + (1.8)) * 64) + 64.0 + 15, 54, 54);
			}
		}

		if (helpText && finishCounter == -1 && !solveFlag) {
			char tempText[20];
			if (inputString[inputIndex] == 'a' || inputString[inputIndex] == 'r' || inputIndex < -1) {
				strcpy_s(tempText, 20, "  Start");
			}
			else {
				if (Graph.stateList[Graph.currentState].final) {
					strcpy_s(tempText, 20, "Accepting");
				}
				else {
					strcpy_s(tempText, 20, "Rejecting");
				}
			}
			glColor4f(0.0, 0.0, 0.0, 0.7);
			drawtext(tempText, Graph.stateList[Graph.currentState].x - (24 * 4.3) + 4, Graph.stateList[Graph.currentState].y - 54 + 4, 24, 24);
			glColor4f(1.0, 1.0, 1.0, 1.0);
			drawtext(tempText, Graph.stateList[Graph.currentState].x - (24 * 4.3), Graph.stateList[Graph.currentState].y - 54, 24, 24);
		}

	}

	/*
	if (currentLevel.clueNum > 0) {
		drawtext("Clues:", renderx - 110, 180, 14, 14);
		for (int i = 0; i < currentLevel.clueNum; i++) {
			drawtext(currentLevel.clues[i], renderx - 100, 180 + 14 + (14 * i), 14, 14);
		}
	}
	drawtext("Accepted:", renderx - 110, 190 + ((currentLevel.clueNum + 1) * 14), 14, 14);
	for (int i = 0; i < currentLevel.clueUnlocks[2]; i++) {
		if (i < currentLevel.clueUnlocks[codeUnlockLevel]) {
			drawtext(currentLevel.acceptingStrings[i], renderx - 100, 190 + 14 + (14 * i) + ((currentLevel.clueNum + 1) * 14), 14, 14);
		}
	}
	drawtext("Rejected:", renderx - 110, 358 + ((currentLevel.clueNum + 1) * 14), 14, 14);
	for (int i = 0; i < currentLevel.clueUnlocks[2]; i++) {
		if (i < currentLevel.clueUnlocks[codeUnlockLevel]) {
			drawtext(currentLevel.rejectingStrings[i], renderx - 100, 358 + 14 + (14 * i) + ((currentLevel.clueNum + 1) * 14), 14, 14);
		}
	}
	*/

	glColor4f(0.0, 0.0, 0.0, 1.0);
	if (displayType >= 2 && displayType != 3) {
		if (currentLevel.par <= 26) {
			drawtext("  Get more bulbs:#     500 Intel", 816, rendery - 63, 20, 20, 0.75);
		}
		else {
			drawtext("Bulb limit reached", 825, rendery - 50, 20, 20, 0.75);
		}
		drawtext("INTEL", 217, 36, 20, 20, 0.8);
	}

	if (displayType >= 1) {
		drawtext("BULBS", 375, rendery - 88, 20, 20, 0.8);
	}

	drawtextCropped(descriptionDisplay, 636, 6, 16, 16, 35, 0.8);

	glColor3f(0.75, 0.75, 0.75);

	if (displayType >= 2 && displayType != 3) {
		_itoa_s(intelDisplay, intelString, 10);
		drawtext(intelString, 544 - (getintsize(intelDisplay) * 54), 74, 54, 54, 1.0);
	}

	if (displayType >= 1) {
		_itoa_s(currentLevel.par - Graph.getStateNum(), stateString, 10);
		drawtext(stateString, 478 - (getintsize(currentLevel.par - Graph.getStateNum()) * 54), rendery - 53, 54, 54, 1.0);
	}

	glColor3f(1.0, 1.0, 1.0);

	placeimageeasy(interfaceTexFront, 0, 0, renderx, rendery, TRUE);

	if (continueSpeech && descriptionBox[(int)descriptionCharCount] == '\0') {
		arrowFloat += 0.1;
		placeimageeasy(downArrow, renderx - 214, 100 + (sin(arrowFloat) * 6.0), 28, 28, TRUE);
	}

	toggleHelp.draw(toggleHelp.active);

	if (testPassCounter > testPassCounterReset - 5.0) {
		glColor4f(1.0, 1.0, 1.0, (testPassCounterReset - testPassCounter) / 5.0);
	}
	if (testPassCounter < 10.0) {
		glColor4f(1.0, 1.0, 1.0, testPassCounter / 10.0);
	}
	char tempText[3];
	strcpy_s(testPassText, 20, "Test ");
	_itoa_s(testNumber, tempText, 10);
	strcat_s(testPassText, 20, tempText);
	strcat_s(testPassText, 20, " passed");
	if (helpText) {
		drawtext(testPassText, 140, rendery - 148, 32, 32, 0.8);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		if (toggleHelp.mouseOver()) {
			drawtext("Help text", mousex - (24 * 8), mousey, 24, 24, 0.8);
		}
		else {
			if (moveState == -1 && !placeState.active && !running) {
				for (int i = 0; i < Graph.getStateNum(); i++) {
					if (Graph.stateList[i].mouseOver()) {
						if (i == 0) {
							drawtext("Rejecting (start)", mousex + 24, mousey, 24, 24, 0.8);
						}
						else {
							if (Graph.stateList[i].final) {
								drawtext("Accepting", mousex + 24, mousey, 24, 24, 0.8);
							}
							else {
								drawtext("Rejecting", mousex + 24, mousey, 24, 24, 0.8);
							}
						}
					}
				}
			}
		}
	}

	glColor4f(1.0, 1.0, 1.0, 1.0);

}