
#include "vlrSoundLayer.h"

#include "cLog.h"
#include <stdio.h>
#include <windows.h>


vlrSoundLayer::vlrSoundLayer()
{
	sound1=NULL;
	sound2=NULL;
		sound3=NULL;
	channel = 0;
		channelef = 0;
	system=NULL;
	
}

vlrSoundLayer::~vlrSoundLayer(){}

bool vlrSoundLayer::Init()
{
	cLog *Log = cLog::Instance();
	//HRESULT hr;
	
  
   
   // int               key;
    //unsigned int      version;


	
result = FMOD::System_Create(&system);
result= system->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
result =  system->init(32, FMOD_INIT_NORMAL, 0);

	return true;
}

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


void vlrSoundLayer::Finalize()
{
	/*
	 result = sound1->release();
    ERRCHECK(result);
    /*result = sound2->release();
    ERRCHECK(result);
    result = sound3->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);
	*/
    
}

void vlrSoundLayer::LoadData(){
	result = system->createSound("intro2dgame_2.wav", FMOD_SOFTWARE, 0, &sound1);
	result = system->createSound("mvj1_3.mp3", FMOD_SOFTWARE, 0, &sound2);
		result = system->createSound("efcalico.mp3", FMOD_SOFTWARE, 0, &sound3);
  // ERRCHECK(result);
  
}

bool vlrSoundLayer::PlaySound(int state){

	switch(state)
	{
		case STATE_MAIN:
		
			result =system->playSound(FMOD_CHANNEL_FREE, sound1, false, &channel);
			break;

	case STATE_GAME:
		
			channel->setPaused(true);
			sound2->setMode(FMOD_LOOP_NORMAL);
			result =system->playSound(FMOD_CHANNEL_FREE, sound2, false, &channel);
			break;


	 }

						return true;


	}
bool vlrSoundLayer::Playeffects(int state){

	channelef->setPaused(true);
	result = sound3->setMode(FMOD_LOOP_OFF); 
	result =system->playSound(FMOD_CHANNEL_FREE, sound3, false, &channelef);

	return true;
	}