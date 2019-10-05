#pragma once

enum Color { 
	def = 0, 
	red = 1, 
	blue = 2, 
	green = 3, 
	white = 4, 
	purple = 5
};

struct ConsoleBuffer {
	char buffer[100 * 60];
	int colors[100 * 60];
	int width;
	int height;

	void Init(int width, int height) {
		Clear();
		this->width = width;
		this->height = height;
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




enum Key {
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
	pressed = 1,
	down = 2,
	released = 3
};

struct Input {
	int num;
	Key keys[10];
	KeyState states[10];

	bool CheckKey(Key key, KeyState state) {
		if (num == 0) { return false; }
		if (num > 10) { num = 10; }
		for (int i = 0; i < num; i++) {
			if (keys[i] == key) {
				if (states[i] == state) { return true; }
				if (state == KeyState::down) {
					if (states[i] == KeyState::pressed) { return true; }
				}
				return false;
			}
		}
		return false;
	}

	bool KeyReleased(Key key) { return CheckKey(key, KeyState::released); }
	bool KeyDown(Key key) { return CheckKey(key, KeyState::down); }
	bool KeyPressed(Key key) { return CheckKey(key, KeyState::pressed); }
};


struct Timer {
	double speed;
	double fastSpeed;
	double counter;
	double additionalPause;
	bool onHold;

	Timer() :counter(0), speed(30), fastSpeed(5), additionalPause(0), onHold(false) {}

	bool CountDown(double deltaTime, bool fastForward) {
		if (onHold) { return false; }
		if (!fastForward && additionalPause > 0) { additionalPause -= deltaTime; return false; }
		if (counter > 0) {
			counter -= deltaTime;
		}
		if (counter <= 0) {
			counter = fastForward ? fastSpeed : speed;
			return true;
		}
		return false;
	}
};

