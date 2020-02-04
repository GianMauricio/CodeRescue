#include "BaseRunner.h"
#include <iostream>

using namespace sf;

const Time BaseRunner::PER_FRAME = seconds(1.f/60.f);
BaseRunner::BaseRunner() : window(VideoMode(WIDTH, HEIGHT), "I wanna commit sUwUicide"){
	if (!Image.loadFromFile("Assets\\Eagle.png")) {
		cout << "Failed to load Plane" << endl;
	}
	fSpeed = 10;
	Body.setTexture(Image);
}

void BaseRunner::run(){
	Clock clock;
	Time FixedUpdate = Time::Zero;

	while (window.isOpen())
	{
		Time elapsedTime = clock.restart();
		FixedUpdate += elapsedTime;

		while (FixedUpdate > PER_FRAME) {
			FixedUpdate -= PER_FRAME;

			processEvents();
			update(PER_FRAME);
		}

		render();
		cout << "direction" << direction << endl;
	}
}

void BaseRunner::render()
{
	window.clear();
	window.draw(Body);
	window.display();
}

void BaseRunner::processEvents()
{
	Event event;
	while (window.pollEvent(event)){
		if (event.type == Event::Closed)
			window.close();

		//Impel movement from key direction
		if (event.type == Event::KeyPressed) {
			HandleKey(event.key.code, true);
		}

		//Dispel movement from key direction
		if (event.type == Event::KeyReleased) {
			HandleKey(event.key.code, false);
		}

		//Set Destination vector from mouse
		if (event.type == Event::MouseButtonPressed) {
			HandleMouse(Vector2f(Mouse::getPosition(window)));
		}
	}
	
}

void BaseRunner::update(Time ElapsedTime)
{
	Body.setOrigin(24.f, 34.f);
	Vector2f offset;
	switch (direction) {
	case Dir::UP:
		offset = { 0, -1 * fSpeed };
		Body.setRotation(0);
		break;

	case Dir::DOWN:
		offset = { 0, fSpeed };
		Body.setRotation(180);
		break;

	case Dir::LEFT:
		offset = { -1 * fSpeed, 0 };
		Body.setRotation(270);
		break;

	case Dir::RIGHT:
		offset = { fSpeed, 0 };
		Body.setRotation(90);
		break;

	//Special case if the mouse was used to generate the destination
	case Dir::SEEK:
		if (abs(Body.getPosition().x - Destination.x) > 10 || abs(Body.getPosition().y - Destination.y > 10)) {
			offset = { (DiffVec.x / Distance) * fSpeed, (DiffVec.y / Distance) * fSpeed };
		}

		else { 
			offset = { 0, 0 }; 
		}
		
		break;
	}
	Body.move(offset);
}

void BaseRunner::HandleKey(Keyboard::Key key, bool isPressed)
{
	if (isPressed) {
		if (key == Keyboard::W) {
			cout << "W pressed";

			direction = UP;
		}

		if (key == Keyboard::A) {
			cout << "A pressed";

			direction = LEFT;
		}

		if (key == Keyboard::S) {
			cout << "S pressed";

			direction = DOWN;
		}

		if (key == Keyboard::D) {
			cout << "D pressed";

			direction = RIGHT;
		}

		if (key == Keyboard::Escape) {
			window.close();
		}
	}

	else {
		if (key == Keyboard::W) {
			cout << "W released";
		}

		if (key == Keyboard::A) {
			cout << "A released";
		}

		if (key == Keyboard::S) {
			cout << "S released";
		}

		if (key == Keyboard::D) {
			cout << "D released";
		}

		direction = NONE;
	}
}
void BaseRunner::HandleMouse(Vector2f mousePos)
{
	direction = Dir::SEEK;
	Destination = mousePos;
	DiffVec = Destination - Body.getPosition();
	Distance = sqrt((DiffVec.x * DiffVec.x) + (DiffVec.y * DiffVec.y));
	Rotation = atan2(DiffVec.y, DiffVec.x);
	Rotation = double(Rotation) * 180 / 3.141592;
	Body.setRotation(90);
	Body.setRotation(Body.getRotation() + Rotation);
}
