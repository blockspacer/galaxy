///
/// Application.cpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#include <sol/sol.hpp>
#include <imgui-SFML.h>
#include <nlohmann/json.hpp>
#include <SFML/Window/Event.hpp>
#include <protostar/utility/Time.hpp>

#include "galaxy/fs/FileSystem.hpp"
#include "galaxy/layer/ImGuiLayer.hpp"
#include "galaxy/scripting/LuaUtils.hpp"
#include "galaxy/core/ServiceLocator.hpp"
#include "galaxy/fs/PhysfsInputStream.hpp"

#include "Application.hpp"

///
/// Core namespace.
///
namespace galaxy
{
	Application::Application(std::unique_ptr<galaxy::Config>& config)
	:m_restart(false)
	{
		// Seed pseudo-random algorithms.
		std::srand(std::time(nullptr));

		// Supposed to improve performance. Need to run tests and ensure we aren't using C stdio.
		std::ios::sync_with_stdio(false);
		
		// Logging.
		std::string lf = "logs/" + protostar::getFormattedTime() + ".txt";
		PL_LOG_I.init(lf);
		PL_LOG_I.setMinimumLevel(pl::Log::Level::INFO);
		// TODO: something for sfml + better exception handling.

		// Set up all of the difference services.
		// The services are configured based off of the config file.

		// Create lua instance and open libraries.
		m_lua = std::make_unique<sol::state>();
		m_lua->open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::os, sol::lib::math, sol::lib::table, sol::lib::io);
		galaxy::ServiceLocator::get().m_lua = m_lua.get();

		// Config reader.
		m_config = std::move(config);
		galaxy::ServiceLocator::get().m_config = m_config.get();

		// File system.
		m_fs = std::make_unique<galaxy::FileSystem>();
		m_fs->mount(m_config->get<std::string>("archive"));
		m_fs->setWriteDir(m_config->get<std::string>("write-dir"));
		galaxy::ServiceLocator::get().m_fs = m_fs.get();

		// App window.
		m_window = std::make_unique<sf::RenderWindow>();
		m_window->create(sf::VideoMode(m_config->get<unsigned int>("width"),
			m_config->get<unsigned int>("height")),
			m_config->get<std::string>("title"),
			sf::Style::Titlebar | sf::Style::Close,
			sf::ContextSettings(0, 0, m_config->get<unsigned int>("anti-alias")));
		
		m_window->requestFocus();
		m_window->setActive();
		m_window->setFramerateLimit(m_config->get<unsigned int>("framerate-limit"));
		m_window->setVerticalSyncEnabled(m_config->get<bool>("vsync"));

		sf::Image icon; // Does not need to be permanent since window copies the data.
		icon.loadFromStream(galaxy::PhysfsInputStream(m_config->get<std::string>("icon")));
		m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		
		m_window->setKeyRepeatEnabled(m_config->get<bool>("key-repeat"));
		m_window->setMouseCursorGrabbed(false);
		m_window->setMouseCursorVisible(m_config->get<bool>("mouse-cursor-visible"));
		m_window->setVisible(true);
		galaxy::ServiceLocator::get().m_window = m_window.get();

		// Game "world".
		m_world = std::make_unique<World>();
		galaxy::ServiceLocator::get().m_world = m_world.get();

		// Event dispatcher.
		m_dispatcher = std::make_unique<starlight::Dispatcher>();
		galaxy::ServiceLocator::get().m_dispatcher = m_dispatcher.get();

		// Serializer.
		m_serializer = std::make_unique<galaxy::Serializer>(m_config->get<std::string>("saves"));
		galaxy::ServiceLocator::get().m_serializer = m_serializer.get();

		//m_textureAtlas = std::make_unique<TextureAtlas>(m_world->m_textureFolderPath, m_configReader->lookup<int>(config, "graphics", "atlasPowerOf"));
		//ServiceLocator::textureAtlas = m_textureAtlas.get();

		//m_textureAtlas->m_nullTexture = m_configReader->lookup<std::string>(config, "graphics", "nullTexture");

		//m_fontBook = std::make_unique<FontBook>(m_configReader->lookup<std::string>(config, "font", "fontScript"));
		//ServiceLocator::fontBook = m_fontBook.get();

		//m_shaderLibrary = std::make_unique<ShaderLibrary>(m_configReader->lookup<std::string>(config, "graphics", "shaderScript"));
		//ServiceLocator::shaderLibrary = m_shaderLibrary.get();

		//m_musicPlayer = std::make_unique<MusicPlayer>(m_configReader->lookup<std::string>(config, "audio", "musicScript"));
		//ServiceLocator::musicPlayer = m_musicPlayer.get();

		//m_musicPlayer->m_nullMusic = m_configReader->lookup<std::string>(config, "audio", "nullMusic");

		//m_soundPlayer = std::make_unique<SoundPlayer>(m_configReader->lookup<std::string>(config, "audio", "soundScript"));
		//ServiceLocator::soundPlayer = m_soundPlayer.get();

		//m_soundPlayer->m_nullSound = m_configReader->lookup<std::string>(config, "audio", "nullSound");

		//m_box2dHelper = std::make_unique<Box2DHelper>(m_configReader->lookup<float32>(config, "box2d", "gravity"));
		//ServiceLocator::box2dHelper = m_box2dHelper.get();

		//m_box2dHelper->m_b2world->SetContactListener(&m_engineCallbacks);

		// Register all usertypes used by this application for sol3.
		LuaUtils::registerUsertypes();

		// Register ImGui layer.
		m_world->pushLayer<galaxy::ImGuiLayer>(&m_restart);
	}

	Application::~Application()
	{
		// We want to destroy everything in a specific order to make sure stuff is freed correctly.
		// And of course the file system being the last to be destroyed.
		m_serializer.reset();
		m_dispatcher.reset();
		m_world.reset();
		m_window.reset();
		m_fs.reset();
		m_config.reset();
		m_lua.reset();

		PL_LOG_I.deinit();
	}

	bool Application::run()
	{
		// This is to measure UPS and FPS.
		int frames = 0;
		int updates = 0;
		std::uint64_t timer = 0;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		// This is to ensure gameloop is running at 60 UPS, independant of FPS.
		const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

		// The timer in milliseconds for UPS and FPS.
		timer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		// Fixed timestep gameloop. Pretty easy to understand.
		// Simply loop the game until the window closes, then the mainloop can handle restarting the application if restart = true.
		sf::Clock clock;
		while (m_window->isOpen())
		{
			sf::Time dt = clock.restart();
			timeSinceLastUpdate += dt;

			while (timeSinceLastUpdate > timePerFrame)
			{
				timeSinceLastUpdate -= timePerFrame;

				sf::Event event;
				while (m_window->pollEvent(event))
				{
					m_world->event(event);

					switch (event.type)
					{
					case sf::Event::Closed:
						m_window->close();
						break;

					#ifdef _DEBUG
					case sf::Event::KeyPressed:
						switch (event.key.code)
						{
						case sf::Keyboard::Escape:
							m_window->close();
							break;
						}
						break;
					#endif
					}
				}

				m_world->update(timeSinceLastUpdate);
				updates++;
			}
			
			// has to be here rather than in editor...
			#ifdef _DEBUG
			ImGui::SFML::Update(*m_window.get(), timeSinceLastUpdate);
			#endif

			m_window->clear(sf::Color::White);
			
			m_world->render();

			m_window->display();

			frames++;
			if ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - timer) > 1000)
			{
				timer += 1000;
				PL_LOG(pl::Log::Level::INFO, std::to_string(updates) + " ups, " + std::to_string(frames) + " fps.");

				updates = 0;
				frames = 0;
			}
		}

		return m_restart;
	}
}