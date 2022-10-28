#include "DetConstruction.hh"
#include "ParamSphere.hh"
#include "SpherePart.hh"

static constexpr G4double pi{ 3.14159265358979323846 };

DetectorConstruction::DetectorConstruction(){} //constructor

DetectorConstruction::~DetectorConstruction(){} //destructor

G4VPhysicalVolume* DetectorConstruction::Construct()
{	
	//get required materials for building volumes
	//for a more comprehensive list of materials in the NIST database
	//see Materials_List.txt
	G4NistManager* manager{ G4NistManager::Instance() };
	G4Material* air{ manager->FindOrBuildMaterial("G4_AIR") };
	G4Material* lead{ manager->FindOrBuildMaterial("G4_Pb") };
	G4Material* stainlessSteel{ manager->FindOrBuildMaterial("G4_STAINLESS-STEEL") };
	G4Material* vacuum{ manager->FindOrBuildMaterial("G4_Galactic") };
	G4Material* gold{ manager->FindOrBuildMaterial("G4_Au") };
	G4Material* glass{ manager->FindOrBuildMaterial("G4_GLASS_PLATE") };

	//construct world volume box
	//shape of box
	G4double world_hx { 5.0 * m };
	G4double world_hy { 5.0 * m };
	G4double world_hz { 5.0 * m };

	//full properties of box: shape, material (and other parameters not used in this case)
	G4Box* worldBox{ new G4Box("World", world_hx, world_hy, world_hz) };
	G4LogicalVolume* worldLog{ new G4LogicalVolume(worldBox, air, "World") };

	//placement and position of box
	G4VPhysicalVolume* worldPhys{ new G4PVPlacement(nullptr, //rotation: none
													G4ThreeVector(0,0,0),//place at origin
													worldLog,//logical volume
													"World",//name
													nullptr,//mother volume:set to null pointer; this object is the mother volume
													false,//no bool operations
													0,//copy number:inserting volume just once
													true//check for overlap of volumes
													) };

	//construct spherical trap volume
	//shape of sphere: radius
	G4double steelRadius { 35 * cm / 2 };
	G4double vacRadius{ 30 * cm / 2 };
	G4double glassThickness{ 4 * mm };

	//first we construct the glass spherical cap like component
	//this is a whole sphere and only the cap like section will not be overwritten by the steel part
	G4Sphere* glassSphere{ new G4Sphere("Glass", 0, steelRadius, 0 * deg, 360 * deg, 0 * deg, 180 * deg) };
	G4LogicalVolume* glassLog{ new G4LogicalVolume(glassSphere, stainlessSteel, "Glass") };

	//place glass volume inside world volume
	G4VPhysicalVolume* glassPhys{ new G4PVPlacement(nullptr, //rotation: none
												G4ThreeVector(0,0,0),//place at origin with respect to mother volume
												glassLog,//logical volume
												"Glass",//name
												worldLog,//mother volume:set to world volume
												false,//no bool operations
												0,//copy number:inserting volume just once
												true//check for overlap of volumes
												) };
	//build steel part of trap
	//we build a spherical section upto where we need the glass cap
	G4Ellipsoid* steelSphere{ new G4Ellipsoid("Steel",steelRadius,steelRadius,steelRadius,-steelRadius + glassThickness,steelRadius - glassThickness) };
	G4LogicalVolume* steelLog{ new G4LogicalVolume(steelSphere, stainlessSteel, "Steel") };

	//place solid trap inside world volume
	G4VPhysicalVolume* steelPhys{ new G4PVPlacement(nullptr, //rotation: none
												G4ThreeVector(0,0,0),//place at origin with respect to mother volume
												steelLog,//logical volume
												"Steel",//name
												glassLog,//mother volume:set to world volume
												false,//no bool operations
												0,//copy number:inserting volume just once
												true//check for overlap of volumes
												) };
	
	//constructing hollow part of trap
	G4Sphere* hollow { new G4Sphere("Hollow", 0, vacRadius, 0, 360 * deg, 0 , 180 * deg)};
	G4LogicalVolume* hollowLog { new G4LogicalVolume(hollow,vacuum,"Hollow") };

	//place hollow trap inside world volume
	G4VPhysicalVolume* hollowPhys{ new G4PVPlacement(nullptr, //rotation: none
											G4ThreeVector(0,0,0),//place at origin with respect to mother volume
											hollowLog,//logical volume
											"Hollow",//name
											steelLog,//mother volume:set to stainless steel volume
											false,//no bool operations
											0,//copy number:inserting volume just once
											true//check for overlap of volumes
											) };

	//now we create the detector volume by parametrization
	//radius of this volume
	G4double detRadius{ vacRadius * 0.99 };
	//first we make a dummy volume which binds to our parametrized volume
	G4Tubs* det{ new G4Tubs("Detector", 0, 1 * cm, 1 * cm,0, 360 * deg) };
	//and create the corresponding logical volume
	G4LogicalVolume* detLog{ new G4LogicalVolume(det,vacuum,"Detector") };
	//now construct the parametrized volume
	G4VPVParameterisation* detParam{ new SphereParametrization(detRadius, 250) };
	G4VPhysicalVolume* detPhys{ new G4PVParameterised("Detector",//name
														detLog,//logical volume
														hollowLog,//mother volume
														kUndefined,//axis of voxelisation. By default we don't pick an axis since 
														//the sphere is symmetric about all 3 axes
														250,//number of copies
														detParam,//parametrization we created
														true//check for overlap of volumes
														) };

	//now we associate a sensitive detector to the vacuum chamber volume
	//this is the area where we want to check electrons passing through
	SensitiveDetector* SD{ new SensitiveDetector("SD") };
	detLog->SetSensitiveDetector(SD);

	//filter out particles of choice
	//detector will only "detect" these particles and others pass right through 
	//without being affected by say a stop and kill command
	G4SDParticleFilter* filter{ new G4SDParticleFilter("particle filter") };
	filter->add("e+");
	filter->add("e-");
	SD->SetFilter(filter);

	return worldPhys;
};

void DetectorConstruction::ConstructSDandField()
{
	SensitiveDetector* SensitiveDet{ new SensitiveDetector("SensitiveDetector") };
	
};