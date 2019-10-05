#pragma once

#include "Console.h"
#include <string>
#include <vector>
using namespace std;

enum class GameTrigger {
	None = 0,
	LoseHealth = 1,
	LoseAmmo = 2,
};

enum class GameKey {
	None = 0,
	HasGun = 1,
};

struct Option {
	Key trigger;
	string text;
	string link;
	GameKey showIfKey;
	GameKey hideIfKey;
	GameTrigger setTrigger;
	GameKey setKey;
	bool valid;

	Option() {}
	Option(string text, string link) :trigger(Key::none), text(text), link(link), showIfKey(GameKey::None), hideIfKey(GameKey::None), setTrigger(GameTrigger::None), setKey(GameKey::None), valid(true) {}
};

struct Entry {
	string ID;
	string text;
	vector<Option> options;
	GameKey setKey;
	Entry() {}
	Entry(string ID, string text) : ID(ID), text(text), options(NULL), setKey(GameKey::None) {}

	Entry AddOptions(Option o1) {
		options.push_back(o1);
		return *this;
	}
	Entry AddOptions(Option o1, Option o2) {
		options.push_back(o1);
		options.push_back(o2);
		return *this;
	}

	Option GetOpt(Key key) {
		for (Option opt : options) {
			if (opt.trigger == key) {
				return opt;
			}
		}
		Option invalid;
		invalid.valid = false;
		return invalid;
	}

	Key optionKeys[5] = {
		Key::key1,
		Key::key2,
		Key::key3,
		Key::key4,
		Key::key5
	};

	string optionLabels[5] = {
		"[1] ",
		"[2] ",
		"[3] ",
		"[4] ",
		"[5] "
	};

	// All options have a showIfKey and hideIfKey.
	// We need to verify those criterias and 
	void FilterOptions(GameKey currentGameKeys[]) {
		int numKeysToCheck = currentGameKeys == NULL ? 0 : (sizeof(currentGameKeys) / sizeof(*currentGameKeys));
		
		
		int cnt = 0;
		for (Option &opt : options) {
			
			bool showFlagIsValid = true;
			bool hideFlagIsValid = true;

			if (opt.showIfKey != GameKey::None) {
				showFlagIsValid = false;
			}

			for (int i = 0; i < numKeysToCheck; i++) {
				if (currentGameKeys[i] == opt.showIfKey) { showFlagIsValid = true; }
				if (currentGameKeys[i] == opt.hideIfKey) { hideFlagIsValid = false; }
			}

			opt.valid = showFlagIsValid && hideFlagIsValid;
			if (opt.valid) {
				opt.trigger = optionKeys[cnt];
				cnt++;
			}
		}
	}
};

Entry* GetEntry(string ID);