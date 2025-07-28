/*
likely support roadmap:

major desktop platforms
 software	| hardware
sdl2 -> fb0 -> uefi -> bios -> gl -> vulkan -> metal -> misc
mobile platforms
android opengl -> android vulkan -> metal -> misc
console platforms
xbox -> ps1 -> ps2 -> xbox360 -> ps3 -> ps4 -> xboxone -> xbos series ->
nintendo wii -> nintendo wiiu -> nintendo 64 -> nintendo 3ds -> nintendo switch ->
sega saturn -> sega dreamcast
embedded systems
raspberry pi

other systems will be added by the community with a basic guide on how to port the engine, its gonna be easy since
the code is "plug and play"

*/

#ifdef SDL2
#include "sdl2.h"
#elif defined(SDL1)
#include "sdl.h"
#elif defined(SDL3)
#include "sdl3.h"s
#elif defined(FB0)
#include "fb0.h"
#elif defined(UEFI)
#include "uefi.h"
#elif defined(BIOS)
#include "bios.h"
#endif