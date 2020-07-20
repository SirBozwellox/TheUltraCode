#include "main.h"

GLuint homeButtonOff2;
GLuint homeButtonOn2;

button fullscreen;
button volume;
button exitBtn;
slider volControl;

void initOptionsScreen() {
	homeButtonOff2 = LoadTexture(homeDirectory, "homeButton1_off.png");
	homeButtonOn2 = LoadTexture(homeDirectory, "homeButton1_on.png");

	fullscreen = button("fullscreen", -110, 290, 640, 64, homeButtonOff2, homeButtonOn2, homeButtonOff2);
	volume = button("volume", -110, 290 + (77 * 1), 640, 64, homeButtonOff2, homeButtonOn2, homeButtonOff2);
	volume.active = TRUE;
	exitBtn = button("exit", -110, 290 + (77 * 4), 640, 64, homeButtonOff2, homeButtonOn2, homeButtonOff2);
	volControl = slider("volControl", 150, 452, 256, 64, sliderBack1, sliderFront1, 0);
	volControl.position = globalVolume;
}

void manageOptionsScreen() {

	if (fullscreen.mouseOver()) {
		if (!fullscreen.hover) {
			tick1.play(FALSE);
		}
		fullscreen.hover = TRUE;
		if (leftclick) {
			bulbPickup.play(FALSE);
			if (fullscreenFlag) {
				windowx = oldWindowx;
				windowy = oldWindowy;
				fullscreenFlag = FALSE;
				resizeWindow(windowx, windowy);
			}
			else {
				oldWindowx = windowx;
				oldWindowy = windowy;
				resizeWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
				fullscreenFlag = TRUE;
			}
			glutFullScreenToggle();
		}
	}
	else {
		fullscreen.hover = FALSE;
	}

	if (exitBtn.mouseOver()) {
		if (!exitBtn.hover) {
			tick1.play(FALSE);
		}
		exitBtn.hover = TRUE;
		if (leftclick) {
			bulbPickup.play(FALSE);
			exitBtn.hover = FALSE;
			nextScreen = HOMESCREEN;
			saveGame();
		}
	}
	else {
		exitBtn.hover = FALSE;
	}

	if (volControl.mouseOver() && leftclick_flag) {
		volControl.calcPosition();
		globalVolume = volControl.position;
	}
	else {
		volControl.position = globalVolume;
	}

}

void drawOptionsScreen() {

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

	glColor4f(1.0, 1.0, 1.0, 0.6);
	placeimageeasy(menuOverlay1, 0, 0, renderx, rendery, TRUE);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	glColor4f(0.0, 0.0, 0.0, 0.45);
	placeimageeasy(homeButtonOff2, -104, 297 + (77 * 0), 640, 64, TRUE);
	placeimageeasy(homeButtonOff2, -104, 297 + (77 * 1), 640, 64, TRUE);
	placeimageeasy(homeButtonOff2, -104, 297 + (77 * 4), 640, 64, TRUE);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	fullscreen.draw();
	volume.draw();
	exitBtn.draw();

	glColor3f(0.05, 0.05, 0.05);
	if (!fullscreenFlag) {
		drawtext("Full", 38, 310, 32, 32, 1.98);
	}
	else {
		drawtext("Window", 38, 310, 32, 32, 1.98);
	}
	drawtext("Volume", 38, 310 + (77 * 1), 32, 32, 1.98);
	drawtext("Return", 38, 310 + (77 * 4), 32, 32, 1.98);
	glColor3f(1.0, 1.0, 1.0);

	volControl.draw();
}