#pragma once
#include "openal/al.h"
#include "openal/alc.h"
#include <unordered_map>
#include <string>
#include "tools.h"
#include<iostream>
#include <fstream>
#define NUM_BUFFERS 3
#define BUFFER_SIZE 4096
#define NUM_SOURCES 6

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
    uint16_t dataSize;
    ALenum format; // TODO: replace audioFormat with this or vice versa.
    std::vector<uint8_t> data;
};



class Sound {
	// what should a single sound have?
	// play, pause, stop, then pack the sound into an unordered map in audiohandler, and call whatever sound
	// is needed
public:
	void Play();
	void Stop();
	void Pause();

private:

};

class AudioHandler {
    // Notes, how would this need to be change to accomodate for level changes? remove old cached audio
public:
    static AudioHandler& Get() {
        return m_Instance;
    }
    bool Init();
    AudioHandler();
    ~AudioHandler();
    Sound* GetSound(std::string sound_name);
    void PlaySound(std::string name);
private:
    static AudioHandler m_Instance;
    ALCcontext* m_pContext;
    ALCdevice* m_pDevice;
    ALuint m_Buffers[NUM_BUFFERS];
    ALuint m_Sources[NUM_SOURCES];
    // Keeps track of allocated buffer count
    int m_iBufferCount;
    Sound LoadSound(std::string path, std::string name);
    WAVFile LoadWAV(std::string path);
    std::unordered_map<std::string, std::unique_ptr<Sound>> m_Sounds; // sound container
    std::unordered_map<std::string, ALuint*> m_SrcMap;
};
void DisplayALError(std::string msg, ALenum error);
