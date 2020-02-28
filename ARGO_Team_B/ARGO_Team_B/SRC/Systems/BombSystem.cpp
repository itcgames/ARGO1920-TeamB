#include "BombSystem.h"

BombSystem::BombSystem() {
	explodeAnimation = 0;
	explodeTimer = 0.2f;
	activeTimer = 0.6f;
	activeAnimation = 0;
}

BombSystem::~BombSystem() {

}

void BombSystem::updateComponent(Component* component) {

}

void BombSystem::updateComponent(float dt,AudioObserver * t_observer, SDL_Rect& t_view) {
	searchEntities();

	for (Entity& bombEntity : m_bombEntitys) {
		BombComponent* bombComp = static_cast<BombComponent*>(bombEntity.getComponent(Types::Bomb));
		int ownerId = bombComp->bombOwner();

		if (bombComp->isPlayerOwnedBomb() && ownerId != 0 ) {
			PlayerComponent* playerComp = static_cast<PlayerComponent*>(m_playerEntitys[ownerId - 1].getComponent(Types::Player));
			
			if (playerComp->getInteract()) {
				PositionComponent* bombPos = static_cast<PositionComponent*>(bombEntity.getComponent(Types::Position));

				PositionComponent* playerPos = static_cast<PositionComponent*>(m_playerEntitys[ownerId - 1].getComponent(Types::Position));

				bombPos->setPosition(playerPos->getPositionX() + (RAT_H / 2), playerPos->getPositionY() + (RAT_W / 2));
				bombComp->playerPlaceBomb();
				playerComp->getABomb(false);
				t_observer->onNotify(AudioObserver::PLACEBOMB);

				AnimatedSpriteComponent* animation = static_cast<AnimatedSpriteComponent*>(bombEntity.getComponent(Types::AnimatedSprite));
			}
		}

		

		/// <summary>
		/// if the bomb state change to activate then start count down
		/// when the timer less then 0, change the state to explode
		/// </summary>
		if (bombComp->getState() == BombState::Activate) {
			float timer = bombComp->getBombTimer();
			if (timer <= 0.0f) {

				for (int i = 0; i < m_playerEntitys.size(); i++)
				{
					ControlComponent* contComp = static_cast<ControlComponent*>(m_playerEntitys[i].getComponent(Types::Control));
					if (contComp != NULL)
					{
						SDL_HapticRumblePlay(contComp->m_controller->m_controllerHaptic, 0.75, 400);
					}
				}
				

				bombComp->setState(BombState::Explode);
				t_observer->onNotify(AudioObserver::EXPLOSION);
				CollisionComponent* bombCollider = static_cast<CollisionComponent*>(bombEntity.getComponent(Types::Collider));
				bombCollider->setCircleRadius(bombComp->getBlastRadius());

				RenderComponent* bombRender = static_cast<RenderComponent*>(bombEntity.getComponent(Types::Render));
				bombRender->setImage("./Assets/explode.png", 100.0f, 100.0f, bombComp->getBlastRadius() * 2, bombComp->getBlastRadius() * 2, 0);
			
				AnimatedSpriteComponent* animation = static_cast<AnimatedSpriteComponent*>(bombEntity.getComponent(Types::AnimatedSprite));

			}
			else {

				timer -= dt;

				RenderComponent* bombRender = static_cast<RenderComponent*>(bombEntity.getComponent(Types::Render));

				activeTimer -= dt;
				if (activeTimer <= 0.0f) {
					activeTimer = timer / 5;
					if (activeAnimation == 0) {
						activeAnimation = 1;
					}
					else if (activeAnimation == 1) {
						activeAnimation = 0;
					}
					cout << activeAnimation << endl;
				}

				bombRender->setImage("./Assets/BombActivating.png", 100.0f, 100.0f, 30, 30, activeAnimation);


				bombComp->setBombTimer(timer);
			}
		}
		else if (bombComp->getState() == BombState::Explode) {
			// animation for exlpode 
			
			float timer = bombComp->getExplosionTimer();
			if (timer <= 0.0f) {
				bombComp->setState(BombState::Removed);
				m_isScreenShaking = false;
			}
			else {
				m_isScreenShaking = true;
				timer -= dt;

				RenderComponent* bombRender = static_cast<RenderComponent*>(bombEntity.getComponent(Types::Render));

				explodeTimer -= dt;
				if (explodeTimer <= 0.0f) {
					explodeTimer = 0.2f;
					explodeAnimation++;
					cout << explodeAnimation << endl;
					if (explodeAnimation >= 5) {
						explodeAnimation = 0;
					}
				}
				
				bombRender->setImage("./Assets/ExplosionSpriteSheet.png", 100.0f, 100.0f, bombComp->getBlastRadius() * 2, bombComp->getBlastRadius() * 2, explodeAnimation);

				bombComp->setExplosionTimer(timer);
			}
		}
		
		ScreenShake(t_view);
	}
}

void BombSystem::ScreenShake(SDL_Rect& t_view)
{
	if (m_isScreenShaking)
	{
			switch (rand() % 2)
			{
			case 0:
				screenShakeAmountX *= -1;
				break;
			case 1:
				screenShakeAmountY *= -1;
				break;
			default:
				break;
			}

			if (t_view.x + screenShakeAmountX >= 0)
			{
				t_view.x += screenShakeAmountX;
			}
			if (t_view.y + screenShakeAmountY >= 0)
			{
				t_view.y += screenShakeAmountY;
			}

		}
		else
		{
			m_isScreenShaking = false;
			t_view.x = 0;
			t_view.y = 0;
			t_view.h = SCR_H;
			t_view.w = SCR_W;
			
		}
}

/// <summary>
/// search the vector entity and find all entity we need
/// </summary>
void BombSystem::searchEntities() {
	m_playerEntitys.clear();
	m_bombEntitys.clear();

	for (Entity& e1 : entities) {
		//get the all player entities from entities vector
		if (e1.getType() == Types::Player)
		{
			m_playerEntitys.push_back(e1);
		}
		//get the all button entites from entities vector
		else if (e1.getType() == Types::Bomb)
		{
			BombComponent* bombComp = static_cast<BombComponent*>(e1.getComponent(Types::Bomb));
			if (bombComp->getState() != BombState::Removed)
			{
				m_bombEntitys.push_back(e1);
			}
		}

	}
}