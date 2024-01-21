//A tile represents something like a background tile. Has size and pos data, and should have an onTouch function for when the player hits it.
//I do eventually want to have custom collision utilizing something like a bitmask specfic to tiles.
#include "iSprite.cpp"
#include <iostream>
#include <bitset>
class Tile : public iSprite
{
private:
	uint16_t bitmask[16];
public:
	Tile(int size, int start_x, int start_y, uint16_t init_bitmask[16]) : iSprite(size, start_x, start_y)
	{
		for (int row = 0; row < 16; row++)
		{
			bitmask[row] = init_bitmask[row];
		}
	}
	void tell() {
		std::cout << size << sprite_start_x << sprite_start_y << std::endl;
	}
	void showMask()
	{
		for (int row = 0; row < 16; row++)
		{
			std::bitset<16> bitmaskBits(bitmask[row]);
			std::cout << bitmaskBits << std::endl;
		}
	}
};