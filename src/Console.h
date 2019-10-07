#pragma once

#include <stdio.h>

enum Color { 
	def = 0, 
	red = 1, 
	blue = 2, 
	green = 3, 
	white = 4, 
	purple = 5
};

struct CCursor {
	int x;
	int y;
};

struct ConsoleBuffer {
	char buffer[100 * 60];
	int colors[100 * 60];
	int width;
	int height;
	CCursor cursor;

	void Init(int width, int height) {
		Clear();
		this->width = width;
		this->height = height;
		this->cursor.x = 0;
		this->cursor.y = 0;
	}

	void SetCursor(int x, int y) {
		cursor.x = x;
		cursor.y = y;
	}

	void Set(char val, int x, int y, Color col) {
		if (x < 0 || x >= width || y < 0 || y >= height) { return; }
		int i = y * width + x;
		buffer[i] = val;
		colors[i] = col;
	}

	char Get(int x, int y) {
		if (x < 0 || x >= width || y < 0 || y >= height) { return 0; }
		return buffer[y * width + x];
	}

	int GetColor(int x, int y) {
		if (x < 0 || x >= width || y < 0 || y >= height) { return 0; }
		return colors[y * width + x];
	}

	void Clear() {
		int len = 100 * 60;
		for (int i = 0; i < len; i++) {
			buffer[i] = 0;
			colors[i] = 0;
		}
	}
	
};




enum class Key {
	none = 0,
	next = 1,
	ffwd = 2,
	key1 = 3,
	key2 = 4,
	key3 = 5,
	key4 = 6,
	key5 = 7
};

enum KeyState {
	invalid = 0,
	down = 1,
	released = 2
};

struct Input {
	Key keysDown[10];
	Key keysUp[10];
	const int num;
	

	Input() : num(10) {
		for (int i = 0; i < num; i++) {
			keysUp[i] = Key::none;
			keysDown[i] = Key::none;
		}
	}

	void AddKey(Key key, KeyState state) {
		if (state == KeyState::down) {
			for (int i = 0; i < num; i++) {
				if (keysDown[i] == Key::none) {
					keysDown[i] = key;
					return;
				}
			}
		}
		else if (state == KeyState::released) {
			bool rSet = false;
			for (int i = 0; i < num; i++) {
				if (keysDown[i] == key) {
					keysDown[i] = Key::none;
				}
				if (!rSet && keysUp[i] == Key::none) {
					rSet = true;
					keysUp[i] = key;
				}
			}
		}
	}

	void ClearKeys(bool forceDownedKeys=false) {
		for (int i = 0; i < num; i++) {
			keysUp[i] = Key::none;
			if (forceDownedKeys) {
				keysDown[i] = Key::none;
			}
		}
	}

	bool CheckKey(Key key, KeyState state) {
		for (int i = 0; i < num; i++) {
			if (state == KeyState::down && keysDown[i] == key) { return true; }
			if (state == KeyState::released && keysUp[i] == key) { return true; }
		}
		return false;
	}

	bool KeyReleased(Key key) { return CheckKey(key, KeyState::released); }
	bool KeyDown(Key key) { return CheckKey(key, KeyState::down); }
};


struct Timer {
	bool shouldDebug;
	double speed;
	double fastSpeed;
	double counter;
	double additionalPause;
	bool onHold;

	Timer() :counter(0), speed(70), fastSpeed(0), additionalPause(0), onHold(false) {}

	bool CountDown(double deltaTime, bool fastForward) {
		
		if (onHold) { return false; }
		if (!fastForward && additionalPause > 0) { additionalPause -= deltaTime; return false; }
		if (counter > 0) {
			counter -= deltaTime;
		}

		if (shouldDebug) {
			printf("deltaTime: %f, counter: %f\n", deltaTime, counter);
		}

		if (counter <= 0) {
			counter = fastForward ? fastSpeed : speed;
			return true;
		}
		return false;
	}
};

