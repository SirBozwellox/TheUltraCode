#include "main.h"

int codesBroken;
bool perfectGame;
bool steamEnabled = TRUE;

void initSteamManager() {
	if (steamEnabled) {
		if (SteamAPI_RestartAppIfNecessary(914950))
		{
			printf("Attempting restart through Steam \n");
			exit(0);
		}

		printf("Connecting to Steam \n");

		if (!SteamAPI_Init())
		{
			printf("Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n");
			exit(0);
		}
		else
		{

			printf("Obtaining user data \n");

			SteamUserStats();

			CSteamID userID = SteamUser()->GetSteamID();
			SteamUserStats()->RequestUserStats(userID);

			// GET RID OF THIS IN RELEASE!!!!!!
//			clearAchievements();
		}
	}
}

bool checkAchievement(char* achName)
{
	if (steamEnabled) {
		bool retval;
		SteamUserStats()->GetAchievement(achName, &retval);
		return retval;
	}
	else {
		return FALSE;
	}
}

void setAchievement(char* achName) {
	if (steamEnabled) {
		SteamUserStats()->SetAchievement(achName);
		SteamUserStats()->StoreStats();
	}
}

void activateAchievement(char* achName) {
	if (steamEnabled) {
		if (!checkAchievement(achName)) {
			setAchievement(achName);
		}
	}
}

int getStat(char* statName) {
	if (steamEnabled) {
		int retval = 0;
		SteamUserStats()->GetStat(statName, &retval);
		return retval;
	}
	else {
		return 0;
	}
}

void setStat(char* statName, float newVal) {
	if (steamEnabled) {
		SteamUserStats()->SetStat(statName, newVal);
		SteamUserStats()->StoreStats();
	}
}

void clearAchievements() {
	if (steamEnabled) {
		SteamUserStats()->ResetAllStats(TRUE);
	}
}