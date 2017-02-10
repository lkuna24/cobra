#ifndef CONCENTRATIONSUM_H
#define CONCENTRATIONSUM_H

#include "AuxKernel.h"
class ConcentrationSum;

template<>
InputParameters validParams<ConcentrationSum>();

class ConcentrationSum : public AuxKernel
{
public:
  ConcentrationSum(const InputParameters & parameters);

  virtual ~ConcentrationSum() {}

protected:
  virtual Real computeValue();

  const VariableValue & _concentrationone;
  const VariableValue & _concentrationtwo;
};

#endif
