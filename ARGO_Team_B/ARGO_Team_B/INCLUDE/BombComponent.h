#ifndef BOMBCOMPONENT
#define BOMBCOMPONENT
#pragma once
#include "Component.h"

enum class BombState {
	Idle,
	Activate,
	Explode,
	Removed
};

class BombComponent : public Component {
public :
	BombComponent();
	~BombComponent();

	void setState(BombState state);
	BombState getState() { return m_currentState; }

	float getBombTimer() { return m_timer; }
	void setBombTimer(float time) { m_timer = time; }

	float getExplosionTimer() { return m_explosionTimer; }
	void setExplosionTimer(float time) { m_explosionTimer = time; }

	void playerGetBomb(int id);
	void playerPlaceBomb();

	bool isPlayerOwnedBomb() { return m_owned; }
	int bombOwner() { return m_ownerId; }
	float getBlastRadius() { return blastRadius; }

private:
	BombState m_currentState;

	float m_timer;
	float m_explosionTimer;

	bool m_owned;
	int m_ownerId;

	float blastRadius;
};
#endif