#include "SpherePart.hh"

SpherePart::SpherePart(G4double radius, G4int copyNo, G4double startHeight, G4double endHeight) : 
	SphRadius{ radius }, numReplicas{ copyNo }, start{ startHeight }, end{ endHeight } //constructor
{};

SpherePart::~SpherePart() {}; //destructor

void SpherePart::ComputeDimensions(G4Tubs& disc, const G4int copyNo, const G4VPhysicalVolume* physVol) const 
{
	G4double height{ end + thickness * copyNo };

    //we add a very small number to the radius at the end because our radius cannot be 0 or Geant4 will raise an error at runtime
    G4double radius{ abs(sqrt(-pow(height,2) + pow(SphRadius,2))) + 0.001 * cm };

    //set required values of thin disc
    disc.SetInnerRadius(0);
    disc.SetOuterRadius(radius);
    //we set a slight gap between each disc so as to ensure 
    //that Geant4 will not complain about any overlapping volumes
    disc.SetZHalfLength(0.98 * thickness);
    disc.SetStartPhiAngle(0);
    disc.SetDeltaPhiAngle(360 * deg);
};

void SpherePart::ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* PhysVol) const 
{
    //no rotation
    PhysVol->SetRotation(nullptr);

    //we also need each ring to be centered at a height depending on the copy number
    G4ThreeVector origin{ G4ThreeVector(0, 0, end + thickness * copyNo) };
    PhysVol->SetTranslation(origin);
};