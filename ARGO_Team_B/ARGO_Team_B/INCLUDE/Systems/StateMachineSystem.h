#pragma once

#include "System.h"
#include "AnimatedSpriteComponent.h"
#include "PositionComponent.h"
#include "Enums.h"
#include "AttackState.h"
#include "IdleState.h"
#include "InteractState.h"
#include "StunnedState.h"
#include "WalkingState.h"

#include <vector>



class StateMachineSystem : public System
{
private:
	State* m_current;

	

public:
	StateMachineSystem();
	~StateMachineSystem();

	void setupSprites();
	void checkStates(State* t_state, Entity* e);
	void updateComponent(Component* c) override;


	void setCurrent(States t_state);

	void setRenderer(SDL_Renderer* t_rend);

	SDL_Renderer* m_renderer;
	SDL_Surface* m_surface;
	std::vector<SpriteSheet*> m_spriteSheets;


};
