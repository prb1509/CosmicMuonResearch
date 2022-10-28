#include "RunAction.hh"

RunAction::RunAction() //constructor
{
	//create ntuples
	//filling the ntuples is taken up by a different class
	//if you wanta different file type try G4"filetype"AnalysisManager
	//xml, root are supported
	auto manager{ G4CsvAnalysisManager::Instance() };

	//set file name
	//this is not important here
	//and is overwrriten in the run_small or run_large macros
	manager->SetFileName("Test"); 
	manager->CreateNtuple("Hits", "Hits");

	//we will not want any spaces in our column names because of how our 
	//python script will parse it later on
	manager->CreateNtupleIColumn("Event");
	manager->CreateNtupleDColumn("x_(mm)");
	manager->CreateNtupleDColumn("y_(mm)");
	manager->CreateNtupleDColumn("z_(mm)");
	manager->CreateNtupleDColumn("charge_(e+)");
	manager->CreateNtupleIColumn("trackID");
	manager->CreateNtupleDColumn("Energy_(MeV)");
	manager->CreateNtupleSColumn("ParticleType");
	manager->FinishNtuple(0);
};

RunAction::~RunAction() {}; //destructor

void RunAction::BeginOfRunAction(const G4Run*) 
{
	//create the csv file 
	auto manager { G4CsvAnalysisManager::Instance() };
	manager->OpenFile();
};

void RunAction::EndOfRunAction(const G4Run*) 
{
	//write the data to the csv file and close it
	auto manager{ G4CsvAnalysisManager::Instance() };
	manager->Write();
	manager->CloseFile();
};