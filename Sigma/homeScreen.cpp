#include "main.h"

GLuint rotorArrow1;
GLuint rotorCover;

rotor::rotor() {

}

rotor::rotor(int inimage, float inx, float iny, float inrotSpeed, int inmoveTimeReset, int intimeOutReset) {
	image = inimage;
	x = inx;
	y = iny;
	rot = 0.0;
	rotSpeed = inrotSpeed;
	moving = false;
	moveTimeReset = inmoveTimeReset;
	timeOutReset = intimeOutReset;
	timer = timeOutReset;
	rotorSize = 256;
}

void rotor::move() {
	if (moving) {
		rot += rotSpeed;
	}
	timer -= 1;
	if (timer <= 0) {
		if (moving) {
			moving = false;
			timer = timeOutReset;
		}
		else {
			moving = true;
			timer = moveTimeReset;
		}
	}
}

void rotor::draw() {
	glColor3f(0.95, 0.95, 0.95);
	placeimagerotatecentre(image, x, y, rotorSize, rotorSize, rot, TRUE);
	placeimagerotatecentre(rotorArrow1, x, y, rotorSize, rotorSize, 0.0, TRUE);
	glColor4f(1.0, 1.0, 1.0, 0.8);
	placeimagerotatecentre(rotorCover, x, y, rotorSize, rotorSize, 0.0, TRUE);
	glColor4f(1.0, 1.0, 1.0, 1.0);
}

rotor fast1;
rotor medium1;
rotor slow1;
rotor fast2;
rotor medium2;
rotor slow2;
rotor fast3;
rotor medium3;
rotor slow3;

GLuint rotor1Yellow;
GLuint rotor1Green;
GLuint rotor1Red;

GLuint background;

GLuint homeButtonOff;
GLuint homeButtonOn;

button newGame;
button continueGame;
button options;
button history;
button quit;

void initHomeScreen() {
	rotor1Yellow = LoadTexture(homeDirectory, "rotor1b.png");
	rotor1Red = LoadTexture(homeDirectory, "rotor2b.png");
	rotor1Green = LoadTexture(homeDirectory, "rotor3b.png");
	rotorCover = LoadTexture(homeDirectory, "rotorCover1.png");

	background = LoadTexture(homeDirectory, "homescreenBack.png");

	homeButtonOff = LoadTexture(homeDirectory, "homeButton1_off.png");
	homeButtonOn = LoadTexture(homeDirectory, "homeButton1_on.png");

	continueGame = button("continue", -110, 290, 640, 64, homeButtonOff, homeButtonOn, homeButtonOff);
	newGame = button("continue", -110, 290 + (77 * 1), 640, 64, homeButtonOff, homeButtonOn, homeButtonOff);
	options = button("continue", -110, 290 + (77 * 3), 640, 64, homeButtonOff, homeButtonOn, homeButtonOff);
	history = button("continue", -110, 290 + (77 * 2), 640, 64, homeButtonOff, homeButtonOn, homeButtonOff);
	quit = button("continue", -110, 290 + (77 * 4), 640, 64, homeButtonOff, homeButtonOn, homeButtonOff);

	fast1 = rotor(rotor1Yellow, (renderx / 2) + 48, (rendery / 2) - 128, (2 * pi) / 26.0 / 1, 1, 0);
	medium1 = rotor(rotor1Red, (renderx / 2) + 48, (rendery / 2) + 128, (2 * pi) / 26.0 / 6.0, 6, (25 * 2) - 4);
	slow1 = rotor(rotor1Green, (renderx / 2) + 48, (rendery / 2) + 128 + 256, (2 * pi) / 26.0 / 6.0, 6, (26 * 26 * 2) - 6);

	fast2 = rotor(rotor1Yellow, (renderx / 2) + 48 + 256, (rendery / 2) - 128, (2 * pi) / 26.0 / 1, 1, 0);
	medium2 = rotor(rotor1Red, (renderx / 2) + 48 + 256, (rendery / 2) + 128, (2 * pi) / 26.0 / 6.0, 6, (25 * 2) - 4);
	slow2 = rotor(rotor1Green, (renderx / 2) + 48 + 256, (rendery / 2) + 128 + 256, (2 * pi) / 26.0 / 6.0, 6, (26 * 26 * 2) - 6);

	fast3 = rotor(rotor1Yellow, (renderx / 2) + 48 + 512, (rendery / 2) - 128, (2 * pi) / 26.0 / 1, 1, 0);
	medium3 = rotor(rotor1Red, (renderx / 2) + 48 + 512, (rendery / 2) + 128, (2 * pi) / 26.0 / 6.0, 6, (25 * 2) - 4);
	slow3 = rotor(rotor1Green, (renderx / 2) + 48 + 512, (rendery / 2) + 128 + 256, (2 * pi) / 26.0 / 6.0, 6, (26 * 26 * 2) - 6);

	rotorArrow1 = LoadTexture(homeDirectory, "rotorArrow1.png");
}

void moveRotors() {
	fast1.move();
	medium1.move();
	slow1.move();
	fast2.move();
	medium2.move();
	slow2.move();
	fast3.move();
	medium3.move();
	slow3.move();
	if (fast1.rot > (pi * 2) - 1.6) {
		fast1.rot -= pi * 2;
		bombeTick1.play(FALSE);
	}
	if (slow1.rot > (pi * 2)) {
		slow1.rot -= pi * 2;
		easterEgg.play(FALSE);
		printf("This is not an easter egg!\n");
	}
}

void manageHomeScreen() {

	if (messageAnim > 0) {
	}
	else {
		if (continueGame.mouseOver()) {
			if (!continueGame.hover) {
				tick1.play(FALSE);
			}
			continueGame.hover = TRUE;
			if (leftclick) {
				if (lastScreen != HOMESCREEN) {
					if (day == 0) {
						showMessage("No save data found");
					}
					else {
						continueGame.hover = FALSE;
						bulbPickup.play(FALSE);
						nextScreen = lastScreen;
					}
				}
				else {
					showMessage("No save data found");
				}
			}
		}
		else {
			continueGame.hover = FALSE;
		}

		if (newGame.mouseOver()) {
			if (!newGame.hover) {
				tick1.play(FALSE);
			}
			newGame.hover = TRUE;
			if (leftclick) {
				if (day == 0) {
					bulbPickup.play(FALSE);
					resetGame();
					saveGame();
					newGame.hover = FALSE;
					initCutScene();
					freeplayMode = FALSE;
					nextScreen = CUTSCENE;
				}
				else {
					showOptionMessage("This will override your current save data. Are you sure you want to start a new game?");
				}
			}
		}
		else {
			newGame.hover = FALSE;
		}

		if (getMessageChoice() == 0) {
			bulbPickup.play(FALSE);
			resetGame();
			saveGame();
			newGame.hover = FALSE;
			initCutScene();
			freeplayMode = FALSE;
			nextScreen = CUTSCENE;
		}

		if (options.mouseOver()) {
			if (!options.hover) {
				tick1.play(FALSE);
			}
			options.hover = TRUE;
			if (leftclick) {
				options.hover = FALSE;
				bulbPickup.play(FALSE);
				nextScreen = OPTIONSSCREEN;
			}
		}
		else {
			options.hover = FALSE;
		}

		if (history.mouseOver()) {
			if (!history.hover) {
				tick1.play(FALSE);
			}
			history.hover = TRUE;
			if (leftclick) {
				bulbPickup.play(FALSE);
				history.hover = FALSE;
				if (freeplayUnlocked) {
					nextScreen = FREEPLAYSCREEN;
				}
				else {
					showMessage("Play through the campaign and win the war to unlock free play mode");
				}
			}
		}
		else {
			history.hover = FALSE;
		}

		if (quit.mouseOver()) {
			if (!quit.hover) {
				tick1.play(FALSE);
			}
			quit.hover = TRUE;
			if (leftclick) {
				bulbPickup.play(FALSE);
				saveGame();
				exit(0);
			}
		}
		else {
			quit.hover = FALSE;
		}
	}

}

void drawHomeScreen() {

	placeimageeasy(background, 0, 0, renderx, rendery, TRUE);

	fast1.draw();
	medium1.draw();
	slow1.draw();
	fast2.draw();
	medium2.draw();
	slow2.draw();
	fast3.draw();
	medium3.draw();
	slow3.draw();

	glColor4f(1.0, 1.0, 1.0, 0.4);
	placeimageeasy(menuOverlay1, 0, 0, renderx, rendery, TRUE);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	glColor4f(0.0, 0.0, 0.0, 0.45);
	for (int i = 0; i < 5; i++) {
		placeimageeasy(homeButtonOff, -104, 297 + (77 * i), 640, 64, TRUE);
	}
	glColor4f(1.0, 1.0, 1.0, 1.0);

	continueGame.draw();
	newGame.draw();
	options.draw();
	history.draw();
	quit.draw();

	glColor3f(0.05, 0.05, 0.05);
	drawtext("Continue", 38, 310, 32, 32, 1.98);
	drawtext("New game", 38, 310 + (77 * 1), 32, 32, 1.98);
	drawtext("Freeplay", 38, 310 + (77 * 2), 32, 32, 1.98);
	drawtext("Options", 38, 310 + (77 * 3), 32, 32, 1.98);
	drawtext("Quit", 38, 310 + (77 * 4), 32, 32, 1.98);
	glColor3f(1.0, 1.0, 1.0);
}