// Tygo Boons 2022

#pragma once

#include "glm/glm.hpp"
#include <SFML/Window.hpp>

#define KEYCODE_AMOUNT		   256
#define MOUSECODE_AMOUNT	   6

namespace Core
{

	class Input
	{
	public:

		// Typedef to detach sf namespace.
		typedef sf::Keyboard::Key Key;
		typedef sf::Mouse::Button Button;

		// Handles events.
		static void SendEvent(sf::Event& event);

		// Clear inputs (must be ran after all input logic).
		static void Flush();

		// Keyboard key pressed.
		static bool IsKeyPressed(Key keycode);

		// Keyboard key held.
		static bool IsKeyHeld(Key keycode);

		// Keyboard key released.
		static bool IsKeyReleased(Key keycode);

		// Mouse button pressed.
		static bool IsMouseButtonPressed(Button button);

		// Mouse button held down.
		static bool IsMouseButtonHeld(Button button);

		// Mouse button released.
		static bool IsMouseButtonReleased(Button button);

		// Get mouse position.
		static glm::vec2 GetMousePosition();

		// Get mouse position on screen from 0,0 on the bottom left to 1,1 on the top right.
		static glm::vec2 GetNormalizedMousePosition();

	private:

		// Keyboard key state bitsets.
		static std::bitset<KEYCODE_AMOUNT> s_KeysPressed;
		static std::bitset<KEYCODE_AMOUNT> s_KeysRepeating;
		static std::bitset<KEYCODE_AMOUNT> s_KeysReleased;

		// Mouse button state bitsets.
		static std::bitset<MOUSECODE_AMOUNT> s_MouseButtonsPressed;
		static std::bitset<MOUSECODE_AMOUNT> s_MouseButtonsRepeating;
		static std::bitset<MOUSECODE_AMOUNT> s_MouseButtonsReleased;

	};
}