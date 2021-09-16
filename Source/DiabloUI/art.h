#pragma once

#include <cstdint>

#include "utils/sdl_ptrs.h"

namespace devilution {

struct Art {
	SDLSurfaceUniquePtr surface;
	int frames;
	int logical_width;
	int frame_height;
	unsigned int palette_version;

	Art()
	{
		surface = nullptr;
		frames = 1;
		logical_width = 0;
		frame_height = 0; // logical frame height (before scaling)
		palette_version = 0;
	}

	int w() const
	{
		return logical_width;
	}

	int h() const
	{
		return frame_height;
	}

	void Unload()
	{
		surface = nullptr;
	}

	~Art()
	{
		if (surface != nullptr)
			Unload();
	}
};

void LoadArt(const char *pszFile, Art *art, int frames = 1, SDL_Color *pPalette = nullptr, const std::array<uint8_t, 256> *colorMapping = nullptr);
void LoadMaskedArt(const char *pszFile, Art *art, int frames = 1, int mask = 250, const std::array<uint8_t, 256> *colorMapping = nullptr);
void LoadArt(Art *art, const std::uint8_t *artData, int w, int h, int frames = 1);

} // namespace devilution
