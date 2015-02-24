//=======================================================================================
// player.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#include "Player.h"

void Player::draw() {

	GameObject::draw();
}

void Player::increaseScale(float collidedScale) {
	if(getScale()<2.5) {
		setScale(getScale()+collidedScale*.05);
	}
}

void Player::decreaseScale(float collidedScale) {
	setScale(getScale()-collidedScale*.05);
}