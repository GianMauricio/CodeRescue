#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class BaseRunner : private NonCopyable{
public:
	static const Time PER_FRAME;
	static const int HEIGHT = 768,
		WIDTH = 1024;

	enum Dir {NONE = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, SEEK};

	BaseRunner();
	void run();

private:
	Time ticks;
	RenderWindow window;
	Dir direction;
	Texture Image;
	Sprite Body;
	Vector2f Destination, DiffVec;
	float fSpeed, Distance, Rotation;

	void render();
	void processEvents();
	void update(Time ElapsedTime);

	void HandleKey(Keyboard::Key key, bool isPressed);
	void HandleMouse(Vector2f mousePos);
};

