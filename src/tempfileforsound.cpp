#define RUN 0

#if RUN

#include "Engine.h"


// Get rid of useless headers later.
#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
// important early goals
// use RAII
// kernighan and ritchie convention
// hungarian notation
// use public, protected, private conventions.

#include <fstream>

#define NUM_BUFFERS 3
#define BUFFER_SIZE 4096
#define NUM_SOURCES 4
void DisplayALError(const char* operation, ALenum error) {
    if (error != AL_NO_ERROR) {
        // Retrieve a human-readable string for the error code
        const char* errStr = alGetString(error);
        std::cerr
            << "[OpenAL Error] " << operation
            << " failed: (" << error << ") "
            << (errStr ? errStr : "Unknown error")
            << std::endl;
    }
}
// one way to do it
struct WAVHeader {
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

int main(int argc, char* argv[]) {

    WAVHeader header;
    std::fstream file("W:\\Projects\\repos\\Aspera\\assets\\sounds\\wpn_denyselect.wav");
    // what is needed
    // the format, in wav this would be 
     // read everything manually
    char buffID[5]; // riff tag
    uint32_t chunkSize = 0;
    char waveID[5];
    buffID[4] = '\0';
    waveID[4] = '\0';
    file.read(buffID, 4); // gets name of buffer id
    file.read(reinterpret_cast<char*>(&chunkSize), 4); // file size - 8 bytes
    file.read(waveID, 4);
    LOG(buffID);
    LOG(chunkSize);
    LOG(waveID);
    std::vector<uint8_t> final_data;
    uint32_t final_data_size = 0;
    while (file) {
        // now we iterate through all the subchunks, we have the initial stuff above
        char chunkID[5] = { 0 };
        uint32_t chunkSize = 0;

        file.read(chunkID, 4);
        file.read(reinterpret_cast<char*>(&chunkSize), 4);
        LOG(chunkID);
        // here we are at the point where we read the 
        if (std::strncmp(chunkID, "fmt", 3) == 0) {
            // now we get subchunk data

            header.fmtSize = chunkSize;
            //file.read(reinterpret_cast<char*>(&header.fmtSize), sizeof(header.fmtSize));
            LOG(header.fmtSize << " fmt size");
            file.read(reinterpret_cast<char*>(&header.audioFormat), sizeof(header.audioFormat));
            LOG(header.audioFormat << " audio format");
            file.read(reinterpret_cast<char*>(&header.numChannels), sizeof(header.numChannels));
            LOG(header.numChannels << " num channels");
            file.read(reinterpret_cast<char*>(&header.sampleRate), sizeof(header.sampleRate));
            LOG(header.sampleRate << " sample rate");
            file.read(reinterpret_cast<char*>(&header.byteRate), sizeof(header.byteRate));
            LOG(header.byteRate << " byte rate");
            file.read(reinterpret_cast<char*>(&header.blockAlign), sizeof(header.blockAlign));
            LOG(header.blockAlign << " block align");
            file.read(reinterpret_cast<char*>(&header.bitsPerSample), sizeof(header.bitsPerSample));
            LOG(header.bitsPerSample << " bits per sample");

        }
        else if (std::strncmp(chunkID, "data", 4) == 0) {
            final_data_size = chunkSize;
            LOG("Found data chunk with size of data: " << chunkSize);
            std::vector<uint8_t> dat(chunkSize); // allocate vector space for all audio
            file.read(reinterpret_cast<char*>(dat.data()), chunkSize);
            final_data = dat;
            break;
        }
        else {
            LOG("seeking!");
            file.seekg(chunkSize, std::ios::cur);
        }
    }
    file.close();

    ALCdevice* device = alcOpenDevice(nullptr);
    ALCcontext* context;
    if (device) {
        LOG("found device");
        context = alcCreateContext(device, nullptr);
    }
    alcMakeContextCurrent(context);
    ALuint g_Buffers[NUM_BUFFERS];
    bool g_bEAX = alIsExtensionPresent("EAX2.0");
    alGetError();
    alGenBuffers(NUM_BUFFERS, g_Buffers);
    auto error = alGetError();
    if (error != AL_NO_ERROR) {
        DisplayALError("alGenBuffers :", error);
        return 0;
    }
    else {
        LOG("Buffers generated");
    }
    // current audio is mono 8
    LOG(header.numChannels);
    LOG(header.audioFormat);
    alBufferData(g_Buffers[0], AL_FORMAT_MONO8, final_data.data(), final_data_size, header.sampleRate);
    error = alGetError();
    if (error != AL_NO_ERROR) {
        DisplayALError("alBufferData buffer 0: ", error);
        alDeleteBuffers(NUM_BUFFERS, g_Buffers);
        return 0;
    }
    ALuint sources[NUM_SOURCES];
    alGenSources(1, sources);

    alSourcei(sources[0], AL_BUFFER, g_Buffers[0]);
    error = alGetError();
    if (error != AL_NO_ERROR) {
        DisplayALError("alSourcei: AL_BUFFER 0 : ", error);
    }
    alSourcePlay(sources[0]);
    system("sleep 5");
    alDeleteBuffers(NUM_BUFFERS, g_Buffers);
    return 0;
}

#endif