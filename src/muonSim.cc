#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "DetConstruction.hh"
#include "PhysList.hh"
#include "ParticleGenerator.hh"
#include "UserActionInit.hh"
#include "RunAction.hh"
#include "SensitiveDetector.hh"
#include "ParamSphere.hh"

int main(int argc, char** argv)
{   
    //random seed
    CLHEP::HepRandom::setTheSeed((unsigned)clock());

    //initializing run
    G4RunManager* runManager{ new G4RunManager() };

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysList);
    runManager->SetUserInitialization(new UserActionInit());

    runManager->Initialize();

    //defining UI session
    G4UIExecutive* ui{ nullptr };
    if (argc == 1) //number of command line arguments: 1 for just the file
    {
        ui = new G4UIExecutive(argc,argv);
    }

    //initializing visualization
    G4VisManager* visManager{ new G4VisExecutive };
    visManager->Initialize();
    G4UImanager* UImanager{ G4UImanager::GetUIpointer() };
    

    if (ui)
    {
        //interactive mode
        //visualize volume, trajectories etc. See the macro file for more info.
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }
    else
    {
        //batch mode
        //triggers when we pass more than 1 argument in the command line
        //other arguments can be macros that we want to execute etc
        G4String command{ "/control/execute " };
        G4String filename{ argv[1] };
        UImanager->ApplyCommand(command + filename);
    }

    //memory management
    delete visManager;
    delete runManager;

    return 0;
}