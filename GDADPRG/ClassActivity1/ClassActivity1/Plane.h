#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Plane : private NonCopyable {
private:
	Sprite sBody;
	Texture tImage;
	Vector2f vPos;
	
public:
	Plane();
	~Plane();
	void Move(Vector2f Destination);
};

