// Miguel Ocana Mercado
//CMPM 265
//Flocking
#define _USE_MATH_DEFINES
#include "Vehicle.h"
#include <cmath>
#include <vector>

VideoMode desktopTemp = VideoMode::getDesktopMode();
const int window_height = desktopTemp.height;
const int window_width = desktopTemp.width;


Vehicle::Vehicle(float x, float y) 
{
	acceleration = Pvector(0, 0);
	float angle = (rand() % 360) * 3.14f / 180.f;
	velocity = Pvector (cos(angle), sin(angle));
	position = Pvector(x, y);
	r = 2.0;
	maxSpeed = 2;
	maxForce = 0.03;

	desSep = 22;
	desAli = 70;
	desCoh = 25;
	SepW = 1.5;
	AliW = 1.0;
	CohW = 1.0;
}

void Vehicle:: Run(vector<Vehicle> boids)
{
	Flock(boids);
	Update();
	Borders();
}

void Vehicle::ApplyForce(Pvector force)
{
	acceleration.addVector(force);
}

void Vehicle::Flock(vector<Vehicle> boids)
{
	Pvector sep = Separate(boids);
	Pvector ali = Align(boids);
	Pvector coh = Cohesion(boids);

	// Arbitrarily weight these forces

	sep.mulScalar(SepW);
	ali.mulScalar(AliW);
	coh.mulScalar(CohW);

	// Add the force vectors to acceleration
	ApplyForce(sep);
	ApplyForce(ali);
	ApplyForce(coh);
}

void Vehicle::Update()
{
	//Slow down not as abrupt
	acceleration.mulScalar(.35);

	// Update velocity
	velocity.addVector(acceleration);

	// Limit speed
	velocity.limit(maxSpeed);
	position.addVector(velocity);

	// Reset accelertion to 0 each cycle
	acceleration.mulScalar(0);
}

Pvector Vehicle::Seek(Pvector target)
{
	Pvector desired;
	desired.subVector(target);  // A vector pointing from the location to the target
	
	// Scale to maximum speed
	desired.normalize();
	desired.mulScalar(maxSpeed);

	// Steering = Desired minus Velocity
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(maxForce);  // Limit to maximum steering force

	return acceleration;
}

void Vehicle::Borders()
{
	if (position.x < 0)    position.x += window_width;
	if (position.y < 0)    position.y += window_height;
	if (position.x > window_width) position.x -= window_width;
	if (position.y > window_height) position.y -= window_height;
}

Pvector Vehicle::Separate(vector<Vehicle> boids)
{
	// Distance of field of vision for separation between boids
	float desiredseparation = desSep;
	Pvector steer(0, 0);
	int count = 0;

	// For every boid in the system, check if it's too close

	for (int i = 0; i < boids.size(); i++) 
	{
		// Calculate distance from current boid to boid we're looking at

		float d = position.distance(boids[i].position);

		// If this is a fellow boid and it's too close, move away from it

		if ((d > 0) && (d < desiredseparation)) 
		{
			Pvector diff(0, 0);
			diff = diff.subTwoVector(position, boids[i].position);
			diff.normalize();
			diff.divScalar(d);      // Weight by distance
			steer.addVector(diff);
			count++;
		}
	}

	// Adds average difference of location to acceleration

	if (count > 0)

		steer.divScalar(static_cast<float>(count));

	if (steer.magnitude() > 0) 
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}

	return steer;
}

Pvector Vehicle::Align(vector<Vehicle> boids)
{
	float neighbordist = desAli; // Field of vision
	Pvector sum(0, 0);
	int count = 0;
	
	for (int i = 0; i < boids.size(); i++) 
	{

		float d = position.distance(boids[i].position);

		if ((d > 0) && (d < neighbordist))
		{ 
			sum.addVector(boids[i].velocity);
			count++;
		}
	}

	// If there are boids close enough for alignment...

	if (count > 0) 
	{
		sum.divScalar(static_cast<float>(count));
		sum.normalize();            
		// Implement Reynolds: Steering = Desired - Velocity
		sum.mulScalar(maxSpeed);    
		Pvector steer;
		steer = steer.subTwoVector(sum, velocity); //sum = desired(average)
		steer.limit(maxForce);
		return steer;
	}

	else 
	{
		Pvector temp(0, 0);
		return temp;
	}
}

Pvector Vehicle::Cohesion(vector<Vehicle> boids)
{
	float neighbordist = desCoh;
	Pvector sum(0, 0);
	int count = 0;

	for (int i = 0; i < boids.size(); i++) 
	{
		float d = position.distance(boids[i].position);

		if ((d > 0) && (d < neighbordist)) 
		{
			sum.addVector(boids[i].position);
			count++;
		}

	}

	if (count > 0) 
	{
		sum.divScalar(count);
		return Seek(sum);

	}

	else 
	{
		Pvector temp(0, 0);
		return temp;
	}
}

float Vehicle::getDesSep() const { return desSep; }

float Vehicle::getDesAli() const { return desAli; }

float Vehicle::getDesCoh() const { return desCoh; }

float Vehicle::getSepW() const { return SepW; }

float Vehicle::getAliW() const { return AliW; }

float Vehicle::getCohW() const { return CohW; }

void Vehicle::setDesSep(float x) { desSep += x; }

void Vehicle::setDesAli(float x) { desAli += x; }

void Vehicle::setDesCoh(float x) { desCoh += x; }

void Vehicle::setSepW(float x) { SepW += x; }

void Vehicle::setAliW(float x) { AliW += x; }

void Vehicle::setCohW(float x) { CohW += x; }

float Vehicle::getAngle(Pvector v) const
{
	// From the definition of the dot product

	float angle = static_cast<float>(atan2(v.x, -v.y) * 180 / M_PI);
	return angle;
}