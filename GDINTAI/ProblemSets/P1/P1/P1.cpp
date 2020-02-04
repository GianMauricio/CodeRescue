//Gian Mauricio
//11839651 X_22

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <unordered_map>
#include <string>

using namespace std;

enum TileType { CLEAN = 0, DIRTY = 1 };
class Tile {
public:
	Tile() {};
	~Tile() {};

	bool isClean()
	{
		if (type == TileType::CLEAN) {
			return true;
		}

		return false;
	}

	void clean() {
		type = CLEAN;
	}

	void contaminate() {
		type = DIRTY;
	}

	TileType getType() {
		return type;
	}
private:
	TileType type = CLEAN;
};
class Grid {
public:
	Grid(int width, int height, int contaminant) {
		Width = width;
		Height = height;
		contaminated = contaminant;

		//Build initial Map
		for (int i = 0; i < Height; i++) {
			vector<Tile*> Row;
			for (int j = 0; j < Width; j++) {
				Row.push_back(new Tile());
			}
			Map.push_back(Row);
		}

		//Contaminate certain tiles in the map until quota is met
		srand(time(NULL));
		int dustBunnies = 0;
		int randomRow, randomCol;
		while (dustBunnies < contaminated) {
			randomCol = rand() % Height;
			randomRow = rand() % Width;

			if (Map[randomRow][randomCol]->isClean()) {
				Map[randomRow][randomCol]->contaminate();
				dustBunnies++;
			}
		}
	}
	~Grid() {};
	bool isAllClean() {
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				if (!(Map[Height][Width]->isClean())) {
					return false;
				}
			}
		}

		return true;
	}
	void clean(int Horizontal, int Vertical) {
		Map[Vertical][Horizontal]->clean();
	}
	void DisplayGrid() {
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				switch (Map[i][j]->getType()) {
				case TileType::CLEAN:
					cout << "-";
					break;
				case TileType::DIRTY:
					cout << "*";
					break;
				}

				cout << " ";
			}
			cout << endl;
		}
	}
private:
	int Width, Height, contaminated;
	vector<vector<Tile*>> Map;
};

class DumbRoomba {
	//Direct pathing. If dirty then clean, otherwise, move.
public:
	//POSITION: Move to nearest corner (Set default direction and Bend direction)
	//DRIVE: Move in default direction
	//STEER: Move in Bend direction and flip default direction
	//SUCC:                 C   L   E   A   N
	enum Action {POSITION = 0, DRIVE = 1, STEER = 2, SUCC = 3};
	DumbRoomba(int posX, int posY, pair<int, int> Limits) {
		index.first = posX;
		index.second = posY;

		Edges = Limits;

		//First Element: Move Order
		//Second Element: Current Tile Status
		//Note: AI will first find the nearest corner, then it will path to the opposite corner
		ActionTable.emplace("Position", POSITION);
		ActionTable.emplace("Drive Dirty", SUCC);
		ActionTable.emplace("Drive Clean", DRIVE);
		ActionTable.emplace("Steer Dirty", SUCC);
		ActionTable.emplace("Steer Clean", STEER);

		if (index.first > (Edges.first/2)) {/*Closest corner is Rightmost*/
			OriginCorner.first = Edges.first - 1;
		}

		else {/*Closest corner is the leftmost*/
			OriginCorner.first = 0;
		}
	}

	void AILogic(string order) {

	}
private:
	pair <int, int> index;
	pair <int, int> Edges;
	pair <int, int> OriginCorner;
	unordered_map <string, Action> ActionTable;
};

class SmartRoomba {
	//Djiktras algorithm, dirtiest path (increased edge weight from pathing to clean tiles).
};

void problem_p1(string input) {
	//Parse string input into seperate strings
	string Parse[] = {"", "", "", ""};
	int nCount = 0;
	for (char x : input) {
		if (x == ' ') { nCount++; continue; }

		else{
			Parse[nCount].append(1, x);
		}
	}

	//Build the grid
	Grid Maze(stoi(Parse[0]), stoi(Parse[0]), stoi(Parse[1]));
	Maze.DisplayGrid();

	//Create the Agent
	pair<int, int> limit = { stoi(Parse[0]), stoi(Parse[0]) };
	DumbRoomba Roomba(stoi(Parse[2]), stoi(Parse[3]), limit);
	//Agent must now position themselves
	Roomba.AILogic("Position");
	while (!Maze.isAllClean()) {
		

	}
}

//Smart Roomba
void problem_p2(string input) {
	
}

int main()
{
	string Test1 = "10 16 0 0";
	problem_p1(Test1);

	string Test2;
	problem_p2(Test2);
}
