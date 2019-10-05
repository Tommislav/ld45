#pragma once
/*
//#include <string>
#include <stdlib.h> // rand/srand
#include <time.h> // time

//using namespace std;

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

	Timer():counter(0), speed(30), fastSpeed(5), additionalPause(0), onHold(false) {}

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
*/

/*
int IntFromChar(char c) {
	char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for (int i=0; i<10; i++) {
		if (nums[i] == c) return i;
	}
	return -1;
}
*/





/*
// read string from file
#include <fstream>

std::string readFromFile(std::string fileName) {
	std::ifstream t(fileName);
	t.seekg(0, std::ios::end);
	size_t size = t.tellg();
	std::string buffer(size, ' ');
	t.seekg(0);
	t.read(&buffer[0], size);
	t.close();
	return buffer;
}
*/

//#endif
