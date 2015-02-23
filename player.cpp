//=======================================================================================
// player.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#include "Player.h"

void Player::draw() {

	GameObject::draw();
}

void Player::increaseScale(float collidedScale) {
	setScale(getScale()+collidedScale*.1f);
}