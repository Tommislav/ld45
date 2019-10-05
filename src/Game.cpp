#include "Console.h"
#include "Writer.h"
#include "Game.h"
#include "Data.h"
#include <string>
using namespace std;

#define START_X 0
#define START_Y 2

const string startID = "Start";

Writer mainWriter;
Writer optionsWriter;
Entry* currentEntry;



void SetCurrentEntry(string ID) {
	Entry* e = GetEntry(ID);
	if (e == NULL) {
		mainWriter.wrSetText("#cR#s0ERROR!!! #cDCould not fetch entry with ID #cR" + startID, 0, 2, CHAR_W, CHAR_H - 2);
		return;
	}
	e->FilterOptions(NULL);
	optionsWriter.wrSetText(e->GetOptionsLinkText(), START_X, 0, CHAR_W-START_X, CHAR_H);
	optionsWriter.timer.speed = -1;

	mainWriter.wrSetText(e->text, START_X, START_Y, CHAR_W - START_X, CHAR_H - START_Y);
	currentEntry = e;
}


void GameInit(ConsoleBuffer* buffer) {
	buffer->SetCursor(START_X, START_Y);
	SetCurrentEntry(startID);
}

Key optionKeys[5] = {
		Key::key1,
		Key::key2,
		Key::key3,
		Key::key4,
		Key::key5
};

bool GameTick(ConsoleBuffer* consoleBuffer, Input input, double deltaTime) {
	mainWriter.fastForward = input.KeyDown(Key::ffwd);
	bool dirty = mainWriter.wrTick(consoleBuffer, deltaTime);


	if (mainWriter.wrAtEnd()) {
		if (!optionsWriter.wrAtEnd()) {
			optionsWriter.y = mainWriter.y + 3;
			optionsWriter.wrTick(consoleBuffer, deltaTime);
		}
		

		for (int i = 0; i < currentEntry->numOptionKeys; i++) {
			Key key = currentEntry->optionKeys[i];
			if (input.KeyReleased(key)) {
				Option opt = currentEntry->GetOpt(key);
				if (opt.valid) {
					consoleBuffer->Clear();
					consoleBuffer->SetCursor(START_X, START_Y);
					SetCurrentEntry(opt.link);
				}
			}
		}
	}
	


	return dirty;
}

GameEffect GetGameEffectToPlay() {
	return (GameEffect)mainWriter.wrGetQueuedEffect();
}


