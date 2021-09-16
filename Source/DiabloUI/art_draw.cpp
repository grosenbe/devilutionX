#include "DiabloUI/art_draw.h"

#include "DiabloUI/diabloui.h"
#include "utils/display.h"
#include "utils/sdl_compat.h"
#include "palette.h"

namespace devilution {

void UpdatePalette(Art *art, const SDL_Surface *output)
{
	if (art->surface->format->BitsPerPixel != 8)
		return;

	if (art->palette_version == pal_surface_palette_version)
		return;

	if (output == nullptr || output->format->BitsPerPixel != 8)
		output = PalSurface;

	if (SDLC_SetSurfaceColors(art->surface.get(), output->format->palette) <= -1)
		ErrSdl();

	art->palette_version = pal_surface_palette_version;
}

void DrawArt(Point screenPosition, Art *art, int nFrame, Uint16 srcW, Uint16 srcH)
{
	if (screenPosition.y >= gnScreenHeight || screenPosition.x >= gnScreenWidth || art->surface == nullptr)
		return;

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = nFrame * art->h();
	srcRect.w = art->w();
	srcRect.h = art->h();

	ScaleOutputRect(&srcRect);

	if (srcW != 0 && srcW < srcRect.w)
		srcRect.w = srcW;
	if (srcH != 0 && srcH < srcRect.h)
		srcRect.h = srcH;
	SDL_Rect dstRect = MakeSdlRect(screenPosition.x, screenPosition.y, srcRect.w, srcRect.h);
	ScaleOutputRect(&dstRect);

	UpdatePalette(art);

	if (SDL_BlitSurface(art->surface.get(), &srcRect, DiabloUiSurface(), &dstRect) < 0)
		ErrSdl();
}

void DrawArt(const Surface &out, Point screenPosition, Art *art, int nFrame, Uint16 srcW, Uint16 srcH)
{
	if (screenPosition.y >= gnScreenHeight || screenPosition.x >= gnScreenWidth || art->surface == nullptr)
		return;

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = nFrame * art->h();
	srcRect.w = art->w();
	srcRect.h = art->h();

	if (srcW != 0 && srcW < srcRect.w)
		srcRect.w = srcW;
	if (srcH != 0 && srcH < srcRect.h)
		srcRect.h = srcH;
	out.Clip(&srcRect, &screenPosition);
	SDL_Rect dstRect { screenPosition.x + out.region.x, screenPosition.y + out.region.y, 0, 0 };

	UpdatePalette(art, out.surface);

	if (SDL_BlitSurface(art->surface.get(), &srcRect, out.surface, &dstRect) < 0)
		ErrSdl();
}

void DrawAnimatedArt(Art *art, Point screenPosition)
{
	DrawArt(screenPosition, art, GetAnimationFrame(art->frames));
}

int GetAnimationFrame(int frames, int fps)
{
	int frame = (SDL_GetTicks() / fps) % frames;

	return frame > frames ? 0 : frame;
}

} // namespace devilution
