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
	uint16_t reserved1;
	uint16_t reserved2;
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
struct BitMasks {
	uint32_t redMask;
	uint32_t greenMask;
	uint32_t blueMask;
	uint32_t alphaMask;
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
		std::cout << size << " " << sprite_start_x << " " << sprite_start_y << " " << std::endl;
	}
	void showMask()
	{
		for (int row = 0; row < 16; row++)
		{
			std::bitset<16> bitmaskBits(bitmask[row]);
			std::cout << bitmaskBits << std::endl;
		}
	}

	void getPixels() {
		//Open the overworld.bmp file for now. We can use an enum param later to choose which file to open.
		std::ifstream file("Overworld.bmp", std::ios::binary);

		//Read the bmpHeader
		BMPHeader bmpHeader;
		file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));
		std::cout << "--------BMP HEADER START--------" << std::endl;
		std::cout << "Signature: " << bmpHeader.signature << std::endl;//Should be "BM"
		std::cout << "File Size: " << bmpHeader.fileSize << std::endl;//Bytes
		std::cout << "Reserved 1: " << bmpHeader.reserved1 << std::endl;//
		std::cout << "Reserved 2: " << bmpHeader.reserved2 << std::endl;//
		std::cout << "Data Offset Location: " << bmpHeader.dataOffset << std::endl;//
		std::cout << "--------BMP HEADER END--------" << std::endl;

		//Read dibHeader
		DIBHeader dibHeader;
		file.read(reinterpret_cast<char*>(&dibHeader), sizeof(DIBHeader));
		std::cout << "--------DIB HEADER START--------" << std::endl;
		std::cout << "Header Size: " << dibHeader.headerSize << std::endl;//V5
		std::cout << "Width: " << dibHeader.width << std::endl;//
		std::cout << "Height: " << dibHeader.height << std::endl;//
		std::cout << "Color Planes: " << dibHeader.colorPlanes << std::endl;//Should be 1
		std::cout << "Bit Depth: " << dibHeader.bitsPerPixel << std::endl;//Should be 32
		std::cout << "Compression: " << dibHeader.compressionMethod << std::endl;//Turns out the file is actually compression value 3 - BI_BITFIELDS
		std::cout << "Image Size: " << dibHeader.imageSize << std::endl;//
		std::cout << "Horizontal Resolution: " << dibHeader.horizontalResolution << std::endl;//
		std::cout << "Vertical Resolution: " << dibHeader.verticalResolution << std::endl;//
		std::cout << "Number of Colors: " << dibHeader.numColors << std::endl;//
		std::cout << "Important Colors: " << dibHeader.importantColors << std::endl;//Probably 0
		std::cout << "--------DIB HEADER END--------" << std::endl;

		//Retrieve bitmask info
		BitMasks masks;
		file.read(reinterpret_cast<char*>(&masks), sizeof(BitMasks));
		std::cout << "--------BITMASK INFORMATION START--------" << std::endl;
		std::cout << "Red Mask: " << std::hex << masks.redMask << std::endl;
		std::cout << "Green Mask: " << masks.greenMask << std::endl;
		std::cout << "Blue Mask: " << masks.blueMask << std::endl;
		std::cout << "Alpha Mask: " << masks.alphaMask << std::endl;
		std::cout << std::dec << "--------BITMASK INFORMATION END--------" << std::endl;

		if (dibHeader.height > 0) {
			dibHeader.height = -dibHeader.height;
		}

		//loop through the region selected and get the pixel data.
		int rowSize = floor((dibHeader.bitsPerPixel * dibHeader.width + 31) / 32) * 4;  // Calculate row size
		std::cout << "Row Size: " << rowSize << std::endl;
		//file.seekg(bmpHeader.dataOffset, std::ios::beg);

		for (int y = sprite_start_y; y < sprite_start_y + 16; y++) {
			for (int x = sprite_start_x; x < sprite_start_x + 16; x++) {
				// Calculate the byte position of the current pixel
				int bytePosition = y * rowSize + x * (dibHeader.bitsPerPixel / 8);
				std::cout << "Byte Position: " << bytePosition << std::endl;
				// Move the file reader to the correct position
				//file.seekg(bytePosition + bmpHeader.dataOffset, std::ios::beg);
				std::cout << "Pixel at X: " << x << " | Y: " << y << std::endl;
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