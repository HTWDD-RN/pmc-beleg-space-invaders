#include <Bullet.h>

Bullet::Bullet(int x, int y){
	xpos = x;
	ypos = y;
}

Bullet::Bullet(){
	xpos = 0;
	ypos = 0;
}

void Bullet::draw(TFT disp){
	disp.stroke(255,255,255);
	disp.line(xpos,ypos,xpos,ypos+3);
}

void Bullet::unDraw(TFT disp){
	disp.stroke(0,0,0);
	disp.line(xpos,ypos,xpos,ypos+3);
}

int Bullet::getX(){
	return xpos;
}

int Bullet::getY(){
	return ypos;
}

void Bullet::moveTo(int x, int y, TFT disp){
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
