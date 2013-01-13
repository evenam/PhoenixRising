#include "XboxController.h"

XboxController::XboxController(int number)
{
	num = number;
	xcs = new XboxControllerState;
}

XboxController::~XboxController()
{
	delete xcs;
}

bool XboxController::is_connected()
{
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    DWORD Result = XInputGetState(num, &state);
    if (Result == ERROR_SUCCESS)
        return true;
    else
        return false;
}

void XboxController::vibrate(int left = 65535, int right = 65535)
{
    XINPUT_VIBRATION Vibration;
    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));
    Vibration.wLeftMotorSpeed = left;
    Vibration.wRightMotorSpeed = right;
    XInputSetState(num, &Vibration);
}

XboxControllerState *XboxController::get_state()
{
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    XInputGetState(num, &state);

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		xcs->button_a.update(true);
	else
		xcs->button_a.update(false);

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
		xcs->button_start.update(true);
	else
		xcs->button_start.update(false);

	if (state.Gamepad.sThumbLX / 32768.f > 0.3f)
		xcs->button_right.update(true);
	else if (state.Gamepad.sThumbLX / 32768.f < -0.3f)
		xcs->button_left.update(true);
	else
	{
		xcs->button_right.update(false);
		xcs->button_left.update(false);
	}

	if (state.Gamepad.sThumbLY / 32768.f > 0.3f)
		xcs->button_up.update(true);
	else if (state.Gamepad.sThumbLY / 32768.f < -0.3f)
		xcs->button_down.update(true);
	else
	{
		xcs->button_down.update(false);
		xcs->button_up.update(false);
	}

	return xcs;
}

XboxControllerState::XboxControllerState()
{
	button_a.reset();
	button_start.reset();
	button_up.reset();
	button_down.reset();
	button_left.reset();
	button_right.reset();
}

XboxControllerState::~XboxControllerState()
{
}

void XboxControllerState::reset()
{
	button_a.reset();
	button_start.reset();
	button_up.reset();
	button_down.reset();
	button_left.reset();
	button_right.reset();
}

Button::Button()
{
	pressed = false;
	current = false;
	released = false;
	_reset = true;
}

Button::~Button()
{
}

bool Button::check()
{
	if (_reset)
		return false;
	else
		return current;
}

bool Button::check_pressed()
{
	return pressed;
}

bool Button::check_released()
{
	return released;
}

void Button::update(bool press)
{
	if (!_reset)
	{
		if (press)
		{
			released = false;
			if ((!pressed) && (!current))
			{
				current = true;
				pressed = true;
			}
			else if ((pressed) && (current))
			{
				pressed = false;
			}
		}
		else
		{
			pressed = false;
			if ((current) && (!released))
			{
				current = false;
				released = true;
			}
			else if ((!current) && (released))
			{
				released = false;
			}	
		}
	}
	else
	{
		if (!press)
			_reset = false;
	}
}

void Button::reset()
{
	pressed = false;
	current = false;
	released = false;
	_reset = true;
}
