///
/// ServiceLocator.cpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#include "ServiceLocator.hpp"

///
/// Core namespace.
///
namespace galaxy
{
	galaxy::ServiceLocator& ServiceLocator::get() noexcept
	{
		static galaxy::ServiceLocator s_serviceLocator;
		return s_serviceLocator;
	}

	sol::state* ServiceLocator::lua() const noexcept
	{
		return m_lua;
	}

	galaxy::Config* ServiceLocator::config() const noexcept
	{
		return m_config;
	}

	galaxy::FileSystem* ServiceLocator::fs() const noexcept
	{
		return m_fs;
	}

	sf::RenderWindow* ServiceLocator::window() const noexcept
	{
		return m_window;
	}

	galaxy::World* ServiceLocator::world() const noexcept
	{
		return m_world;
	}

	galaxy::Editor* ServiceLocator::editor() const noexcept
	{
		return m_editor;
	}

	starlight::Dispatcher* ServiceLocator::dispatcher() const noexcept
	{
		return m_dispatcher;
	}

	galaxy::Serializer* ServiceLocator::serializer() const noexcept
	{
		return m_serializer;
	}

	ServiceLocator::ServiceLocator()
		:m_lua(nullptr), m_config(nullptr), m_fs(nullptr), m_window(nullptr), m_world(nullptr), m_editor(nullptr), m_dispatcher(nullptr)
	{
	}
}