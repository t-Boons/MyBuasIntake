// Tygo Boons 2022

#pragma once

#include "Core/Core.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "glm/glm.hpp"

namespace Core
{
	struct WindowProperties
	{
		sf::ContextSettings ContextSettings = sf::ContextSettings();
		bool Fullscreen = false;
		glm::ivec2 Resolution = { 1280, 720 };
		std::string Name = "My Window";
	};

	class Window
	{
		MAKE_SHARED_ONEPARAM(Window, WindowProperties, properties)

	public:
		// Initialize window.
		Window(WindowProperties properties);

		// See if window is opened.
		bool IsOpen() const { return m_Window->isOpen(); }

		// Poll events.
		bool PollEvent(sf::Event& event) const { return m_Window->pollEvent(event); }

		// Close the window.
		void Close() const { m_Window->close(); }

		// Get the resolution of the window.
		const glm::vec2& GetResolution() const { return m_Resolution; }

		// Get fullscreen resolution
		glm::vec2 GetFullscreenResolution() const;

		// Pop OpenGL states.
		void PopGLStates() const { m_Window->popGLStates(); }

		// Push OpenGL states.
		void PushGLStates() const { m_Window->pushGLStates(); }

		// Get native SFML window.
		sf::RenderWindow* GetSFMLWindow() const { return m_Window; }
		
		// Display the current renderbuffer.
		void Display() const { m_Window->display(); }

		// Get window properties.
		const WindowProperties& GetProperties() const { return m_Properties; }

	private:
		sf::RenderWindow* m_Window;
		glm::vec2 m_Resolution;
		WindowProperties m_Properties;
	};
}