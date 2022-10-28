#ifndef USERACTIONINIT_HH
#define USERACTIONINIT_HH

#include "ParticleGenerator.hh"
#include "G4VUserActionInitialization.hh"
#include "RunAction.hh"

//class to initiliaze user action classes
class UserActionInit:public G4VUserActionInitialization
{
public:
	UserActionInit();
	~UserActionInit();
	virtual void Build() const;
};
#endif 

