// Tygo Boons 2022

#include "mypch.h"

#include "Input.h"
#include "Game.h"
#include "Core.h"

namespace Core
{
	// Initialize bitsets and other static input variables.
	std::bitset<KEYCODE_AMOUNT> Input::s_KeysPressed = std::bitset<KEYCODE_AMOUNT>();
	std::bitset<KEYCODE_AMOUNT> Input::s_KeysRepeating = std::bitset<KEYCODE_AMOUNT>();
	std::bitset<KEYCODE_AMOUNT> Input::s_KeysReleased = std::bitset<KEYCODE_AMOUNT>();

	std::bitset<MOUSECODE_AMOUNT> Input::s_MouseButtonsPressed = std::bitset<MOUSECODE_AMOUNT>();
	std::bitset<MOUSECODE_AMOUNT> Input::s_MouseButtonsRepeating = std::bitset<MOUSECODE_AMOUNT>();
	std::bitset<MOUSECODE_AMOUNT> Input::s_MouseButtonsReleased = std::bitset<MOUSECODE_AMOUNT>();

	void Input::SendEvent(sf::Event& event)
	{

		// Update if key is pressed.
		if (event.type == event.KeyPressed)
		{
			// Only run if key is not being repeated.
			if (!s_KeysRepeating[event.key.code])
			{
				s_KeysPressed.set(event.key.code, true);
				s_KeysRepeating.set(event.key.code, true);
			}
		}

		// Update if key is released.
		if (event.type == event.KeyReleased)
		{
			s_KeysReleased.set(event.key.code, true);
			s_KeysRepeating.set(event.key.code, false);
		}



		// Update if mouse button is pressed.
		if (event.type == event.MouseButtonPressed)
		{
			// Only run if button is not being repeated.
			if (!s_MouseButtonsRepeating[event.key.code])
			{
				s_MouseButtonsPressed.set(event.mouseButton.button, true);
				s_MouseButtonsRepeating.set(event.mouseButton.button, true);
			}
		}

		// Update if mouse button is released
		if (event.type == event.MouseButtonReleased)
		{
			s_MouseButtonsReleased.set(event.mouseButton.button, true);
			s_MouseButtonsRepeating.set(event.mouseButton.button, false);
		}

	}

	void Input::Flush()
	{
		// Reset all bits to clear input states.
		s_KeysPressed.reset();
		s_KeysReleased.reset();

		s_MouseButtonsPressed.reset();
		s_MouseButtonsReleased.reset();
	}

	bool Input::IsKeyPressed(Key keyCode)
	{
		return s_KeysPressed[keyCode];
	}

	bool Input::IsKeyReleased(Key keyCode)
	{
		return s_KeysReleased[keyCode];
	}

	bool Input::IsKeyHeld(Key keycode)
	{
		return s_KeysRepeating[keycode];
	}

	bool Input::IsMouseButtonPressed(Button button)
	{
		return s_MouseButtonsPressed[button];
	}

	bool Input::IsMouseButtonHeld(Button button)
	{
		return s_MouseButtonsRepeating[button];
	}

	bool Input::IsMouseButtonReleased(Button button)
	{
		return s_MouseButtonsReleased[button];
	}

	glm::ivec2 Input::GetMousePosition()
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*Core::Game::Get()->GetWindow()->GetSFMLWindow());
		return { mousePos.x, mousePos.y };
	}

	glm::vec2 Input::GetNormalizedMousePosition()
	{
		// Get screen size and mouse position.
		glm::vec2 screenSize = Core::Game::Get()->GetWindow()->GetResolution();
		glm::vec2 mousePosition = GetMousePosition();;

		// Get normalized screen position and change coordinate origin to the bottom left of the screen.
		glm::vec2 normalizedPosition = glm::vec2(static_cast<float>(mousePosition.x) / static_cast<float>(screenSize.x),
			-static_cast<float>(mousePosition.y) / static_cast<float>(screenSize.y) + 1.0f);

		return normalizedPosition;
	}
}