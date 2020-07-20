#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

class button {
public:
	char name[40];
	bool active;
	int x;
	int y;
	int width;
	int height;
	bool hover;
	bool click;
	GLuint normalTex;
	GLuint hoverTex;
	GLuint clickTex;
	button();
	button(char* inname, int inx, int iny, int inwidth, int inheight, int innormalTex, int inhoverTex, int inclickTex);
	void draw();
	void man();
	bool mouseOver();
	bool compare(button inButton);
};

class slider {
	public:
		char name[40];
		bool active;
		int x;
		int y;
		int width;
		int height;
		float position;
		int orientation = 0;
		bool click;
		GLuint back;
		GLuint front;
		slider();
		slider(char* inname, int inx, int iny, int inwidth, int inheight, int inback, int infront, int inorientation);
		bool mouseOver();
		void draw();
		void setPosition(float inpos);
		void calcPosition();
};

class textButton {
public:
	char name[40];
	char text[40];
	int fontsize;
	bool active;
	int x;
	int y;
	int width;
	int height;
	bool hover;
	bool click;
	GLuint normalTex;
	GLuint hoverTex;
	GLuint clickTex;
	textButton();
	textButton(char* inname, char* intext, int insize, int inx, int iny, int inwidth, int inheight, int innormalTex, int inhoverTex, int inclickTex);
	void draw();
	void man();
	bool mouseOver();
};

class toggle {
public:
	char name[40];
	bool active;
	int x;
	int y;
	int width;
	int height;
	bool enabled;
	GLuint normalTex;
	GLuint enabledTex;
	toggle();
	toggle(char* inname, int inx, int iny, int inwidth, int inheight, int innormalTex, int inenabledTex);
	void draw();
	void man();
	bool mouseOver();
	bool compare(toggle inTog);
};

#endif