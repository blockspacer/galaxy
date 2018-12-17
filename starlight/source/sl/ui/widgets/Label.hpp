///
/// Label.hpp
/// starlight
///
/// Created by reworks on 17/12/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef STARLIGHT_LABEL_HPP_
#define STARLIGHT_LABEL_HPP_

#include "sl/ui/Widget.hpp"

namespace sl
{
	///
	/// Label for UI objects. Does not support tooltips.
	///
	class Label final : public Widget
	{
	public:
		///
		/// Constructor.
		///
		/// \param x x pos relative to UI panel.
		/// \param y y pos relative to UI panel.
		/// \param text Label text.
		/// \param font Label font.
		/// \param col Label colour.
		///
		Label(int x, int y, const std::string& text, const std::string& font, const ALLEGRO_COLOR col);
		
		///
		/// Destructor.
		///
		~Label() noexcept;

		///
		/// Update the widget.
		///
		void update() override;

		///
		/// Render the widget.
		///
		/// Does not render the tooltip.
		///
		void render() override;

		///
		/// Changes current text.
		///
		/// \param text New text to set.
		///
		void setText(const std::string& text);

	private:
		///
		/// Default constructor.
		/// Deleted.
		///
		Label() = delete;

	private:
		///
		/// Text to display.
		///
		std::string m_text;

		///
		/// Text font.
		///
		ALLEGRO_FONT* m_font;

		///
		/// Text colour.
		///
		ALLEGRO_COLOR m_colour;
	};
}

#endif