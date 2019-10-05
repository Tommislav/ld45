#pragma once
#include "Console.h"
#include <string>



#define CHAR_W 80
#define CHAR_H 55
#define SPRITE_W 8
#define SPRITE_H 8

enum class GameEffect {
	None = 0,
	ScreenShake = 1
};

void GameInit(ConsoleBuffer* buffer);
bool GameTick(ConsoleBuffer* consoleBuffer, Input input, double deltaTime);
GameEffect GetGameEffectToPlay();

