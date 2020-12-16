#include "Monster.h"

void Monster::initVariables(Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture texture_sheet)
{
	this->health = health;
	this->walkSpeed = walk_speed;
	this->damage = damage;
	this->textureSheet = texture_sheet;
	this->attribute = attribute;
	this->isDead = false;

}

Monster::Monster(float x, float y, Entity::EntityAttributes attribute, int health, float walk_speed, int damage, sf::Texture texture_sheet)
{
	this->initVariables(attribute, health, walk_speed, damage, texture_sheet);

	this->originPoint = sf::Vector2f(x, y);
	//this->sprite.setScale(-0.5f, 0.5f);

	this->setPositions(x, y);

}

Monster::~Monster()
{
}

void Monster::updateMonsterMove(const float& dt)
{
	float x = this->getPosition().x;
	float y = this->getPosition().y;

	float heavy = 30.f;

	switch (this->attribute) {
	case EntityAttributes::NORMAL:
			// step 1
			if (x < 290 - 70 && y > 579) {
				this->move(1.f, 0.f, dt);
			}

		// step 2
			else if (x < 365 - 70 && y > 579) {
				this->move(1.f, 0.f, dt);
				if (y < 810) {
					this->move(0.f, 1.f, dt);
				}
			}

		// step 3
			else if (x < 455 - 70 && y > 579) {
				this->move(1.f, 0.f, dt);
			}

		// step 4
			else if (x < 554 - 70 && y > 579) {
				this->move(1.f, 0.f, dt);
				if (y > 619) {
					this->move(0.f, -1.f, dt);
				}
			}

		// step 5
			else if (x < 652 && y > 579) {
				this->move(1.f, 0.f, dt);
				if (y < 654) {
					this->move(0.f, 0.5f, dt);
				}
			}

		// step 6
			else if (x < (1100 - 70) && y > 579) {
				this->move(1.f, 0.f, dt);
			}

		// step 7
			else if (x < (1200 - 50) && y > 344) {
				this->move(1.f, 0.f, dt);
				if (y > 500) {
					this->move(0.f, -1.f, dt);
				}
			}
			else if (y > 344) {
				this->move(0.f, -1.f, dt);
				//if (x >  )
			}

		// step 8
			else if (x > 600 + 70 && y > 326) {
				this->move(-1.f, 0.f, dt);
				if (x < 670 + 30) {
					this->move(0.f, -1.f, dt);
				}
			}

		// step 9
			else if (y > 160 - 156) {
				if (x > 650 - 20) {
					this->move(-1.f, 0.f, dt);
				}
				this->move(0.f, -1.f, dt);
			}

		// step 10
			else if (y < 160 - 156 && x < 1900) {
				this->move(1.f, 0.f, dt);
			}
			break;
	case EntityAttributes::HEAVY:
		// step 1
		if (x < 290 - 70 && y > 579-heavy) {
			this->move(1.f, 0.f, dt);
		}

		// step 2
		else if (x < 365 - 70 && y > 579-heavy) {
			this->move(1.f, 0.f, dt);
			if (y < 810-heavy) {
				this->move(0.f, 1.f, dt);
			}
		}

		// step 3
		else if (x < 455 - 70 && y > 579-heavy) {
			this->move(1.f, 0.f, dt);
		}

		// step 4
		else if (x < 554 - 70 && y > 579-heavy) {
			this->move(1.f, 0.f, dt);
			if (y > 619-heavy) {
				this->move(0.f, -1.f, dt);
			}
		}

		// step 5
		else if (x < 652 && y > 579-heavy) {
			this->move(1.f, 0.f, dt);
			if (y < 654-heavy) {
				this->move(0.f, 0.5f, dt);
			}
		}

		// step 6
		else if (x < (1100 - 70) && y > 579-heavy) {
			this->move(1.f, 0.f, dt);
		}

		// step 7
		else if (x < (1200 - 50) && y > 344-heavy) {
			this->move(1.f, 0.f, dt);
			if (y > 500-heavy) {
				this->move(0.f, -1.f, dt);
			}
		}
		else if (y > 344-heavy) {
			this->move(0.f, -1.f, dt);
			//if (x >  )
		}

		// step 8
		else if (x > 600 + 70 && y > 326-heavy) {
			this->move(-1.f, 0.f, dt);
			if (x < 670 + 50) {
				this->move(0.f, -1.f, dt);
			}
		}

		// step 9
		else if (y > 160 - 156-heavy) {
			if (x > 650-40) {
				this->move(-1.f, 0.f, dt);
			}
			this->move(0.f, -1.f, dt);
		}

		// step 10
		else if (y < 160 - 156-heavy && x < 1900) {
			this->move(1.f, 0.f, dt);
		}
		break;
	case EntityAttributes::FLY:
		// step 1
		if (x < 290 - 70 && y > 579) {
			this->move(1.5f, 0.f, dt);
		}

		// step 2
		else if (x < 365 - 70 && y > 579) {
			this->move(1.5f, 0.f, dt);
			if (y < 810) {
				this->move(0.f, 1.5f, dt);
			}
		}

		// step 3
		else if (x < 455 - 70 && y > 579) {
			this->move(1.5f, 0.f, dt);
		}

		// step 4
		else if (x < 554 - 70 && y > 579) {
			this->move(1.5f, 0.f, dt);
			if (y > 619) {
				this->move(0.f, -1.5f, dt);
			}
		}

		// step 5
		else if (x < 652 && y > 579) {
			this->move(1.5f, 0.f, dt);
			if (y < 654) {
				this->move(0.f, 0.5f, dt);
			}
		}

		// step 6
		else if (x < (1100 - 70) && y > 579) {
			this->move(1.5f, 0.f, dt);
		}

		// step 7
		else if (x < (1200 - 50) && y > 344) {
			this->move(1.5f, 0.f, dt);
			if (y > 500) {
				this->move(0.f, -1.5f, dt);
			}
		}
		else if (y > 344) {
			this->move(0.f, -1.5f, dt);
			//if (x >  )
		}

		// step 8
		else if (x > 600 + 70 && y > 326) {
			this->move(-1.5f, 0.f, dt);
			if (x < 670 + 50) {
				this->move(0.f, -1.5f, dt);
			}
		}

		// step 9
		else if (y > 160 - 156) {
			if (x > 650 - 20) {
				this->move(-1.5f, 0.f, dt);
			}
			this->move(0.f, -1.5f, dt);
		}

		// step 10
		else if (y < 160 - 156 && x < 1900) {
			this->move(1.5f, 0.f, dt);
		}
		break;
	}


}

void Monster::update(const float& dt)
{
	this->movementComponent->update(dt);



	//this->hitboxComponent->update(dt, this->sprite.getPosition());
	// idle right
	if (this->movementComponent->getMovementState() == MovementComponent::MovementState::IDLE ||
		this->movementComponent->getMovementState() == MovementComponent::MovementState::RIGHT) {
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(0.5f, 0.5f);
		this->animationComponent->play("WALK", dt);
	}
	// idle left
	else {
		this->sprite.setScale(-0.5f, 0.5f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 0.7f, 0.f);
		if (this->attribute == EntityAttributes::HEAVY) {
			this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 0.7f - 25.f, 0.f);
		}
		else if (this->attribute == EntityAttributes::FLY) {
			this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 0.7f - 25.f, 0.f);
		}
		this->animationComponent->play("WALK", dt);
	}
}
