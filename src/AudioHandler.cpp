#include "AudioHandler.h"

AudioHandler AudioHandler::m_Instance;

bool AudioHandler::Init() {
    m_iBufferCount = 0;
    this->m_pDevice = alcOpenDevice(nullptr);
    if (m_pDevice) {
        LOG("Device found");
        LOG("Setting context");
        this->m_pContext = alcCreateContext(this->m_pDevice, nullptr);

    }
    alcMakeContextCurrent(this->m_pContext);
    bool g_bEAX = alIsExtensionPresent("EAX2.0");
    alGetError();
    alGenBuffers(NUM_BUFFERS, this->m_Buffers);
    if (alGetError() != AL_NO_ERROR) {
        // error
        DisplayALError("alGenBuffers: ", alGetError());
        return false;
    }
    else {
        LOG("Generated buffers");
    }
    
    for (int i = 0; i < NUM_SOURCES; ++i) {
        ALuint source;
        alGenSources(1, &source);
        m_Sources[i] = source;
        LOG("Source Generated");
    }
    this->LoadSound("assets/sounds/wpn_denyselect.wav", "wpn_denyselect");
    this->LoadSound("assets/sounds/wpn_hudoff.wav", "wpn_hudoff");
    return true;
}

AudioHandler::AudioHandler() {
    
}
AudioHandler::~AudioHandler() {

}

Sound* AudioHandler::GetSound(std::string sound_name) {
	if (this->m_Sounds.find(sound_name) != m_Sounds.end()) {
		return m_Sounds[sound_name].get();
	}
	LOG("Could not find sound");
	return nullptr;
}

Sound AudioHandler::LoadSound(std::string path, std::string name){
    WAVFile header = this->LoadWAV(path);
    LOG(header.byteRate);
    LOG("Current buffer count at start: " << this->m_iBufferCount);
    alBufferData(this->m_Buffers[m_iBufferCount], header.format, header.data.data(), header.dataSize, header.sampleRate);
    if (alGetError() != AL_NO_ERROR) {
        DisplayALError("alBufferData buffer " + std::to_string(m_iBufferCount), alGetError());
    }
    alSourcei(this->m_Sources[m_iBufferCount], AL_BUFFER, this->m_Buffers[m_iBufferCount]);
    if (alGetError() != AL_NO_ERROR) {
        DisplayALError("alSourcei: AL_BUFFER " + std::to_string(m_iBufferCount), alGetError());
    }
    
    
    LOG("Incrementing buffer count: ");
    this->m_SrcMap[name] = &m_Sources[m_iBufferCount];
    ++m_iBufferCount;
    LOG(m_iBufferCount);
    
    
    //alSourcePlay(m_Sources[0]);
    /*
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
    */



    return Sound();    
}

WAVFile AudioHandler::LoadWAV(std::string path){
    // horrible code
    WAVFile header;
    std::fstream file(path);
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
            header.dataSize = chunkSize;
            LOG("Found data chunk with size of data: " << chunkSize);
            std::vector<uint8_t> dat(chunkSize); // allocate vector space for all audio
            file.read(reinterpret_cast<char*>(dat.data()), chunkSize);
            final_data = dat;
            header.data = dat;
            break;
        }
        else {
            LOG("seeking!");
            file.seekg(chunkSize, std::ios::cur);
        }
    }
    file.close();


    // do the rest of the audio conditionals here
    if (header.bitsPerSample == 8 && header.numChannels == 1) {
        header.format = AL_FORMAT_MONO8;
    }

    return header;
}

void AudioHandler::PlaySound(std::string name) {
    if (m_SrcMap.find(name) != m_SrcMap.end()) {
        LOG("Found sound");
        if (m_SrcMap[name] == nullptr) {
            LOG("danglign?");
        }
        alSourcePlay(*m_SrcMap[name]);
    }
}

void DisplayALError(std::string msg, ALenum error){
    std::string errStr = alGetString(error);
    LOG("Error message: " << msg << " Failed: " << error << errStr);
}
