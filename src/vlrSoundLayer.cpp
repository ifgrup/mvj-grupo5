
#include "vlrSoundLayer.h"

#include "cLog.h"
#include <stdio.h>
#include <windows.h>


vlrSoundLayer::vlrSoundLayer()
{
	sound1=NULL;
	sound2=NULL;
		sound3=NULL;
			sound4=NULL;
			sound5=NULL;
	channel = 0;
	channel2 = 0;
		channelef = 0;
		channelef1=0;
		channelef2=0;
	system=NULL;
	
	
}

vlrSoundLayer::~vlrSoundLayer(){}

bool vlrSoundLayer::Init()
{
	cLog *Log = cLog::Instance();

	result = FMOD::System_Create(&system);
	result= system->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
	result =  system->init(32, FMOD_INIT_NORMAL, 0);
	return true;
}

void vlrSoundLayer::ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
		char kk[256];
		sprintf(kk,"FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		cLog::Instance()->Msg(kk);
		
        exit(-1);
    }
}


void vlrSoundLayer::Finalize()
{
	
	result = sound1->release();
    ERRCHECK(result);
    result = sound2->release();
    ERRCHECK(result);
    result = sound3->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);
	
    
}

void vlrSoundLayer::LoadData(){
	result = system->createSound("drumloop.wav", FMOD_SOFTWARE, 0, &sound1);
	result = system->createSound("mvj1_3.mp3", FMOD_SOFTWARE, 0, &sound2);
		result = system->createSound("efcalico.mp3", FMOD_SOFTWARE, 0, &sound3);
		result = system->createSound("laser-01.mp3", FMOD_SOFTWARE, 0, &sound4);
			result = system->createSound("efcalico.mp3", FMOD_SOFTWARE, 0, &sound5);//falta sonido pasos
		
  // ERRCHECK(result);
  
}

bool vlrSoundLayer::PlaySound(int state){
	bool sonando=false;

	

	switch(state)
	{
		case STATE_MAIN:
			channelef->setPaused(true);
			channelef1->setPaused(true);
		channel->isPlaying(&sonando);
		if(sonando==false){
			result =system->playSound(FMOD_CHANNEL_FREE, sound1, false, &channel);
			
		}
		break;

	case STATE_GAME:
		
			channel->setPaused(true);
			channelef->setPaused(true);
			channelef1->setPaused(true);
			
			channel2->isPlaying(&sonando);
			if(sonando==false){
			sound2->setMode(FMOD_LOOP_NORMAL);
			result =system->playSound(FMOD_CHANNEL_FREE, sound2, false, &channel2);
			}
			break;


	 }

						return true;


	}


bool vlrSoundLayer::Playeffects(int state){
	



	bool sonando=false;
	bool sonando1=false;
   sound5->setMode(FMOD_LOOP_NORMAL);

	switch(state)
	{
		case 1:
			channelef->setPaused(false);
		channelef->isPlaying(&sonando);
		if(sonando==false){
			result =system->playSound(FMOD_CHANNEL_FREE, sound4, false, &channelef);
			
		}
		break;

	case 2:
		
			channelef1->setPaused(false);
			channelef1->isPlaying(&sonando1);
			if(sonando1==false){
		
			result =system->playSound(FMOD_CHANNEL_FREE, sound5, false, &channelef1);
			}
			break;
case 3:
		
			//channelef2->setPaused(false);
			channelef2->isPlaying(&sonando1);
			if(sonando1==false){
		
			result =system->playSound(FMOD_CHANNEL_FREE, sound3, false, &channelef2);
			}
			break;


	 }

						return true;



	//channelef->setPaused(true);
	//result = sound3->setMode(FMOD_LOOP_OFF); 

/*
	channelef->isPlaying(&sonando);
	if(sonando==false){
	result =system->playSound(FMOD_CHANNEL_FREE, sound3, false, &channelef);
	}
	return true;*/
	}


bool vlrSoundLayer::SoundEffectsUnit(cCritter *Critter){


	if(Critter->IsMoving()){
		Playeffects(2);
	}else{
	channelef1->setPaused(true);
	}

	if(Critter->GetShooting()){
	Playeffects(1);
	
	}else{
	channelef->setPaused(true);
	}

	if(Critter->AlAtaquue()){
	Playeffects(3);
	
	}else{
//channelef2->setPaused(true);
	}

	/*
	if(Critter->IsFiring()){
	result =system->playSound(FMOD_CHANNEL_FREE, sound4, false, &channelef2);
	}
	*/

	//channelef1->setPaused(true);


		
//	if(!Critter->IsMoving()){
		//channelef1->setPaused(false);
		//result = sound5->setMode(FMOD_LOOP_NORMAL);
//	result =system->playSound(FMOD_CHANNEL_FREE, sound5, false, &channelef1);
	
//	}//else{
	//channelef1->setPaused(true);

//}
	return true;
	}