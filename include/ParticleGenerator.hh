#ifndef PARTICLEGENERATOR_HH
#define PARTICLEGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

class G4GeneralParticleSource;
class G4ParticleGun;

class ParticleGenerator:public G4VUserPrimaryGeneratorAction
{
public:
	ParticleGenerator(); //constructor
	~ParticleGenerator(); //destructor

	virtual void GeneratePrimaries(G4Event*);

	// method to access particle source
	const G4GeneralParticleSource* GetCurrentSource() const { return gps; }

private:
	G4GeneralParticleSource* gps{};
};

#endif 
