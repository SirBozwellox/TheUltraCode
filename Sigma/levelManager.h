#ifndef LEVELMANAGER_H_INCLUDED
#define LEVELMANAGER_H_INCLUDED

extern char baseLevels[6][100];
extern char easyLevels[14][100];
extern char hardLevels[14][100];

extern char levelList[50][100];

extern int levelCount;

class level {
	public:
		char filename[100];
		char codename[100];
		char description[1000];
		char testStrings[20][20];
		char* createTestString(int testNum);
		int par;
		int reward;
		level();
		level(char infilename[100]);
		void load();
		void printInfo();
};

#endif
