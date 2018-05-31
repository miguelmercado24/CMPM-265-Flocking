// Miguel Ocana Mercado
//CMPM 265
//Flocking
#pragma once
#include "Flock.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class VehicleSystem {

private:

	sf::RenderWindow _window;
	int _window_width;
	int _window_height;
	Flock flock;
	float boidsSize;

	vector<sf::CircleShape> boidShapes;

	void Render(Text text, float fps, Text text2, Text text3, Text text4,

		Text text5, Text text6, Text text7, Text text8);

// Creating the boids

	void createBoid(float x, float y,Color fillColor, Color outlineColor);
	void InputManager();

public:

	// For console instructions

	VehicleSystem();
	void Run();

};