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
//Enemy e[5];
Enemy e = Enemy(10, 10);
Player p = Player(50, 50);
int offset = 0;
bool direction = true;

void setup() {
	Serial.begin(9600);
	Serial.println("beginning tft setup");
	myScreen.begin();
    myScreen.background(0,0,0);
	myScreen.setTextSize(2);

	//for(int i = 0; i < 5; i++){
	//	e[i] = Enemy(10+i*20, 10);
	//}
	//for(int i = 0; i < 5; i++){
	//	e[i].render();
	//	e[i].draw(myScreen);
	//}
	e.draw(myScreen);
}

void loop() {
	e.moveTo(10 + offset/8, 10, myScreen);
	//for(int i = 0; i < 5; i++){
	//	e[i].moveTo(10 + i * 20 + offset, 10, myScreen);
	//}
	delay(10);
	if (direction) {
		offset++;
	}else {
		offset--;
	}

	if (offset > 100 || offset < 0) {
		direction = !direction;
	}
}

