///
///  FontBook.hpp
///  rework
///
///  Created by reworks on 22/09/2017.
///  Copyright (c) 2018+ reworks.
///  Refer to LICENSE.txt for more details.
///

#ifndef REWORK_FONTBOOK_HPP_
#define REWORK_FONTBOOK_HPP_

#include <allegro5/allegro_font.h>

#include "re/types/ResourceCache.hpp"
#include "re/types/ServiceLocator.hpp"

namespace re
{
	class FontBook final : public ServiceLocator<FontBook>, public ResourceCache<ALLEGRO_FONT*>
	{
	public:
		///
		/// \brief Construct FontManager and add fonts.
		///
		/// You can have multiple of the same font file provided the id and size are different.
		/// E.g. "Arial12" or "Arial14".
		///
		/// \param script Script file containing font data to parse.
		///
		FontBook(const std::string& script);

		///
		/// Cleanup fonts.
		///
		~FontBook() override;

		///
		/// Clean up resources.
		///
		void clean() override;

	private:
		///
		/// Default Constructor.
		/// Deleted.
		///
		FontBook() = delete;

		///
		/// Copy Constructor.
		/// Deleted.
		///
		FontBook(const FontBook&) = delete;

		///
		/// Move Constructor.
		/// Deleted.
		///
		FontBook(FontBook&&) = delete;
	};
}

#endif