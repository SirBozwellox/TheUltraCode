#include "main.h"

using namespace std;

int cutSceneSpot;
int nextCutSceneSpot;
float currentChar;
float currentCharAdd = 0.5;
float fade = 0.0;

GLuint cutsceneOverlay;

GLuint rotor1GreenSepia;
GLuint rotor1YellowSepia;
GLuint rotor1RedSepia;

rotor rotorWheels[18];

char openingText[5][300] = {
	"It's 1942, Europe is in turmoil, falling to an unrelenting Nazi force. Everyday thousands of allied soldiers lose their lives on the battlefield.",
	"Meanwhile in a country mansion in South East England, a group of expert mathematicians are fighting a battle of their own. Breaking an unbreakable German code.",
	"They intercept a constant stream of German messages, encrypted using their Enigma machines. Successfully deciphering those messages could save millions of lives and put an end to the war.",
	"You, William Taylor, are one of the silent men, fighting a war that no one knows is being fought.",
	""};

int openingImages[5];

sound openingAudio[5] = {
	sound("vo/opening_1.mp3"),
	sound("vo/opening_2.mp3"),
	sound("vo/opening_3.mp3"),
	sound("vo/opening_4.mp3")
};

char roundupText[5][300] = {
	"Welcome. I see some new faces here today, for those of you who don't know I'm Lieutenant General Frederick Morgan, but please, call me Freddie.",
	"As you chaps know by now we're planning on bringing the fight back to mainland Europe. There's been a lot of discussion over where this invasion should take place but we think we've got a plan. This is Operation Roundup.",
	"An allied force made up of 48 divisions are to land on the various beaches between the ports of Boulogne and Le Havre and over a few days push the Axis forces back to Paris.",
	"We require information about what sort of forces the Germans have along the coast of Northern France, that's where Bletchley comes in. I know we can trust you to get that information. Good luck, gentlemen.",
	""};

int roundupImages[5];

sound roundupAudio[5] = {
	sound("vo/roundup_1.mp3"),
	sound("vo/roundup_2.mp3"),
	sound("vo/roundup_3.mp3"),
	sound("vo/roundup_4.mp3")
};

char sledgehammerText[5][300] = {
	"Welcome. I see some new faces here today, for those of you who don't know I'm Lieutenant General Frederick Morgan, but please, call me Freddie.",
	"As you chaps know by now we're planning on bringing the fight back to mainland Europe. There's been a lot of discussion over where this invasion should take place but we think we've got a plan. This is Operation Sledgehammer.",
	"An allied force made up of 48 divisions are to capture the French seaports of Brest and Cherbourg and over a few days push the Axis forces back to Paris.",
	"We require information about what sort of forces the Germans have at Brest and Cherbourg, that's where Bletchley comes in. I know we can trust you to get that information. Good luck, gentlemen.",
	"" };

int sledgehammerImages[5];

sound sledgehammerAudio[5] = {
	sound("vo/sledgehammer_1.mp3"),
	sound("vo/sledgehammer_2.mp3"),
	sound("vo/sledgehammer_3.mp3"),
	sound("vo/sledgehammer_4.mp3")
};

char fortitudeText[5][300] = {
	"Welcome back gentlemen. We've had some setbacks in our plans for an invasion of Northern France, but you're help in these operations is still extremely valuable.",
	"Anyway, this is Operation Fortitude, our plan to deceive the enemy on the whereabouts of our upcoming invasion of mainland Europe.",
	"By using fake documents and reports that will be leaked to the enemy we will trick them into thinking we plan to invade the Pas de Calais. We will even be employing fake blow up armies to trick reconnaissance aircraft.",
	"Your job will be to intercept and decrypt German messages to check whether the Axis powers have swallowed the bait. We're counting on you gentlemen, good luck.",
	"" };

int fortitudeImages[5];

sound fortitudeAudio[5] = {
	sound("vo/fortitude_1.mp3"),
	sound("vo/fortitude_2.mp3"),
	sound("vo/fortitude_3.mp3"),
	sound("vo/fortitude_4.mp3")
};

char overlordText[7][300] = {
	"After much deliberation we've finally come to an agreement on a plan for the invasion of Northern France. This, gentlemen, is Operation Overlord.",
	"In the summer of 1944 over 160,000 British, American and Canadian troops will land on the beaches of Normandy. The beach will be broken into five sections; Utah, Omaha, Sword, Gold and Juno.",
	"Before the raid around 1200 aircraft will take out German defences along the coast. Unfortunately the short operating range of the Spitfire and Tornado restrict the possible landing sites to Normandy.",
	"We worry that locations like the Pas de Calais, although much closer to the British coast, will be too obvious. And other landing sites pose greater threats to our landing forces.",
	"We require you to get any information you can about what defensive forces the Germans have along the coast of Normandy. Closer to the invasion we'll also require information on the movements of German troops.",
	"This operation is of the utmost secrecy, the Axis cannot know we plan to invade Normandy. I know that we can trust you all to get the information we need to make this operation a success.",
	""};

int overlordImages[7];

sound overlordAudio[7] = {
	sound("vo/overlord_1.mp3"),
	sound("vo/overlord_2.mp3"),
	sound("vo/overlord_3.mp3"),
	sound("vo/overlord_4.mp3"),
	sound("vo/overlord_5.mp3"),
	sound("vo/overlord_6.mp3")
};

char bodyguardText[5][300] = {
	"With Operation Fortitude complete we're moving onto larger deception strategies to cover up Operation Overlord. We've received information that German coastal defences are stretched thin and we want to use this to our full advantage.",
	"If we can successfully get the Germans to move their coastal units away from Normandy in the run up to the landings then we might stand a chance of breaking through their defences.",
	"This is Operation Bodyguard, the Allied plan to deceive the Germans into thinking that the invasion of Normandy is merely a distraction for a larger invasion elsewhere.",
	"Bletchley Park will be required to gain information on how well these deception strategies are working and what the Axis powers think our invasion plans are. You have your orders, gentlemen.",
	"" };

int bodyguardImages[5];

sound bodyguardAudio[5] = {
	sound("vo/bodyguard_1.mp3"),
	sound("vo/bodyguard_2.mp3"),
	sound("vo/bodyguard_3.mp3"),
	sound("vo/bodyguard_4.mp3")
};

char pointblankText[4][300] = {
	"The recent surge in German air superiority along with their repeated use of the V1 rockets to attack allied cities has forced us to retaliate. This, gentlemen, is Operation Pointblank.",
	"The codebreakers at Bletchley are to report any messages regarding the location of German air bases, aircraft factories and V1 sites to Military Intelligence as soon as they're decrypted.",
	"Following that, these locations will be bombed in order to reduce the effectiveness of the Luftwaffe. This should hopefully increase the chance of success with Operation Overlord. That is all.",
	"" };

int pointblankImages[4];

sound pointblankAudio[4] = {
	sound("vo/pointblank_1.mp3"),
	sound("vo/pointblank_2.mp3"),
	sound("vo/pointblank_3.mp3")
};

char gambitText[4][300] = {
	"As part of the Normandy landings planned for a few months time we require information on the capabilities and positions of German U-boats. This will form part of Operation Gambit.",
	"During the landings we will be sending in two X-class submarines who will indicate the edges of the landing sites.",
	"Any information Bletchley can provide regarding the positions of German U-boats in the sea around Normandy will be vital in keeping these submarines from being destroyed. You are dismissed, gentlemen.",
	"" };

int gambitImages[4];

sound gambitAudio[4] = {
	sound("vo/gambit_1.mp3"),
	sound("vo/gambit_2.mp3"),
	sound("vo/gambit_3.mp3")
};

char tigerText[5][300] = {
	"With D-Day right around the corner we've been running various practice drills on Slapton Sands in South Devon. Unfortunately a recent rehearsal was cut short due to an attack.",
	"Nine German E-boats, presumably on patrol in the area, spotted the landing craft and opened fire. This resulted in the deaths of around 800 servicemen.",
	"Worse than that, we fear the Germans may be on to our invasion strategy and so the point of this operation, codenamed Tiger, is to uncover exactly what the Germans know and to put them off the scent.",
	"You must report any information regarding the failure of this Overlord rehearsal to Military Intelligence as soon as it is discovered. Those are your orders gentlemen.",
	"" };

int tigerImages[5];

sound tigerAudio[5] = {
	sound("vo/tiger_1.mp3"),
	sound("vo/tiger_2.mp3"),
	sound("vo/tiger_3.mp3"),
	sound("vo/tiger_4.mp3")
};

char neptuneText[5][300] = {
	"The day is nearly upon us, gentlemen. Soon thousands of troops will land on the beaches of Normandy in an attempt to sway the war in the Allies' favour.",
	"In this final phase, named Operation Neptune, we require information on the positions of German radar stations along the French coast.",
	"The night before the invasion, paratroopers will be dropped at these locations and tamper with the radar equipment in order to deceive the enemy.",
	"Hopefully this should give our boys the advantage they need to make Operation Overlord a success. Good luck, gentlemen, we're counting on you.",
	"" };

int neptuneImages[5];

sound neptuneAudio[5] = {
	sound("vo/neptune_1.mp3"),
	sound("vo/neptune_2.mp3"),
	sound("vo/neptune_3.mp3"),
	sound("vo/neptune_4.mp3")
};

char badEndText[8][300] = {
	"On the 6th of June, 1944, over 150,000 Allied troops landed on the beaches of Normandy in the largest seaborne invasion ever undertaken.",
	"On the first day of fighting only two of the five beachheads were connected and the target cities of Caen and Bayeux remained under German control.",
	"In the days that followed there were tremendous Allied casualties and none of the planned objectives of Operation Overlord were met. The invasion had been a failure.",
	"Knowing that an invasion from the Western Front would not be possible again for some time, the Axis powers focused their efforts on the Eastern Front and by the end of 1944 Germany had successfully captured Stalingrad.",
	"With continued V-2 rocket attacks on Allied cities, factories and military bases, the Allied forces soon dwindled and a German invasion on the English South coast seemed inevitable.",
	"After discovery by reconnaissance aircraft in early 1945, both Bletchley Park and the Dollis Hill research centre were successfully bombed and any hope of an Allied victory was destroyed with them.",
	"The story of Bletchley Park ends here, and so, William Taylor, does yours.",
	"" };

int badEndImages[8];

sound badEndAudio[8] = {
	sound("vo/bad_end_1.mp3"),
	sound("vo/bad_end_2.mp3"),
	sound("vo/bad_end_3.mp3"),
	sound("vo/bad_end_4.mp3"),
	sound("vo/bad_end_5.mp3"),
	sound("vo/bad_end_6.mp3"),
	sound("vo/bad_end_7.mp3")
};

char goodEndText[9][300] = {
	"On the 6th of June, 1944, over 150,000 Allied troops landed on the beaches of Normandy in the largest seaborne invasion ever undertaken.",
	"On the first day of fighting only two of the five beachheads were connected and the target cities of Caen and Bayeux remained under German control.",
	"In the days that followed the Allies saw many more casualties, but in diverting German forces towards the Western Front, the Eastern Front was weakened. The Soviet army managed to push the German forces back and in the process occupied Poland.",
	"On the 7th of May 1945, Nazi Germany unconditionally surrendered to the Soviet Union. For Europe the war was over. But a far greater war between the Allies and the Soviet Union was on the horizon.",
	"Bletchley Park soon closed, the Bombe and Colossus machines were dismantled and any German decrypts were burned. The work done there remained top secret for nearly 30 years.",
	"In 1952 Alan Turing was prosecuted for homosexuality and charged with gross indecency. After undergoing chemical castration he took his own life two years later.",
	"The contributions made by the codebreakers at Bletchley Park are thought to have shortened the war by at least two years and played a vital role in the Allied victory.",
	"Thank you, William, your work here is done.",
	"" };

int goodEndImages[10];

sound goodEndAudio[9] = {
	sound("vo/good_end_1.mp3"),
	sound("vo/good_end_2.mp3"),
	sound("vo/good_end_3.mp3"),
	sound("vo/good_end_4.mp3"),
	sound("vo/good_end_5.mp3"),
	sound("vo/good_end_6.mp3"),
	sound("vo/good_end_7.mp3"),
	sound("vo/good_end_8.mp3")
};

char bestEndText[10][300] = {
	"On the 6th of June, 1944, over 150,000 Allied troops landed on the beaches of Normandy in the largest seaborne invasion ever undertaken.",
	"On the first day of fighting only two of the five beachheads were connected and the target cities of Caen and Bayeux remained under German control.",
	"However in the days that followed the Allied soldiers pushed forward and by the 26th of June both Cherbourg and Caen had been liberated. On the 25th of August, German forces surrendered Paris.",
	"During this time the codebreakers at Bletchley Park worked round the clock to decrypt messages about German plans and troop movements. The information they provided was crucial in making the Allied invasion a success.",
	"On the 7th of May 1945, Nazi Germany unconditionally surrendered. For Europe the war was over.",
	"Bletchley Park soon closed, the Bombe and Colossus machines were dismantled and any German decrypts were burned. The work done there remained top secret for nearly 30 years.",
	"In 1952 Alan Turing was prosecuted for homosexuality and charged with gross indecency. After undergoing chemical castration he took his own life two years later.",
	"The contributions made by the codebreakers at Bletchley Park are thought to have shortened the war by at least two years and played a vital role in the Allied victory.",
	"Thank you, William, your work here is done.",
	"" };

int bestEndImages[10];

sound bestEndAudio[10] = {
	sound("vo/best_end_1.mp3"),
	sound("vo/best_end_2.mp3"),
	sound("vo/best_end_3.mp3"),
	sound("vo/best_end_4.mp3"),
	sound("vo/best_end_5.mp3"),
	sound("vo/best_end_6.mp3"),
	sound("vo/best_end_7.mp3"),
	sound("vo/best_end_8.mp3"),
	sound("vo/best_end_9.mp3")
};

int scratchImages[10];

sound audioList[13][10];
int audioIndex = 0;

void loadCutSceneImages() {
	openingImages[0] = LoadTexture(homeDirectory, "cutscenes/1_1.png");
	openingImages[1] = LoadTexture(homeDirectory, "cutscenes/1_2.png");
	openingImages[2] = LoadTexture(homeDirectory, "cutscenes/1_3.png");
	openingImages[3] = LoadTexture(homeDirectory, "cutscenes/1_4c.png");

	roundupImages[0] = LoadTexture(homeDirectory, "cutscenes/operations_back.png");
	roundupImages[1] = LoadTexture(homeDirectory, "cutscenes/roundup_2.png");
	roundupImages[2] = LoadTexture(homeDirectory, "cutscenes/roundup_3.png");
	roundupImages[3] = LoadTexture(homeDirectory, "cutscenes/roundup_4.png");

	incLoad();

	sledgehammerImages[0] = LoadTexture(homeDirectory, "cutscenes/operations_back.png");
	sledgehammerImages[1] = LoadTexture(homeDirectory, "cutscenes/sledgehammer_2.png");
	sledgehammerImages[2] = LoadTexture(homeDirectory, "cutscenes/sledgehammer_3.png");
	sledgehammerImages[3] = LoadTexture(homeDirectory, "cutscenes/sledgehammer_4.png");

	fortitudeImages[0] = LoadTexture(homeDirectory, "cutscenes/operations_back.png");
	fortitudeImages[1] = LoadTexture(homeDirectory, "cutscenes/fortitude_2.png");
	fortitudeImages[2] = LoadTexture(homeDirectory, "cutscenes/fortitude_3.png");
	fortitudeImages[3] = LoadTexture(homeDirectory, "cutscenes/fortitude_4.png");

	incLoad();

	overlordImages[0] = LoadTexture(homeDirectory, "cutscenes/overlord_1.png");
	overlordImages[1] = LoadTexture(homeDirectory, "cutscenes/overlord_2.png");
	overlordImages[2] = LoadTexture(homeDirectory, "cutscenes/overlord_3.png");
	overlordImages[3] = LoadTexture(homeDirectory, "cutscenes/overlord_4.png");
	overlordImages[4] = LoadTexture(homeDirectory, "cutscenes/overlord_5.png");
	overlordImages[5] = LoadTexture(homeDirectory, "cutscenes/overlord_6.png");

	bodyguardImages[0] = LoadTexture(homeDirectory, "cutscenes/operations_back.png");
	bodyguardImages[1] = LoadTexture(homeDirectory, "cutscenes/bodyguard_2.png");
	bodyguardImages[2] = LoadTexture(homeDirectory, "cutscenes/bodyguard_3.png");
	bodyguardImages[3] = LoadTexture(homeDirectory, "cutscenes/bodyguard_4.png");

	incLoad();

	pointblankImages[0] = LoadTexture(homeDirectory, "cutscenes/pointblank_1.png");
	pointblankImages[1] = LoadTexture(homeDirectory, "cutscenes/pointblank_2.png");
	pointblankImages[2] = LoadTexture(homeDirectory, "cutscenes/pointblank_3.png");

	gambitImages[0] = LoadTexture(homeDirectory, "cutscenes/gambit_1.png");
	gambitImages[1] = LoadTexture(homeDirectory, "cutscenes/gambit_2.png");
	gambitImages[2] = LoadTexture(homeDirectory, "cutscenes/gambit_3.png");

	incLoad();

	tigerImages[0] = LoadTexture(homeDirectory, "cutscenes/operations_back.png");
	tigerImages[1] = LoadTexture(homeDirectory, "cutscenes/tiger_2.png");
	tigerImages[2] = LoadTexture(homeDirectory, "cutscenes/tiger_3.png");
	tigerImages[3] = LoadTexture(homeDirectory, "cutscenes/tiger_4.png");

	neptuneImages[0] = LoadTexture(homeDirectory, "cutscenes/operations_back.png");
	neptuneImages[1] = LoadTexture(homeDirectory, "cutscenes/neptune_2.png");
	neptuneImages[2] = LoadTexture(homeDirectory, "cutscenes/neptune_3.png");
	neptuneImages[3] = LoadTexture(homeDirectory, "cutscenes/neptune_4.png");

	incLoad();

	scratchImages[0] = LoadTexture(homeDirectory, "cutscenes/scratches/scratch1.png");
	scratchImages[1] = LoadTexture(homeDirectory, "cutscenes/scratches/scratch2.png");
	scratchImages[2] = LoadTexture(homeDirectory, "cutscenes/scratches/scratch3.png");
	scratchImages[3] = LoadTexture(homeDirectory, "cutscenes/scratches/scratch4.png");
	scratchImages[4] = LoadTexture(homeDirectory, "cutscenes/scratches/scratch5.png");
	scratchImages[5] = LoadTexture(homeDirectory, "cutscenes/scratches/scratch6.png");
	scratchImages[6] = LoadTexture(homeDirectory, "cutscenes/scratches/scratch7.png");
	scratchImages[7] = LoadTexture(homeDirectory, "cutscenes/scratches/scratch8.png");
	scratchImages[8] = LoadTexture(homeDirectory, "cutscenes/scratches/scratch9.png");
	scratchImages[9] = LoadTexture(homeDirectory, "cutscenes/scratches/scratch10.png");

	incLoad();

	badEndImages[0] = LoadTexture(homeDirectory, "cutscenes/end_1.png");
	badEndImages[1] = LoadTexture(homeDirectory, "cutscenes/end_2.png");
	badEndImages[2] = LoadTexture(homeDirectory, "cutscenes/end_bad_3.png");
	badEndImages[3] = LoadTexture(homeDirectory, "cutscenes/end_bad_4.png");
	badEndImages[4] = LoadTexture(homeDirectory, "cutscenes/end_bad_5.png");
	badEndImages[5] = LoadTexture(homeDirectory, "cutscenes/end_bad_6.png");
	badEndImages[6] = LoadTexture(homeDirectory, "cutscenes/end_bad_7.png");

	goodEndImages[0] = LoadTexture(homeDirectory, "cutscenes/end_1.png");
	goodEndImages[1] = LoadTexture(homeDirectory, "cutscenes/end_2.png");
	goodEndImages[2] = LoadTexture(homeDirectory, "cutscenes/end_bad_3.png");
	goodEndImages[3] = LoadTexture(homeDirectory, "cutscenes/end_good_4.png");
	goodEndImages[4] = LoadTexture(homeDirectory, "cutscenes/end_good_5.png");
	goodEndImages[5] = LoadTexture(homeDirectory, "cutscenes/end_good_6.png");
	goodEndImages[6] = LoadTexture(homeDirectory, "cutscenes/end_good_7.png");
	goodEndImages[7] = LoadTexture(homeDirectory, "cutscenes/2_1.png");

	incLoad();

	bestEndImages[0] = LoadTexture(homeDirectory, "cutscenes/end_1.png");
	bestEndImages[1] = LoadTexture(homeDirectory, "cutscenes/end_2.png");
	bestEndImages[2] = LoadTexture(homeDirectory, "cutscenes/end_best_3.png");
	bestEndImages[3] = LoadTexture(homeDirectory, "cutscenes/end_best_4.png");
	bestEndImages[4] = LoadTexture(homeDirectory, "cutscenes/end_good_4.png");
	bestEndImages[5] = LoadTexture(homeDirectory, "cutscenes/end_good_5.png");
	bestEndImages[6] = LoadTexture(homeDirectory, "cutscenes/end_good_6.png");
	bestEndImages[7] = LoadTexture(homeDirectory, "cutscenes/end_good_7.png");
	bestEndImages[8] = LoadTexture(homeDirectory, "cutscenes/2_1.png");

	memcpy(audioList[0], openingAudio, sizeof(openingAudio));
	memcpy(audioList[1], roundupAudio, sizeof(roundupAudio));
	memcpy(audioList[2], sledgehammerAudio, sizeof(sledgehammerAudio));
	memcpy(audioList[3], fortitudeAudio, sizeof(fortitudeAudio));
	memcpy(audioList[4], overlordAudio, sizeof(overlordAudio));
	memcpy(audioList[5], bodyguardAudio, sizeof(bodyguardAudio));
	memcpy(audioList[6], pointblankAudio, sizeof(pointblankAudio));
	memcpy(audioList[7], gambitAudio, sizeof(gambitAudio));
	memcpy(audioList[8], tigerAudio, sizeof(tigerAudio));
	memcpy(audioList[9], neptuneAudio, sizeof(neptuneAudio));
	memcpy(audioList[10], badEndAudio, sizeof(badEndAudio));
	memcpy(audioList[11], goodEndAudio, sizeof(goodEndAudio));
	memcpy(audioList[12], bestEndAudio, sizeof(bestEndAudio));

	cutsceneAudio = audioList[0][0];

}

float rotorTimer = 0.0;

void initCutScene() {
	cutSceneSpot = 0;
	nextCutSceneSpot = 0;
	currentChar = 0.0;
	fade = 3.0;

	cutsceneOverlay = LoadTexture(homeDirectory, "cutsceneOverlay.png");

	rotor1YellowSepia = LoadTexture(homeDirectory, "rotor1_sepia.png");
	rotor1RedSepia = LoadTexture(homeDirectory, "rotor2_sepia.png");
	rotor1GreenSepia = LoadTexture(homeDirectory, "rotor3_sepia.png");

	for (int i = 0; i < 18; i += 3) {
		rotorWheels[i + 2] = rotor(rotor1GreenSepia, 64 + ((i / 3) * 256), (rendery / 2) - 320, (2 * pi) / 26.0, 1, 0);
		rotorWheels[i+0] = rotor(rotor1YellowSepia, 64 + ((i / 3) * 256), (rendery / 2) + 256 - 320, (2 * pi) / 26.0, 1, 0);
		rotorWheels[i+1] = rotor(rotor1RedSepia, 64 + ((i / 3) * 256), (rendery / 2) + 512 - 320, (2 * pi) / 26.0, 1, 0);
		rotorWheels[i + 0].rot = ((pi * 2.0) / 26.0) * (0 + (i / 1));
		rotorWheels[i + 1].rot = ((pi * 2.0) / 26.0) * (0 + (i / 1));
		rotorWheels[i + 2].rot = ((pi * 2.0) / 26.0) * (0 + (i / 1));
	}

	rotorTimer = 0.0;

	if (day == maxDay + 1) {
		if (warEffort < 0.7) {
			activateAchievement("steamAch_5");
		}
		else {
			activateAchievement("steamAch_6");
			if (perfectGame && warEffort >= 1.0) {
				activateAchievement("steamAch_7");
			}
		}
	}

	filmTicker.play(true);
	filmTicker.volume = 0.01;

	if (day == 1) {
		audioIndex = 0;
	}
	else {
		if (day == maxDay + 1) {
			if (warEffort >= 0.7) {
				if (checkSuccessful("Overlord")) {
					audioIndex = 12;
				}
				else {
					audioIndex = 11;
				}
			}
			else {
				audioIndex = 10;
			}
		}
		else {
			switch (cueOperationIntro) {
				case 0:
					if (strcmp(operationList[0].name, "Roundup") == 0) {
						audioIndex = 1;
					}
					else {
						audioIndex = 2;
					}
					break;
				case 1:
					audioIndex = 3;
					break;
				case 2:
					audioIndex = 4;
					break;
				case 3:
					audioIndex = 5;
					break;
				case 4:
					audioIndex = 6;
					break;
				case 5:
					audioIndex = 7;
					break;
				case 6:
					audioIndex = 8;
					break;
				case 7:
					audioIndex = 9;
					break;
			}
		}
	}

	cutsceneAudio = audioList[audioIndex][0];

}

float zoom = 0.0;
float zoomPlus = 0.00015;
int xOffset = 0;
int yOffset = 0;
int offsetMove = 3;
int offsetMax = 6;
float scratchCount = 0.0;
void drawCutsceneImage(int texture) {
	placeimageeasy(texture, xOffset + 0 - (int)(640 * zoom), yOffset + 100 - (int)(232 * zoom), (int)(1280 * (1.0 + zoom)), (int)(464 * (1.0 + zoom)), TRUE);
	glColor4f(1.0, 1.0, 1.0, 0.45);
	placeimageeasy(scratchImages[(int)(scratchCount)], 0, 100, 1280, 464, TRUE);
	glColor4f(1.0, 1.0, 1.0, 1.0);
}

void manageCutScene() {

	scratchCount += 0.2;
	scratchCount = floor(scratchCount * 10) / 10.0;
	if (floor(scratchCount) == scratchCount) {
		xOffset += (rand() & offsetMove) - (offsetMove / 2);
		yOffset += (rand() & offsetMove) - (offsetMove / 2);
		if (xOffset < -offsetMax) { xOffset = -offsetMax; }
		if (yOffset < -offsetMax) { yOffset = -offsetMax; }
		if (xOffset > offsetMax) { xOffset = offsetMax; }
		if (yOffset > offsetMax) { yOffset = offsetMax; }
	}
	if (scratchCount >= 10) {
		scratchCount = 0;
	}

	if (zoom < 0.5) {
		zoom += zoomPlus;
	}

	if (nextCutSceneSpot != cutSceneSpot) {
		fade += 0.025;
		if (fade >= 1.0) {
			cutSceneSpot = nextCutSceneSpot;
			currentChar = 0;
			zoom = 0.0;
		}
	}
	else {
		fade -= 0.025;
	}
	if (fade < 0.0) {
		fade = 0.0;
	}

	if (leftclick_flag) {
		currentCharAdd = 1.0;
	}
	else {
		currentCharAdd = 0.5;
	}

	if (cutsceneAudio.playing == false && fade == 0.0) {
		if (cutsceneAudio.position == 0) {
			cutsceneAudio = audioList[audioIndex][cutSceneSpot];
			cutsceneAudio.play(false);
		}
	}
	cutsceneAudio.baseVolume = 1.0 - fade;
	if (fade >= 1.0) {
		cutsceneAudio.stop();
	}

	if (day == 1) {
		if (leftclick && openingText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025) {
			nextCutSceneSpot += 1;
		}
		if (cutSceneSpot >= 4) {
			initDayScreen("");
			nextScreen = DAYSCREEN;
		}
		if (openingText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
			currentChar += currentCharAdd;
		}
	}
	else if (day == maxDay + 1) {
		if (warEffort >= 0.7) {
			if (checkSuccessful("Overlord")) {
				if (leftclick && bestEndText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025 && rotorTimer == 0.0) {
					nextCutSceneSpot += 1;
//					cutSceneSpot = nextCutSceneSpot;
//					fade = 0.0;
//					currentChar = 0.0;
				}
				if (bestEndText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
					currentChar += currentCharAdd;
				}
				if (cutSceneSpot >= 9) {
					initCredits();
					nextScreen = CREDITS;
					saveGame();
				}
			}
			else {
				if (leftclick && goodEndText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025 && rotorTimer == 0.0) {
					nextCutSceneSpot += 1;
//					cutSceneSpot = nextCutSceneSpot;
//					fade = 0.0;
//					currentChar = 0.0;
				}
				if (goodEndText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
					currentChar += currentCharAdd;
				}
				if (cutSceneSpot >= 8) {
					initCredits();
					nextScreen = CREDITS;
					saveGame();
				}
			}
		}
		else {
			if (leftclick && badEndText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025 && rotorTimer == 0.0) {
				nextCutSceneSpot += 1;
//				cutSceneSpot = nextCutSceneSpot;
//				fade = 0.0;
//				currentChar = 0.0;
			}
			if (badEndText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
				currentChar += currentCharAdd;
			}
			if (cutSceneSpot >= 7) {
				initCredits();
				nextScreen = CREDITS;
				saveGame();
			}
		}

	}
	else {
		switch (cueOperationIntro) {
			case 0:
				if (strcmp(operationList[0].name, "Roundup") == 0) {
					if (leftclick && roundupText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025) {
						nextCutSceneSpot += 1;
					}
					if (cutSceneSpot >= 4) {
						nextScreen = PUZZLESCREEN;
						initPuzzleScreen();
					}
					if (roundupText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
						currentChar += currentCharAdd;
					}
				}
				else {
					if (leftclick && sledgehammerText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025) {
						nextCutSceneSpot += 1;
					}
					if (cutSceneSpot >= 4) {
						nextScreen = PUZZLESCREEN;
						initPuzzleScreen();
					}
					if (sledgehammerText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
						currentChar += currentCharAdd;
					}
				}
				break;
			case 1:
				if (leftclick && fortitudeText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025) {
					nextCutSceneSpot += 1;
				}
				if (cutSceneSpot >= 4) {
					if (levelCount < 0) {
						nextScreen = PUZZLESCREEN;
						initPuzzleScreen();
					}
					else {
						nextScreen = CHOOSESCREEN;
						initChooseScreen();
					}
				}
				if (fortitudeText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
					currentChar += currentCharAdd;
				}
				break;
			case 2:
				if (leftclick && overlordText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025) {
					nextCutSceneSpot += 1;
				}
				if (cutSceneSpot >= 6) {
					if (levelCount < 0) {
						nextScreen = PUZZLESCREEN;
						initPuzzleScreen();
					}
					else {
						nextScreen = CHOOSESCREEN;
						initChooseScreen();
					}
				}
				if (overlordText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
					currentChar += currentCharAdd;
				}
				break;
			case 3:
				if (leftclick && bodyguardText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025) {
					nextCutSceneSpot += 1;
				}
				if (cutSceneSpot >= 4) {
					if (levelCount < 0) {
						nextScreen = PUZZLESCREEN;
						initPuzzleScreen();
					}
					else {
						nextScreen = CHOOSESCREEN;
						initChooseScreen();
					}
				}
				if (bodyguardText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
					currentChar += currentCharAdd;
				}
				break;
			case 4:
				if (leftclick && pointblankText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025) {
					nextCutSceneSpot += 1;
				}
				if (cutSceneSpot >= 3) {
					if (levelCount < 0) {
						nextScreen = PUZZLESCREEN;
						initPuzzleScreen();
					}
					else {
						nextScreen = CHOOSESCREEN;
						initChooseScreen();
					}
				}
				if (pointblankText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
					currentChar += currentCharAdd;
				}
				break;
			case 5:
				if (leftclick && gambitText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025) {
					nextCutSceneSpot += 1;
				}
				if (cutSceneSpot >= 3) {
					if (levelCount < 0) {
						nextScreen = PUZZLESCREEN;
						initPuzzleScreen();
					}
					else {
						nextScreen = CHOOSESCREEN;
						initChooseScreen();
					}
				}
				if (gambitText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
					currentChar += currentCharAdd;
				}
				break;
			case 6:
				if (leftclick && tigerText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025) {
					nextCutSceneSpot += 1;
				}
				if (cutSceneSpot >= 4) {
					if (levelCount < 6) {
						nextScreen = PUZZLESCREEN;
						initPuzzleScreen();
					}
					else {
						nextScreen = CHOOSESCREEN;
						initChooseScreen();
					}
				}
				if (tigerText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
					currentChar += currentCharAdd;
				}
				break;
			case 7:
				if (leftclick && neptuneText[cutSceneSpot][(int)currentChar] == '\0' && fade <= 0.025) {
					nextCutSceneSpot += 1;
				}
				if (cutSceneSpot >= 4) {
					if (levelCount < 6) {
						nextScreen = PUZZLESCREEN;
						initPuzzleScreen();
					}
					else {
						nextScreen = CHOOSESCREEN;
						initChooseScreen();
					}
				}
				if (neptuneText[cutSceneSpot][(int)currentChar] != '\0' && fade == 0.0) {
					currentChar += currentCharAdd;
				}
				break;
			default:
				nextScreen = PUZZLESCREEN;
				initPuzzleScreen();
				break;
		}
	}
}

void drawCutScene() {

	glColor4f(0.0, 0.0, 0.0, 1.0);
	placeimageeasy(tex1, 0, 0, renderx, rendery, FALSE);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	char temptext[1000];
	if (day == 1) {
		drawCutsceneImage(openingImages[cutSceneSpot]);
		strcpy_s(temptext, 1000, openingText[cutSceneSpot]);
	}
	else if (day == maxDay + 1) {
		if (warEffort >= 0.7) {
			if (checkSuccessful("Overlord")) {
				placeimageeasy(bestEndImages[cutSceneSpot], xOffset + 0 - (int)(640 * zoom), yOffset + 100 - (int)(232 * zoom), (int)(1280 * (1.0 + zoom)), (int)(464 * (1.0 + zoom)), TRUE);
				if (cutSceneSpot == 8) {
					placeimageeasy(bestEndImages[cutSceneSpot], xOffset + 0 - (int)(640 * 0.0), yOffset + 100 - (int)(232 * 0.0), (int)(1280 * (1.0 + 0.0)), (int)(464 * (1.0 + 0.0)), TRUE);
					for (int i = 0; i < 18; i += 1) {
						rotorWheels[i].move();
						rotorWheels[i].x += xOffset;
						rotorWheels[i].y += yOffset;
						rotorWheels[i].draw();
						rotorWheels[i].x -= xOffset;
						rotorWheels[i].y -= yOffset;
						if (rotorWheels[i].rotSpeed > 0.0) {
							rotorWheels[i].rotSpeed -= 0.0004;
							if (rotorWheels[i].rotSpeed < 0.0) {
								rotorWheels[i].rotSpeed = 0.0;
							}
						}
					}
				}
				glColor4f(1.0, 1.0, 1.0, 0.45);
				placeimageeasy(scratchImages[(int)(scratchCount)], 0, 100, 1280, 464, TRUE);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				strcpy_s(temptext, 1000, bestEndText[cutSceneSpot]);
			} else {
				placeimageeasy(goodEndImages[cutSceneSpot], xOffset + 0 - (int)(640 * zoom), yOffset + 100 - (int)(232 * zoom), (int)(1280 * (1.0 + zoom)), (int)(464 * (1.0 + zoom)), TRUE);
				if (cutSceneSpot == 7) {
					placeimageeasy(goodEndImages[cutSceneSpot], xOffset + 0 - (int)(640 * 0.0), yOffset + 100 - (int)(232 * 0.0), (int)(1280 * (1.0 + 0.0)), (int)(464 * (1.0 + 0.0)), TRUE);
					for (int i = 0; i < 18; i += 1) {
						rotorWheels[i].move();
						rotorWheels[i].x += xOffset;
						rotorWheels[i].y += yOffset;
						rotorWheels[i].draw();
						rotorWheels[i].x -= xOffset;
						rotorWheels[i].y -= yOffset;
						if (rotorWheels[i].rotSpeed > 0.0) {
							rotorWheels[i].rotSpeed -= 0.0004;
							if (rotorWheels[i].rotSpeed < 0.0) {
								rotorWheels[i].rotSpeed = 0.0;
							}
						}
					}
				}
				glColor4f(1.0, 1.0, 1.0, 0.45);
				placeimageeasy(scratchImages[(int)(scratchCount)], 0, 100, 1280, 464, TRUE);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				strcpy_s(temptext, 1000, goodEndText[cutSceneSpot]);
			}
		}
		else {
			drawCutsceneImage(badEndImages[cutSceneSpot]);
			strcpy_s(temptext, 1000, badEndText[cutSceneSpot]);
		}

	}
	else {
		switch (cueOperationIntro) {
			case 0:
				if (strcmp("Roundup", operationList[0].name) == 0) {
					strcpy_s(temptext, 1000, roundupText[cutSceneSpot]);
					drawCutsceneImage(roundupImages[cutSceneSpot]);
				}
				else {
					strcpy_s(temptext, 1000, sledgehammerText[cutSceneSpot]);
					drawCutsceneImage(sledgehammerImages[cutSceneSpot]);
				}
				break;
			case 1:
				strcpy_s(temptext, 1000, fortitudeText[cutSceneSpot]);
				drawCutsceneImage(fortitudeImages[cutSceneSpot]);
				break;
			case 2:
				strcpy_s(temptext, 1000, overlordText[cutSceneSpot]);
				drawCutsceneImage(overlordImages[cutSceneSpot]);
				break;
			case 3:
				strcpy_s(temptext, 1000, bodyguardText[cutSceneSpot]);
				drawCutsceneImage(bodyguardImages[cutSceneSpot]);
				break;
			case 4:
				strcpy_s(temptext, 1000, pointblankText[cutSceneSpot]);
				drawCutsceneImage(pointblankImages[cutSceneSpot]);
				break;
			case 5:
				strcpy_s(temptext, 1000, gambitText[cutSceneSpot]);
				drawCutsceneImage(gambitImages[cutSceneSpot]);
				break;
			case 6:
				strcpy_s(temptext, 1000, tigerText[cutSceneSpot]);
				drawCutsceneImage(tigerImages[cutSceneSpot]);
				break;
			case 7:
				strcpy_s(temptext, 1000, neptuneText[cutSceneSpot]);
				drawCutsceneImage(neptuneImages[cutSceneSpot]);
				break;
			default:
				strcpy_s(temptext, 1000, "");
				break;
		}
	}

	placeimageeasy(cutsceneOverlay, 0, 0, renderx, rendery, FALSE);

	temptext[(int)currentChar] = '\0';
	drawtextCropped(temptext, 32, rendery - 128, 24, 24, 56, 0.9);	

	glColor4f(0.0, 0.0, 0.0, fade);
	placeimageeasy(tex1, 0, 0, renderx, rendery, FALSE);

	glColor4f(1.0, 1.0, 1.0, 1.0);

}
