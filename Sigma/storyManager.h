#ifndef STORYMANAGER_H_INCLUDED
#define STORYMANAGER_H_INCLUDED

extern char curLetterText[2000];

extern char letterAudioFile[100];

extern char letterList[58][100];

extern int curLetter;

class operation {
	public:
		char name[100];
		int startDay;
		int duration;
		int currentIntel;
		int requiredIntel;
		int temporaryIntel;
		bool completed;
		int waitFor;
		float multiplier;
		float tapeRot;
		GLuint image;
		operation();
		operation(char inname[100], int instartDay, int induration, int inrequiredIntel, int waitFor);
		operation(char inname[100], int instartDay, int induration, int inrequiredIntel, int waitFor, float inmult);
		operation(char inname[100], int instartDay, int induration, int inrequiredIntel, int waitFor, float inmult, int inimage);
		void setRot();
		void reset();
		void draw(int y);
		void draw2(int y);
};

extern operation operationList[10];

extern int startingOp;
extern bool bodyguardComplete;
extern bool pointblankComplete;
extern bool winningCheck;
extern bool gambitComplete;
extern int cueOperationIntro;

void loadLetterText(char filename[100]);
void initStoryManager();
void setDay(int inval);
void manageStory();
bool checkActive(int op);
bool checkActive(char opName[20]);
bool checkSuccessful(char opName[20]);
void loadCurrentLetter();

#endif
