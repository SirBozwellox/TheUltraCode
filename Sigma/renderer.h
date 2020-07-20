#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

extern float windowx;
extern float windowy;
extern float oldWindowx;
extern float oldWindowy;

extern float screenmultx;
extern float screenmulty;

extern bool stretch;
extern bool fullscreenFlag;

extern GLuint tex1;
extern GLuint blank;

extern GLuint state1;
extern GLuint state1on;
extern GLuint stateBack;
extern GLuint stateBackOn;

extern GLuint wireGreen1;
extern GLuint wireRed1;
extern GLuint wireGreen2;
extern GLuint wireRed2;
extern GLuint wireGreenLoop1;
extern GLuint wireRedLoop1;
extern GLuint wireRedGreen1;
extern GLuint wireGlow1;
extern GLuint wireGlow2;
extern GLuint wireBlack1;
extern GLuint wireShadeBottom;
extern GLuint wireShadeTop;
extern GLuint wireLoopShadeBottom;
extern GLuint wireLoopShadeTop;
extern GLuint wireLoopShadeLeft;
extern GLuint wireLoopShadeRight;
extern GLuint glow3;

extern GLuint delete1;

extern GLuint playButtonUp;
extern GLuint playButtonDown;
extern GLuint stopButtonUp;
extern GLuint stopButtonDown;
extern GLuint exitButtonUp;
extern GLuint exitButtonDown;

extern GLuint messageBoxImg;
extern GLuint cog1;
extern GLuint success1;

extern GLuint sliderBack1;
extern GLuint sliderBack2;
extern GLuint sliderFront1;
extern GLuint sliderFront2;

extern GLuint codewordButton1;
extern GLuint codewordButton2;

extern GLuint bulb1;
extern GLuint bulb2;
extern GLuint bulb3;

extern GLuint buttonOff;
extern GLuint buttonOn;

extern GLuint spark2a;
extern GLuint spark2b;
extern GLuint spark2c;
extern GLuint spark2d;

extern GLuint glow1;
extern GLuint glow2;

extern GLuint menuOverlay1;

extern float fadeValue;

extern float gravity;

extern int loadCount;

class spark {
	public:
		int timer;
		bool active;
		float oldx;
		float oldy;
		float x;
		float y;
		float movex;
		float movey;
		void move();
		void draw();
		spark();
		spark(float inx, float iny, float inmovex, float inmovey);
};

void consoleLog(char text[300], ...);
void drawSprite(int spriteTex, float posx, float posy, float posz, float size, bool smoothTex);
void initRenderer(int windowWidth, int windowHeight);
void incLoad();
void renderLoadingScreen(int value);
void render();
void resizeWindow(int width, int height);
void createSparks(float inx, float iny, int num);
void manageSparks();
void resetSparks();
void manageShake();
void setShake(int offset);

#endif