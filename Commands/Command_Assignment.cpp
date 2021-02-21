#include <iostream>
#include <thread>
#include <vld.h>
#include "InputManager.h"

#pragma comment(lib, "XInput.lib")

using namespace DAE;

int main()
{
	auto inputManager = InputManager();
	auto t            = std::chrono::high_resolution_clock::now();

	GameActor actor{};
	
	while (true)
	{
		Command* command = inputManager.ProcessInput();

		if (command)
		{
			command->Execute(actor);	
		}
		
		// if (inputManager.IsPressed(ControllerButton::GamePadA))
		// 	std::cout << "Button A has been pressed" << std::endl;
		// else if (inputManager.IsPressed(ControllerButton::GamePadB))
		// 	std::cout << "Button B has been pressed" << std::endl;
		// else if (inputManager.IsPressed(ControllerButton::GamePadY))
		// 	std::cout << "Button Y has been pressed" << std::endl;
		// else if (inputManager.IsPressed(ControllerButton::GamePadX))
		// {
		// 	std::cout << "Button X has been pressed" << std::endl;
		// 	break;
		// }

		t += std::chrono::milliseconds(16); // we want 60 fps
		std::this_thread::sleep_until(t);
	}
	std::cout << "Let's end." << std::endl;

}
