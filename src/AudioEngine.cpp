#include "AudioEngine.h"

bool AudioEngine::Init(){
	this->m_pDevice = alcOpenDevice(nullptr);
	if (m_pDevice) {
		this->m_pContext = alcCreateContext(this->m_pDevice, nullptr);
		alcMakeContextCurrent(this->m_pContext); // one context only
	}
	else {
		LOG("Could get handle to audio device");
		return false;
	}
	
	
}


