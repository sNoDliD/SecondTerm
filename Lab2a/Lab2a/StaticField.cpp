#include "Header.h"

static Mode g_mode = Mode::FIXEDSIZE;

Mode WorkMode() {
	return g_mode;
}

void SetWorkMode(Mode mode) {
	g_mode = mode;
}
