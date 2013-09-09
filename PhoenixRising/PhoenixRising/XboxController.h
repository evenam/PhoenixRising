#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>

class Button
{
private:
	bool pressed;
	bool released;
	bool current;

	bool _reset;
public:
	Button();
	~Button();

	bool check();
	bool check_pressed();
	bool check_released();

	void update(bool check);
	void reset();
};

class XboxControllerState
{
public:
	Button button_a;
	Button button_start;

	Button button_up;
	Button button_down;
	Button button_left;
	Button button_right;

	XboxControllerState();
	~XboxControllerState();

	void reset();
};

class XboxController
{
private:
	int num;
	XINPUT_STATE state;
	XboxControllerState *xcs;
public:
	XboxController(int number);
	bool is_connected();
	void vibrate(int left, int right);
	XboxControllerState *get_state();
	~XboxController();
};

#endif