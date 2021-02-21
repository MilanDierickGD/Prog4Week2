#pragma once
#include <windows.h>
#include <Xinput.h>

#include "Command.h"

#define XINPUT_GAMEPAD_DPAD_UP			0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN		0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT		0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT		0x0008
#define XINPUT_GAMEPAD_START			0x0010
#define XINPUT_GAMEPAD_BACK				0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB		0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB		0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER	0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER	0x0200
#define XINPUT_GAMEPAD_A				0x1000
#define XINPUT_GAMEPAD_B				0x2000
#define XINPUT_GAMEPAD_X				0x4000
#define XINPUT_GAMEPAD_Y				0x8000

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30

namespace DAE
{
	struct Controller
	{
		bool Connected;
		size_t ControllerIndex;
		XINPUT_STATE State;
	};

	enum class ControllerButton
	{
		DPadUp = XINPUT_GAMEPAD_DPAD_UP,
		DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		GamePadStart = XINPUT_GAMEPAD_START,
		GamePadBack = XINPUT_GAMEPAD_BACK,
		GamePadLeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		GamePadRightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		GamePadA = XINPUT_GAMEPAD_A,
		GamePadB = XINPUT_GAMEPAD_B,
		GamePadX = XINPUT_GAMEPAD_X,
		GamePadY = XINPUT_GAMEPAD_Y,
	};

	class InputManager
	{
	public:
		InputManager() = default;
		DAE::Command* ProcessInput();
		bool IsPressed(ControllerButton button, size_t playerIndex = 0) const;

	private:
		Controller m_Controllers[XUSER_MAX_COUNT];

		Command* m_DPadUp;
		Command* m_DPadDown;
		Command* m_DPadLeft;
		Command* m_DPadRight;
		Command* m_GamePadStart;
		Command* m_GamePadBack;
		Command* m_GamePadLeftThumb;
		Command* m_GamePadRightThumb;
		Command* m_GamePadA;
		Command* m_GamePadB;
		Command* m_GamePadX;
		Command* m_GamePadY;

		void CalculateDeadzone(size_t controllerIndex);
	};
}
