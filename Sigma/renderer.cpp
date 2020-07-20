#include "main.h"

using namespace std;

float windowx = 1;
float windowy = 1;
float oldWindowx = 1;
float oldWindowy = 1;
float screenmultx = 1.0;
float screenmulty = 1.0;

bool stretch = FALSE;
bool fullscreenFlag = FALSE;

int const sparkNum = 200;

spark sparkList[sparkNum];

int shakeOffset = 0;

void manageShake() {
	if (shakeOffset < 0) {
		shakeOffset = -(shakeOffset + 1);
	}
	else if (shakeOffset > 0) {
		shakeOffset = -(shakeOffset - 1);
	}
	if (abs(shakeOffset) < 5) {
		shakeOffset = 0;
	}
}

void setShake(int offset) {
	shakeOffset = offset;
}

void resetSparks() {
	for (int i = 0; i < sparkNum; i++) {
		sparkList[i] = spark();
	}
}

void createSparks(float inx, float iny, int num) {
	for (int x = 0; x < num; x++) {
		bool found = FALSE;
		for (int i = 0; i < sparkNum; i++) {
			if (!sparkList[i].active && !found) {
				found = TRUE;
				float mx = ((rand() % 100) - 50) * 0.06;
				float my = ((rand() % 100) - 100) * 0.075;
				sparkList[i] = spark(inx, iny, mx, my);
			}
		}
	}
	sparkSound1.play(FALSE);
}

void manageSparks() {
	for (int i = 0; i < sparkNum; i++) {
		sparkList[i].move();
		if (sparkList[i].y > rendery + 16) {
			sparkList[i] = spark();
		}
	}
}

GLuint tex1;
GLuint blank;

GLuint state1;
GLuint state1on;
GLuint stateBack;
GLuint stateBackOn;

GLuint wireGreen1;
GLuint wireRed1;
GLuint wireGreen2;
GLuint wireRed2;
GLuint wireRedLoop1;
GLuint wireGreenLoop1;
GLuint wireRedGreen1;
GLuint wireGlow1;
GLuint wireGlow2;
GLuint wireBlack1;
GLuint wireShadeBottom;
GLuint wireShadeTop;
GLuint wireLoopShadeBottom;
GLuint wireLoopShadeTop;
GLuint wireLoopShadeLeft;
GLuint wireLoopShadeRight;

GLuint delete1;

GLuint buttonUp1;
GLuint buttonDown1;

GLuint playButtonUp;
GLuint playButtonDown;

GLuint stopButtonUp;
GLuint stopButtonDown;

GLuint exitButtonUp;
GLuint exitButtonDown;

GLuint messageBoxImg;
GLuint cog1;
GLuint success1;

GLuint sliderBack1;
GLuint sliderBack2;
GLuint sliderFront1;
GLuint sliderFront2;

GLuint codewordButton1;
GLuint codewordButton2;

GLuint bulb1;
GLuint bulb2;
GLuint bulb3;

GLuint whiteRotor;

GLuint buttonOff;
GLuint buttonOn;

GLuint spark1;
GLuint spark2a;
GLuint spark2b;
GLuint spark2c;
GLuint spark2d;

GLuint glow1;
GLuint glow2;
GLuint glow3;

GLuint menuOverlay1;

GLuint loadingScreen;

float gravity = 0.4;

spark::spark() {
	x = 0.0;
	y = 0.0;
	movex = 0.0;
	movey = 0.0;
	active = FALSE;
	timer = 0;
}

spark::spark(float inx, float iny, float inmovex, float inmovey) {
	timer = 25;
	x = inx;
	y = iny;
	movex = inmovex;
	movey = inmovey;
	active = TRUE;
}

void spark::move() {
	oldx = x;
	oldy = y;
	if (active) {
		timer -= 1;
		if (timer <= 0) {
			active = FALSE;
		}
		x += movex;
		y += movey;
		movey += gravity;
	}
}

void spark::draw() {
	if (active) {
		glColor4f(1.0, 1.0, 1.0, (timer / 10.0));
		placeimageeasy(spark1, oldx - 3, oldy - 2, 4, 4, TRUE);
		glColor4f(1.0, 1.0, 1.0, timer / 10.0);
		placeimageeasy(spark1, x - 3, y - 2, 4, 4, TRUE);
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
}

float fadeValue = 0.0;

void drawSprite(int spriteTex, float posx, float posy, float posz, float size, bool smoothTex)
{
	float tempCoords[3] = { 0.0, 0.0, 0.0 };
	placeimageeasy(spriteTex, tempCoords[0] - (size * 0.5f), tempCoords[1] - (size * 1.33f * 0.5f), size, size * 1.33f, smoothTex);
}

char consoleText[20][300];
int consoleTimer = 0;
bool consoleEnabled = TRUE;

void consoleLog(char text[300], ...) {

	va_list valist;

	for (int i = 9; i > 0; i--) {
		strcpy_s(consoleText[i], consoleText[i - 1]);
	}

	char outText[300] = "";

	int i = 0;
	int l = 0;
	while (text[i] != '\0') {
		if (text[i] == '%') {
			switch (text[i]) {
				case 's':
					break;
			}
		}
		i++;
	}

	strcpy_s(consoleText[0], text);
	printf(text);
}

void renderConsole() {
	if (consoleEnabled) {
		for (int i = 0; i < 20; i++) {
			drawtext(consoleText[i], 8, windowx - 8 - (i * 16), 16, 16);
		}
	}
}

void initRenderer(int windowWidth, int windowHeight)
{
	resizeWindow(windowWidth, windowHeight);
	oldWindowx = windowWidth;
	oldWindowy = windowHeight;

	tex1 = LoadTexture(homeDirectory, "stone1.png");
	blank = LoadTexture(homeDirectory, "blank.png");

	font1 = LoadTexture(homeDirectory, "fontlist2.png");
	font2 = LoadTexture(homeDirectory, "fontlist4.png");

	state1 = LoadTexture(homeDirectory, "state2.png");
	state1on = LoadTexture(homeDirectory, "state2on.png");

	stateBack = LoadTexture(homeDirectory, "stateBack.png");
	stateBackOn = LoadTexture(homeDirectory, "stateBackOn.png");

	wireGreen1 = LoadTexture(homeDirectory, "wireGreen1.png");
	wireRed1 = LoadTexture(homeDirectory, "wireRed1.png");
	wireGreen2 = LoadTexture(homeDirectory, "wireGreen2.png");
	wireRed2 = LoadTexture(homeDirectory, "wireRed2.png");
	wireRedLoop1 = LoadTexture(homeDirectory, "wireRedLoop1.png");
	wireGreenLoop1 = LoadTexture(homeDirectory, "wireGreenLoop1.png");
	wireRedGreen1 = LoadTexture(homeDirectory, "wireRedGreen2.png");
	wireGlow1 = LoadTexture(homeDirectory, "wireGlow1.png");
	wireGlow2 = LoadTexture(homeDirectory, "wireGlow2.png");
	wireBlack1 = LoadTexture(homeDirectory, "wireBlack1.png");
	wireShadeBottom = LoadTexture(homeDirectory, "wireShadeBottom.png");
	wireShadeTop = LoadTexture(homeDirectory, "wireShadeTop.png");
	wireLoopShadeBottom = LoadTexture(homeDirectory, "wireLoopShadeBottom.png");
	wireLoopShadeTop = LoadTexture(homeDirectory, "wireLoopShadeTop.png");
	wireLoopShadeLeft = LoadTexture(homeDirectory, "wireLoopShadeLeft.png");
	wireLoopShadeRight = LoadTexture(homeDirectory, "wireLoopShadeRight.png");

	delete1 = LoadTexture(homeDirectory, "delete2.png");

	playButtonUp = LoadTexture(homeDirectory, "playButtonUp.png");
	playButtonDown = LoadTexture(homeDirectory, "playButtonDown.png");
	stopButtonUp = LoadTexture(homeDirectory, "stopButtonUp.png");
	stopButtonDown = LoadTexture(homeDirectory, "stopButtonDown.png");

	messageBoxImg = LoadTexture(homeDirectory, "messageBox2.png");
	cog1 = LoadTexture(homeDirectory, "cog1.png");
	success1 = LoadTexture(homeDirectory, "success1.png");

	sliderBack1 = LoadTexture(homeDirectory, "sliderBack1.png");
	sliderBack2 = LoadTexture(homeDirectory, "sliderBack2.png");
	sliderFront1 = LoadTexture(homeDirectory, "sliderFront1.png");
	sliderFront2 = LoadTexture(homeDirectory, "sliderFront2.png");

	exitButtonUp = LoadTexture(homeDirectory, "exitButtonUp.png");
	exitButtonDown = LoadTexture(homeDirectory, "exitButtonDown.png");

	codewordButton1 = LoadTexture(homeDirectory, "codewordsButton1.png");
	codewordButton2 = LoadTexture(homeDirectory, "codewordsButton2.png");

	bulb1 = LoadTexture(homeDirectory, "bulb1.png");
	bulb2 = LoadTexture(homeDirectory, "bulb2.png");
	bulb3 = LoadTexture(homeDirectory, "bulb3.png");

	whiteRotor = LoadTexture(homeDirectory, "whiteRotor.png");

	buttonOff = LoadTexture(homeDirectory, "stateSmallOff.png");
	buttonOn = LoadTexture(homeDirectory, "stateSmallOn.png");

	spark1 = LoadTexture(homeDirectory, "spark1.png");
	spark2a = LoadTexture(homeDirectory, "spark2a.png");
	spark2b = LoadTexture(homeDirectory, "spark2b.png");
	spark2c = LoadTexture(homeDirectory, "spark2c.png");
	spark2d = LoadTexture(homeDirectory, "spark2d.png");

	glow1 = LoadTexture(homeDirectory, "glow1.png");
	glow2 = LoadTexture(homeDirectory, "glow2.png");

	menuOverlay1 = LoadTexture(homeDirectory, "menuOverlay1.png");

	loadingScreen = LoadTexture(homeDirectory, "loadingScreen.png");

	glow3 = LoadTexture(homeDirectory, "glow3.png");

	resetSparks();

}

void resizeWindow(int width, int height)
{
	windowx = width;
	windowy = height;
	glutReshapeWindow(windowx, windowy);
	if (!stretch) {
		calculateScreenShift();
	}
	else {
		screenmultx = windowx / renderx;
		screenmulty = windowy / rendery;
		screenshiftx = 0;
		screenshifty = 0;
	}
}

int loadCount = 0;

void incLoad() {
	loadCount += 1;
	renderLoadingScreen(0);
}

void renderLoadingScreen(int value) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	enable2d((int)windowx, (int)windowy);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	placeimageeasy(loadingScreen, 0, 0, windowx, windowy, TRUE);

	for (int i = 0; i < 15; i++) {
		if (i < loadCount) {
			placeimageeasy(bulb3, 32 + (i * 32), 480, 32, 32, TRUE);
		}
		else {
			placeimageeasy(bulb1, 32 + (i * 32), 480, 32, 32, TRUE);
		}
	}

	glutSwapBuffers();

}

void render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	enable2d((int)windowx, (int)windowy);

	glTranslatef(shakeOffset, 0.0f, 0.0f);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	// Draw background colour
	glColor4f(0.0f, 0.45f, 1.0f, 1.0f);
	placeimageeasy(NULL, 0, 0, renderx, rendery, FALSE);


	// Draw scene
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//	placeimageeasy(tex1, 32, 32, 128, 128, FALSE);
//	interfaceRenderer();

	if (screen == INTELSCREEN) {
		drawIntelScreen();
	}
	else if (screen == PUZZLESCREEN) {
		drawPuzzleScreen();
	}
	else if (screen == WAREFFORTSCREEN) {
		drawWarEffortScreen();
	}
	else if (screen == LETTERSCREEN) {
		drawLetterScreen();
	}
	else if (screen == DAYSCREEN) {
		drawDayScreen();
	}
	else if (screen == HOMESCREEN) {
		drawHomeScreen();
	}
	else if (screen == SPLASHSCREEN) {
		drawSplashScreen();
	}
	else if (screen == CUTSCENE) {
		drawCutScene();
	}
	else if (screen == CHOOSESCREEN) {
		drawChooseScreen();
	}
	else if (screen == OPTIONSSCREEN) {
		drawOptionsScreen();
	}
	else if (screen == FREEPLAYSCREEN) {
		drawFreePlayScreen();
	}
	else if (screen == CREDITS) {
		drawCredits();
	}
	else if (screen == LOADINGSCREEN) {
//		renderLoadingScreen();
	}

	for (int i = 0; i < sparkNum; i++) {
		sparkList[i].draw();
	}

	if (screen == nextScreen) {
		if (fadeValue > 0.0) {
			fadeValue -= 0.025;
		}
	}
	if (screen != nextScreen && messageAnim <= 0) {
		if (fadeValue < 1.0) {
			fadeValue += 0.025;
		}
		else {
			resetSparks();
			screen = nextScreen;
		}
	}

	if (messageActive) {
		if (messageAnim < 530) {
			messageAnim += 3 + int((530 - messageAnim) / 20);
			if (messageAnim > 540) {
				messageAnim = 540;
			}
		}
	}
	else {
		if (messageAnim > 0) {
			messageAnim -= 15;
			if (messageAnim < 0) {
				messageAnim = 0;
			}
		}
	}
	if (messageAnim > 0) {
		messageBox.y = messageAnim - 540;
		closeMessage.y = messageAnim - 94;
		messageYes.y = messageAnim - 134;
		messageNo.y = messageAnim - 134;
		glColor4f(0.0, 0.0, 0.0, 0.4);
		placeimagerotatecentre(cog1, 420 + 7, messageAnim + 7 - 332, 128, 128, ((float)(messageAnim) / 540.0) * pi * 2, TRUE);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		placeimagerotatecentre(cog1, 420, messageAnim - 332, 128, 128, ((float)(messageAnim) / 540.0) * pi * 2, TRUE);
		messageBox.draw();
		glColor4f(0.0, 0.0, 0.0, 1.0);
		drawtextCropped2(messageText, 407, messageAnim - 316, 16, 16, 30, font2);
		glColor3f(1.0, 1.0, 1.0);
		if (solveFlag && screen == PUZZLESCREEN) {
			placeimageeasy(success1, 0, messageAnim - 540, renderx, rendery, TRUE);
		}
		if (messageType == 0) {
			closeMessage.draw();
		}
		else {
			messageYes.draw();
			messageNo.draw();
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			drawtext("Y", messageYes.x + 21, messageYes.y + 22, 32, 32);
			drawtext("N", messageNo.x + 21, messageYes.y + 22, 32, 32);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	glColor4f(0.0f, 0.0f, 0.0f, fadeValue);
	placeimageeasy(NULL, 0, 0, renderx, rendery, FALSE);

	if (saveTimer > 0) {
		if (saveTimer >= 140) {
			glColor4f(1.0f, 1.0f, 1.0f, (180 - saveTimer) / 40.0);
		}
		else if (saveTimer <= 40) {
			glColor4f(1.0f, 1.0f, 1.0f, saveTimer / 40.0);
		}
		else {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
		drawtext("SAVING", 8, 8, 24, 24);
		placeimagerotatecentre(whiteRotor, 20 + (24 * 6), 16, 24, 24, -saveTimer * 0.1, TRUE);
		saveTimer -= 1;
	}

	renderConsole();

	// Draw black bars
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(screenshiftx, 0.0f);
	glVertex2f(screenshiftx, windowy);
	glVertex2f(0.0f, windowy);
	glVertex2f(windowx-screenshiftx, 0.0f);
	glVertex2f(windowx, 0.0f);
	glVertex2f(windowx, windowy);
	glVertex2f(windowx-screenshiftx, windowy);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(windowx, 0.0f);
	glVertex2f(windowx, screenshifty);
	glVertex2f(0.0f, screenshifty);
	glVertex2f(0.0f, windowy-screenshifty);
	glVertex2f(windowx, windowy-screenshifty);
	glVertex2f(windowx, windowy);
	glVertex2f(0.0f, windowy);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glutSwapBuffers();

	glTranslatef(-shakeOffset, 0.0f, 0.0f);

}