#ifndef PHYSLIST_HH
#define PHYSLIST_HH

#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"
#include "G4Electron.hh"
#include "G4MuonMinus.hh"
#include "G4EmStandardPhysics.hh"
#include "QBBC.hh"
#include "Shielding.hh"
#include "G4DecayPhysics.hh"

class PhysList :public G4VModularPhysicsList
{
public:
	PhysList(); //constructor
	~PhysList(); //destructor
};
#endif 
