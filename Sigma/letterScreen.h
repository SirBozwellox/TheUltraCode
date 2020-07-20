#ifndef LETTERSCREEN_H_INCLUDED
#define LETTERSCREEN_H_INCLUDED

extern GLuint smallFont;

class envelope {
	public:
		GLuint image;
		float rot;
		float x;
		float y;
		float movex;
		float movey;
		float moverot;
		float accelx;
		float accely;
		float accelrot;
		float width;
		float height;
		envelope();
		envelope(int inimage, float inx, float iny, float inwidth, float inheight);
		void setMove(float inx, float iny, float inrot);
		void setAccel(float inx, float iny, float inrot);
		void draw();
		void move();
};

class letter {
	public:
		GLuint image;
		char text[2000];
		GLuint font;
		letter();
		letter(int inimage, int infont, char intext[2000]);
		void draw();
};

extern GLuint letterScreen1;

void initLetterScreen();
void manageLetterScreen();
void drawLetterScreen();

#endif
