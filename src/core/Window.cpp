// Tygo Boons 2022

#include "mypch.h"
#include "Window.h"

namespace Core
{
	// Creates the window instance.
	Window::Window(WindowProperties properties)
		: m_Resolution(properties.Resolution),
		m_Window(new sf::RenderWindow(sf::VideoMode(properties.Resolution.x, properties.Resolution.y), properties.Name, properties.Style, properties.ContextSettings))
	{
		// Print initialization messages.
		LOG_INFO("Initializing window:")
		LOG_INFO(" Name: " + properties.Name)
		LOG_INFO(" Resolution: " + VEC2STR(properties.Resolution))
	}
}