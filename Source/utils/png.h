#pragma once

#include <SDL.h>

#include "miniwin/miniwin.h"
#include "storm/storm.h"
#include "storm/storm_sdl_rw.h"

#ifdef __cplusplus
extern "C" {
#endif

const int IMG_INIT_PNG = 0x00000002;

int IMG_Init(int flags);
void IMG_Quit(void);
int IMG_isPNG(SDL_RWops *src);
SDL_Surface *IMG_LoadPNG_RW(SDL_RWops *src);
int IMG_SavePNG(SDL_Surface *surface, const char *file);
int IMG_SavePNG_RW(SDL_Surface *surface, SDL_RWops *dst, int freedst);

inline SDL_Surface *IMG_LoadPNG(const char *file)
{
	SDL_RWops *src = SDL_RWFromFile(file, "rb");
	return IMG_LoadPNG_RW(src);
}

#ifdef __cplusplus
}
#endif

namespace devilution {

inline int InitPNG()
{
	return IMG_Init(IMG_INIT_PNG);
}

inline void QuitPNG()
{
	IMG_Quit();
}

inline SDL_Surface *LoadPNG(const char *file)
{
	SDL_RWops *rwops = SFileOpenRw(file);
	return IMG_LoadPNG_RW(rwops);
}

} // namespace devilution
