#ifndef XBOX360CONTROLLER
#define XBOX360CONTROLLER
//author ZhenzeZhao

#include <SDL.h>
#include <iostream>

/// <summary>
/// data to store the current state of the controller
/// </summary>
struct GamePadstate
{
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbStickClick;
	bool RightThumbStickClick;
	bool DpadUp;
	bool DpadDown;
	bool DpadRight;
	bool DpadLeft;
	bool Start;
	bool Back;
	bool Xbox;
	float RTtigger;
	float LTtigger;
	SDL_Point RighThumbStick;
	SDL_Point LeftThumbStick;
};

class Xbox360Controller {
private:
	//deadzone for the dpad
	const int dpadThreshold = 50;

	const int m_joystick_index;

	SDL_GameController* m_controllerHandles;

public:
	// the current state of all the buttons
	GamePadstate m_currentState;

	int getID();

	Xbox360Controller(int currentControll);
	~Xbox360Controller();
	//void update();
	bool isConnected();
	bool connect();

	void checkButton();

};

#endif
