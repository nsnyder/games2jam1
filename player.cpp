//=======================================================================================
// player.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#include "Player.h"

void Player::draw() {

	GameObject::draw();
}

void Player::increaseScale(float collidedScale) {
	if(getScale()<2.5) {
		setScale(getScale()+collidedScale*.25);
	}
}

void Player::decreaseScale(float collidedScale) {
	float newScale = max(0.0f, getScale()-collidedScale*.25);
	setScale(newScale);
}

void Player::update(float dt) {
	decreaseScale(0.05f*dt);
	GameObject::update(dt);
}