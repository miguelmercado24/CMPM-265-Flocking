#include "Flock.h"
#include "VehicleSystem.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#define BOID_AMOUNT 50

using namespace sf;

// Construct window using SFML

VehicleSystem::VehicleSystem()
{
	//Setting the window settings here instead of main

	VideoMode desktop = VideoMode::getDesktopMode();
	this->_window_height = desktop.height;
	this->_window_width = desktop.width;
	this->_window.create(sf::VideoMode(_window_width, _window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);

}

// Run the simulation. Run creates the boids that we'll display, checks for user input, and updates the view

void VehicleSystem::Run()
{

	for (int i = 0; i < BOID_AMOUNT; i++) 
		{
			createBoid(_window_width / 2, _window_height / 2,Color::Green, Color::Blue);
		}

	//Whole block of text can probably simplified in a function as well in order to remove redundancy

	Font font;
	font.loadFromFile("consola.ttf");

	Text fpsText("Frames per Second: ", font);
	fpsText.setFillColor(Color::White);
	fpsText.setCharacterSize(12);
	fpsText.setPosition(_window_width - 162, 0);

	Text vehicleText("Total Boid Count: " + to_string(flock.getSize()), font);
	vehicleText.setFillColor(Color::White);
	vehicleText.setCharacterSize(12);
	vehicleText.setPosition(_window_width - 155, 36);

	Text dSepText("Separation Amount: " + to_string(flock.getBoid(0).getDesSep()), font);
	dSepText.setFillColor(Color::White);
	dSepText.setCharacterSize(12);
	dSepText.setPosition(_window_width - 162, 60);

	Text dAliText("Alignment Amount: " + to_string(flock.getBoid(0).getDesAli()), font);
	dAliText.setFillColor(Color::White);
	dAliText.setCharacterSize(12);
	dAliText.setPosition(_window_width - 155, 72);

	Text dCohText("Cohesion Amount: " + to_string(flock.getBoid(0).getDesCoh()), font);
	dCohText.setFillColor(Color::White);
	dCohText.setCharacterSize(12);
	dCohText.setPosition(_window_width - 148, 84);

	Text dSepWText("Separation Weight: " + to_string(flock.getBoid(0).getSepW()), font);
	dSepWText.setFillColor(Color::White);
	dSepWText.setCharacterSize(12);
	dSepWText.setPosition(_window_width - 162, 108);

	Text dAliWText("Alignment Weight: " + to_string(flock.getBoid(0).getAliW()), font);
	dAliWText.setFillColor(Color::White);
	dAliWText.setCharacterSize(12);
	dAliWText.setPosition(_window_width - 155, 120);

	Text dCohWText("Cohesion Weight: " + to_string(flock.getBoid(0).getCohW()), font);
	dCohWText.setFillColor(Color::White);
	dCohWText.setCharacterSize(12);
	dCohWText.setPosition(_window_width - 148, 132);


	sf::Clock clock;


	while (_window.isOpen()) 
	{
		float currentTime = clock.restart().asSeconds();
		float fps = 1 / currentTime; // 1 / refresh time = estimate of fps
		InputManager();
		Render(fpsText, fps, vehicleText,dSepText, dAliText, dCohText, dSepWText, dAliWText, dCohWText);
	}

}



void VehicleSystem::InputManager()

{
	Event event;

	while (_window.pollEvent(event)) 
	{
		// Implemented alternate ways to close the window. (Pressing the escape, X, and BackSpace key also close the program.)

		if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X))
		{
			_window.close();
		}

		// Event to create new "prey" boids

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) 
		{
			createBoid(rand() % _window_width, rand() % _window_height, Color::Green, Color::Blue);
		}

		//Events for modifying the values in Boids

		//Increase Desired Separation
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
		{
			flock.addDesSep();
		}

		//Decrease Desired Separation
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
		{
			flock.subDesSep();
		}


		//Modify Alignment
		//Increase Desired Alignment
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
		{
			flock.addDesAli();
		}


		//Decrease Desired Alignment
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
		{
			flock.subDesAli();
		}


		//Modify Cohesion
		//Increase Desired Cohesion
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
		{
			flock.addDesCoh();
		}


		//Decrease Desired Cohesion
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
		{
			flock.subDesCoh();
		}


		// Adding Separation
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
		{
			flock.addSepW();
		}


		//Decreasing Separation
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::J)
		{
			flock.subSepW();
		}


		//Adding Alignment Function
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O)
		{
			flock.addAliW();
		}


		//Substracting Alignment Function
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K)
		{
			flock.subAliW();
		}


		//Adding Cohesion Function
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		{
			flock.addCohW();
		}

		//Subtracting Alignment Function
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
		{
			flock.subCohW();
		}


		//Closing the window
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
		{
			_window.close();
			VehicleSystem temp;;
			temp.Run();
		}
	}


	//Adding a Vehicle boid if mouse is clicked.

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		// Gets mouse coordinates, sets that as the location of the boid and the shape

		sf::Vector2i mouseCoords = sf::Mouse::getPosition(_window);
		createBoid(mouseCoords.x, mouseCoords.y, Color::Red, Color::Yellow);
	}
}



void VehicleSystem::createBoid(float x, float y, Color fillColor, Color outlineColor)
{
	int size = rand() % 10 - 2;
	Vehicle b (x, y);
	sf::CircleShape boidShape(size, 3);
	boidShape.setPosition(x, y);
	boidShape.setFillColor(fillColor);
	boidShape.setOutlineColor(outlineColor);
	boidShape.setOutlineThickness(.5);

	flock.addBoid(b);
	boidShapes.push_back(boidShape);

	// New Shape is drawn

	_window.draw(boidShapes[boidShapes.size() - 1]);

}


//Method of passing text needs refactoring

void VehicleSystem::Render(Text fpsText, float fps, Text boidText,
Text dSepText, Text dAliText, Text dCohText, Text dSepWText,Text dAliWText,Text dCohWText)
{
	_window.clear();

	//Updating and drawing text can possibly be put in it's own function as well

	fpsText.setString("Frames per Second: " + to_string(int(fps + 0.5)));
	_window.draw(fpsText);

	boidText.setString("Total Boid Count: " + to_string(flock.getSize()));
	_window.draw(boidText);

	dSepText.setString("Separation Amount: " + to_string(int(flock.getBoid(0).getDesSep() + 0.5)));
	_window.draw(dSepText);

	dAliText.setString("Alignment Amount: " + to_string(int(flock.getBoid(0).getDesAli() + 0.5)));
	_window.draw(dAliText);

	dCohText.setString("Cohesion Amount: " + to_string(int(flock.getBoid(0).getDesCoh() + 0.5)));
	_window.draw(dCohText);

	dSepWText.setString("Separation Weight: " + to_string(flock.getBoid(0).getSepW()));
	_window.draw(dSepWText);

	dAliWText.setString("Alignment Weight: " + to_string(flock.getBoid(0).getAliW()));
	_window.draw(dAliWText);

	dCohWText.setString("Cohesion Weight: " + to_string(flock.getBoid(0).getCohW()));
	_window.draw(dCohWText);


	// Draws all of the Boids out, and applies functions that are needed to update.

	for (int i = 0; i < boidShapes.size(); i++) 
	{
		_window.draw(boidShapes[i]);

		// Matches up the location of the shape to the boid

		boidShapes[i].setPosition(flock.getBoid(i).position.x, flock.getBoid(i).position.y);


		// Calculates the angle where the velocity is pointing so that the triangle turns towards it.

		float theta = flock.getBoid(i).getAngle(flock.getBoid(i).velocity);
		boidShapes[i].setRotation(theta);


		// Prevent boids from moving off the screen through wrapping

		// If boid exits right boundary

		if (boidShapes[i].getPosition().x > _window_width)

			boidShapes[i].setPosition(boidShapes[i].getPosition().x - _window_width, boidShapes[i].getPosition().y);

		// If boid exits bottom boundary

		if (boidShapes[i].getPosition().y > _window_height)

			boidShapes[i].setPosition(boidShapes[i].getPosition().x, boidShapes[i].getPosition().y - _window_height);

		// If boid exits left boundary

		if (boidShapes[i].getPosition().x < 0)

			boidShapes[i].setPosition(boidShapes[i].getPosition().x + _window_width, boidShapes[i].getPosition().y);

		// If boid exits top boundary

		if (boidShapes[i].getPosition().y < 0)

			boidShapes[i].setPosition(boidShapes[i].getPosition().x, boidShapes[i].getPosition().y + _window_height);

	}

	// Applies the three rules to each boid in the flock and changes them accordingly.

	flock.flocking();
	_window.display();

}