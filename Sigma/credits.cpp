#include "main.h"

GLuint logo2;

char creditText[19][50] = {
	"Design, programming, graphics and music",
	"Jack Gloyens",
	"",
	"",
	"Narrative design                       ",
	"Hannah Kelly",
	"",
	"",
	"Cast                                   ",
	"Alan Turing - David Nagaj",
	"Hugh Alexander - Cameron Steen",
	"Commander Travis - Alex Webber-Date",
	"Frederick Morgan - Charlie Collinson",
	"Max Newman - Hannah Kelly",
	"",
	"",
	"Published by Flying Interactive"
};

float scroll = 0.0;
float scrollSpeed = 1.0;

void initCredits() {
	logo2 = LoadTexture(homeDirectory, "logo2.png");
	scroll = 0.0;
	scrollSpeed = 1.0;
}

void manageCredits() {
	if (leftclick_flag) {
		scrollSpeed = 4.0;
	}
	else {
		scrollSpeed = 1.0;
	}
}

void drawCredits() {

	scroll += scrollSpeed;

	glColor3f(0.0, 0.0, 0.0);
	placeimageeasy(tex1, 0, 0, renderx, rendery, FALSE);

	glColor3f(1.0, 1.0, 1.0);

	placeimageeasy(logo2, (renderx / 2) - 275, rendery - scroll, 551, 234, TRUE);

	for (int i = 0; i < 20; i++) {
		drawtext_centre(creditText[i], renderx / 2, rendery + 360 + (i * 64) - scroll, 32, 32, 0.82);
	}

	if (rendery + 260 + (18 * 64) - scroll < -64) {
		nextScreen = HOMESCREEN;
		lastScreen = DAYSCREEN;
		initDayScreen("0 days remaining");
	}

}