#ifndef SPHEREPART_HH
#define SPHEREPART_HH

#include "G4VPVParameterisation.hh"
#include "G4PVParameterised.hh"
#include "G4SystemOfUnits.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"

class SpherePart: public G4VPVParameterisation
{
public:
	SpherePart(G4double radius, G4int copyNo, G4double startHeight, G4double endHeight); //constructor
	~SpherePart(); //destructor

	virtual void ComputeDimensions(G4Tubs& disc, const G4int copyNo, const G4VPhysicalVolume* physVol) const;

	virtual void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* PhysVol) const;

private:
	//we include here variables that are independent of copy number
	//but are required to get the dimensions of r
	G4double SphRadius{};
	G4int numReplicas{};
	G4double start{};
	G4double end{};
	G4double thickness{ (abs(start - end)) / numReplicas }; //thickness of each disc; independent of copy number
};
#endif