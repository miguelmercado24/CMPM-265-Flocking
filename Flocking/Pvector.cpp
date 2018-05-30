// Miguel Ocana Mercado
//CMPM 265
//Flocking
#define _USE_MATH_DEFINES
#include"Pvector.h"

// Sets values of x and y for Pvector

void Pvector::set(float i, float o)
{
	x = i;
	y = o;
}

void Pvector::addVector(Pvector v)
{
	x += v.x;
	y += v.y;
}

// Adds to a Pvector by a constant number

void Pvector::addScalar(float s)

{
	x += s;
	y += s;
}

// Subtracts 2 vectors

void Pvector::subVector(Pvector v)
{
	x -= v.x;
	y -= v.y;
}

// Subtracts two vectors and returns the difference as a vector

Pvector Pvector::subTwoVector(Pvector v, Pvector v2)
{
	Pvector tmp;
	v.x -= v2.x;
	v.y -= v2.y;
	tmp.set(v.x, v.y);
	return tmp;
}

// Adds to a Pvector by a constant number

void Pvector::subScalar(float s)
{
	x -= s;
	y -= s;
}

// Multiplies 2 vectors

void Pvector::mulVector(Pvector v)
{
	x *= v.x;
	y *= v.y;
}

// Adds to a Pvector by a constant number

void Pvector::mulScalar(float s)

{
	x *= s;
	y *= s;
}

// Divides 2 vectors

void Pvector::divVector(Pvector v)
{
	x /= v.x;
	y /= v.y;
}

// Adds to a Pvector by a constant number

void Pvector::divScalar(float s)
{
	x /= s;
	y /= s;
}


void Pvector::limit(double max)
{
	double size = magnitude();

	if (size > max) 
	{
		set(x / size, y / size);
	}
}

// Calculates the distance between the first Pvector and second Pvector

float Pvector::distance(Pvector v) const
{
	float dx = x - v.x;
	float dy = y - v.y;
	float dist = sqrt(dx*dx + dy*dy);
	return dist;
}

// Calculates the dot product of a vector

float Pvector::dotProduct(Pvector v) const
{
	float dot = x * v.x + y * v.y;
	return dot;
}

// Calculates magnitude of referenced object

float Pvector::magnitude() const
{
	return sqrt(x*x + y*y);
}

void Pvector::setMagnitude(float x)
{
	normalize();
	mulScalar(x);
}

// Calculate the angle between Pvector 1 and Pvector 2

float Pvector::angleBetween(Pvector v) const
{
	if (x == 0 && y == 0) return 0.0f;
	if (v.x == 0 && v.y == 0) return 0.0f;

	double dot = x * v.x + y * v.y;

	double v1mag = sqrt(x * x + y * y);

	double v2mag = sqrt(v.x * v.x + v.y * v.y);

	double amt = dot / (v1mag * v2mag); //dot product / product of magnitudes gives amt

	if (amt <= -1) {

		return M_PI;

	}

	else if (amt >= 1) {

		return 0;

	}

	float tmp = acos(amt);

	return tmp;

}


// normalize divides x and y by magnitude if it has a magnitude.

void Pvector::normalize()
{
	float m = magnitude();

	if (m > 0)
	{
		set(x / m, y / m);
	}

	else {
		set(x, y);
	}

}


// Creates and returns a copy of the Pvector used as a parameter

Pvector Pvector::copy(Pvector v)
{
	Pvector copy(v.x, v.y);
	return copy;
}
