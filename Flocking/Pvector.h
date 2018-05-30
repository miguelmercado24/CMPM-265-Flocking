// Miguel Ocana Mercado
//CMPM 265
//Flocking
#pragma once

#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;


class Pvector {

public:
	
	float x,y;

	//Constructors

	Pvector() {}

	Pvector(float xComp, float yComp)
	{
		x = xComp;
		y = yComp;
	}

	void set(float x, float y);

	//Scaling functions scale a vector by a float

	void addVector(Pvector v);

	void addScalar(float x);

	void subVector(Pvector v);

	static Pvector subTwoVector(Pvector v, Pvector v2);

	void subScalar(float x);

	void mulVector(Pvector v);

	void mulScalar(float x);

	void divVector(Pvector v);

	void divScalar(float x);

	void limit(double max);


	//Calculating Functions

	float distance(Pvector v) const;

	float dotProduct(Pvector v) const;

	float magnitude() const;

	void setMagnitude(float x);

	float angleBetween(Pvector v) const;

	void normalize();


	static Pvector copy(Pvector v);

};