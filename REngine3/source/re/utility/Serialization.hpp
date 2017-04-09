//
//  Serialization.hpp
//  REngine3
//
//  Created by reworks on 20/10/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#ifndef RENGINE3_SERIALIZATION_HPP_
#define RENGINE3_SERIALIZATION_HPP_

#include <fstream>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "re/app/World.hpp"
#include "re/component/TransformComponent.hpp"

// http://www.boost.org/doc/libs/1_62_0/libs/serialization/doc/index.html

namespace re
{
	namespace serialization
	{
		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Serialize the engine.
		*/
		inline void save(World* world, const std::string& fileName)
		{
			std::ofstream out(fileName);

			boost::archive::binary_oarchive oa(out);

			for (auto& it : world->GetAlive())
			{
				oa << it.second;
				oa << *(it.second.Get<TransformComponent>());
			}

			for (auto& it : world->GetDead())
			{
				oa << it.second;
				oa << *(it.second.Get<TransformComponent>());
			}

			out.close();
		}

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Deserialize the engine.
		*/
		inline void load(World* world, const std::string& fileName)
		{
			std::ifstream in(fileName);

			boost::archive::binary_iarchive ia(in);

			for (auto& it : world->GetAlive())
			{
				ia >> it.second;
				ia >> *(it.second.Get<TransformComponent>());
			}

			for (auto& it : world->GetDead())
			{
				ia >> it.second;
				ia >> *(it.second.Get<TransformComponent>());
			}

			in.close();
		}
	}
}

#endif
