///
/// main.cpp
/// sandbox
///
/// Refer to LICENSE.txt for more details.
///

#include <galaxy/core/World.hpp>
#include <galaxy/core/Application.hpp>
#include <galaxy/core/ServiceLocator.hpp>

#include "GameLayer.hpp"

class Sandbox : public galaxy::Application
{
public:
	Sandbox(std::unique_ptr<galaxy::Config>& config)
		:galaxy::Application(config)
	{
	}
};

int main(int argc, char **argv)
{
	bool restart = false;

	do
	{
		restart = false;

		{
			try
			{
				std::unique_ptr<galaxy::Config> config = std::make_unique<galaxy::Config>();
				config->init("bin/config.json");
				if (!config->open())
				{
					config->define<std::string>("archive", "bin/data.zip");
					config->define<std::string>("write-dir", "write-dir");
					config->define<unsigned int>("width", 1280);
					config->define<unsigned int>("height", 720);
					config->define<std::string>("title", "sandbox");
					config->define<unsigned int>("anti-alias", 2);
					config->define<unsigned int>("framerate-limit", 0);
					config->define<bool>("vsync", false);
					config->define<std::string>("icon", "icon.png");
					config->define<bool>("key-repeat", false);
					config->define<bool>("mouse-cursor-visible", true);
					config->define<std::string>("saves", "saves/");

					config->create();
					config->open();
				}

				Sandbox sandbox(config);

				galaxy::World* world = galaxy::ServiceLocator::get().world();
				world->pushLayer<GameLayer>();

				restart = sandbox.run();
			}
			catch (const std::exception& e)
			{
				PL_LOG(pl::Log::Level::ERROR_, e.what());
			}
			catch (...)
			{
				PL_LOG(pl::Log::Level::ERROR_, "Threw an unknown exception. Why are you not inheriting from std::exception?");
			}
		}

	} while (restart);
		
	return 0;
}