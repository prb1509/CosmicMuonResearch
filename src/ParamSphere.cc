#include "ParamSphere.hh"
#include <cassert>

SphereParametrization::SphereParametrization(G4double radius, G4int copyNo) : SphRadius{ radius }, numReplicas{ copyNo } //constructor
{}; 
SphereParametrization::~SphereParametrization() {}; //destructor

void SphereParametrization::ComputeDimensions(G4Tubs& disc, const G4int copyNo, const G4VPhysicalVolume* physVol) const 
{
	//We want to construct the sphere through "infinitesimally thin" discs which vary in 
	//radius as functions of height. More exactly, r = sqrt(R^2 - h^2), where R is the radius of the sphere.
    //Only constructs full spheres and not sections.

    //height of disc above center
    //depends on copy number as per the relation below
    G4double height{ thickness *  (numReplicas - 2.0 * copyNo) }; 

    assert(height <= SphRadius); //check that the height above center is always less than or equal to the radius of the sphere
    //theoretically should never occur

    //radius of disc; depends on copy number
    //we add a very small number to the radius at the end because our radius cannot be 0 or Geant4 will raise an error at runtime
    G4double radius{ abs(sqrt(-pow(height,2) + pow(SphRadius,2))) + 0.01 * cm}; 

    //set required values of thin disc
    disc.SetInnerRadius(0);
    disc.SetOuterRadius(radius);
    //we set a slight gap between each disc so as to ensure 
    //that Geant4 will not complain about any overlapping volumes
    disc.SetZHalfLength(0.99 * thickness);
    disc.SetStartPhiAngle(0);
    disc.SetDeltaPhiAngle(360 * deg);


};

void SphereParametrization::ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* PhysVol) const
{
    //no rotation
    PhysVol->SetRotation(nullptr);

    //we also need each disc to be centered at a height depending on the copy number
    G4ThreeVector origin{G4ThreeVector(0, 0, thickness * (numReplicas - 2.0 * copyNo ))};
    PhysVol->SetTranslation(origin);
};