#include <Player.h>

Player::Player(int x, int y){
	xpos = x;
	ypos = y;
}

void Player::draw(TFT disp){
	if (hasMoved) {
		disp.fill(255,255,255);
		disp.rect(xpos-5,ypos,xpos+5,ypos+3);
	}
	hasMoved = false;
}

void Player::unDraw(TFT disp){
	if (hasMoved) {
		disp.fill(0,0,0);
		disp.rect(xpos-5,ypos,xpos+5,ypos+3);
	}
}

int Player::getX(){
	return xpos;
}

int Player::getY(){
	return ypos;
}

void Player::moveTo(int x, int y){
	xpos = x;
	ypos = y;
	hasMoved = true;
}

