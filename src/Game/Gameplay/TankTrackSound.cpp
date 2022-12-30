// 2022 Tygo Boons

#include "mypch.h"
#include "TankTrackSound.h"
#include "Utils/TimedEvent.h"

namespace Gameplay
{
	void TankTrackSound::Start()
	{
		// Create all audio sources for driving.
		RefPtr<Entity::AudioSource> shootSound0 = AddComponent(Entity::AudioSource::Create());
		shootSound0->LoadClipFromFile("Assets/Audio/Effects/Drive0.wav");
		shootSound0->SetVolume(0.15f);

		RefPtr<Entity::AudioSource> shootSound1 = AddComponent(Entity::AudioSource::Create());
		shootSound1->LoadClipFromFile("Assets/Audio/Effects/Drive1.wav");
		shootSound1->SetVolume(0.15f);

		RefPtr<Entity::AudioSource> shootSound2 = AddComponent(Entity::AudioSource::Create());
		shootSound2->LoadClipFromFile("Assets/Audio/Effects/Drive2.wav");
		shootSound2->SetVolume(0.15f);

		RefPtr<Entity::AudioSource> shootSound3 = AddComponent(Entity::AudioSource::Create());
		shootSound3->LoadClipFromFile("Assets/Audio/Effects/Drive3.wav");
		shootSound3->SetVolume(0.15f);

		m_TrackSounds.push_back(shootSound0);
		m_TrackSounds.push_back(shootSound1);
		m_TrackSounds.push_back(shootSound2);
		m_TrackSounds.push_back(shootSound3);

		UpdatePitch();

		// Get tank engine reference.
		m_TankEngine = GetComponent<TankEngine>();

		m_Time = 0;
		m_CurrentTrackSound = 0;
	}

	void TankTrackSound::Update()
	{
		m_Time += Core::Time::GetDeltaTime() * m_TankEngine->GetSpeed();

		// Play sound with current track index.
		if (m_Time > SOUND_DELAY)
		{
			m_Time = 0;

			// Update current track index.
			m_CurrentTrackSound++;
			m_CurrentTrackSound = m_CurrentTrackSound >= m_TrackSounds.size() ? 0 : m_CurrentTrackSound;

			// Play the right track sound.
			m_TrackSounds[m_CurrentTrackSound]->Play();
		}
	}

	void TankTrackSound::UpdatePitch()
	{
		for (auto& s : m_TrackSounds)
		{
			s->SetPitch(m_Pitch);
		}
	}
}