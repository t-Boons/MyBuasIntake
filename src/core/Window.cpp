// Tygo Boons 2022

#include "mypch.h"
#include "Window.h"

namespace Core
{
	// Creates the window instance.
	Window::Window(WindowProperties properties)
		: m_Resolution(properties.Resolution),
		m_Window(new sf::RenderWindow(sf::VideoMode(properties.Resolution.x, properties.Resolution.y),
			properties.Name, properties.Fullscreen ? sf::Style::Fullscreen : sf::Style::None, properties.ContextSettings)),
		m_Properties(properties)
	{
		// Print initialization messages.
		LOG_INFO("Initializing window:")
		LOG_INFO(" Name: " + properties.Name)
		LOG_INFO(" Resolution: " + VEC2STR(properties.Resolution))
		LOG_INFO(" Fullscreen: " + STR(properties.Fullscreen))
	}

	glm::vec2 Window::GetFullscreenResolution() const
	{
		// Get desktop resolution.
		glm::vec2 desktopRes = glm::vec2(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

		// Select desktop resolution or screen resolution based on if it is fullscreen.
		return m_Properties.Fullscreen ? desktopRes : m_Resolution;
	}
}