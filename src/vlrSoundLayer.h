
#ifndef __SOUNDLAYER_H__
#define __SOUNDLAYER_H__



#pragma comment(lib,"fmodex_vc.lib")
#include <windows.h>

#include <fmod.hpp>
#include <fmod_errors.h>
#include "cCritter.h"
#define STATE_MAIN	0
#define STATE_GAME	1
#define STATE_WIN	2
#define PASOS	0
#define DISPARO	1
#define ATAQUE	2	





class vlrSoundLayer 
{

public:
	
	vlrSoundLayer ();
	virtual ~vlrSoundLayer();

	bool Init(); 
	
	void ERRCHECK(FMOD_RESULT result);
	void vlrSoundLayer::LoadData();

	bool PlaySound(int state);
	bool Playeffects(int state);
	bool SoundEffectsUnit(cCritter *Critter);
	void Finalize();
	//
private:
	FMOD::Sound      *sound1, *sound2, *sound3,*sound4,*sound5;
    FMOD::Channel    *channel ,*channel2,*channelef, *channelef1,	*channelef2;
	FMOD_RESULT       result;
  FMOD::System     *system;
  
};


#endif
