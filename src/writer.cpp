

#include <iostream>
#include <string>
#include "Console.h"

using namespace std;

struct Writer {
	bool fastForward = false;
	bool skipToEnd = false;

	ConsoleBuffer *buffer;
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
	Writer() : pos(0), len(0), startX(0), startY(0), x(0), y(0), w(0), h(0), layer(0), col(Color::def) {}

	bool wrAtEnd() {
		return pos == len;
	}
};




void wrParseCommand(Writer &writer, char command, char instr) {
	if (command == 'n') { // newline
		writer.x = writer.startX;
		writer.y ++;
		}
	if (command == 'p') { // pause
		if (instr == '0') { writer.timer.additionalPause = 100; }
		else if (instr == '1') { writer.timer.additionalPause = 500; }
		else if (instr == '2') { writer.timer.additionalPause = 1000; }
		else if (instr == '3') { writer.timer.additionalPause = 1500; }
	}
	if (command == 's') { // speed 
		if (instr == '0') { writer.timer.speed = 5; }
		else if (instr == '1') { writer.timer.speed = 30; }
		else if (instr == '2') { writer.timer.speed = 50; }
		else if (instr == '3') { writer.timer.speed = 150; }
		else if (instr == '9') { writer.timer.speed = -1; }
	}
	if (command == 'c') { // color
		if (instr == 'R') { writer.col = Color::red; }
		else if (instr == 'G') { writer.col = Color::green; }
		else if (instr == 'B') { writer.col = Color::blue; }
		else if (instr == 'W') { writer.col = Color::white; }
		else if (instr == 'P') { writer.col = Color::purple; }
		else if (instr == 'D') { writer.col = Color::def; }
	}
	if (command == '>') { // option marker
		//printAt(instr, writer.x, writer.y, Color::purple);
		//writer.x ++;
	}
}


// @private: actually put one more character on screen. No check for Eof or nuthin
void __wrPutChar(Writer &writer) {
	char c = writer.text[writer.pos];
	if (c == '^') {
		wrParseCommand(writer, 'n', ' ');
		writer.pos++;
	//	__wrPutChar(writer);
		return;
	}
	else if (c == '#') {
		wrParseCommand(writer, writer.text[writer.pos+1], writer.text[writer.pos+2]);
		writer.pos += 3;
	//	__wrPutChar(writer);
		return;
	}

	if (c == '.') {
		writer.timer.additionalPause = 500;
	}

	writer.buffer->Set(c, writer.x, writer.y, writer.col);
	writer.pos ++;
	writer.x ++;
}

// Write out every single character until we reach the end. No timers. No waiting.
void wrFlushEverything(Writer &writer) {
	while(!writer.wrAtEnd()) {
		__wrPutChar(writer);
	}
}

bool wrPutChar(Writer &writer, double deltaTime) {
	if (writer.wrAtEnd()) {return false;}

	if (deltaTime == -1 || writer.skipToEnd) {
		writer.skipToEnd = false;
		wrFlushEverything(writer);
		return true;
	}

	if (writer.timer.speed == -1) {
		while (!writer.wrAtEnd() && writer.timer.speed == -1) {
			__wrPutChar(writer);
		}
		return true;
	}

	if (!writer.timer.CountDown(deltaTime, writer.fastForward)) {
		return false;
	}

	__wrPutChar(writer);
	return true;
}

// TODO: Don't hardcode!!
void wrResize(Writer &writer) {
	writer.w = 100;
	writer.h = 60;
	int lastSpace = 0;
	int lastSpaceX = writer.startX;
	int x = writer.startX;
	for (int i=0; i<writer.len; i++) {
		char c = writer.text[i];

		if (c == '#') {
			if (writer.text[i+1] == 'n') { x = 0; }
			i+=2;
			continue;
		}

		if (c == '^') { writer.text[i] = ' '; }
		if (c == ' ') { 
			lastSpace = i;
			lastSpaceX = x;
		 }
		
		x++;
		if (x >= writer.w) {
			writer.text[lastSpace] = '^';
			x -= lastSpaceX;
		}
	}
	// re-write all resized text
	int oldPos = writer.pos;
	writer.pos = 0;
	for (int i=0; i<oldPos; i++) {
		wrPutChar(writer, -1);
	}
}

void wrSetText(Writer &writer, string text, int startX, int startY) {
	writer.text = text;
	writer.pos = 0;
	writer.len = text.size();
	writer.startX = writer.x = startX;
	writer.startY = writer.y = startY;
	writer.timer.speed = 30;
	wrResize(writer);
}

