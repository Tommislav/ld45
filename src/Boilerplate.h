#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>

struct DeltaTime {
	Uint64 lastTime;
	double deltaTime;

	DeltaTime() : lastTime(0), deltaTime(0) {}
	double Update(){
		Uint64 now = SDL_GetPerformanceCounter();
		deltaTime = (double)((now - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency());
		lastTime = now;
		return deltaTime;
	}
};


SDL_Rect GetRect(int x, int y, int w, int h) {
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

SDL_Color GetColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_Color c;
	c.r = red;
	c.g = green;
	c.b = blue;
	return c;
}


struct SDLContext {
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool success;
};


struct Sprite {
	SDL_Texture* texture;
	SDL_Rect sourceRect;
	SDL_Rect targetRect;
	bool success;

	void Blit(int i, int x, int y, SDLContext* context) {
		if (!this->success) { return; }

		sourceRect.x = i % 16 * 8;
		sourceRect.y = i / 16 * 8;
		targetRect.x = x;
		targetRect.y = y;
		SDL_RenderCopy(context->renderer, texture, &sourceRect, &targetRect);
	}
	void Destroy() {
		if (texture != nullptr) { SDL_DestroyTexture(texture); }
		texture = nullptr;
	}
	void SetColorModulation(Uint8 r, Uint8 g, Uint8 b) {
		SDL_SetTextureColorMod(texture, r, g, b);
	}
};

Sprite LoadSprite(const char* bitmapPath, SDLContext* context) {
	Sprite sprite;
	sprite.texture = NULL;

	SDL_Surface* surface = nullptr;
	surface = SDL_LoadBMP(bitmapPath);
	if (surface == nullptr) { 
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error loading bitmap", SDL_GetError(), NULL);
		return sprite;
	}

	// make transparent
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

	sprite.texture = SDL_CreateTextureFromSurface(context->renderer, surface);
	SDL_FreeSurface(surface);

	if (sprite.texture == nullptr) { 
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error create texture", SDL_GetError(), NULL);
		return sprite; 
	}

	sprite.targetRect = GetRect(0, 0, 8, 8);
	sprite.sourceRect = GetRect(0, 0, 8, 8);
	sprite.success = true;
	return sprite;
}


SDLContext InitSDL(const char* title, int w, int h) {
	SDLContext context;
	context.window = nullptr;
	context.renderer = nullptr;
	context.success = false;


	// init sdl
	if (SDL_Init(SDL_INIT_VIDEO) != 0) { return context; }

	// create window
	context.window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if (context.window == nullptr) { return context; }

	// create renderer
	context.renderer = SDL_CreateRenderer(context.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (context.renderer == nullptr) { return context; }

	context.success = true;
	return context;
}

void DestroySDLContext(SDLContext context) {
	if (context.renderer != nullptr) { SDL_DestroyRenderer(context.renderer); }
	if (context.window != nullptr) { SDL_DestroyWindow(context.window); }
}
