// Miguel Ocana Mercado
//CMPM 265
//Flocking
#pragma once

#include"Vehicle.h"

class Flock {

public:

	vector<Vehicle> flock;

	//Constructors

	Flock() {}

	// Accessor functions
	int getSize() const;
	Vehicle getBoid(int i);

	// Mutator Functions

	void addBoid(Vehicle b);
	void removeBoid();
	void flocking();

	//For accessing and modifying values

	void addDesSep();

	void subDesSep();

	void addDesAli();

	void subDesAli();

	void addDesCoh();

	void subDesCoh();

	void addSepW();

	void subSepW();

	void addAliW();

	void subAliW();

	void addCohW();

	void subCohW();

};