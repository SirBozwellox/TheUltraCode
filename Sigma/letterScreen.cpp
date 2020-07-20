#include "main.h"

GLuint letterScreen1;
GLuint envelope1;
GLuint letter1;

GLuint smallFont;

envelope env1;

letter let1;

button continueButton3;

bool showLetter = FALSE;
float letterFade = 0.0;

GLuint signatures[4];

int letterSenders2[22] = { 0, 1, 1, 1, 1, 2, 0, 2, 0, 1, 2, 2, 3, 1, 2, 0, 2, 1, 1, 0, 0, 0 };

envelope::envelope() {
	x = 0;
	y = 0;
	movex = 0;
	movey = 0;
	accelx = 0;
	accely = 0;
	rot = 0;
	accelrot = 0;
	image = blank;
	width = 0;
	height = 0;
}

envelope::envelope(int inimage, float inx, float iny, float inwidth, float inheight) {
	image = inimage;
	x = inx;
	y = iny;
	rot = 0;
	width = inwidth;
	height = inheight;
	movex = 0;
	movey = 0;
	moverot = 0;
	accelx = 0;
	accely = 0;
	accelrot = 0;
}

void envelope::setMove(float inx, float iny, float inrot) {
	movex = inx;
	movey = iny;
	moverot = inrot;
}

void envelope::setAccel(float inx, float iny, float inrot) {
	accelx = inx;
	accely = iny;
	accelrot = inrot;
}

void envelope::move() {
	x += movex;
	y += movey;
	rot += moverot;
	movex += accelx;
	movey += accely;
	moverot += accelrot;
	if (abs(movex) <= abs(accelx)) {movex = 0.0;}
	if (abs(movey) <= abs(accely)) { movey = 0.0; }
	if (abs(moverot) <= abs(accelrot)) { moverot = 0.0; }
}

void envelope::draw() {
	glColor4f(0.0, 0.0, 0.0, 0.5);
	placeimagerotatecentre(image, x + 4, y + 4, width, height, rot, TRUE);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	placeimagerotatecentre(image, x, y, width, height, rot, TRUE);
}

letter::letter() {
	font = blank;
	image = blank;
}

letter::letter(int inimage, int infont, char intext[2000]) {
	image = inimage;
	font = infont;
	strcpy_s(text, 2000, intext);
}

void letter::draw() {
	placeimageeasy(image, (renderx / 2) - 400, 64, 705, 950, TRUE);
	glColor3f(0.0, 0.0, 0.0);
	drawtextCropped3(text, (renderx / 2) + 8 - 382, 86 + 4, 13, 13, 50, smallFont);
	glColor3f(1.0, 1.0, 1.0);
}

void initLetterScreen() {
	letterScreen1 = LoadTexture(homeDirectory, "letterScreen1.png");
	envelope1 = LoadTexture(homeDirectory, "letter2.png");
	letter1 = LoadTexture(homeDirectory, "letterBack1.png");
	continueButton3 = button("continue", 957, rendery + 1, 312, 94, codewordButton1, codewordButton2, codewordButton2);
	env1 = envelope(envelope1, -320, rendery / 2, 640, 320);
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	env1.rot = -2.0;
	env1.setMove(20.0, 0, 0.0415 + (r * 0.005));
	env1.setAccel(-0.21, 0, -0.0005);
	showLetter = FALSE;
	letterFade = 0.0;
	loadCurrentLetter();
	let1 = letter(letter1, font2, curLetterText);
	printf("Letter screen initalised\n");

	smallFont = LoadTexture(homeDirectory, "fontlist4_small.png");

	signatures[0] = LoadTexture(homeDirectory, "signatureTravis.png");
	signatures[1] = LoadTexture(homeDirectory, "signatureTuring.png");
	signatures[2] = LoadTexture(homeDirectory, "signatureHugh.png");
	signatures[3] = LoadTexture(homeDirectory, "signatureNewman.png");
}

void manageLetterScreen() {

	continueButton3.hover = FALSE;
	if (continueButton3.mouseOver()) {
		continueButton3.hover = TRUE;
	}

	if (leftclick) {
		if (!showLetter && env1.movex == 0.0) {
			openLetter.play(FALSE);
			showLetter = TRUE;
			letterAudio.play(false);
		}
		if (continueButton3.mouseOver() && showLetter) {
			if (cueOperationIntro == -1) {
				if (levelCount < 0) {
					nextScreen = PUZZLESCREEN;
					initPuzzleScreen();
				}
				else {
					if (day == maxDay + 1) {
						initCutScene();
						nextScreen = CUTSCENE;
					}
					else {
						nextScreen = CHOOSESCREEN;
						initChooseScreen();
					}
				}
			}
			else {
				printf("Cue operation cutscene: %i\n", cueOperationIntro);
				nextScreen = CUTSCENE;
				initCutScene();
			}
//			managePuzzleScreen();
		}
		else {
			if (showLetter) {
//				curLetter += 1;
//				loadLetterText(letterList[curLetter]);
//				let1 = letter(letter1, font2, curLetterText);
			}
		}
	}

	if (showLetter) {
		if (continueButton3.y > rendery - 94 && letterFade > 0.5) {
			continueButton3.y -= 5;
		}
		if (letterFade < 1.0) {
			letterFade += 0.05;
		}
	}

	env1.move();

}

void drawLetterScreen() {
	placeimageeasy(letterScreen1, 0, 0, renderx, rendery, TRUE);

	env1.draw();

	glColor4f(0.0, 0.0, 0.0, letterFade * 0.6);
	placeimageeasy(letterScreen1, 0, 0, renderx, rendery, TRUE);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	if (letterFade > 0.0) {
		glColor4f(1.0, 1.0, 1.0, letterFade);
		let1.draw();
		glColor4f(1.0, 1.0, 1.0, letterFade * 0.9);
		if (day == 21) {
			if (levelCount == 19) {
				placeimageeasy(signatures[1], 620, rendery - 70, 72 * 4, 72, true);
			}
			else {
				placeimageeasy(signatures[0], 620, rendery - 70, 72 * 4, 72, true);
			}
		}
		else {
			placeimageeasy(signatures[letterSenders2[day - 1]], 620, rendery - 70, 72 * 4, 72, true);
		}
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}


	continueButton3.draw();

	glColor3f(0.0, 0.0, 0.0);

	drawtext("Continue", 1018, continueButton3.y + 38, 32, 32, 0.7);

	glColor3f(1.0, 1.0, 1.0);

}