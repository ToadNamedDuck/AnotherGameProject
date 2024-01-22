//A tile represents something like a background tile. Has size and pos data, and should have an onTouch function for when the player hits it.
//I do eventually want to have custom collision utilizing something like a bitmask specfic to tiles.
//The coordinates of the tile start at it's position in the scene times 16. ends at +16.
// 
//Instead of making special tiles that are portals, spikes, pits etc with custom logic, we can make overloads that declare the tile as a portal or a pit or something
// 
//Portals will need a scene to go to, as well as which entrance it directly links to. Ideally, way in the future, it can choose a type of transition effect.
//Portals may also need to be marked as normal or entrance-only.
//A pit that drops you into a new room is an example of an entrance only portal. Implement later

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
	void draw()
	{
		//Using the size, we want to get the correct tile off the grid using the provided coordinates, then assuming we know the tile is in the view of the camera, we call draw.
		// I think what we have to do is potentially return a 16x16 grid of pixel data to render - but definitely don't store it in the Tile itself.
		// 
		// 
		//Camera is size of the window. Determine where the camera is by scene width subtracted from the scene width and same with height. - Assumes player is ALWAYS middle of screen.
		//Make camera later.

		//Note to move: player internal tile position is not dividing the player position by 16, but modulo by 16.
	}
};