#pragma once
#include "Console.h"

void GameInit();
void GameTick(ConsoleBuffer* consoleBuffer, Input input, double deltaTime);
bool GameNeedsRedraw();