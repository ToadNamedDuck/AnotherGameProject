//This is a base class that will be an interface for all sprites - enemies, tiles, etc.
class iSprite
{
protected:
	//width and height in pixels
	int size;
	//Following 2 are for pulling the sprite off of the spritesheet
	int sprite_start_x;
	int sprite_start_y;
public:
	iSprite(int s, int x, int y) : size(s), sprite_start_x(x), sprite_start_y(y) {}
	virtual ~iSprite() {};
};