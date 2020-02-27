#pragma once
#include <cctype>
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
	Walking,
	WalkingBomb
};

enum class GameStates
{
	Game,
	MainMenu,
	Credits,
	Hosting,
	Joining,
	QuitGame
};

enum class EntityType
{
	Default,
	Rat,
	Bomb,
	Spike
};

static const int SCR_W = 1920;
static const int SCR_H = 1080;

static const int RAT_W = 30;
static const int RAT_H = 60;


struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};



