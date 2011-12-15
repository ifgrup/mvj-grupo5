
#ifndef __SOUNDLAYER_H__
#define __SOUNDLAYER_H__



#pragma comment(lib,"fmodex_vc.lib")
#include <windows.h>

#include <fmod.hpp>
#include <fmod_errors.h>

#define STATE_MAIN	0
#define STATE_GAME	1




class vlrSoundLayer 
{

public:
	
	vlrSoundLayer ();
	virtual ~vlrSoundLayer();

	bool Init(); 
	
	void ERRCHECK(FMOD_RESULT result);
	void vlrSoundLayer::LoadData();

	bool vlrSoundLayer::PlaySound(int state);
	bool vlrSoundLayer::Playeffects(int state);
	void vlrSoundLayer::Finalize();
	//
private:
	FMOD::Sound      *sound1, *sound2, *sound3;
    FMOD::Channel    *channel ,*channelef;
	FMOD_RESULT       result;
  FMOD::System     *system;
};


#endif
