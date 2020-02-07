#include <iostream>

#include "Game.h"


int Entity::m_instanceCount = 0;
int ControlComponent::s_controlID = 0;

int main(int argc,char*argv[])
{
	Game game;
	game.run();

	return 0;
}
