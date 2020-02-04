#include "Plane.h"

Plane::Plane()
{
	if (!tImage.loadFromFile("Assets\\Eagle.png"));
}

void Plane::Move(Vector2f Destination)
{
	//First rotate the plane to face the destination vector
	
}
