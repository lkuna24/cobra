//Base Classes
#include "CobraApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

//Kernels
#include "Migration.h"
#include "EDiffusion.h"
#include "Electrostatics.h"
#include "NeutralityTwo.h"

//Auxkernels
#include "ConcentrationSum.h"


template<>
InputParameters validParams<CobraApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

CobraApp::CobraApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  //ModulesApp::registerObjects(_factory);
  CobraApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  //ModulesApp::associateSyntax(_syntax, _action_factory);
  CobraApp::associateSyntax(_syntax, _action_factory);
}

CobraApp::~CobraApp()
{
}

// External entry point for dynamic application loading
extern "C" void CobraApp__registerApps() { CobraApp::registerApps(); }
void
CobraApp::registerApps()
{
  registerApp(CobraApp);
}

// External entry point for dynamic object registration
extern "C" void CobraApp__registerObjects(Factory & factory) { CobraApp::registerObjects(factory); }
void
CobraApp::registerObjects(Factory & factory)
{
  registerKernel(Migration);
  registerKernel(EDiffusion);
  registerKernel(Electrostatics);
  registerKernel(NeutralityTwo);
  registerAux(ConcentrationSum);
}

// External entry point for dynamic syntax association
extern "C" void CobraApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { CobraApp::associateSyntax(syntax, action_factory); }
void
CobraApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
