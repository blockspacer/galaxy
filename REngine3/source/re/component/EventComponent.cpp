//
//  EventComponent.cpp
//  REngine3
//
//  Created by reworks on 22/09/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#include "re/types/Event.hpp"

#include "EventComponent.hpp"

namespace re
{
	EventComponent::EventComponent()
	{
	}

	EventComponent::~EventComponent()
	{
		m_events.clear();
	}

	void EventComponent::SubmitOnEvent(EventType type, std::function<void(void)> func)
	{
		auto it = m_events.find(type);
		if (it != m_events.end())
		{
			m_events[type].push_back(func);
		}
		else
		{
			m_events.emplace(type, std::vector<std::function<void(void)>>());
			m_events[type].push_back(func);
		}
	}

	void EventComponent::OnEvent(EventType type)
	{
		auto it = m_events.find(type);

		for (auto& v : it->second)
		{
			v();
		}
	}
}