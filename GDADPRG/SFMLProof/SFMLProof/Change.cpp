#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(200, 200), "Changer");

	//Holds all possible colors;
	vector<Color> ColorSet;
	ColorSet.push_back(Color::Red);
	ColorSet.push_back(Color::Green);
	ColorSet.push_back(Color::Blue);
	ColorSet.push_back(Color::Yellow);

	//All Current shapes
	CircleShape Circle(100.0f);
	CircleShape Triangle(100.0f, 3);
	RectangleShape Box(Vector2f{ 100 , 100 });
	Box.setPosition(Vector2f{ 50, 50 });

	//Tracks current shape and color
	int nShape = 0,
		nColor = 0;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed) {
				nShape++;
				nShape = nShape % 3;
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Space) {
					nColor++;
					nColor = nColor % 4;
				}
			}
		}

		window.clear();
		switch (nShape) {
		case 0:/*Draw Circle*/
			Circle.setFillColor(ColorSet[nColor]);
			window.draw(Circle);
			break;

		case 1:/*Draw Triangle*/
			Triangle.setFillColor(ColorSet[nColor]);
			window.draw(Triangle);
			break;

		case 2:/*Draw Box*/
			Box.setFillColor(ColorSet[nColor]);
			window.draw(Box);
			break;
		}
		window.display();
	}

	return 0;
}