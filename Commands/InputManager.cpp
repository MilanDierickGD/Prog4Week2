#include "InputManager.h"

#include <cmath>

DAE::Command* DAE::InputManager::ProcessInput()
{
	// TODO: Only get the state of a controller if it's active, and don't check every controller every frame to see if it's connected
	for (DWORD index = 0; index < XUSER_MAX_COUNT; ++index)
	{
		RtlSecureZeroMemory(&m_Controllers[index].State, sizeof XINPUT_STATE);

		// TODO: Cached states should be compared against the results of XInputGetState to determine what changes were made that frame instead
		m_Controllers[index].Connected = XInputGetState(index, &m_Controllers[index].State);

		CalculateDeadzone(index);

		// Process keystrokes
		XINPUT_KEYSTROKE* keystroke = nullptr;
		
		while (XInputGetKeystroke(index, 0, keystroke) == ERROR_SUCCESS)
		{
			// TODO: Fire events for keystrokes with the type of key pressed and the index of the controller
		}
	}

	// TODO: This is temporary, should be replaced by events
	if (IsPressed(ControllerButton::GamePadA)) return m_GamePadA;
	if (IsPressed(ControllerButton::GamePadB)) return m_GamePadB;
	if (IsPressed(ControllerButton::GamePadX)) return m_GamePadX;
	if (IsPressed(ControllerButton::GamePadY)) return m_GamePadY;
	
	return nullptr;
}

bool DAE::InputManager::IsPressed(ControllerButton button, const size_t playerIndex) const
{
	return m_Controllers[playerIndex].State.Gamepad.wButtons & static_cast<DWORD>(button);
}

void DAE::InputManager::CalculateDeadzone(const size_t controllerIndex)
{
	// Calculate deadzone
	if (m_Controllers[controllerIndex].Connected)
	{
		XINPUT_STATE* state = &m_Controllers[controllerIndex].State;

		// TODO: Configure a controller and see what values we are working with here to properly calculate deadzone
		const float lx = state->Gamepad.sThumbLX;
		const float ly = state->Gamepad.sThumbLY;

		// Determine how far the controller is pushed
		float magnitude = sqrt(lx * lx + ly * ly);

		// Determine the direction the controller is pushed
		float normalizedLx = lx / magnitude;
		float normalizedLy = ly / magnitude;

		float normalizedMagnitude = 0;

		// Check if the controller is outside a circular dead zone
		if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			// Clip the magnitude at its expected maximum value
			if (magnitude > 32767) magnitude = 32767;

			// Adjust magnitude relative to the end of the dead zone
			magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

			// Optionally normalize the magnitude with respect to its expected range
			// giving a magnitude value of 0.0 to 1.0
			normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		}
		else // If the controller is in the deadzone zero out the magnitude
			{
			magnitude           = 0.0;
			normalizedMagnitude = 0.0;
			}
	}
}
