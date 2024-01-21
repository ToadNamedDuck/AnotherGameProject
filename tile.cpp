//A tile represents sprite information. An array of sprites should be provided to a scene so it can be drawn and for interraction purposes
#include "iSprite.cpp"
#include <iostream>
class Tile : public iSprite
{

public:
	Tile(int size, int start_x, int start_y) : iSprite(size, start_x, start_y) {}
	void tell() {
		std::cout << size << sprite_start_x << sprite_start_y << std::endl;
	}
};