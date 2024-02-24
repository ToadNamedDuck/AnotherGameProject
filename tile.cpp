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
#include <fstream>
#include <bitset>

#pragma pack(push, 1)
struct BMPHeader {
	uint16_t signature; // BM
	uint32_t fileSize;
	uint32_t reserved;
	uint32_t dataOffset;
};
struct DIBHeader {
	uint32_t headerSize;
	int32_t width;
	int32_t height;
	uint16_t colorPlanes;
	uint16_t bitsPerPixel;
	uint32_t compressionMethod;
	uint32_t imageSize;
	int32_t horizontalResolution;
	int32_t verticalResolution;
	uint32_t numColors;
	uint32_t importantColors;
};
#pragma pack(pop)

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
	//The whole getPixels idea is just... flawed. I should load the images in main, and maybe pass a pointer to the already active file reads for each one in memory.
	//It doesn't solve the fact that the pixel data was just incorrect entirely though.
	//Lot to learn about bitmap files apparently.

	void getPixels() {
		//Open the overworld.bmp file for now. We can use an enum param later to choose which file to open.
		std::ifstream file("Overworld.bmp", std::ios::binary);

		//Read the bmpHeader
		BMPHeader bmpHeader;
		file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));
		//Read dibHeader
		DIBHeader dibHeader;
		file.read(reinterpret_cast<char*>(&dibHeader), sizeof(DIBHeader));
		//loop through the region selected and get the pixel data.

		std::cout << dibHeader.bitsPerPixel << std::endl;
		std::cout << dibHeader.width << std::endl;
		std::cout << dibHeader.height << " - height" << std::endl;

		file.seekg(bmpHeader.dataOffset);
		for (int y = sprite_start_y; y < sprite_start_y + 16; y++) {
			for (int x = sprite_start_x; x < sprite_start_x + 16; x++) {
				// Calculate the byte position of the current pixel
				int rowSize = floor((dibHeader.bitsPerPixel * dibHeader.width + 31) / 32) * 4;  // Calculate row size for the specific region
				int bytePosition = y * rowSize + x * (dibHeader.bitsPerPixel / 8);
				std::cout << "Row Size: " << rowSize << " " << "Byte Position: " << bytePosition << std::endl;
				// Move the file reader to the correct position
				file.seekg(bytePosition, std::ios::beg);

				// Read RGBA values
				char pixel[4];
				file.read(pixel, sizeof(pixel));

				// Access RGBA values
				unsigned char blue = static_cast<unsigned char>(pixel[0]);
				unsigned char green = static_cast<unsigned char>(pixel[1]);
				unsigned char red = static_cast<unsigned char>(pixel[2]);
				unsigned char alpha = static_cast<unsigned char>(pixel[3]);

				// Your code to use RGBA values goes here
				// ...

				// Example: Print RGBA values
				std::cout << "Pixel at (" << x << ", " << y << "): ";
				std::cout << "R=" << static_cast<int>(red) << ", ";
				std::cout << "G=" << static_cast<int>(green) << ", ";
				std::cout << "B=" << static_cast<int>(blue) << ", ";
				std::cout << "A=" << static_cast<int>(alpha) << std::endl;
			}
		}

		//Using the size, we want to get the correct tile off the grid using the provided coordinates, then assuming we know the tile is in the view of the camera, we call draw.
		// I think what we have to do is potentially return a 16x16 grid of pixel data to render - but definitely don't store it in the Tile itself.
		// 
		// 
		//Camera is size of the window. Determine where the camera is by scene width subtracted from the scene width and same with height. - Assumes player is ALWAYS middle of screen.
		//Make camera later.

		//Note to move: player internal tile position is not dividing the player position by 16, but modulo by 16.
	}
};