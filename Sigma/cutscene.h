#ifndef CUTSCENE_H_INCLUDED
#define CUTSCENE_H_INCLUDED

extern int cutSceneSpot;

extern char openingText[5][300];
extern int openingImages[5];

void loadCutSceneImages();
void initCutScene();
void manageCutScene();
void drawCutScene();

#endif
