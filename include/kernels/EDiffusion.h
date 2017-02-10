#ifndef EDIFFUSION_H
#define EDIFFUSION_H

#include "Kernel.h"

class EDiffusion;

template<>
InputParameters validParams<EDiffusion>();

class EDiffusion : public Kernel
{
public:
  EDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  const VariableValue & _concentration;
  const VariableGradient & _concentration_grad;
  const unsigned int _concentration_var;
  const Real _diffcoeff;
};

#endif // EDiffusion_H
