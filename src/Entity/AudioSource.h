// Tygo Boons 2022

#pragma once

#include "Component.h"
#include <SFML/Audio.hpp>

namespace Entity
{
	class AudioSource : public Component
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(AudioSource)

	public:
		AudioSource();

		void Update() override;

		// Load audio clip from file.
		void LoadClipFromFile(const std::string& filepath);

		// Play audio clip.
		void Play();

		// Stop audio clip.
		void Stop();

		// Set playback time
		void SetTime(float time);

		// Returns the current play time of the clip.
		float GetTime() const { return m_PlaybackTime; }

		// Set audio pitch.
		void SetPitch(float pitch);

		// Get audio pitch.
		float GetPitch() const { return m_Pitch; }

		// Set audio volume.
		void SetVolume(float volume);

		// Get audio volume.
		float GetVolume() const { return m_Volume; }

		// Enable or disable audio looping.
		void SetLooping(bool looping);

		// See if audio is looping.
		bool IsLooping() const { return m_IsLooping; }

	private:
		float m_PlaybackTime;
		float m_Pitch;
		float m_Volume;
		bool m_IsLooping;
		sf::SoundBuffer m_Clip;
		sf::Sound m_Sound;
	};
}