#include "main.h"

int tutorialLevel;
bool continueSpeech;

sound tutorial_1_1;
sound tutorial_1_2;
sound tutorial_1_3;
sound tutorial_1_4;
sound tutorial_1_5;
sound tutorial_1_6;
sound tutorial_1_7;
sound tutorial_1_8;
sound tutorial_1_9;
sound tutorial_1_10;
sound tutorial_1_11;
sound tutorial_1_12;
sound tutorial_1_12b;

sound tutorial_2_1;
sound tutorial_2_2;
sound tutorial_2_3;
sound tutorial_2_4;

sound tutorial_3_1;
sound tutorial_3_2;
sound tutorial_3_3;
sound tutorial_3_4;
sound tutorial_3_5;
sound tutorial_3_exit;
sound tutorial_3_intel;

void initTutorialManager() {
	tutorialLevel = 0;
	continueSpeech = FALSE;

	tutorial_1_1 = sound("vo/tutorial_1-1.mp3");
	tutorial_1_2 = sound("vo/tutorial_1-2.mp3");
	tutorial_1_3 = sound("vo/tutorial_1-3.mp3");
	tutorial_1_4 = sound("vo/tutorial_1-4.mp3");
	tutorial_1_5 = sound("vo/tutorial_1-5.mp3");
	tutorial_1_6 = sound("vo/tutorial_1-6.mp3");
	tutorial_1_7 = sound("vo/tutorial_1-7.mp3");
	tutorial_1_8 = sound("vo/tutorial_1-8.mp3");
	tutorial_1_9 = sound("vo/tutorial_1-9.mp3");
	tutorial_1_10 = sound("vo/tutorial_1-10.mp3");
	tutorial_1_11 = sound("vo/tutorial_1-11.mp3");
	tutorial_1_12 = sound("vo/tutorial_1-12.mp3");
	tutorial_1_12b = sound("vo/tutorial_1-12b.mp3");

	tutorial_2_1 = sound("vo/tutorial_2-1.mp3");
	tutorial_2_2 = sound("vo/tutorial_2-2.mp3");
	tutorial_2_3 = sound("vo/tutorial_2-3.mp3");
	tutorial_2_4 = sound("vo/tutorial_2-4.mp3");

	tutorial_3_1 = sound("vo/tutorial_3-1.mp3");
	tutorial_3_2 = sound("vo/tutorial_3-2.mp3");
	tutorial_3_3 = sound("vo/tutorial_3-3.mp3");
	tutorial_3_4 = sound("vo/tutorial_3-4.mp3");
	tutorial_3_5 = sound("vo/tutorial_3-5.mp3");
	tutorial_3_exit = sound("vo/tutorial_3-exit.mp3");
	tutorial_3_intel = sound("vo/tutorial_3-intel.mp3");

}

void manageTutorial() {
	continueSpeech = FALSE;

	if (screen == PUZZLESCREEN & !freeplayMode) {
		if (day == 1) {
			if (tutorialLevel == 0 && !solveFlag) {
				newDescription("Mr Taylor I presume. Commander Travis said you'd be coming. I'm Alan Turing, the man in charge of hut 8. Anyway enough of the introductions, we'd better get started.");
				tutorialAudio = tutorial_1_1;
				tutorialAudio.play(false);
				tutorialLevel += 1;
			}
			if (tutorialLevel == 1) {
				continueSpeech = TRUE;
				if (leftclick && descriptionBox[(int)descriptionCharCount] == '\0') {
					newDescription("First off try moving one of the bulbs in the middle by holding down the left click and dragging it.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_1_2;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 2) {
				if (moveState != -1) {
					newDescription("Good. Now you'll notice two wires coming out of each bulb. Try clicking and dragging a wire to move it.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_1_3;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 3) {
				if (placeEdge != -1) {
					newDescription("Now try dragging a wire from one bulb to the other to connect them.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_1_4;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 4) {
				if (Graph.edgeExists(0, 1) || Graph.edgeExists(1, 0)) {
					newDescription("You can also use a wire to connect a bulb to itself, try that.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_1_5;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 5) {
				if (Graph.edgeExists(0, 0) || Graph.edgeExists(1, 1)) {
//					newDescription("Very good indeed. These wires act as transitions for each digit in a codeword. A codeword will only be accepted if the last bulb that's on is green. You can make any bulb accepting, except the starting blue one, by right clicking on it. Try making the A bulb accepting.");
					newDescription("Very good indeed. These numbered wires show where the current will flow for each digit in a codeword.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_1_6;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 6) {
				continueSpeech = TRUE;
				if (leftclick && descriptionBox[(int)descriptionCharCount] == '\0') {
					newDescription("Once a codeword has been read by the machine, if the last bulb that's on is clear then the codeword is rejected. However if the last bulb that's on is green then the machine will accept the codeword.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_1_7;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 7) {
				continueSpeech = TRUE;
				if (leftclick && descriptionBox[(int)descriptionCharCount] == '\0') {
					newDescription("You can make any bulb accepting, apart from the starting blue one, by right clicking on it. Try making the A bulb an accepting bulb.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_1_8;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 8) {
				if (Graph.stateList[1].final) {
					newDescription("By default any bulbs you add will reject codewords if they are on at the end. Now try connecting all the wires, anyway you want, and then press the play button on the right.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_1_9;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 9) {
				if (running) {
					newDescription("When the machine is running a set of test codes will come through on the tape on the left. You can stop the tape with the stop button or change the speed with the slider.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_1_10;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 10) {
				continueSpeech = TRUE;
				if (leftclick && descriptionBox[(int)descriptionCharCount] == '\0') {
					newDescription("As you can see for each number in the codeword the current flows through the relevant wire from bulb to bulb.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_1_11;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 11) {
				continueSpeech = TRUE;
				if (leftclick && descriptionBox[(int)descriptionCharCount] == '\0') {
					tutorialAudio.stop();
					if (!running) {
						newDescription("Now try connecting the wires so that if a codeword contains at least a single 1 then it'll be accepted, but a codeword that's all 0s will be rejected.");
						tutorialAudio = tutorial_1_12;
						tutorialAudio.play(false);
					}
					else {
						if (finishCounter >= 0 && finishCounter <= 8) {
							newDescription("Now try connecting the wires so that if a codeword contains at least a single 1 then it'll be accepted, but a codeword that's all 0s will be rejected.");
							tutorialAudio = tutorial_1_12;
							tutorialAudio.play(false);
						}
						else {
							newDescription("Now stop the machine and try connecting the wires so that if a codeword contains at least a single 1 then it'll be accepted, but a codeword that's all 0s will be rejected.");
							tutorialAudio = tutorial_1_12b;
							tutorialAudio.play(false);
						}
					}
					tutorialLevel += 1;
				}
			}
			if (solveFlag) {
			}
		}

		if (day == 2) {
			if (tutorialLevel == 0) {
				newDescription("Welcome back Mr Taylor, can I call you William? Anyway let's get back to work shall we?");
				tutorialAudio = tutorial_2_1;
				tutorialAudio.play(false);
				tutorialLevel += 1;
			}
			if (tutorialLevel == 1) {
				continueSpeech = TRUE;
				if (leftclick && descriptionBox[(int)descriptionCharCount] == '\0') {
					newDescription("Firstly try adding a new bulb to the machine by dragging it from the plus on the bottom left and dropping it on to the plug board in the middle.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_2_2;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 2) {
				if (Graph.stateList[1].active) {
					newDescription("You can also remove any bulbs, except the starting one, by dragging them over the red X in the bottom right corner.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_2_3;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 3) {
				if (!Graph.stateList[1].active) {
					newDescription("Excellent. Now today's Enigma settings only seem to accept codewords where the last digit is a 1, codewords that end in a 0 are rejected. Try building a machine to filter these codewords.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_2_4;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (solveFlag) {
			}
		}

		if (day == 3) {
			if (tutorialLevel == 0) {
				newDescription("William! Good to finally meet you old chap, Alan's told me a lot about you. Well then, let's finish off your training...");
				tutorialAudio = tutorial_3_1;
				tutorialAudio.play(false);
				tutorialLevel += 1;
			}
			if (tutorialLevel == 1) {
				continueSpeech = TRUE;
				if (leftclick && descriptionBox[(int)descriptionCharCount] == '\0') {
					newDescription("As you know each time we break a code we gain some intel about the enemy. You can spend this intel on a number of things, including new bulbs to help build machines. Try buying a bulb by clicking on the note at the bottom.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_3_2;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 2) {
				if (currentLevel.par > 2) {
					newDescription("Good. Finally, if you're completely stumped and can't solve the Enigma settings for a particular day then you can always click the exit button at the bottom.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_3_3;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 3) {
				continueSpeech = TRUE;
				if (leftclick && descriptionBox[(int)descriptionCharCount] == '\0' && !exitButton.mouseOver()) {
					newDescription("But you obviously won't earn any intel for that day. Anyway I'm sure you'll never need to use it, let's crack on with today's settings.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_3_4;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 4) {
				continueSpeech = TRUE;
				if (leftclick && descriptionBox[(int)descriptionCharCount] == '\0') {
					newDescription("Use the three bulbs you've got to construct a machine that allows any codewords where the first digit is a 1 and rejects codewords where the first digit is a 0. Good luck William.");
					tutorialAudio.stop();
					tutorialAudio = tutorial_3_5;
					tutorialAudio.play(false);
					tutorialLevel += 1;
				}
			}
			if (tutorialLevel == 5) {
//				if (leftclick && descriptionBox[(int)descriptionCharCount] == '\0') {
//					newDescription("Now use the three bulbs you've got to construct a machine that allows any codewords where the first digit is a 1 and rejects codewords where the first digit is a 0. Good luck Mr Taylor.");
//					tutorialLevel += 1;
//				}
			}
		}

	}
	else {
		if (screen != HOMESCREEN && screen != OPTIONSSCREEN && screen != FREEPLAYSCREEN) {
			tutorialLevel = 0;
		}
	}

}