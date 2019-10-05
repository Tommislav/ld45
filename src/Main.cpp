
#include <SDL2/SDL.h>
#include <stdio.h>
#include "Game.h"
#include "Boilerplate.h"
#include "Fnt.h"
#include "Console.h"




#define CHAR_W 100
#define CHAR_H 60
#define SPRITE_W 8
#define SPRITE_H 8

void RenderConsoleBuffer(ConsoleBuffer* buffer, SDLContext* context, Sprite* sprite) {
	int w = buffer->width;
	int h = buffer->height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int color = buffer->GetColor(x, y);
			char c = buffer->Get(x, y);
			sprite[color].Blit(CharToFnt(c), x * SPRITE_W, y * SPRITE_H, context);
		}
	}
}


int main(int argc, char* argv[]) {
	
	SDLContext context = InitSDL("Goodbye World", CHAR_W * SPRITE_W, CHAR_H * SPRITE_H);
	if (!context.success) {
		DestroySDLContext(context);
		SDL_Quit();
	}
	printf("InintSDL success");

	Sprite coloredSprites[6];
	for (int i = 0; i < 6; i++) {
		coloredSprites[i] = LoadSprite("Assets/font.bmp", &context);
	}
	coloredSprites[Color::def].SetColorModulation(123, 123, 123);
	coloredSprites[Color::red].SetColorModulation(255, 0, 0);
	coloredSprites[Color::green].SetColorModulation(0, 255, 0);
	coloredSprites[Color::blue].SetColorModulation(0, 0, 255);
	coloredSprites[Color::white].SetColorModulation(255, 255, 255);
	coloredSprites[Color::purple].SetColorModulation(255, 0, 255);

	int mapFromLen = 10;
	SDL_Keycode mapFrom[] = {
		SDLK_ESCAPE, // none
		SDLK_RETURN, // next
		SDLK_SPACE, // ffwd
		SDLK_1,
		SDLK_2,
		SDLK_3,
		SDLK_4,
		SDLK_5,
		SDLK_6,
		SDLK_7
	};

	SDL_Event e;
	bool quit = false;
	ConsoleBuffer consoleBuffer;
	consoleBuffer.Init(CHAR_W, CHAR_H);
	Input inp;
	DeltaTime dt;

	// draw one initial time before starting the loop
	SDL_RenderClear(context.renderer);
	SDL_RenderPresent(context.renderer);

	while(!quit) {
		while(SDL_PollEvent(&e)) {
			// Check for quit
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
				quit = true;
				break;
			}

			inp.num = 0;
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
				for (int i = 0; i < mapFromLen; i++) {
					if (e.key.keysym.sym == mapFrom[i]) {
						inp.keys[inp.num] = (Key)i;
						inp.states[inp.num] = e.type == SDL_KEYUP ? KeyState::released : KeyState::down;
						inp.num++;
						if (inp.num >= 10) { inp.num = 9; } // prevent overflow
					}
					
				}
			}
		} // end of event polling

		double deltaTime = dt.Update();
		GameTick(&consoleBuffer, inp, deltaTime);
		if (!GameNeedsRedraw()) {
			continue;
		}

		SDL_RenderClear(context.renderer);
		RenderConsoleBuffer(&consoleBuffer, &context, coloredSprites);
		
		/*
		ConsoleBuffer buffer;
		buffer.Init(CHAR_W, CHAR_H);
		const char* str = "Hej din gamla galosh HEJ HEJ STORA BOKSTAVER";
		int len = SDL_strlen(str);
		for (int i = 0; i < len; i++) {
			buffer.Set(CharToFnt(str[i]), i + 3, 9, Color::def);
		}
		buffer.Set(Fnt::Heart, 10, 10, Color::red);

		RenderConsoleBuffer(&buffer, &context, coloredSprites);

		Sprite sprite = coloredSprites[Color::green];
		sprite.Blit(Fnt::Heart, 0, 0, &context);
		sprite.Blit(1, 8, 0, &context);
		sprite.Blit(Fnt::A, 16, 0, &context);
		sprite.Blit(Fnt::a, 24, 0, &context);
		sprite.Blit(Fnt::Filled, 32, 0, &context);
		sprite.Blit(Fnt::Dissolve1, 40, 0, &context);
		sprite.Blit(Fnt::Dissolve2, 48, 0, &context);
		sprite.Blit(Fnt::Dissolve3, 56, 0, &context);

		sprite.Blit(Fnt::Frame1Vert, 8*5,8*5, &context);
		sprite.Blit(Fnt::Frame1Vert, 8*7,8*5, &context);
		sprite.Blit(Fnt::Frame1Horiz, 8*6,8*4, &context);
		sprite.Blit(Fnt::Frame1Horiz, 8*6,8*6, &context);
		sprite.Blit(Fnt::Frame1TL, 8*5,8*4, &context);
		sprite.Blit(Fnt::Frame1TR, 8*5,8*6, &context);
		sprite.Blit(Fnt::Frame1BL, 8*7,8*4, &context);
		sprite.Blit(Fnt::Frame1BR, 8*7,8*6, &context);
		sprite.Blit(Fnt::Heart, 8*6, 8*5, &context);
		*/
		SDL_RenderPresent(context.renderer);
	}

	DestroySDLContext(context);
	SDL_Quit();
	return 0;
}

