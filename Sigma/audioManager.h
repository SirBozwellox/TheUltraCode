#ifndef AUDIOMANAGER_H_INCLUDED
#define AUDIOMANAGER_H_INCLUDED

using namespace irrklang;

extern char audioDirectory[200];

extern char victoryAudio[4][3][100];
extern char failureAudio[4][3][100];
extern int letterSenders[22];

extern float globalVolume;

extern ISoundEngine* audioEngine;

class sound {
	public:
		char filename[200];
		ISound* handle;
		bool playing;
		float baseVolume;
		float volume;
		float fadeVal;
		float fadeSpeed;
		int position;
		bool looping;
		void play(bool loop);
		void pause();
		void resume();
		void stop();
		void man();
		void drop();
		bool isValid();
		sound();
		sound(char infile[200]);
};

extern sound bombeFastTicker1;
extern sound bombeTick1;
extern sound homeScreenMusic;
extern sound openLetter;
extern sound bulbPickup;
extern sound bulbDrop;
extern sound wire1;
extern sound wire2;
extern sound lightClick;
extern sound tick1;
extern sound tick2;
extern sound typeWriter1;
extern sound clickTick1;
extern sound puzzleScreenMusic;
extern sound dayMusic;
extern sound paperSlide1;
extern sound fileSelect1;
extern sound bulbClick1;
extern sound sparkSound1;
extern sound sparkSound2;
extern sound messageDown;
extern sound messageUp;
extern sound filmTicker;
extern sound victoryMusic;
extern sound letterAudio;
extern sound puzzleEnd;
extern sound tutorialAudio;
extern sound cutsceneAudio;
extern sound easterEgg;

void initAudioManager();

void manageAudio();

#endif
