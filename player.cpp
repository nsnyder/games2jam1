//=======================================================================================
// player.h by Nick Halvorsen (C) 2015 All Rights Reserved.
//=======================================================================================

#include "Player.h"

void Player::draw() {

	GameObject::draw();
}

void Player::increaseScale(float collidedScale) {
	if(getScale()<2.5) {
		setScale(getScale()+ .05);
	}
}

void Player::decreaseScale(float collidedScale) {
	float newScale = max(0.0f, getScale()-collidedScale*.25);
	setScale(newScale);
}

void Player::update(float dt) {
	decreaseScale(getScale()*0.025f*dt);
	GameObject::update(dt);
}