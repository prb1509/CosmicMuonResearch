#ifndef DETCONSTRUCTION_HH
#define DETCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Sphere.hh"
#include "G4Orb.hh"
#include "G4Cons.hh"
#include "SensitiveDetector.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4Ellipsoid.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction(); //constructor
	~DetectorConstruction(); //destructor

	virtual G4VPhysicalVolume* Construct();

private:
	//sensitive detector
	virtual void ConstructSDandField();
};
#endif