//A scene will serve as a classed object that represents a level, with a grid-like structure that takes "tiles" to fill slots. It could also take a list of enemies with predefined positions.
#include <string>
class Scene {
private:
	std::string Name;
	//TilesWidth is how many tiles across the scene should be - Minimum 1 tile
	int TilesWidth;
	int TilesHeight;
	//Tile TileArray[] - Tiles can be defined in their own file and included here
	//Enemy EnemyArray[] - See above

public:
	Scene(std::string Name, int TilesWidth, int TilesHeight)
		:Name(Name)
	{
		if (TilesWidth < 1)
		{
			this->TilesWidth = 1;
		}
		else this->TilesWidth = TilesWidth;

		if (TilesHeight < 1)
		{
			this->TilesHeight = 1;
		}
		else this->TilesHeight = TilesHeight;
	}
};