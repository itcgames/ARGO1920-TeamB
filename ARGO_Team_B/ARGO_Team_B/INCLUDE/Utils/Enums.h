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

enum class EntityType
{
	Default,
	Rat,
	Bomb,
	Spike
};

#endif // !ENUMS_H
