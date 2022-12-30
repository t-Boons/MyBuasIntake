// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "TankEngine.h"

#define SOUND_DELAY 0.5f

namespace Gameplay
{
	class TankEngine;

	class TankTrackSound : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankTrackSound)

	public:

		// Constructor is done like this to make to pitch default to 1 before any pitch can manually be set. 
		// Otherwise pitch would be 0 if not manually changed.
		TankTrackSound()
			: m_Pitch(1)
		{}

		virtual void Start() override;

		virtual void Update() override;

		// Set the pitch of the sounds.
		void SetPitch(float pitch) { m_Pitch = pitch; UpdatePitch(); };

	private:
		// Update the audiosource pitches.
		void UpdatePitch();

	private:
		std::vector<RefPtr<Entity::AudioSource>> m_TrackSounds;
		RefPtr<TankEngine> m_TankEngine;
		uint8_t m_CurrentTrackSound;
		float m_Time, m_Pitch;
	};
}