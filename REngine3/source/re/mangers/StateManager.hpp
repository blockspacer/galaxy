//
//  StateManager.hpp
//  REngine3
//
//  Created by reworks on 5/10/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#ifndef RENGINE3_STATEMANAGER_HPP_
#define RENGINE3_STATEMANAGER_HPP_

#include <memory>

#include <SFML/System/Time.hpp>

#include "re/types/Service.hpp"

namespace sf
{
	class Event;
	class Shader;
	class Font;
	class Texture;
}

namespace re
{
	class VFS;
	class World;
	class Window;
	class ConfigReader;
	class StateManager;
	
	template<typename Resource>
	class ResourceManager;

	class State
	{
	public:
		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Virtual destructor.
		*/
		virtual ~State();

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Load the states resources.
		*/
	    virtual void load() = 0;

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Unload the states resources.
		*/
	    virtual void unload() = 0;
	    
		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Poll for events in the current state.
		*/
	    virtual void handlePollEvents(sf::Event& event) = 0;

        /*
         * IMPORTS: none
         * EXPORTS: none
         * PURPOSE: Real-Time input of event feedback.
         */
        virtual void handleEvents(sf::Event& event) = 0;
        
		/*
		* IMPORTS: delta time
		* EXPORTS: none
		* PURPOSE: Updates the current state.
		*/
	    virtual void update(sf::Time dt) = 0;

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Render the current state.
		*/
	    virtual void render() = 0;

	protected:
		// Services
		Window* m_window;
		World* m_world;
		VFS* m_vfs;
		StateManager* m_stateManager;
		ResourceManager<sf::Font>* m_fontManager;
		ResourceManager<sf::Shader>* m_shaderManager;
		ResourceManager<sf::Texture>* m_spriteSheetManager;

		// Allows for loading stuff only once in load()
		bool m_doneOnce = false;
	};

	class StateManager : public Service
	{
	public:	    
		/*
		* IMPORTS: pointer to new state
		* EXPORTS: none
		* PURPOSE: Change the current state. Calls unload then load(), but NOT clean()!
		*/
	    void changeState(std::shared_ptr<State> s);

		/*
		* IMPORTS: optional state to reload to.
		* EXPORTS: none
		* PURPOSE: reloads the current state. Calls unload() and clean()
		*/
		void reloadState(std::shared_ptr<State> s = nullptr);

		/*
		* IMPORTS: pointer to new state
		* EXPORTS: none
		* PURPOSE: This changes the state but WITHOUT CHANGING RESOURCES!
		*/
	    void setState(std::shared_ptr<State> s);
	    
        /*
         * IMPORTS: none
         * EXPORTS: none
         * PURPOSE: Poll for events in the current state.
         */
        void handlePollEvents(sf::Event& event);
        
        /*
         * IMPORTS: none
         * EXPORTS: none
         * PURPOSE: Real-Time input of event feedback.
         */
        void handleEvents(sf::Event& event);

		/*
		* IMPORTS: delta time
		* EXPORTS: none
		* PURPOSE: Updates the current state.
		*/
	    void update(sf::Time dt);

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Render the current state.
		*/
	    void render();
	    
		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Load the states resources.
		*/
	    void load();

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Unload the states resources.
		*/
	    void unload();
			    
	private:
	    std::shared_ptr<State> m_currentState;
	};
}

#endif