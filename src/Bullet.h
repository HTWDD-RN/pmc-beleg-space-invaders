#include <TFT.h>
#include <SPI.h>

class Bullet{
	public:
		Bullet();
		Bullet(int x, int y);
		void draw(TFT disp);
		void unDraw(TFT disp);
		void moveTo(int x, int y, TFT disp);
		int getX();
		int getY();
	private:
		int xpos;
		int ypos;
		bool hasMoved = false;
};
