#pragma once
#include "openal/al.h"
#include "openal/alc.h"
#include "tools.h"
#include <vector>


class SoundBuffer {

};

class SoundSource {


};


class AudioEngine {
public:
	static AudioEngine& Get() {
		return m_Instance;
	}
	// use dr_wav to get pcm data, fill in 
	bool Init();


private:
	size_t m_cMaxSize;
	ALCdevice* m_pDevice;
	ALCcontext* m_pContext;
	static AudioEngine m_Instance;
};
