# About
This code simulates the effect of cosmic ray muons on a 
spherical apparatus. Subsequently, the number of daughter 
electrons forming from the showers, and their corresponding
energies are calculated.

---
---

## CODE

### 1. Geometry

The geometry is constructed in the DetectorConstruction class, 
defined in DetConstruction.hh/cc. The geometry consists of a
 world box containing an outer sphere made of stainless steel, 
and an inner sphere of vacuum. Lastly, it includes a
parametrized spherical volume that serves as a sensitive detector.
See Sensitive Detector for more info about this component.
For a list of materials that can be used, see Material_List.txt.

***

### 2. Physics List

Particle types, and physics processes such as decay, absorption etc
are governed by the G4EmStandardPhysics physics list which are all 
defined in the PhysList class in PhysList.hh/cc. 

***

### 3. Particle Source

The particle source is defined in the ParticleGenerator class defined in 
ParticleGenerator.hh/cc. A list of particles can be found in Particle_List.txt.
The default options of this source is a circular beam following a cos^2 
angular distribution, and a power law energy distribution (alpha = 2.5)
within the range of 1-100 GeV. 
These settings can be modified in the macros run_small.mac or run_large.mac
 depending on how many particles you wish to generate.

***

### 4. Sensitive Detector

This is a way to collect the information of electrons and positrons that pass through the 
vacuum chamber. First the detector is parametrized in the 
SphereParametrization class defined in ParamSphere.hh/cc. 
Each parametrized component can then be used to detect and filter certain particles,
in this case electrons and positrons. 

***

### 5. Event Collection

Each muon constitutes an event. So if our source shoots a 100 muons, there will be 
a 100 events in the run. Given detection by the sensitive detector, various bits of information
are stored in an ntuple through the RunAction class defined in RunAction.hh/cc.
The data is then saved in a csv file through the G4CsvAnalysisManager,
although options exist for xml, root files as well. Further analysis can be done in 
MATLAB, R, Python etc by reading in the csv file. 

***

### 6. User Action Initialization

The class UserActionInit instantiates and registers to the Geant4 kernel 
the various user defined action classes, namely ParticleGenerator and RunAction.
The code is written for sequential mode, but can be modified for multi threading
 if necessary.

***
## GUI

The user interface is defined via the G4UIExecutive class in muonSim.cc.
The initialization and commands can be done through a macro file.

---

## VISUALIZATION

The visualization is defined via the G4VisExecutive class in muonSim.cc.
The initialization and commands are doen through the macro file
vis.mac. The macro file init_vis.mac executes this macro and it is itself executed 
in the main() function of muonSim.cc.

---
## DATA ANALYSIS

Data analysis is done purely in Python 3.10. The script MuonSimAnalysis.py 
is responsible for reading in the csv files and subsequent analysis such as 
plotting.
