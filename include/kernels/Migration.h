#ifndef MIGRATION_H
#define MIGRATION_H

#include "Kernel.h"

class Migration;

template<>
InputParameters validParams<Migration>();

class Migration : public Kernel
{
public:
  Migration(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  const VariableValue & _concentration;
  const unsigned int _concentration_var;
  const Real _diffcoeff;
  const Real _valence;
  const Real _FaradayConst;
  const VariableValue &  _Potential;
  const VariableGradient & _Potential_grad;
  const unsigned int _Potential_var;
  const Real _gasconstR;
  const Real _temp;
};

#endif // Migration_H
