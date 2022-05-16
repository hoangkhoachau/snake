#include "sound.h"

#pragma region Sound
Sound::Sound()
{
	filename = NULL;
}

Sound::~Sound()
{
	if (filename != NULL)
	{
		delete filename;
		filename = NULL;
	}

}

void Sound::SetSound(string file)
{
	wchar_t* wtext = new wchar_t[file.size() + 1];
	mbstowcs(wtext, file.c_str(), file.size() + 1);//Plus null
	filename = wtext;

}

bool Sound::PlayLoop()
{
	return PlaySoundW(filename, NULL, SND_LOOP | SND_ASYNC | SND_FILENAME | SND_NOSTOP);
}

bool Sound::PlayOnce()
{
	return PlaySoundW(filename, NULL, SND_FILENAME | SND_SYNC);
}

bool Sound::PlayOnceBackground()
{
	return PlaySoundW(filename, NULL, SND_FILENAME | SND_ASYNC);
}

bool Sound::StopPlaying()
{
	return PlaySound(NULL, NULL, NULL);
}
#pragma endregion

#pragma region SoundEffect
SoundEffect::SoundEffect()
{
	start.SetSound("Audio//start.wav");
	credit.SetSound("Audio//Snake_Credit.wav");		    // OKE
	eat1.SetSound("Audio//eating.wav");			   
	eat2.SetSound("Audio//Snake_Eat.wav");	            // OKE
	lose1.SetSound("Audio//Snake_Lose_1.wav");			// OKE
	lose2.SetSound("Audio//Snake_Lose.wav");			// OKE
	passLevel.SetSound("Audio//Snake_Pass_Level.wav");	// OKE
	background.SetSound("Audio//Snake_Intro.wav");		// OKE
	menu.SetSound("Audio//Snake_Menu.wav");			    // OKE
	enter.SetSound("Audio//Snake_Enter.wav");		    // OKE
	clock.SetSound("Audio//Snake_Clock.wav");		    // OKE
	timeoff.SetSound("Audio//Snake_Time_Off.wav");		// OKE
	passLevel5.SetSound("Audio//Snake_Pass5.wav");	    // OKE
	ready.SetSound("Audio//Snake_Count.wav");			// OKE
	error.SetSound("Audio//Snake_Error.wav");			// OKE
	hitting.SetSound("Audio//hitting.wav");
}

SoundEffect::~SoundEffect() {}

void SoundEffect::playStart()
{
	start.PlayOnceBackground();
}

void SoundEffect::playBackground()
{
	background.PlayLoop();
}

void SoundEffect::playEat1()
{
	eat1.PlayOnceBackground();
}

void SoundEffect::playEat2()
{
	eat2.PlayOnceBackground();
}

void SoundEffect::playEnter()
{
	enter.PlayOnceBackground();
}

void SoundEffect::playLose1()
{
	lose1.PlayOnceBackground();
}

void SoundEffect::playCredit()
{
	credit.PlayOnceBackground();
}

void SoundEffect::playLose2()
{
	lose2.PlayOnceBackground();
}

void SoundEffect::playPassLevel()
{
	passLevel.PlayOnceBackground();
}

void SoundEffect::playClock()
{
	clock.PlayOnceBackground();
}

void SoundEffect::playReady()
{
	ready.PlayOnceBackground();
}

void SoundEffect::playTimeOff()
{
	timeoff.PlayOnceBackground();
}

void SoundEffect::playMenu()
{
	menu.PlayOnceBackground();
}

void SoundEffect::playPassLevel5()
{
	passLevel5.PlayOnceBackground();
}

void SoundEffect::playError()
{
	error.PlayOnceBackground();
}

void SoundEffect::StopSound()
{
	PlaySound(NULL, NULL, NULL);
}
void SoundEffect::playHitting()
{
	hitting.PlayOnceBackground();
}
#pragma endregion