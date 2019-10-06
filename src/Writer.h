

#include <iostream>
#include <string>
#include "Console.h"

using namespace std;

struct Writer {
	bool fastForward = false;
	bool skipToEnd = false;
	bool updateCursor = true;

	string text;
	int pos;
	int len;
	Timer timer;
	int startX;
	int startY;
	int x;
	int y;
	int w;
	int h;
	int layer;
	Color col;
	int queuedEffect;
	Writer() : pos(0), len(0), startX(0), startY(0), x(0), y(0), w(0), h(0), layer(0), col(Color::def), queuedEffect(0) {}

	bool wrAtEnd() {
		return pos == len;
	}

	void wrParseCommand(char command, char instr) {
		if (command == 'n') { // newline
			x = startX;
			y++;
		}

		/*
	Entry("", "")
	.AddText(
		OptionalText("").ShowIfKey().HideIfKey())
	.AddOptions(
		Option("", "").HideIfKey().ShowIfKey.TriggerKey(),
		Option("", "").HideIfKey().ShowIfKey.TriggerKey(),
		Option("", "").HideIfKey().ShowIfKey.TriggerKey(),
		Option("", "").HideIfKey().ShowIfKey.TriggerKey()
	),
		
		
		
		*/


		if (command == 'p') { // pause
			if (instr == '0') { timer.additionalPause = 100; }
			else if (instr == '1') { timer.additionalPause = 500; }
			else if (instr == '2') { timer.additionalPause = 1000; }
			else if (instr == '3') { timer.additionalPause = 1500; }
			else if (instr == '4') { timer.additionalPause = 3000; }
		}
		if (command == 's') { // speed 
			if (instr == '0') { timer.speed = 5; }
			else if (instr == '1') { timer.speed = 70; }
			else if (instr == '2') { timer.speed = 150; }
			else if (instr == '3') { timer.speed = 200; }
			else if (instr == '4') { timer.speed = 250; }
			else if (instr == '9') { timer.speed = -1; }
		}
		if (command == 'c') { // color
			if (instr == 'R') { col = Color::red; }
			else if (instr == 'G') { col = Color::green; }
			else if (instr == 'B') { col = Color::blue; }
			else if (instr == 'W') { col = Color::white; }
			else if (instr == 'P') { col = Color::purple; }
			else if (instr == 'D') { col = Color::def; }
		}
		if (command == 'e') { // effect
			queuedEffect = IntFromChar(instr); // 1=shake, 2=shoot, 3=soul, 4=health
		}
		if (command == '>') { // option marker
			//printAt(instr, writer.x, writer.y, Color::purple);
			//writer.x ++;
		}
	}

	// @private: actually put one more character on screen. No check for Eof or nuthin
	void __wrPutChar(ConsoleBuffer* buffer) {
		char c = text[pos];
		if (c == '^') {
			wrParseCommand('n', ' ');
			pos++;
			return;
		}
		else if (c == '#') {
			wrParseCommand(text[pos + 1], text[pos + 2]);
			pos += 3;
			return;
		}

		if (c == '.') {
			timer.additionalPause = 1200;
		}

		buffer->Set(c, x, y, col);
		pos++;
		x++;
	}

	// Write out every single character until we reach the end. No timers. No waiting.
	void wrFlushEverything(ConsoleBuffer* buffer) {
		while (!wrAtEnd()) {
			__wrPutChar(buffer);
		}
	}

	bool wrTick(ConsoleBuffer* buffer, double deltaTime) {
		if (wrAtEnd()) { return false; }

		if (deltaTime == -1 || skipToEnd) {
			skipToEnd = false;
			wrFlushEverything(buffer);
			return true;
		}

		if (timer.speed == -1) {
			while (!wrAtEnd() && timer.speed == -1) {
				__wrPutChar(buffer);
			}
			return true;
		}

		if (!timer.CountDown(deltaTime, fastForward)) {
			return false;
		}

		__wrPutChar(buffer);

		if (updateCursor) {
			buffer->SetCursor(x, y);
		}

		return true;
	}

	// TODO: Don't hardcode!!
	void wrResize(int width, int height) {
		w = width;
		h = height;
		// Runtime scaling does not currently work. Lets not even pretend it does
		
		int lastSpace = 0;
		int lastSpaceX = startX;
		int x = startX;
		for (int i = 0; i < len; i++) {
			char c = text[i];

			if (c == '#') {
				if (text[i + 1] == 'n') { x = 0; }
				i += 2;
				continue;
			}

			if (c == '^') { text[i] = ' '; }
			if (c == ' ') {
				lastSpace = i;
				lastSpaceX = x;
			}

			x++;
			if (x >= w) {
				text[lastSpace] = '^';
				x -= lastSpaceX;
			}
		}
		// re-write all resized text
		/*
		int oldPos = pos;
		pos = 0;
		for (int i = 0; i < oldPos; i++) {
			wrTick(-1);
		}
		*/
	}

	void wrSetText(string str, int startX, int startY, int width, int height) {
		text = str;
		pos = 0;
		len = text.size();
		this->startX = x = startX;
		this->startY = y = startY;
		timer.speed = 30;
		wrResize(width, height);
	}

	int wrGetQueuedEffect() {
		if (this->queuedEffect == 0) { return 0; }
		int effect = this->queuedEffect;
		this->queuedEffect = 0;
		return effect;
	}

	int IntFromChar(char c) {
		char nums[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		for (int i = 0; i < 10; i++) {
			if (nums[i] == c) return i;
		}
		return -1;
	}
};