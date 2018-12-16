///
/// ToggleButton.hpp
/// starlight
///
/// Created by reworks on 16/12/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef STARLIGHT_TOGGLEBUTTON_HPP_
#define STARLIGHT_TOGGLEBUTTON_HPP_

#include <array>

#include "sl/events/MouseMovedEvent.hpp"
#include "sl/events/MousePressedEvent.hpp"
#include "sl/events/MouseReleasedEvent.hpp"
#include "sl/ui/Widget.hpp"

namespace sl
{
	///
	/// Creates a button that toggles from one state to another.
	//  Can be used to create check boxes or radial ui objects.
	///
	class ToggleButton final : public Widget
	{
		///
		/// Defines a state for the button.
		///
		enum class State
		{
			///
			/// When the button is in an off state.
			///
			OFF = 0,

			///
			/// When the button is in an on state.
			///
			ON = 1,

			///
			/// When the button is being hovered on.
			///
			HOVER = 2
		};

	public:
		///
		/// Image Constructor.
		///
		/// \param bounds Dimensions of the widget, relative to the panel.
		/// \param images Array of image names to load.
		///			images[0] is OFF state, images[1] is ON state and images[2] is mouse over (hover) state.
		///
		ToggleButton(const sl::Rect<int>& bounds, const std::array<std::string, 3>& images);

		///
		/// Destructor.
		///
		~ToggleButton() noexcept override;

		///
		/// Update the widget.
		///
		void update() override;

		///
		/// \brief Render the widget.
		///
		/// This should only contain code on rendering the widget.
		/// And don't forget to check for and draw the tooltip.
		///
		void render() override;

		///
		/// \brief Allows for button to recieve MousePressedEvents. Automatically registered with entt.
		///
		/// This is to be used with entt's dispatcher (sl::Locator::dispatcher).
		///
		/// \param e MousePressedEvent object.
		///
		void receivePress(const sl::MousePressedEvent& e);

		///
		/// \brief Allows for button to recieve MouseMovedEvents. Automatically registered with entt.
		///
		/// This is to be used with entt's dispatcher (sl::Locator::dispatcher).
		///
		/// \param e MouseMovedEvent object.
		///
		void recieveMoved(const sl::MouseMovedEvent& e);

		///
		/// Register callback function when button is pressed.
		///
		/// \param callback Return type void, no arguments. Function pointer.
		///
		void registerCallback(const std::function<void()>& callback);

	private:
		///
		/// Default constructor.
		/// Deleted.
		///
		ToggleButton() = delete;

	private:
		///
		/// Current state of the button.
		///
		ToggleButton::State m_state;

		///
		/// Images for each button state.
		///
		std::array<ALLEGRO_BITMAP*, 3> m_images;

		///
		/// Callback function.
		///
		std::function<void()> m_callback;
	};
}

#endif