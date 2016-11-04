#ifndef COBRAAPP_H
#define COBRAAPP_H

#include "MooseApp.h"

class CobraApp;

template<>
InputParameters validParams<CobraApp>();

class CobraApp : public MooseApp
{
public:
  CobraApp(InputParameters parameters);
  virtual ~CobraApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* COBRAAPP_H */
