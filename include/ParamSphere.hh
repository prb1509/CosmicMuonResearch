#ifndef PARAMSPHERE_HH
#define PARAMSPHERE_HH

#include "G4VPVParameterisation.hh"
#include "G4PVParameterised.hh"
#include "G4SystemOfUnits.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"

class SphereParametrization : public G4VPVParameterisation
{
public: 
	SphereParametrization(G4double radius, G4int copyNo);//constructor
	~SphereParametrization(); //destructor

	virtual void ComputeDimensions(G4Tubs& disc, const G4int copyNo, const G4VPhysicalVolume* physVol) const;

	virtual void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* PhysVol) const;

private:
	//we include here variables that are independent of copy number
	//but are required to get the dimensions of r
	G4double SphRadius{};
	G4int numReplicas{};
	G4double thickness{ SphRadius / numReplicas }; //thickness of each disc; independent of copy number
};
#endif 
