#include "UserActionInit.hh"
#include "RunAction.hh"

UserActionInit::UserActionInit()  {};

UserActionInit::~UserActionInit() {};

void UserActionInit::Build() const
{
	//instantiate class of G4VUserPrimaryGeneratorAction in Build method
	ParticleGenerator* generator { new ParticleGenerator };
	SetUserAction(generator);

	//instantiate class of G4UserRunAction
	RunAction* runAction { new RunAction };
	SetUserAction(runAction);
};