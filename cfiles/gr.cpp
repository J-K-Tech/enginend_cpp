#include<enginend.h>
bool accelerated=false;


Window::Window(int width, int height, const char* title) {INITWINDOW}
Window::~Window() {CLOSEWINDOW}

void Window::update() {
	if (pressed(SDL_SCANCODE_LALT) && pressed(SDL_SCANCODE_F4)) running = false;
	#ifdef __AVX2__
	keys.justchanged = _mm256_setzero_si256();
	#elif defined(__SSE__)
	keys.justchanged[0] = _mm_setzero_si128();
	keys.justchanged[1] = _mm_setzero_si128();
	#elif defined(__MMX__)
	keys.justchanged[0] = _mm_setzero_si64();
	keys.justchanged[1] = _mm_setzero_si64();
	keys.justchanged[2] = _mm_setzero_si64();
	keys.justchanged[3] = _mm_setzero_si64();
	#else
	memset(keys.justchanged, 0, 32);
	#endif
	INITDRAW
	for (int i = 0; i < draws; i++) {
		drawfuncs[i](objects[i], this);
	}
	drawfuncs = nullptr;
	objects = nullptr;
	draws = 0;
	ENDDRAW
}
color clearcolor={254,0,0,255};
void Window::bind(void (*func)(Object*,Window*), Object* obj) {
	drawfuncs = (void(**)(Object*,Window*))realloc(drawfuncs, sizeof(void(*)(Object*)) * (draws + 1));
	drawfuncs[draws] = func;
	objects = (Object**)realloc(objects, sizeof(Object*) * (draws + 1));
	objects[draws] = obj;
	draws++;
}
void World::render(Window* window) {
}