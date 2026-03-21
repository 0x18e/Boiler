#include "AudioEngine.h"


bool SoundBuffer::LoadFromFile(const std::string& name){
	drwav wav;
	if (!drwav_init_file(&wav, name.c_str())) {
		std::cerr << "Failed to open WAV: " << name << '\n';
		return false;
	}
	
	size_t totalSamples = wav.totalSampleCount;
	std::vector<drwav_int16> pcmData(totalSamples);
	drwav_uint64 samplesRead = drwav_read_s16(&wav, totalSamples, pcmData.data());
	drwav_uninit(&wav);

	if (samplesRead == 0) {
		std::cerr << "[SoundBuffer] No data decoded: " << name << "\n";
		return false;
	}
	
	ALenum format = (wav.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	alGenBuffers(1, &m_Buffer);
	alBufferData(
		m_Buffer,
		format,
		pcmData.data(),
		static_cast<ALsizei>(samplesRead * sizeof(int16_t)),
		wav.sampleRate
	);

	if (alGetError() != AL_NO_ERROR) {
		std::cerr << "[SoundBuffer] alBufferData error: " << name << "\n";
		return false;
	}
	LOG("Loaded sound");
	return true;
	
}
SoundBuffer::~SoundBuffer() {

}
void SoundBuffer::Clear() {
	if (m_Buffer != 0) {
		alDeleteBuffers(1, &this->m_Buffer);
	}
}

SoundSource::SoundSource() {
	alGenSources(1, &m_Source);
}

SoundSource::~SoundSource() {
}

void SoundSource::SetBuffer(const std::shared_ptr<SoundBuffer>& buffer) {
	m_BufferRef = buffer;
	alSourcei(m_Source, AL_BUFFER, buffer->GetBuffer());
}

void SoundSource::Play(bool loop) {
	alSourcei(m_Source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	alSourcePlay(m_Source);
}

void SoundSource::Stop() {
	alSourceStop(m_Source);
}

void SoundSource::SetPositions(glm::vec3 vec) {
	alSource3f(m_Source, AL_POSITION, vec.x, vec.y, vec.z);
}

// AudioEngine
AudioEngine AudioEngine::m_Instance;

bool AudioEngine::Init(){
	this->m_pDevice = alcOpenDevice(nullptr);
	if (!m_pDevice) {
		std::cerr << "AudioEngine failed to open default device\n";
		return false;
	}
	this->m_pContext = alcCreateContext(this->m_pDevice, nullptr);
	if (!m_pContext || !alcMakeContextCurrent(this->m_pContext)) {
		// one context only
		std::cerr << "AudioEngine failed to create or set a contexnt\n";
		return false;
	}
	
	return true;
}

void AudioEngine::Shutdown() {
	alcMakeContextCurrent(nullptr);
	if (m_pContext) {
		alcDestroyContext(m_pContext);
		m_pContext = nullptr;
	}
	if (m_pDevice) {
		alcCloseDevice(m_pDevice);
		m_pDevice = nullptr;
	}
	for (auto& ptr : this->m_LoadedBuffers) {
		LOG("Clearing Loaded buffers");
		ptr.get()->Clear();
	}
	m_LoadedBuffers.clear();
	LOG("Destroyed audio engine");
}

std::shared_ptr<SoundBuffer> AudioEngine::LoadSound(const std::string& filename) {
	std::shared_ptr<SoundBuffer> buf = std::make_shared<SoundBuffer>();
	if (!buf->LoadFromFile(filename)) {
		return nullptr;
	}
	m_LoadedBuffers.push_back(buf);
	return buf;
}