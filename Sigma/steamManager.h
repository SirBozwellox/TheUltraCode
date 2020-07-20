#ifndef STEAMMANAGER_H_INCLUDED
#define STEAMMANAGER_H_INCLUDED

extern int codesBroken;
extern bool perfectGame;
extern bool steamEnabled;

void initSteamManager();
bool checkAchievement(char* achName);
void setAchievement(char* achName);
void activateAchievement(char* achName);
int getStat(char* statName);
void setStat(char* statName, float newVal);
void clearAchievements();

#endif