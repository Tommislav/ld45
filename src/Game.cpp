#include "Console.h"
#include "Writer.h"
#include "Game.h"
#include "Data.h"
#include <string>
#include <list>
using namespace std;

#define START_X 0
#define START_Y 4

const string startID = "GetBadgeBeg1";


int health = 10;
int soul = 10;
int ammo = 0;
bool isGameOver = false;

Writer mainWriter;
Writer optionsWriter;
Writer statusWriter;
Entry* currentEntry;

list<GameKey> currentGameKeys;

void SetCurrentEntry(string ID) {
	Entry* e = GetEntry(ID);
	if (e == NULL) {
		mainWriter.wrSetText("#cR#s0ERROR!!! #cDCould not fetch entry with ID #cR" + startID, 0, 2, CHAR_W, CHAR_H - 2);
		return;
	}
	e->FilterOptions(currentGameKeys);
	optionsWriter.wrSetText(e->GetOptionsLinkText(), START_X, 0, CHAR_W-START_X, CHAR_H);
	optionsWriter.timer.speed = -1;

	mainWriter.wrSetText(e->GetText(currentGameKeys), START_X, START_Y, CHAR_W - START_X, CHAR_H - START_Y);

	if (e->setKey != GameKey::None) { 
		currentGameKeys.push_back(e->setKey); 
	}
	currentEntry = e;
}

void AddGameKey(GameKey key) {
	currentGameKeys.push_back(key);
}

void RemoveGameKey(GameKey key) {
	currentGameKeys.remove(key);
}


void GameInit(ConsoleBuffer* buffer) {
	/*
	string valid = ValidateEntryLinks();
	mainWriter.wrSetText(valid, 0, 0, CHAR_W, CHAR_H);
	mainWriter.skipToEnd = true;
	mainWriter.wrTick(buffer, 100);
	return;
	*/
	statusWriter.timer.speed = -1;
	statusWriter.updateCursor = false;
	mainWriter.timer.fastSpeed = 2;
	mainWriter.timer.shouldDebug = true;
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

	if (mainWriter.fastForward) {
		int a = 0;
		a++;
	}

	bool dirty = mainWriter.wrTick(consoleBuffer, deltaTime);

	if (dirty) {
		string status = "¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ Health: " + to_string(health) + " ¤¤ Soul: " + to_string(soul) + " ¤¤ Ammo: " + to_string(ammo) + " ¤¤¤¤¤¤¤¤¤";
		//int len = status.size();
		//int extra = CHAR_W - len - 2;
		//for (int i = 0; i < extra; i++) { status += "¤"; }
		statusWriter.wrSetText(status, 0, 1, CHAR_W, 1);
		statusWriter.skipToEnd = true;
		statusWriter.wrTick(consoleBuffer, 100);
	}


	if (mainWriter.wrAtEnd()) {

		if (isGameOver) { return false; }

		// Game over soul
		if (soul <= 0) {
			isGameOver = true;
			SetCurrentEntry("GameOverSouls");
			return false;
		}

		// Game over health
		if (health <= 0) {
			isGameOver = true;
			SetCurrentEntry("GameOverHealth");
			return false;
		}

		// Continue

		if (!optionsWriter.wrAtEnd()) {
			optionsWriter.y = mainWriter.y + 3;
			optionsWriter.wrTick(consoleBuffer, deltaTime);
		}
		

		for (int i = 0; i < currentEntry->numOptionKeys; i++) {
			Key key = currentEntry->optionKeys[i];
			if (input.KeyReleased(key)) {
				Option opt = currentEntry->GetOpt(key);
				if (opt.valid) {
					if (opt.setTrigger != GameTrigger::None) {
						// SOMETHING HAPPENS!!!

						if (opt.setTrigger == GameTrigger::AddAmmo3SoulMinus1) {
							ammo += 3;
							soul -= 1;
						}

					}
					if (opt.setKey != GameKey::None) {
						currentGameKeys.push_back(opt.setKey);
					}

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
	GameEffect effect = (GameEffect)mainWriter.wrGetQueuedEffect();

	if (effect == GameEffect::Shoot) {
		ammo -= 1;
		if (ammo <= 0) { RemoveGameKey(GameKey::HasAmmo); }
		effect = GameEffect::ScreenShake;
	}
	if (effect == GameEffect::LoseHealth) {
		health -= 1;
		effect = GameEffect::ScreenShake;
	}
	if (effect == GameEffect::AddHealth3) {
		health += 3;
	}
	if (effect == GameEffect::LoseSoul) {
		soul -= 1;
		effect = GameEffect::ScreenShake;
	}
	if (effect == GameEffect::AddAmmo1) {
		ammo += 1;
		AddGameKey(GameKey::HasAmmo);
		AddGameKey(GameKey::HasGun);
	}
	if (effect == GameEffect::AddAmmo3) {
		ammo += 3;
		AddGameKey(GameKey::HasAmmo);
		AddGameKey(GameKey::HasGun);
	}
	if (effect == GameEffect::AddAmmo6) {
		ammo += 6;
		AddGameKey(GameKey::HasAmmo);
		AddGameKey(GameKey::HasGun);
	}

	return effect;
}


