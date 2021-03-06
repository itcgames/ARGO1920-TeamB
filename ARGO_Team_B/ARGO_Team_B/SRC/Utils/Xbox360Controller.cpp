#include "Xbox360Controller.h"

int Xbox360Controller::getID()
{
	return m_joystick_index;
}

Xbox360Controller::Xbox360Controller(int currentControll) :
	m_joystick_index(currentControll)
{
	if (connect()) {
		m_controllerHandles = SDL_GameControllerOpen(m_joystick_index);

		m_joystick = SDL_JoystickOpen(m_joystick_index);
		if (m_joystick != NULL)
		{
			m_controllerHaptic = SDL_HapticOpenFromJoystick(m_joystick);
			if (m_controllerHaptic == NULL)
			{
				std::cout << "controller doesnt support haptic" << std::endl;
			}
			else
			{
				if (SDL_HapticRumbleInit(m_controllerHaptic) < 0)
				{
					std::cout << "Unable to initialise Rumble" << std::endl;
				}
			}
		}
	}
}

Xbox360Controller::~Xbox360Controller() {
	delete(this);
}

bool Xbox360Controller::connect() {
	return isConnected();
}

bool Xbox360Controller::isConnected() {
	//std::cout << SDL_IsGameController(m_joystick_index) << " controller: " << m_joystick_index << std::endl;
	if (SDL_IsGameController(m_joystick_index)) {		
		return true;
	}
	else {
		return false;
	}
}

/// <summary>
/// get the input from controller
/// </summary>
void Xbox360Controller::checkButton() {

	// check if new controller connect to the pc
	if (m_controllerHandles == NULL && connect()) {
		m_controllerHandles = SDL_GameControllerOpen(m_joystick_index);
	}

	m_currentState.A = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_A);
	m_currentState.B = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_B);
	m_currentState.X = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_X);
	m_currentState.Y = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_Y);

	m_currentState.DpadRight = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	m_currentState.DpadLeft = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	m_currentState.DpadUp = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_DPAD_UP);
	m_currentState.DpadDown = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_DPAD_DOWN);

	m_currentState.LB = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	m_currentState.RB = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

	m_currentState.LeftThumbStickClick = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_LEFTSTICK);
	m_currentState.RightThumbStickClick = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_RIGHTSTICK);

	m_currentState.Start = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_START);
	m_currentState.Back = SDL_GameControllerGetButton(m_controllerHandles, SDL_CONTROLLER_BUTTON_BACK);

	m_currentState.RTtigger = SDL_GameControllerGetAxis(m_controllerHandles, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
	m_currentState.LTtigger = SDL_GameControllerGetAxis(m_controllerHandles, SDL_CONTROLLER_AXIS_TRIGGERLEFT);

	m_currentState.LeftThumbStick.x = SDL_GameControllerGetAxis(m_controllerHandles, SDL_CONTROLLER_AXIS_LEFTX);
	m_currentState.LeftThumbStick.y = SDL_GameControllerGetAxis(m_controllerHandles, SDL_CONTROLLER_AXIS_LEFTY);
	m_currentState.RightThumbStick.x = SDL_GameControllerGetAxis(m_controllerHandles, SDL_CONTROLLER_AXIS_RIGHTX);
	m_currentState.RightThumbStick.y = SDL_GameControllerGetAxis(m_controllerHandles, SDL_CONTROLLER_AXIS_RIGHTY);

	/*std::cout << "controller : " << m_joystick_index;
	std::cout << " X : " << m_currentState.LeftThumbStick.x << std::endl;
	std::cout << " Y : " << m_currentState.LeftThumbStick.y << std::endl;*/
}
