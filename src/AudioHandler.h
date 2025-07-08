#pragma once
#include "openal/al.h"
#include "openal/alc.h"
#include <unordered_map>
#include <string>
#include<iostream>

#define NUM_BUFFERS 3
#define BUFFER_SIZE 4096
#define NUM_SOURCES 4

struct WAVFile {
    char riff[4];
    uint32_t chunkSize;
    char wave[4];
    char fmt[4];
    uint32_t fmtSize;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};

class AudioHandler {
	// Notes, how would this need to be change to accomodate for level changes? remove old cached audio
public:
    AudioHandler();
    ~AudioHandler();
    Sound* GetSound(std::string sound_name);
private:
    ALCcontext* m_pContext;
    ALCdevice* m_pDevice;
    ALuint m_Buffers[NUM_BUFFERS];
    ALuint m_Sources[NUM_SOURCES];

	Sound LoadSound();
	WAVFile* LoadWAV();
    std::unordered_map<std::string, std::unique_ptr<Sound>> m_Sounds; // sound container
};

class Sound {
	// what should a single sound have?
	// play, pause, stop, then pack the sound into an unordered map in audiohandler, and call whatever sound
	// is needed
public:
	void Play();
	void Stop();
	void Pause();
    WAVFile m_Data;
private:
    ALuint source; // dont think i need this
};