#ifndef ENUMS_H
#define ENUMS_H

enum class Types {
	Health,
	Position,
	Render,
	Button,
	Traps,
	Control,
	AnimatedSprite,
	Collider,
	Door,
	Player,
	Goal,
	Bomb,
	Game,
	TestBot
};

enum class States {
	Attack,
	Idle,
	Interact,
	Stunned,
	Walking
};

#endif // !ENUMS_H
