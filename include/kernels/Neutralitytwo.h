#ifndef NEUTRALITYTWO_H
#define NEUTRALITYTWO_H

#include "Kernel.h"

class NeutralityTwo;

template<>
InputParameters validParams<NeutralityTwo>();

class NeutralityTwo : public Kernel
{
public:
  NeutralityTwo(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  const VariableValue & _concentrationone;
  const unsigned int _concentrationone_var;
  const Real _valenceone;
  const VariableValue & _concentrationtwo;
  const unsigned int _concentrationtwo_var;
  const Real _valencetwo;
  const Real _FaradayConst;
};

#endif // NEUTRALITYTWO_H
