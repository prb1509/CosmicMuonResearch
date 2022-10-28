#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4VTouchable.hh"
#include "G4SDChargedFilter.hh"
#include "G4SDParticleFilter.hh"
#include "G4RunManager.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4TrackingManager.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
public:
	SensitiveDetector(G4String); //constructor
	~SensitiveDetector(); //destructor

private:
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};
#endif
