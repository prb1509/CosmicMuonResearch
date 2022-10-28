#include "PhysList.hh"

PhysList::PhysList() //constructor
{
	RegisterPhysics(new G4EmStandardPhysics());
	//add any other physics lists below
	//for example:
	//RegisterPhysics(new G4DecayPhysics());
};

PhysList::~PhysList() {}; //destructor