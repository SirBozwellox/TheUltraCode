#include "main.h"

using namespace irrklang;

//char audioDirectory[200] = "C:/Users/Admin/Documents/Visual Studio 2015/Sigma/assets/audio/";
//char audioDirectory[200] = "../assets/audio/";
char audioDirectory[200] = "assets/audio/";

float globalVolume = 1.0;

float fadeAmount = 0.01;

char victoryAudio[4][3][100] = {
	{ "vo/travis_victory_1.mp3", "vo/travis_victory_2.mp3", "vo/travis_victory_3.mp3" },
	{ "vo/turing_victory_1.mp3", "vo/turing_victory_2.mp3", "vo/turing_victory_4.mp3" },
	{ "vo/hugh_victory_1.mp3", "vo/hugh_victory_2.mp3", "vo/hugh_victory_3.mp3" },
	{ "vo/newman_victory_1.mp3", "vo/newman_victory_1.mp3", "vo/newman_victory_1.mp3" }
};

char failureAudio[4][3][100] = {
	{ "vo/travis_failure_1.mp3", "vo/travis_failure_2.mp3", "vo/travis_failure_3.mp3" },
	{ "vo/turing_failure_1.mp3", "vo/turing_failure_2.mp3", "vo/turing_failure_3.mp3" },
	{ "vo/hugh_failure_1.mp3", "vo/hugh_failure_2.mp3", "vo/hugh_failure_3.mp3" },
	{ "vo/newman_failure_1.mp3", "vo/newman_failure_1.mp3", "vo/newman_failure_1.mp3" }
};

int letterSenders[22] = {0, 1, 1, 2, 1, 1, 2, 0, 2, 0, 1, 2, 2, 3, 1, 2, 0, 2, 1, 1, 0};

ISoundEngine* audioEngine = createIrrKlangDevice();

sound bombeFastTicker1;
sound bombeTick1;
sound homeScreenMusic;
sound openLetter;
sound bulbPickup;
sound bulbDrop;
sound wire1;
sound wire2;
sound lightClick;
sound tick1;
sound tick2;
sound typeWriter1;
sound clickTick1;
sound puzzleScreenMusic;
sound dayMusic;
sound paperSlide1;
sound fileSelect1;
sound bulbClick1;
sound sparkSound1;
sound sparkSound2;
sound messageDown;
sound messageUp;
sound filmTicker;
sound victoryMusic;
sound letterAudio;
sound puzzleEnd;
sound tutorialAudio;
sound cutsceneAudio;
sound easterEgg;

sound::sound(char infile[200]) {
	strcpy_s(filename, 200, audioDirectory);
	strcat_s(filename, 200, infile);
	playing = FALSE;
	baseVolume = 1.0;
	volume = 1.0;
	fadeVal = 1.0;
	fadeSpeed = 0.01;
	position = 0;
}

sound::sound(){}

bool sound::isValid() {
	if (strcmp(filename, "") == 0) {
		return false;
	}
	return true;
}

void sound::drop() {
	audioEngine->removeSoundSource(filename);
	strcpy_s(filename, "");
}

void sound::play(bool loop) {
	handle = audioEngine->play2D(filename, loop, false, true);
	playing = TRUE;
	looping = loop;
}

void sound::pause() {
	position = handle->getPlayPosition();
	handle->setIsPaused(true);
	playing = false;
}

void sound::resume() {
	play(looping);
	handle->setVolume(volume * baseVolume);
	handle->setPlayPosition(position);
}

void sound::stop() {
	if (playing) {
		handle->stop();
//		drop();
		playing = FALSE;
		position = 0;
	}
}

void sound::man() {
	if (playing) {
		if (handle != NULL) {
			if (fadeVal > volume) {
				volume += fadeSpeed;
			}
			if (fadeVal < volume) {
				volume -= fadeSpeed;
			}
			handle->setVolume(volume * baseVolume);
		}
		if (volume < 0.0) {
			volume = 0.0;
		}
		if (volume > 1.0) {
			volume = 1.0;
		}
	}
}

void initAudioManager() {
	if (steamEnabled) {
		strcpy_s(audioDirectory, "assets/audio/");
	}
	else {
		strcpy_s(audioDirectory, "../assets/audio/");
	}
	bombeFastTicker1 = sound("bombe_fast_ticker1.mp3");
	bombeFastTicker1.baseVolume = 0.25;
	bombeTick1 = sound("bombe_tick1.mp3");
	bombeTick1.baseVolume = 0.11;
	openLetter = sound("open_letter.mp3");
	bulbPickup = sound("bulb_pickup_1.mp3");
	bulbDrop = sound("bulb_drop_1.mp3");
	wire1 = sound("wire1.mp3");
	wire1.baseVolume = 0.8;
	wire2 = sound("wire2.mp3");
	wire2.baseVolume = 0.8;
	lightClick = sound("light_click.mp3");
	tick1 = sound("tick1.mp3");
	tick1.baseVolume = 0.8;
	tick2 = sound("tick2.mp3");
	tick2.baseVolume = 0.8;
	typeWriter1 = sound("typewriter1.mp3");
	typeWriter1.baseVolume = 0.8;
	clickTick1 = sound("bombe_tick1.mp3");
	clickTick1.baseVolume = 0.4;
	puzzleScreenMusic = sound("puzzlescreen_1.mp3");
	dayMusic = sound("dayscreen_3.mp3");
	dayMusic.baseVolume = 0.8;
	paperSlide1 = sound("paper_slide_1.mp3");
	paperSlide1.baseVolume = 0.5;
	fileSelect1 = sound("file_select_1.mp3");
	bulbClick1 = sound("bulb_click_1.mp3");
	sparkSound1 = sound("spark1.mp3");
	sparkSound1.baseVolume = 0.25;
	sparkSound2 = sound("spark3.mp3");
	sparkSound2.baseVolume = 0.15;
	messageDown = sound("messageDown.mp3");
	messageDown.baseVolume = 1.0;
	messageUp = sound("messageUp.mp3");
	messageUp.baseVolume = 1.0;
	victoryMusic = sound("victory_1.mp3");
	victoryMusic.baseVolume = 0.8;
	filmTicker = sound("film_ticker_1.mp3");
	filmTicker.baseVolume = 0.2;
	easterEgg = sound("vo/this_is_not_an_easter_egg.mp3");
	easterEgg.baseVolume = 1.0;

	homeScreenMusic = sound("homescreen_1.mp3");

	tutorialAudio = sound("");

	audioEngine->setSoundVolume(0.5f);
}

void manageAudio() {
	if (!audioEngine)
	{
		printf("Error starting audio engine \n");
	}
	else {
		audioEngine->setSoundVolume(globalVolume);
	}

	if (screen == HOMESCREEN || screen == OPTIONSSCREEN || screen == WAREFFORTSCREEN) {
		if (!bombeFastTicker1.playing) {
			bombeFastTicker1.play(TRUE);
		}
		bombeFastTicker1.volume = 1.0 - fadeValue;
		bombeTick1.volume = 1.0 - fadeValue;
	}
	else {
		bombeFastTicker1.stop();
	}

	if (screen == HOMESCREEN || screen == SPLASHSCREEN || screen == OPTIONSSCREEN || screen == CREDITS) {
		homeScreenMusic.fadeVal = 1.0;
		if (!homeScreenMusic.playing) {
			homeScreenMusic.play(TRUE);
		}
	}
	else {
		if (screen == CUTSCENE && cueOperationIntro == -1) {
			if (homeScreenMusic.volume <= fadeAmount) {
				homeScreenMusic.stop();
				homeScreenMusic.play(TRUE);
			}
			homeScreenMusic.fadeVal = 0.3;
		}
		else {
			homeScreenMusic.fadeVal = 0.0;
		}
	}

	if (screen == PUZZLESCREEN || screen == INTELSCREEN || screen == FREEPLAYSCREEN) {
		puzzleScreenMusic.fadeVal = 1.0;
		if (!puzzleScreenMusic.playing) {
			puzzleScreenMusic.play(TRUE);
		}
	}
	else {
		puzzleScreenMusic.fadeVal = 0.0;
		if (puzzleScreenMusic.volume <= fadeAmount) {
			puzzleScreenMusic.stop();
		}
	}

	if (screen == DAYSCREEN) {
		dayMusic.fadeVal = 1.0;
		if (!dayMusic.playing) {
			dayMusic.play(TRUE);
		}
	}
	else {
		dayMusic.fadeVal = 0.0;
		if (dayMusic.volume <= fadeAmount) {
			dayMusic.stop();
		}
		if (dayMusic.volume > dayMusic.fadeVal) {
			dayMusic.volume += fadeAmount * 0.5;
		}
	}

	if (screen == LETTERSCREEN) {
		letterAudio.fadeVal = 1.0;
		if (letterAudio.position != 0 && !letterAudio.playing) {
			letterAudio.resume();
		}
	}
	else {
		letterAudio.fadeVal = 0.0;
	}

	letterAudio.man();
	if (letterAudio.volume <= 0.01) {
		letterAudio.pause();
	}

	tutorialAudio.fadeSpeed = 0.05;
	if (screen == PUZZLESCREEN) {
		if (letterAudio.volume <= 0.01 && letterAudio.isValid()) {
			letterAudio.drop();
		}
		tutorialAudio.fadeVal = 1.0;
		if (tutorialAudio.position != 0 && !tutorialAudio.playing) {
			tutorialAudio.resume();
		}
	}
	else {
		tutorialAudio.fadeVal = 0.0;
	}

	tutorialAudio.man();
	if (tutorialAudio.volume <= 0.05) {
		if (screen != PUZZLESCREEN) {
			tutorialAudio.stop();
		}
		else {
			tutorialAudio.pause();
		}
	}

	cutsceneAudio.fadeSpeed = 0.05;
	if (screen == CUTSCENE) {
		filmTicker.fadeVal = 1.0;
		cutsceneAudio.fadeVal = 1.0;
		if (cutsceneAudio.position != 0 && !cutsceneAudio.playing) {
			cutsceneAudio.resume();
		}
	}
	else {
		filmTicker.fadeVal = 0.0;
		cutsceneAudio.fadeVal = 0.0;
	}

	cutsceneAudio.man();
	if (cutsceneAudio.volume <= 0.05) {
		cutsceneAudio.pause();
	}

//	if (filmTicker.volume == 0.0) {
//		filmTicker.stop();
//	}

	bombeFastTicker1.man();
	bombeTick1.man();
	homeScreenMusic.man();

	bulbPickup.man();
	bulbDrop.man();
	wire1.man();
	wire2.man();
	lightClick.man();
	tick1.man();
	tick2.man();
	typeWriter1.man();
	clickTick1.man();
	puzzleScreenMusic.man();
	dayMusic.man();
	paperSlide1.man();
	fileSelect1.man();
	bulbClick1.man();
	sparkSound1.man();
	sparkSound2.man();
	messageDown.man();
	messageUp.man();
	victoryMusic.man();
	filmTicker.man();

}