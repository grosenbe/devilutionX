#pragma once

#include "DiabloUI/art.h"
#include "engine.h"

namespace devilution {

void UpdatePalette(Art *art, const SDL_Surface *output = nullptr);

void DrawArt(Point screenPosition, Art *art, int nFrame = 0, Uint16 srcW = 0, Uint16 srcH = 0);

void DrawArt(const Surface &out, Point position, Art *art, int nFrame = 0, Uint16 srcW = 0, Uint16 srcH = 0);

void DrawAnimatedArt(Art *art, Point screenPosition);

int GetAnimationFrame(int frames, int fps = 60);

} // namespace devilution
