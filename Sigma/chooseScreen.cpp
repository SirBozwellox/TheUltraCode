#include "main.h"

GLuint chooseScreenTexture;
GLuint file;

char codename1[100];
char codename2[100];
char codename3[100];
char par1[100];
char par2[100];
char par3[100];

int pickLevelType;

int fileWidth = 408 * 1.5;
int fileHeight = 450 * 1.5;
int file1x = (renderx / 2) - (408 * 1.5) - 10;
int file1y = rendery - (450 * 1.4);
int file2x = (renderx / 2) + 10;
int file2y = rendery - (450 * 1.4);
int file3x = (renderx / 2) - (fileWidth * 0.5);
int file3y = rendery - (450 * 1.4);
int offset1;
int offset2;
int offset3;

void initChooseScreen() {
	chooseScreenTexture = LoadTexture(homeDirectory, "letterScreen1.png");
	file = LoadTexture(homeDirectory, "file2.png");
	pickLevelType = 0;

	strcpy_s(codename1, 100, "Codename: ");
	strcpy_s(codename2, 100, "Codename: ");
	strcpy_s(codename3, 100, "Codename: ");

	if (levelCount >= 6) {
		strcat_s(codename1, 100, level(easyLevels[levelCount - 6]).codename);
		strcat_s(codename2, 100, level(hardLevels[levelCount - 6]).codename);
		sprintf_s(par1, 100, "Minimum: %i bulbs", level(easyLevels[levelCount - 6]).par);
		sprintf_s(par2, 100, "Minimum: %i bulbs", level(hardLevels[levelCount - 6]).par);
	}
	else {
		strcat_s(codename3, 100, level(baseLevels[levelCount]).codename);
		sprintf_s(par3, 100, "Minimum: %i bulbs", level(baseLevels[levelCount]).par);
	}

	offset1 = 32;
	offset2 = 32;
	offset3 = 32;

}

void manageChooseScreen() {

	if (levelCount >= 6) {
		if (mousex > file1x && mousex < file1x + fileWidth && mousey > file1y && mousey < file1y + fileHeight) {
			if (offset1 >= 32) {
				paperSlide1.play(FALSE);
			}
			if (offset1 > 0) {
				offset1 -= 4;
			}
			if (leftclick) {
				fileSelect1.play(FALSE);
				pickLevelType = 0;
				initPuzzleScreen();
				nextScreen = PUZZLESCREEN;
			}
		}
		else {
			if (offset1 < 32) {
				offset1 += 4;
			}
		}

		if (mousex > file2x && mousex < file2x + fileWidth && mousey > file2y && mousey < file2y + fileHeight) {
			if (offset2 >= 32) {
				paperSlide1.play(FALSE);
			}
			if (offset2 > 0) {
				offset2 -= 4;
			}
			if (leftclick) {
				fileSelect1.play(FALSE);
				pickLevelType = 1;
				initPuzzleScreen();
				nextScreen = PUZZLESCREEN;
			}
		}
		else {
			if (offset2 < 32) {
				offset2 += 4;
			}
		}
	}
	else {
		if (mousex > file3x && mousex < file3x + fileWidth && mousey > file3y && mousey < file3y + fileHeight) {
			if (offset3 >= 32) {
				paperSlide1.play(FALSE);
			}
			if (offset3 > 0) {
				offset3 -= 4;
			}
			if (leftclick) {
				fileSelect1.play(FALSE);
				pickLevelType = 0;
				initPuzzleScreen();
				nextScreen = PUZZLESCREEN;
			}
		}
		else {
			if (offset3 < 32) {
				offset3 += 4;
			}
		}
	}

}

void drawChooseScreen() {

	placeimageeasy(chooseScreenTexture, 0, 0, renderx, rendery, TRUE);

	if (levelCount >= 6) {
		placeimageeasy(file, file1x, file1y + offset1, fileWidth, fileHeight, TRUE);
		placeimageeasy(file, file2x, file2y + offset2, fileWidth, fileHeight, TRUE);

		glColor4f(0.0, 0.0, 0.0, 0.85);
//		drawtext("Choose a code to break:", 170, 36, 28, 28, 0.8);

		drawtext_centre(codename1, file1x + (fileWidth / 2.0) - 32, file1y + (32 * 6.6) + offset1, 28, 28, 0.8);
		drawtext("Type: Enigma", file1x + 64, file1y + (32 * 11) + offset1, 20, 20, 0.8);
		drawtext(par1, file1x + 64, file1y + (32 * 12) + offset1, 20, 20, 0.8);
		drawtext("Intel gained: 1000", file1x + 64, file1y + (32 * 13) + offset1, 20, 20, 0.8);

		drawtext_centre(codename2, file2x + (fileWidth / 2.0) - 32, file2y + (32 * 6.6) + offset2, 28, 28, 0.8);
		drawtext("Type: Tunny", file2x + 64, file2y + (32 * 11) + offset2, 20, 20, 0.8);
		drawtext(par2, file2x + 64, file2y + (32 * 12) + offset2, 20, 20, 0.8);
		drawtext("Intel gained: 2500", file2x + 64, file2y + (32 * 13) + offset2, 20, 20, 0.8);

		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
	else {

		placeimageeasy(file, file3x, file3y + offset3, fileWidth, fileHeight, TRUE);

		glColor4f(0.0, 0.0, 0.0, 0.85);
		//		drawtext("Today's code:", 170, 36, 28, 28, 0.8);

		drawtext_centre(codename3, file3x + (fileWidth / 2.0) - 32, file3y + (32 * 6.6) + offset3, 28, 28, 0.8);
		drawtext("Type: Enigma", file3x + 64, file3y + (32 * 11) + offset3, 20, 20, 0.8);
		drawtext(par3, file3x + 64, file3y + (32 * 12) + offset3, 20, 20, 0.8);
		if (levelCount == 2) {
			drawtext("Intel gained: 1000", file3x + 64, file3y + (32 * 13) + offset3, 20, 20, 0.8);
		}
		else if (levelCount > 2) {
			drawtext("Intel gained: 1500", file3x + 64, file3y + (32 * 13) + offset3, 20, 20, 0.8);
		}

		glColor4f(1.0, 1.0, 1.0, 1.0);
	}

}