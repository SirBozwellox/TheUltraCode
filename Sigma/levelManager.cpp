#include "main.h"

//char levelDirectory[100] = "C:/Users/Admin/Documents/Visual Studio 2015/Sigma/assets/levels";
//char levelDirectory[100] = "../assets/levels";
char levelDirectory[100] = "assets/levels";

char baseLevels[6][100] = {
	"level3.lvl",
	"level2.lvl",
	"level1.lvl",
	"level4.lvl",
	"level5.lvl",
	"level6.lvl"
};

char easyLevels[14][100] = {
	"level8.lvl",
	"level15.lvl",
	"level13.lvl",
	"level36.lvl",
	"level7.lvl",
	"level21.lvl",
	"level10.lvl",
	"level12.lvl",
	"level20.lvl",
	"level19.lvl",
	"level16.lvl",
	"level29.lvl",
	"level25.lvl",
	"level32.lvl",
};

char hardLevels[14][100] = {
	"level14.lvl",
	"level18.lvl",
	"level17.lvl",
	"level11.lvl",
	"level24.lvl",
	"level26.lvl",
	"level30.lvl",
	"level35.lvl",
	"level27.lvl",
	"level31.lvl",
	"level38.lvl",
	"level28.lvl",
	"level22.lvl",
	"level33.lvl"
};

char levelList[50][100] = {
	"level3.lvl",
	"level2.lvl",
	"level1.lvl",
	"level4.lvl",
	"level5.lvl",
	"level6.lvl",
	"level15.lvl",
	"level7.lvl",
	"level8.lvl",
	"level13.lvl",
	"level10.lvl",
	"level14.lvl",
	"level20.lvl",
	"level12.lvl",
	"level17.lvl",
	"level21.lvl",
	"level18.lvl",
	"level19.lvl",
	"level16.lvl",
	"level11.lvl",
	"level25.lvl",
	"level24.lvl",
	"level26.lvl",
	"level27.lvl",
	"level22.lvl",
	"level29.lvl",
	"level28.lvl",
	"level30.lvl",
	"level31.lvl",
	"level32.lvl",
	"level33.lvl",
	"level35.lvl",
	"level36.lvl",
	"level38.lvl"
};
// 34 levels total

int levelCount = 0;

level::level() {

}

level::level(char infilename[100]) {
	strcpy_s(filename, 100, infilename);
	load();
//	printInfo();
}

void level::load() {
	char dir[100] = "";
	if (!steamEnabled) {
		strcpy_s(dir, "../");
	}
	strcat_s(dir, levelDirectory);
	strcat_s(dir, "/");
	strcat_s(dir, filename);

	printf("Loading level: ");
	printf(dir);
	printf("\n");

	std::ifstream infile(dir);
	std::string line;
	char curLine[1000];
	int lineCount = 0;
	while (std::getline(infile, line))
	{
		strcpy_s(curLine, 1000, line.c_str());

//		printf(curLine);
//		printf("\n");

		if (lineCount == 0) {
			strcpy_s(codename, 100, line.c_str());
		}

		if (lineCount == 1) {
			strcpy_s(description, 1000, line.c_str());
		}

		if (lineCount == 2) {
			par = atoi(line.c_str());
		}

		if (lineCount == 3) {
			reward = atoi(line.c_str());
		}

		if (lineCount >= 5) {
			strcpy_s(testStrings[lineCount - 5], 20, line.c_str());
		}

		lineCount += 1;
	}
}

void level::printInfo() {
	printf("\nTests: \n");
	for (int i = 0; i < 20; i++) {
		printf(testStrings[i]);
		printf("\n");
	}
}

char* level::createTestString(int testNum) {
	char retval[400];
	strcpy_s(retval, 400, "");
	for (int i = 0; i < testNum; i++) {
		int randval = rand() % 20;
		strcat_s(retval, testStrings[randval]);
	}
	strcat_s(retval, "f");
	strcat_s(retval, "\0");
	return retval;
}