#ifndef __SHDEBOUNCER_H__
#define __SHDEBOUNCER_H__

#include <Arduino.h>

class SHDebouncer {
private:
	unsigned long lastPoll = 0;
	byte debounceDelay;
public:
	SHDebouncer(byte delay) {
		debounceDelay = delay;
	}

	SHDebouncer() {
	}

	void begin(byte delay) {
		debounceDelay = delay;
	}

	bool Debounce() {
		if (millis() - lastPoll > debounceDelay) {
			lastPoll = millis();
			return true;
		}
		return false;
	}
};

#endif