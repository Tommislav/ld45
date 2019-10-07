
#include <SDL2/SDL.h>
#include <stdio.h>
#include "Game.h"
#include "Boilerplate.h"
#include "Fnt.h"
#include "Console.h"

#include <stdlib.h> // rand/srand
#include <thread> // time






void RenderConsoleBuffer(ConsoleBuffer* buffer, SDLContext* context, Sprite* sprite) {
	int w = buffer->width;
	int h = buffer->height;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int color = buffer->GetColor(x, y);
			char c = buffer->Get(x, y);
			sprite[color].Blit(CharToFnt(c), x * SPRITE_W, y * (SPRITE_H + 2), context);
		}
	}
}


void DrawCursor(bool blank, ConsoleBuffer* buffer, Sprite* sprite, SDLContext* context) {
	Fnt cursorSprite = blank ? Fnt::Blank : Fnt::Cursor;
	int x = buffer->cursor.x * SPRITE_W;
	int y = buffer->cursor.y * (SPRITE_H + 2);
	sprite->Blit(cursorSprite, x, y, context);
}


struct EffectPlayer {
	SDLContext* context;
	GameEffect effect;
	bool isPlaying;
	double timeLeft;
	int screenX;
	int screenY;
	EffectPlayer() :effect(GameEffect::None), isPlaying(false), timeLeft(0) {}
};

void StartEffect(EffectPlayer* ep, GameEffect effectToStart) {
	if (ep->isPlaying || effectToStart == GameEffect::None) { return; }
	ep->effect = effectToStart;
	ep->isPlaying = true;
	SDL_GetWindowPosition(ep->context->window, &(ep->screenX), &(ep->screenY));

	if (effectToStart == GameEffect::ScreenShake) {
		ep->timeLeft = 800;
	}
}

void PlayEffect(EffectPlayer* ep, double deltaTime) {
	if (ep->effect == GameEffect::None || !ep->isPlaying) { return; }
	ep->timeLeft -= deltaTime;

	if (ep->timeLeft <= 0) {
		SDL_SetWindowPosition(ep->context->window, ep->screenX, ep->screenY);
		ep->isPlaying = false;
		ep->effect = GameEffect::None;
		return;
	}

	int windowX = ep->screenX;
	int windowY = ep->screenY;
	windowX += rand() % 20 - 10;
	windowY += rand() % 20 - 10;
	SDL_SetWindowPosition(ep->context->window, windowX, windowY);
}





int main(int argc, char* argv[]) {
	
	srand(time(NULL)); // initialize rng

	SDLContext context = InitSDL("Ludum Dare 45", CHAR_W * SPRITE_W, CHAR_H * SPRITE_H);
	if (!context.success) {
		DestroySDLContext(context);
		SDL_Quit();
	}

	Sprite coloredSprites[6];
	for (int i = 0; i < 6; i++) {
		coloredSprites[i] = LoadSprite("Assets/font.bmp", &context);
	}
	coloredSprites[Color::def].SetColorModulation(180, 180, 180);
	coloredSprites[Color::red].SetColorModulation(255, 0, 0);
	coloredSprites[Color::green].SetColorModulation(140, 250, 140);
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
	EffectPlayer effectPlayer;
	effectPlayer.context = &context;
	Timer cursorBlinkTimer;
	cursorBlinkTimer.speed = 400;
	bool cursorBlinkSolidState = false;

	// draw one initial time before starting the loop
	SDL_RenderClear(context.renderer);
	SDL_RenderPresent(context.renderer);
	GameInit(&consoleBuffer);

	while(!quit) {
		while(SDL_PollEvent(&e)) {
			// Check for quit
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
				quit = true;
				break;
			}

			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
				for (int i = 0; i < mapFromLen; i++) {
					if (e.key.keysym.sym == mapFrom[i]) {
						inp.AddKey(Key(i), e.type == SDL_KEYUP ? KeyState::released : KeyState::down);
					}
					
				}
			}
		} // end of event polling

		double deltaTime = dt.Update();
		bool needsRedraw = GameTick(&consoleBuffer, inp, deltaTime);

		inp.ClearKeys();

		// start game effect if applicable!
		StartEffect(&effectPlayer, GetGameEffectToPlay());
		PlayEffect(&effectPlayer, deltaTime);
		

		// update blinking cursor state?
		bool cursorUpdate = cursorBlinkTimer.CountDown(deltaTime, false);
		if (cursorUpdate) { 
			cursorBlinkSolidState = !cursorBlinkSolidState; 
			needsRedraw = true;
		}

		if (!needsRedraw) {
			SDL_Delay(1);
			continue;
		}

		SDL_RenderClear(context.renderer);
		RenderConsoleBuffer(&consoleBuffer, &context, coloredSprites);
		DrawCursor(cursorBlinkSolidState, &consoleBuffer, &coloredSprites[Color::def], &context);

		SDL_RenderPresent(context.renderer);
	}

	// DESTROY
	for (int i = 0; i < 6; i++) {
		coloredSprites[i].Destroy();
	}

	DestroySDLContext(context);
	SDL_Quit();
	return 0;
}

