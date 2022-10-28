#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name) :G4VSensitiveDetector(name) {}; //constructor

SensitiveDetector::~SensitiveDetector() {}; //destructor

G4bool SensitiveDetector::ProcessHits(G4Step* Step, G4TouchableHistory* ROhist) 
{	
	//get the track
	G4Track* track{ Step->GetTrack() };

	track->GetCreatorProcess();

	// From the track you can obtain the pointer to the dynamic particle
	const G4DynamicParticle* dynamicParticle = track->GetDynamicParticle();
	// From the dynamic particle, retrieve the particle definition, charge, and kinetic energy
	G4ParticleDefinition* particle = dynamicParticle->GetDefinition();
	G4double charge{ dynamicParticle->GetCharge() };
	G4double energy{ dynamicParticle->GetKineticEnergy() };

	//uncomment if you want the track to stop immediately after the particle is detected
	//track->SetTrackStatus(fStopAndKill);

	//position related quantities
	G4StepPoint* preStepPoint{ Step->GetPreStepPoint() };
	G4StepPoint* postStepPoint{ Step->GetPostStepPoint() }; 
	G4ThreeVector Pos{ preStepPoint->GetPosition() };

	//detector relared quantities
	//unused in this analysis
	const G4VTouchable* touchable{ Step->GetPreStepPoint()->GetTouchable() };
	G4VPhysicalVolume* physVol{ touchable->GetVolume() };
	G4ThreeVector posDet{ physVol->GetTranslation() };
	G4int copynum{ touchable->GetCopyNumber() };

	//each muon will correspond to an event
	G4int event{ G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID() };

	//trackID is unqiue for every particle in an event. This helps us distinguish
	//between individual particles in an event of a run.
	G4int trackID{ track->GetTrackID() };

	//fill our ntuple with position, energy, trackID etc data
	G4CsvAnalysisManager* manager{ G4CsvAnalysisManager::Instance() };
	manager->FillNtupleIColumn(0, event);
	manager->FillNtupleDColumn(1, Pos[0]);
	manager->FillNtupleDColumn(2, Pos[1]);
	manager->FillNtupleDColumn(3, Pos[2]);
	manager->FillNtupleDColumn(4, charge);
	manager->FillNtupleIColumn(5, trackID);
	manager->FillNtupleDColumn(6, energy);
	manager->FillNtupleSColumn(7, particle->GetParticleName());
	manager->AddNtupleRow(0);

	//just return true for now
	//don't think it does anything currently
	return true;
};