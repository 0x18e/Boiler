#pragma once
#include "openal/al.h"
#include "openal/alc.h"
#include "dr_wav.h"
#include "tools.h"
#include <vector>
#include<memory>
class SoundBuffer {
public:
	SoundBuffer() : m_Buffer(0) {};
	~SoundBuffer();
	bool LoadFromFile(const std::string& name);
	void Clear();
	ALuint GetBuffer() const { return m_Buffer; }; // cannot modify m_BufferID;
private:
	ALuint m_Buffer;
};

class SoundSource {
public:
	SoundSource();
	~SoundSource();

	void SetBuffer(const std::shared_ptr<SoundBuffer>& buffer);
	void Play(bool loop = false);
	void Stop();
	void SetPositions(glm::vec3 vec);
private:
	ALuint m_Source;
	std::shared_ptr<SoundBuffer> m_BufferRef;
};

class AudioEngine {
public:
	static AudioEngine& Get() {
		return m_Instance;
	}
	// use dr_wav to get pcm data, fill in 
	bool Init();
	void Shutdown();

	std::shared_ptr<SoundBuffer> LoadSound(const std::string& filename);

private:
	AudioEngine() : m_pDevice(nullptr), m_pContext(nullptr) {}
	~AudioEngine() {};

	size_t m_cMaxSize;
	ALCdevice* m_pDevice;
	ALCcontext* m_pContext;
	static AudioEngine m_Instance;
	std::vector<std::shared_ptr<SoundBuffer>> m_LoadedBuffers;
};
