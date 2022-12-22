// Tygo Boons 2022

#include "mypch.h"
#include "AudioSource.h"

namespace Entity
{
	// Set default values.
	AudioSource::AudioSource()
		: m_IsLooping(false),
		m_Pitch(1.0f),
		m_Volume(100.0f),
		m_PlaybackTime(0.0f)
	{
		m_Sound.setLoop(false);
		m_Sound.setPitch(m_Pitch);
		m_Sound.setVolume(m_Volume);
		m_Sound.setPlayingOffset(sf::Time());
	}

	void AudioSource::Update()
	{
		m_PlaybackTime = m_Sound.getPlayingOffset().asSeconds();
	}

	void AudioSource::LoadClipFromFile(const std::string& filepath)
	{
		// Set audio clip file path.
		m_ClipFilePath = filepath;

		// Loads the file.
		bool loaded = m_Clip.loadFromFile(m_ClipFilePath);

		ASSERT(loaded, "File could not be found: " + m_ClipFilePath)


		// Assign the clip to the sound source.
		m_Sound.setBuffer(m_Clip);
	}

	void AudioSource::Play()
	{	
		// Play sound if a sound buffer is found.
		if (m_Sound.getBuffer())
		{
			m_Sound.play();
		}
		else
		{
			LOG_ERROR(GAMEOBJECT_IDENTITY + " AudioSource has no audio clip and can not be played.")
		}
	}

	void AudioSource::Stop()
	{
		// Stop audio.
		m_Sound.stop();
	}

	void AudioSource::SetTime(float time)
	{
		// Make sure time is not less than 0.
		if (time < 0)
		{
			time = 0;
		}

		m_PlaybackTime = time;

		// Set the playing offset of the audio clip.
		m_Sound.setPlayingOffset(sf::Time(sf::seconds(time)));
	}

	void AudioSource::SetPitch(float pitch)
	{
		// Create new pitch variable that is clamped.
		float newPitch = glm::clamp(pitch, 0.01f, 3.0f);

		// Warn if pitch is changed.
		if (pitch != newPitch)
		{
			LOG_WARN(GAMEOBJECT_IDENTITY + "Pitch is out of range. Now set to: " + STR(newPitch))
		}

		// Set new pitch variable.
		m_Pitch = newPitch;

		// Set new pitch in sound.
		m_Sound.setPitch(m_Pitch);
	}

	void AudioSource::SetVolume(float volume)
	{
		// Create new volume variable that is clamped.
		float newVolume = glm::clamp(volume, 0.0f, 1.0f);

		// Warn if volume is changed.
		if (volume != newVolume)
		{
			LOG_WARN(GAMEOBJECT_IDENTITY + "Volume is out of range. Now set to: " + STR(newVolume))
		}

		// Set new volume variable.
		m_Volume = newVolume;

		// Set new volume in sound.
		m_Sound.setVolume(m_Volume * 100.0f);
	}

	void AudioSource::SetLooping(bool looping)
	{
		m_IsLooping = looping;
		m_Sound.setLoop(looping);
	}
}