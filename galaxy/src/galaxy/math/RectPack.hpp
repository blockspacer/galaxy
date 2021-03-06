///
/// RectPack.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_RECTPACK_HPP_
#define GALAXY_RECTPACK_HPP_

#include <vector>
#include <optional>

#include <protostar/shapes/Rect.hpp>

///
/// Core namespace.
///
namespace galaxy
{
	///
	///	Rectangle 2D bin packing class.
	///
	class RectPack final
	{
	public:
		///
		/// Default constructor.
		///
		RectPack() noexcept;
		
		///
		/// Default destructor.
		///
		~RectPack() noexcept = default;

		///
		/// Set starting width and height of rectangle.
		///
		/// Generally should be a power of 2.
		///
		/// \param width Width of the master rectangle.
		/// \param height Height of the master rectangle.
		///
		void init(const int width, const int height);

		///
		/// Pack a rectangle into the master rectangle.
		///
		/// \param width Width of the rectangle to pack.
		/// \param height Height of the rectangle to pack.
		///
		/// \return Returns the location of the packed rectangle on the master rectangle.
		///			Otherwise, returns a std::nullopt.
		///
		std::optional<protostar::Rect<int>> pack(const int width, const int height) noexcept;

		///
		/// Get total width.
		///
		const int getWidth() const noexcept;

		///
		/// Get total height.
		///
		const int getHeight() const noexcept;

	private:
		///
		/// The starting width of the rectangle.
		///
		int m_width;

		///
		/// The starting width of the rectangle.
		///
		int m_height;

		///
		/// Free space in master rectangle.
		///
		std::vector<protostar::Rect<int>> m_freeRects;
	};
}

#endif