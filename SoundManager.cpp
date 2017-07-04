//
//  SoundManager.cpp
//  Block Tricks
//
//  Created by Benny Abramovici on 2/26/15.
//  Copyright (c) 2015 Benny Abramovici. All rights reserved.
//
#include "SoundManager.h"

SoundManager* SoundManager::s_pInstance;

SoundManager::SoundManager()
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, (4096 / 2));
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}

bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
    if(type == SOUND_MUSIC)
    {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if(pMusic == 0)
        {
            std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        
        m_music[id] = pMusic;
        return true;
    }
    else if(type == SOUND_SFX)
    {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if(pChunk == 0)
        {
            std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        
        m_sfxs[id] = pChunk;
        return true;
    }
    return false;
}

void SoundManager::playMusic(std::string id, int loop)
{
    if (soundOn)
    Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(std::string id, int loop)
{
    if (soundOn)
    Mix_PlayChannel(-1, m_sfxs[id], loop);
}

void SoundManager::initAll()
{
    soundOn = true;
    Mix_VolumeMusic(64);
    
    this->load("bg_music.mp3", "bg", SOUND_MUSIC);
    this->load("moveBlock.wav","move",SOUND_SFX);
    this->load("clearBlock.wav","clear",SOUND_SFX);
    this->load("crash.wav","crash",SOUND_SFX);
    this->load("rotateRight.wav","rr",SOUND_SFX);
    this->load("rotateLeft.wav","rl",SOUND_SFX);
    this->load("blockLanded.wav","land",SOUND_SFX);
    
}

// allows the cycling of sound on and off by pressing the s key

void SoundManager::update()
{
    if ((soundOn) && (Mix_PlayingMusic() == 0)) // if sound selected on but music is not playing
        this->playMusic("bg", -1);
    else if (soundOn == false)  // if sound selected off
        Mix_HaltMusic();
}















