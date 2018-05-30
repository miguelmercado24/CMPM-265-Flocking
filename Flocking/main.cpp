// Miguel Ocana Mercado
//CMPM 265
//Flocking

#include"Flock.h"

int main()
{
	RenderWindow window(sf::VideoMode(800, 600), "CMPM 25 Flocking!");

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
