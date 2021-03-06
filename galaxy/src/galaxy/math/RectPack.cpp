///
/// RectPack.cpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#include "RectPack.hpp"

///
/// Core namespace.
///
namespace galaxy
{
	RectPack::RectPack() noexcept
		:m_width(0), m_height(0)
	{
	}

	void RectPack::init(const int width, const int height)
	{
		m_width = width;
		m_height = height;
		
		m_freeRects.emplace_back(0, 0, m_width, m_height);
	}

	std::optional<protostar::Rect<int>> RectPack::pack(const int width, const int height) noexcept
	{
		// Result.
		std::optional<protostar::Rect<int>> result = std::nullopt;

		// Go over each space in the rectangle, in reverse order (i.e. smallest -> largest).
		for (auto rit = m_freeRects.rbegin(); rit != m_freeRects.rend();/* ++rit*/)
		{
			auto& space = *rit;

			// Check if rect can fit into space.
			if (width <= space.m_width && height <= space.m_height)
			{
				// Make the packed area rectangle.
				result = std::make_optional<protostar::Rect<int>>(space.m_x, space.m_y, space.m_width, space.m_height);

				// Check to see if shape fills completely.
				if (width == space.m_width && height == space.m_height)
				{
					// Destroy since not free space anymore.
					std::advance(rit, 1);
					m_freeRects.erase(rit.base());
				}
				else if (width == space.m_width)
				{
					// If just width fits, shrink new space.
					space.m_y += height;
					space.m_height -= height;
				}
				else if (height == space.m_height)
				{
					// Same as width, for height.
					space.m_x += width;
					space.m_width -= width;
				}
				else
				{
					// Otherwise, split up existing space.
					m_freeRects.emplace_back(space.m_x + width, space.m_y, space.m_width - width, height);
					space.m_y += height;
					space.m_height -= height;
				}
			}
			else
			{
				// Try next space.
				++rit;
			}
		}

		return result;
	}

	const int RectPack::getWidth() const noexcept
	{
		return m_width;
	}

	const int RectPack::getHeight() const noexcept
	{
		return m_height;
	}
}