#include <Player.h>

Player::Player(int x, int y){
	xpos = x;
	ypos = y;
}

Player::Player(){
	xpos = 0;
	ypos = 0;
}

void Player::draw(TFT disp){
	disp.stroke(255,255,255);
	disp.line(xpos,ypos,xpos+10,ypos+3);
	disp.line(xpos,ypos,xpos-10,ypos+3);
}

void Player::unDraw(TFT disp){
	disp.stroke(0,0,0);
	disp.line(xpos,ypos,xpos+10,ypos+3);
	disp.line(xpos,ypos,xpos-10,ypos+3);
}

int Player::getX(){
	return xpos;
}

int Player::getY(){
	return ypos;
}

void Player::moveTo(int x, int y, TFT disp){
	if (x != xpos || y != ypos) {
		this->unDraw(disp);
		hasMoved = true;
	}
	xpos = x;
	ypos = y;
	if (hasMoved) {
		this->draw(disp);
		hasMoved = false;
	}
}
