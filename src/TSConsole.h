#pragma once

struct TSConsoleBuffer {
	int buffer[500 * 400];
	int width;
	int height;

	void Init(int width, int height) {
		buffer[500*400] = {};
		this->width = width;
		this->height = height;
	}

	void Set(int val, int x, int y) {
		if (x < 0 || x >= width || y < 0 || y >= height) { return; }
		int i = y * width + x;
		buffer[i] = val;
	}

	int Get(int x, int y) {
		if (x < 0 || x >= width || y < 0 || y >= height) { return 0; }
		return buffer[y * width + x];
	}
};

