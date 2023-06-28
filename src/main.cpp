#include "Arduino.h"
#include <TFT.h>
#include <SPI.h>
#include <Enemy.h>
#include <Player.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

#define cs 10
#define dc 9
#define rst 8

TFT myScreen = TFT(cs, dc, rst);
Enemy e[5];
Player p = Player(50, 50);
int offset = 0;
bool direction = true;

void setup() {
	Serial.begin(9600);
	Serial.println("beginning tft setup");
	myScreen.begin();
    myScreen.background(0,0,0);
	myScreen.setTextSize(2);

	for(int i = 0; i < 5; i++){
		e[i] = Enemy(10+i*20, 10);
	}
}

void loop() {
	p.draw(myScreen);
	for(int i = 0; i < 5; i++){
		e[i].moveTo(10 + i * 20 + offset / 4, 10);
		e[i].render();
		e[i].draw(myScreen);
	}
	delay(10);
	p.unDraw(myScreen);
	for(int i = 0; i < 5; i++){
		e[i].unDraw(myScreen);
	}
	if (direction) {
		offset++;
	}else {
		offset--;
	}

	if (offset > 80 || offset < 0) {
		direction = !direction;
	}
}

