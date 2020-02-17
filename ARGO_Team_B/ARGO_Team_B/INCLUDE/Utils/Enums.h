#ifndef ENUMS_H
#define ENUMS_H

enum class Types {
	Health,
	Position,
	Render,
	Button,
	Traps,
	Controller,
	AnimatedSprite,
	Collider,
	Door,
	Player,
	Goal,
	Bomb
};

enum class States {
	Attack,
	Idle,
	Interact,
	Stunned,
	Walking
};
enum class GameStates
{
	Game,
	MainMenu,
	Credits
};
#endif // !ENUMS_H
