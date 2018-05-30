// Miguel Ocana Mercado
//CMPM 265
//Flocking
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Pvector.h"

using namespace std;
using namespace sf;

class Vehicle {

public:
	Pvector position;
	Pvector acceleration;
	Pvector velocity;
	
	float r;
	float maxForce;  //Maximum steering force
	float maxSpeed;	//Maximum speed

	Vehicle(float x, float y);

	void Run(vector<Vehicle> boids);
	void ApplyForce(Pvector force);
	void Flock(vector<Vehicle> boids);
	void Update();
	Pvector Seek(Pvector target);
	void Borders();
	Pvector Separate(vector<Vehicle> boids);
	Pvector Align(vector<Vehicle> boids);
	Pvector Cohesion(vector<Vehicle> boids);

	float desSep;
	float desAli;
	float desCoh;
	float SepW;
	float AliW;
	float CohW;

	float getDesSep() const;
	float getDesAli() const;
	float getDesCoh() const;
	float getSepW() const;
	float getAliW() const;
	float getCohW() const;

	void setDesSep(float x);
	void setDesAli(float x);
	void setDesCoh(float x);
	void setSepW(float x);
	void setAliW(float x);
	void setCohW(float x);


private:


};
