// Tygo Boons 2022

#include "mypch.h"
#include "Window.h"

namespace Core
{
	// Creates the window instance.
	Window::Window(WindowProperties properties)
		: m_Resolution(properties.Resolution),
		m_Window(new sf::RenderWindow(sf::VideoMode(properties.Resolution.x, properties.Resolution.y), properties.Name, 7U, properties.ContextSettings))
	{
		// Print initialization messages.
		LOG_INFO("Initializing window:")
		LOG_INFO(" Name: " + properties.Name)
		LOG_INFO(" Resolution: " + VEC2STR(properties.Resolution))
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