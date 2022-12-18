// Tygo Boons 2022

#include "mypch.h"
#include "Window.h"

namespace Core
{
	Window::Window(WindowProperties properties)
	{
		// Create new window instance with properties.
		m_Window = new sf::RenderWindow(sf::VideoMode(properties.Resolution.x, properties.Resolution.y), "Wii - Tanks", 7U, properties.ContextSettings);

		// Set resolution.
		m_Resolution = properties.Resolution;
	}

	glm::vec2 Window::GetNormalizedMousePosition() const
	{
		// Get screen size and mouse position.
		glm::vec2 screenSize = m_Resolution;
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_Window);

		// Get normalized screen position and change coordinate origin to the bottom left of the screen.
		glm::vec2 normalizedPosition = glm::vec2(static_cast<float>(mousePosition.x) / static_cast<float>(screenSize.x),
			-static_cast<float>(mousePosition.y) / static_cast<float>(screenSize.y) + 1.0f);

		return normalizedPosition;
	}
}