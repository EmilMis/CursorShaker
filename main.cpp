#include <iostream>
#include <windows.h>
#include <thread>

//config
int MOVE_AMOUNT = 10;
int MOVE_DELAY = 50;
int MOUSE_CHECK_DELAY = 10;
int PROGRAM_DELAY = 8500;

char KEY_BREAK = 'S';
int KEY_DELAY = 2500;
int KEY_CHECK_DELAY = 100;

int BEEP_FREQ = 800;
int BEEP_DELAY = 1500;

using namespace std;

void checkKey() {
	while (true) {
		int count = 0;
		while (GetKeyState(KEY_BREAK) & 0x8000) {
			if (count >= (KEY_DELAY / KEY_CHECK_DELAY)) {
				Beep(BEEP_FREQ, BEEP_DELAY);
				exit(0);
			}
			Sleep(KEY_CHECK_DELAY);
			count++;
		}
	}
}

void progSleep(int amount, int checkMouseDelay) {

	while (true) {

		POINT mousepos;
		GetCursorPos(&mousepos);

		for (int i = 0; i < (amount / checkMouseDelay); i++) {
			POINT newmousepos;
			GetCursorPos(&newmousepos);
			if (newmousepos.x != mousepos.x || newmousepos.y != mousepos.y)break;
			Sleep(checkMouseDelay);
			if (i == (amount / checkMouseDelay) - 1)return;
		}


	}

}

void moveMouse(int amount, int time) {
	POINT point;
	GetCursorPos(&point);
	
	for (int i = 0; i < 3; i++) {
		SetCursorPos(point.x + amount, point.y);
		Sleep(time);
		SetCursorPos(point.x, point.y);
		Sleep(time);
		SetCursorPos(point.x - amount, point.y);
		Sleep(time);
		SetCursorPos(point.x, point.y);
		Sleep(time);
	}

}

int main(void) {
	thread th(checkKey);
	while (true) {
		progSleep(PROGRAM_DELAY, MOUSE_CHECK_DELAY);
		moveMouse(MOVE_AMOUNT, MOVE_DELAY);
	}

	return 0;
}
