#include <Enemy.h>

Enemy::Enemy(int x, int y){
	xpos = x;
	ypos = y;
}

Enemy::Enemy(){
	xpos = 0;
	ypos = 0;
}

void Enemy::draw(TFT disp){
	if (hp > 0 && hasMoved == 1) {
		disp.stroke(255,255,255);
		for (int i = 0; i < sizeof(lines) / sizeof(line); i++) {
			line l = lines[i];
			disp.line(l.x1, l.y1, l.x2,l.y2);
		}
		hasMoved = 2;
	}
}

void Enemy::unDraw(TFT disp){
	if (hp > 0 && hasMoved == 2) {
		disp.fill(0,0,0);
		disp.rect(xpos-5,ypos,xpos+10,ypos+10);
	}
}

void Enemy::render(){
	line line1 = {xpos,ypos,xpos+5,ypos};
	line line2 = {xpos+5,ypos,xpos+5,ypos+5};
	line line3 = {xpos+5,ypos+5,xpos+10,ypos+5};
	line line4 = {xpos+10,ypos+5,xpos+10,ypos+10};
	line line5 = {xpos+10,ypos+10,xpos-5,ypos+10};
	line line6 = {xpos-5,ypos+10,xpos-5,ypos+5};
	line line7 = {xpos-5,ypos+5,xpos,ypos+5};
	line line8 = {xpos,ypos,xpos,ypos+5};
	lines[0] = line1;
	lines[1] = line2;
	lines[2] = line3;
	lines[3] = line4;
	lines[4] = line5;
	lines[5] = line6;
	lines[6] = line7;
	lines[7] = line8;
}

int Enemy::getX(){
	return xpos;
}

int Enemy::getY(){
	return ypos;
}

void Enemy::moveTo(int x, int y){
	if (x != xpos || y != ypos) {
		hasMoved = 1;
	}
	xpos = x;
	ypos = y;
}

int Enemy::getHP(){
	return hp;
}
