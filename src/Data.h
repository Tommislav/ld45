#pragma once

#include "Console.h"
#include <string>
#include <vector>
#include <list>
using namespace std;

enum class GameTrigger {
	None,
	LoseHealth,
	LoseAmmo,
	AddAmmo1,
	AddAmmo3,
	LoseHealthAndAmmo,
	LoseSoul,

};

enum class GameKey {
	None,
	Invalid,
	Test,
	Test2,
	HasGun,
	HasBadge,
	HasFriend,
	HasLocationOfDaughter,

};

struct Option {
	Key trigger;
	string text;
	string link;
	string triggerText;
	GameKey showIfKey;
	GameKey hideIfKey;
	GameTrigger setTrigger;
	GameKey setKey;
	bool valid;

	Option() {}
	Option(string text, string link) :trigger(Key::none), text(text), link(link), triggerText(""), showIfKey(GameKey::None), hideIfKey(GameKey::None), setTrigger(GameTrigger::None), setKey(GameKey::None), valid(true) {}
	Option(string text, string link, GameKey showIfKey, GameKey hideIfKey, GameKey setKey, GameTrigger trigger) :trigger(Key::none), text(text), link(link), triggerText(""), showIfKey(showIfKey), hideIfKey(hideIfKey), setTrigger(trigger), setKey(setKey), valid(true) {}

	Option ShowIfKey(GameKey key) {
		showIfKey = key;
		return *this;
	}
	Option HideIfKey(GameKey key) {
		hideIfKey = key;
		return *this;
	}
	Option TriggerKey(GameKey key) {
		setKey = key;
		return *this;
	}
};

struct OptionalText {
	string text;
	GameKey showIfKey;
	GameKey hideIfKey;
	OptionalText() {}
	OptionalText(string text) : text(text), showIfKey(GameKey::None), hideIfKey(GameKey::None) {}
	OptionalText ShowIfKey(GameKey key) {
		showIfKey = key;
		return *this;
	}
	OptionalText HideIfKey(GameKey key) {
		hideIfKey = key;
		return *this;
	}
};

struct Entry {
	string ID;
	string text;
	vector<OptionalText> optionalTexts;
	vector<Option> options;
	GameKey setKey;
	Entry() {}
	Entry(string ID, string text, GameKey setKey=GameKey::None) : ID(ID), text(text), setKey(setKey) {}

	Entry AddOptions(Option o1) {
		options.push_back(o1);
		return *this;
	}
	Entry AddOptions(Option o1, Option o2) {
		options.push_back(o1);
		options.push_back(o2);
		return *this;
	}
	Entry AddOptions(Option o1, Option o2, Option o3) {
		options.push_back(o1);
		options.push_back(o2);
		options.push_back(o3);
		return *this;
	}
	Entry AddOptions(Option o1, Option o2, Option o3, Option o4) {
		options.push_back(o1);
		options.push_back(o2);
		options.push_back(o3);
		options.push_back(o4);
		return *this;
	}
	Entry AddOptions(Option o1, Option o2, Option o3, Option o4, Option o5) {
		options.push_back(o1);
		options.push_back(o2);
		options.push_back(o3);
		options.push_back(o4);
		options.push_back(o5);
		return *this;
	}
	Entry AddText(OptionalText extraText) {
		optionalTexts.push_back(extraText);
		return *this;
	}
	Entry TriggerKey(GameKey key) {
		setKey = key;
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

	// Haha, I put them inside the Entry struct by mistake
	// and now I use them in Game.cpp X-D
	// I'm a bum
	int numOptionKeys = 5;
	Key optionKeys[5] = {
		Key::key1,
		Key::key2,
		Key::key3,
		Key::key4,
		Key::key5
	};

	string optionLabels[5] = {
		"#cP[1]#cW ",
		"#cP[2]#cW ",
		"#cP[3]#cW ",
		"#cP[4]#cW ",
		"#cP[5]#cW "
	};

	// All options have a showIfKey and hideIfKey.
	// We need to verify those criterias and 
	void FilterOptions(list<GameKey> currentGameKeys) {
		int cnt = 0;
		for (Option &opt : options) {
			
			bool showFlagIsValid = true;
			bool hideFlagIsValid = true;

			if (opt.showIfKey != GameKey::None) {
				showFlagIsValid = false;
			}

			for (GameKey gameKey : currentGameKeys) {
				if (gameKey == opt.showIfKey) { showFlagIsValid = true; }
				if (gameKey == opt.hideIfKey) { hideFlagIsValid = false; }
			}

			opt.valid = showFlagIsValid && hideFlagIsValid;

			if (opt.valid) {
				opt.trigger = optionKeys[cnt];
				opt.triggerText = optionLabels[cnt];
				cnt++;
			}
		}
	}

	string GetText(list<GameKey> currentGameKeys) {
		if (optionalTexts.size() == 0) {
			return text;
		}

		string s = text;
		for (OptionalText& extra : optionalTexts) {
			bool showFlagIsValid = true;
			bool hideFlagIsValid = true;

			if (extra.showIfKey != GameKey::None) {
				showFlagIsValid = false;
			}

			for (GameKey gameKey : currentGameKeys) {
				if (gameKey == extra.showIfKey) { showFlagIsValid = true; }
				if (gameKey == extra.hideIfKey) { hideFlagIsValid = false; }
			}

			if (showFlagIsValid && hideFlagIsValid) {
				s += extra.text;
			}
		}
		return s;
	}

	string GetOptionsLinkText() {
		string s = "";
		for (Option &opt : options) {
			if (opt.valid) {
				s += opt.triggerText + opt.text + "#n ";
			}
		}
		return s;
	}
};

Entry* GetEntry(string ID);