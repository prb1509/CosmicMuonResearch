#include "ParticleGenerator.hh"
#include "Randomize.hh"

ParticleGenerator::ParticleGenerator() : gps{new G4GeneralParticleSource} //constructor
{
};

ParticleGenerator::~ParticleGenerator() //destructor
{
	delete gps;
};

void ParticleGenerator::GeneratePrimaries(G4Event* Event) 
{	
	//particle source implementation
	gps->GeneratePrimaryVertex(Event);
};