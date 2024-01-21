//A scene will serve as a classed object that represents a level, with a grid-like structure that takes "tiles" to fill slots. It could also take a list of enemies with predefined positions.
#include <string>
class Scene {
private:
	std::string Name;
	//TilesWidth is how many tiles across the scene should be - Minimum 1 tile.
	int TilesWidth;
	//TilesHeight is how many tiles up and down the scene should be - Minimum 1 tile.
	int TilesHeight;
	//Tile TileArray[] - Tiles can be defined in their own file and included here
	//Enemy EnemyArray[] - See above

	//May need both: boolean for displaying the name (to turn off showing it when you transition to a new scene in the same area/dungeon
	// and potentially an array of "portals"/Doors/exits and what scene they lead to

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

Scene newScene = Scene("New Scene", 5, 4);