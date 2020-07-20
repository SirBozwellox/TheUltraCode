#ifndef HOMESCREEN_H_INCLUDED
#define HOMESCREEN_H_INCLUDED

class rotor {
public:
	int image;
	float rot;
	float x;
	float y;
	float rotSpeed;
	int moveTimeReset;
	int timeOutReset;
	int timer;
	bool moving;
	int rotorSize;
	rotor();
	rotor(int inimage, float inx, float iny, float inrotSpeed, int inmoveTimeReset, int intimeOutReset);
	void move();
	void draw();
};

extern GLuint background;

extern rotor fast1;
extern rotor medium1;
extern rotor slow1;
extern rotor fast2;
extern rotor medium2;
extern rotor slow2;
extern rotor fast3;
extern rotor medium3;
extern rotor slow3;

extern GLuint rotor1Yellow;
extern GLuint rotor1Green;
extern GLuint rotor1Red;

void initHomeScreen();

void moveRotors();

void manageHomeScreen();

void drawHomeScreen();

#endif
