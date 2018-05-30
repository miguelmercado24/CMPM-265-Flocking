// Miguel Ocana Mercado
//CMPM 265
//Flocking

//#include "Vehicle.h"
#include"Flock.h"

int Flock::getSize() const 
{ 
	return flock.size(); 
}

Vehicle Flock::getBoid(int i) 
{ 
	return flock[i]; 
}

void Flock::addBoid(Vehicle b) 
{ 
	flock.push_back(b); 
}

// Runs the run function for every boid in the flock checking against the flock itself. Which in turn applies all the rules to the flock.

void Flock::flocking()
{

	for (int i = 0; i < flock.size(); i++)
	{
		//Checking for a range instead of the whole flock

		for (int j = 0; j < flock.size(); j++)
		{
			if (flock[i].position.distance(flock[j].position) <= abs(20))
			{
				flock[i].Run(flock);
			}
		}
	}
}


void Flock::addDesSep()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesSep(1);
	}
}


void Flock::subDesSep()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesSep(-1);
	}
}


void Flock::addDesAli()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesAli(1);
	}
}

void Flock::subDesAli()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesAli(-1);
	}
}

void Flock::addDesCoh()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesCoh(1);
	}
}


void Flock::subDesCoh()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setDesCoh(-1);
	}
}


void Flock::addSepW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setSepW(.1);
	}
}


void Flock::subSepW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setSepW(-.1);
	}
}


void Flock::addAliW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setAliW(.1);
	}
}


void Flock::subAliW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setAliW(-.1);
	}
}


void Flock::addCohW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setCohW(.1);
	}
}


void Flock::subCohW()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].setCohW(-.1);
	}
}
