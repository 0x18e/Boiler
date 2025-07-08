#include "AudioHandler.h"

AudioHandler::AudioHandler() {

}

Sound* AudioHandler::GetSound(std::string sound_name) {
	if (this->m_Sounds.find(sound_name) != m_Sounds.end()) {
		return this->m_Sounds[sound_name];
	}
	LOG("Could not find sound");
	return nullptr;
}
