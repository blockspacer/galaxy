///
/// TextureAtlas.hpp
/// starlight
///
/// Created by reworks on 29/11/2017.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef STARLIGHT_TEXTUREATLAS_HPP_
#define STARLIGHT_TEXTUREATLAS_HPP_

#include <unordered_map>
#include <allegro5/color.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_font.h>

#include "sl/math/Rect.hpp"
#include "sl/types/ResourceCache.hpp"
#include "sl/libs/MaxRectsBinPack/MaxRectsBinPack.hpp"

namespace sl
{
	class TextureAtlas final : public ResourceCache<Rect<int>>
	{
	public:
		///
		/// \brief Constructor.
		///
		/// Loads all textures and performs a maxrectbinpack algorithm on them, then frees textures.
		///
		/// \param powerOfTwoDimension The power of two to create the sprite sheet. E.g. 11 would result in an atas size of 2048x2048.
		///
		TextureAtlas(int powerOfTwoDimension);

		///
		/// Destructor. Frees texture atlas.
		///
		~TextureAtlas() override;

		///
		/// \brief Add a texture to the atlas.
		///
		/// Usually used when you generate a texture, such as a tilemap, that is not included in the assets.
		///
		/// \param ID ID of texture to add. Do not include extension.
		/// \param textureData Bitmap to add. WARNING! textureData WILL NOT BE FREED BY THIS FUNCTION!
		///
		void addTextureToAtlas(const std::string& ID, ALLEGRO_BITMAP* textureData);

		///
		/// \brief Add bitmap text to the atlas.
		///
		/// Usually used when you want to render text.
		///
		/// \param ID ID of texture to add. Do not include extension.
		/// \param text Text to draw.
		/// \param font Font to use.
		/// \param col Colour to use.
		///
		void addTextToAtlas(const std::string& ID, const std::string& text, ALLEGRO_FONT* font, ALLEGRO_COLOR col);

		///
		/// Add a new rectangle to the atlas, but it uses an existing texture.
		///
		/// \param ID ID of texture to add. Do not include extension.
		/// \param Rect x,y -> Upper Left, Upper Right on atlas, w,h -> Width and Height of area to cover.
		///
		void addRectToAtlas(const std::string& ID, const Rect<int>& rect);

		///
		/// Like al_draw_bitmap
		/// http://liballeg.org/a5docs/trunk/graphics.html#al_draw_bitmap
		///
		void al_draw_packed_bitmap(const std::string& texture, float dx, float dy, int flags);

		///
		/// Like al_draw_tinted_bitmap
		/// http://liballeg.org/a5docs/trunk/graphics.html#al_draw_tinted_bitmap
		///
		void al_draw_tinted_packed_bitmap(const std::string& texture, ALLEGRO_COLOR tint, float dx, float dy, int flags);

		///
		/// Like al_draw_tinted_scaled_rotated_bitmap
		/// http://liballeg.org/a5docs/trunk/graphics.html#al_draw_tinted_scaled_rotated_bitmap
		///
		void al_draw_tinted_scaled_rotated_packed_bitmap(const std::string& texture, ALLEGRO_COLOR tint, float cx, float cy, float dx, float dy, float xscale, float yscale, float angle, int flags);

		///
		/// Calls al_create_sub_bitmap() properly and returns the bitmap of the
		/// packed image. You can then draw and manipulate the bitmap yourself.
		///
		/// Be aware that you need to manually destroy the created bitmap
		/// when you are finished with al_destroy_bitmap()
		///
		/// http://liballeg.org/a5docs/trunk/graphics.html#al_create_sub_bitmap
		///
		ALLEGRO_BITMAP* al_create_packed_sub_bitmap(const std::string& texture);

		///
		/// Draws the internal full texture atlas to the screen. Useful for debugging.
		///
		/// \param x X coord.
		/// \param y Y coord.
		///
		void drawInternalTexture(float x = 0.0f, float y = 0.0f);

		///
		/// Clean up resources.
		///
		void clean() override;

	private:
		///
		/// Default Constructor.
		/// Deleted.
		///
		TextureAtlas() = delete;

	private:
		ALLEGRO_BITMAP* m_atlas;
		rbp::MaxRectsBinPack m_bin;
	};
}

#endif