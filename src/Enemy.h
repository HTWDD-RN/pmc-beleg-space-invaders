#include <TFT.h>
#include <SPI.h>

struct line{
	int x1;
	int y1;
	int x2;
	int y2;
};

class Enemy {
	public:
		Enemy();
		Enemy(int x, int y);
		void draw(TFT disp);
		void unDraw(TFT disp);
		void render();
		void moveTo(int x, int y, TFT disp);
		int getX();
		int getY();
		int getHP();
		line lines[8];
	private:
		int xpos;
		int ypos;
		int hp = 10;
		bool hasMoved = false;
};
