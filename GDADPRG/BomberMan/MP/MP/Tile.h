#include <SFML/Graphics.hpp>

using namespace sf;
class Tile{
public:
	Tile(int x, int y);
	~Tile();

	enum TileType {Empty = 0, Wall = 1, Rock = 2, Exit = 3};
private:
	Vector2i coordinates;
	TileType type;

};

